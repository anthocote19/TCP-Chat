# TCP Server and Client Application

## Overview
This project implements a **TCP Server** and **TCP Client** in Python with the following features:
 
### TCP Server Features:
- Displays a **welcome message** on the server side when started.
- Has a buffer size of **1024 characters** for communication.
- Listens on port **1024** and supports cross-platform usage.
- Manages multiple clients simultaneously using threading.
- Accepts **user-defined names** for connected clients.
- Broadcasts messages to all clients, including:
  - New connections.
  - Disconnections.
  - Messages sent by clients.
- Displays the number of connected members on both the server and clients when members join or leave.

### TCP Client Features:
- Allows users to:
  - Connect to the server using the **hostname/IP address**.
  - Enter and send messages to other connected clients.
- Displays:
  - A **confirmation** message when a message is sent.
  - Messages from other members in real time.
  - The number of connected members when updated.
- Uses port **1024** and is cross-platform.

---

## File Structure
- `server.py`: Contains the implementation of the TCP server.
- `client.py`: Contains the implementation of the TCP client.

---

## How to Run the Application

### Prerequisites
- Python 3.x installed on your system.
- Ensure that the required port (1024) is not blocked by a firewall.

### Steps to Run
1. **Start the Server**:
   - Open a terminal and navigate to the directory containing the files.
   - Run the command:
     ```bash
     python server.py
     ```
   - The server will display a welcome message and wait for client connections.

2. **Start the Clients**:
   - Open additional terminals for each client.
   - Run the command:
     ```bash
     python client.py
     ```
   - Enter the server's hostname/IP when prompted.
   - Enter your name when prompted to join the chat.

3. **Communicate**:
   - Clients can now send messages, which will be displayed on:
     - The server.
     - All other connected clients.
   - Connection and disconnection notifications are broadcasted to all members.

---

## Features in Action

### Server Side:
- Displays:
  - A welcome message when started.
  - Notifications for new connections and disconnections.
  - The total number of connected members.

### Client Side:
- Prompts:
  - To enter the server's hostname/IP.
  - To provide a username.
- Displays:
  - A confirmation message when a message is sent.
  - Messages from other connected members.
  - Updates when members join or leave.

---

## Example
### Server Output:



### Client Output:


---

## Notes
- The application uses the `socket` library for network communication.
- Threading ensures the server can handle multiple clients simultaneously.
- The project is compatible with Windows, macOS, and Linux.

---

## Future Improvements
- Add encryption for secure communication.
- Implement a GUI for better usability.
- Include a logging system for server activities.
- Add timeout for inactive clients.

---

## License
This project is licensed under the MIT License.

