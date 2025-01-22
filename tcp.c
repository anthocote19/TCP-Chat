#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#define PORT 1024
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

typedef struct {
    SOCKET socket;
    char name[50];
} Client;

Client clients[MAX_CLIENTS];
int client_count = 0;

void broadcast_message(const char *message, SOCKET sender) {
    for (int i = 0; i < client_count; i++) {
        if (clients[i].socket != sender) {
            send(clients[i].socket, message, strlen(message), 0);
        }
    }
}

void remove_client(SOCKET client_socket) {
    for (int i = 0; i < client_count; i++) {
        if (clients[i].socket == client_socket) {
            closesocket(clients[i].socket);
            clients[i] = clients[client_count - 1];
            client_count--;
            break;
        }
    }
}

DWORD WINAPI handle_client(void *arg) {
    SOCKET client_socket = *(SOCKET *)arg;
    char buffer[BUFFER_SIZE];
    char name[50];

    recv(client_socket, name, sizeof(name), 0);
    sprintf(buffer, "%s has joined the chat.\n", name);
    broadcast_message(buffer, client_socket);
    send(client_socket, buffer, strlen(buffer), 0);

    sprintf(buffer, "Connected clients: %d\n", client_count);
    broadcast_message(buffer, client_socket);

    while (1) {
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) break;
        buffer[bytes_received] = '\0';

        char message[BUFFER_SIZE + 50];
        sprintf(message, "%s: %s", name, buffer);
        broadcast_message(message, client_socket);
    }

    sprintf(buffer, "%s has left the chat.\n", name);
    broadcast_message(buffer, client_socket);
    remove_client(client_socket);
    closesocket(client_socket);

    sprintf(buffer, "Connected clients: %d\n", client_count);
    broadcast_message(buffer, INVALID_SOCKET);

    return 0;
}

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_size;

    WSAStartup(MAKEWORD(2, 2), &wsa);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr *)&server, sizeof(server));
    listen(server_socket, MAX_CLIENTS);

    printf("Server started on port %d.\nWelcome to the chat server!\n", PORT);

    while (1) {
        client_size = sizeof(client);
        client_socket = accept(server_socket, (struct sockaddr *)&client, &client_size);

        if (client_count < MAX_CLIENTS) {
            clients[client_count].socket = client_socket;
            recv(client_socket, clients[client_count].name, sizeof(clients[client_count].name), 0);
            client_count++;

            CreateThread(NULL, 0, handle_client, &client_socket, 0, NULL);
        } else {
            const char *message = "Server full.\n";
            send(client_socket, message, strlen(message), 0);
            closesocket(client_socket);
        }
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}
