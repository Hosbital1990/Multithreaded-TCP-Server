# Multithreaded TCP Server and Client

This project implements a **multithreaded TCP server and client** application in C++ using modern C++20 features. It supports concurrent connections and efficient communication using `epoll` and a thread pool.

---

## Features

- **Multithreaded TCP Server**: Handles multiple clients simultaneously using modern threading techniques.
- **Custom Thread Pool**: Distributes tasks efficiently across available threads.
- **Modern C++20**: Leverages the latest C++ features for clean and concise code.
- **Robust Error Handling**: Gracefully handles socket, threading, and system errors.
- **Telnet Support**: Allows testing with the `telnet` utility or the included client.

---

## Requirements

- **Compiler**: GCC 13 or higher (C++20 support required).
- **Build System**: `make` utility.
- **Libraries**:
  - POSIX sockets (standard on Linux).
  - Standard C++ Library.

---

## Directory Structure

project_root/ ├── include/ # Header files ├── src/ # Source files ├── object/ # Compiled object files (auto-generated) ├── main.cpp # Entry point of the application ├── Makefile # Build system configuration └── README.md # Project documentation

yaml
Copy code

---

## How to Build

### Steps to Build:

1. Clone the repository:

   ```bash
   git clone <repository-url>
   cd <repository-directory>
Compile the project:

bash
Copy code
make
The binary (main) will be generated in the root directory.
Compiled object files will be placed in the object/ directory.
To clean up the build:

bash
Copy code
make clean
Removes all .o files from object/ and the main binary.
How to Run
Running the Server:
Start the server:

bash
Copy code
./main
You will see this message:

text
Copy code
Server started, waiting for clients!
You can use this command in terminal: telnet 127.0.0.1 8080
The server listens for client connections and echoes received messages.

Connecting to the Server:
Option 1: Using the Built-in Client
The project includes a client. You can run it using:

bash
Copy code
./main
The client connects to the server and exchanges messages automatically.

Option 2: Using Telnet
Use the telnet utility to connect to the server:

bash
Copy code
telnet 127.0.0.1 8080
Replace 8080 with the configured port if different.

Once connected, type a message, and the server will echo it back.

Example:

text
Copy code
telnet 127.0.0.1 8080
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
Hello, Server!
Hello, Server!
Configuration
You can modify the following parameters in main.cpp to suit your requirements:

PORT: Default port number (e.g., 8080).
MAX_CONNECTION: Maximum allowed client connections (e.g., 10).
MAX_THREAD: Number of threads in the thread pool (e.g., 4).
Example Output
Server Output:
text
Copy code
Server started, waiting for clients!
You can use this command in terminal: telnet 127.0.0.1 8080
Message from client: Hello, Server!
Client Output:
text
Copy code
Connected to the server at 127.0.0.1:8080
Sent: Hello, Server!
Received: Hello, Server!
Troubleshooting
Common Issues:
Port Already in Use:

Change the port number in main.cpp to an available port.
Check which process is using the port:
bash
Copy code
sudo lsof -i -P -n | grep LISTEN
Telnet Not Installed:

Install Telnet using:
bash
Copy code
sudo apt-get install telnet
Permission Denied for Binary:

Ensure execution permissions:
bash
Copy code
chmod +x main
Make Command Not Found:

Install make using:
bash
Copy code
sudo apt-get install build-essential
How the Server Works
The server starts and listens on the specified port.
Clients can connect using the built-in client or Telnet.
Messages sent by the client are echoed back by the server.
The server handles multiple connections using epoll and threads from the thread pool.