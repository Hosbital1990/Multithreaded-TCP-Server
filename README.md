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
- **Execution** Executable with Makefile in terminal and also with VScode - code writen with Ubuntu24
- **Compiler**: GCC 13 or higher (C++20 support required).
- **Build System**: `make` utility.
- **Libraries**:
  - POSIX sockets (standard on Linux).
  - Standard C++ Library.

---

## Directory Structure

project_root/ ├── include/ # Header files ├── src/ # Source files ├── object/ # Compiled object files (auto-generated) ├── main.cpp # Entry point of the application ├── Makefile # Build system configuration └── README.md # Project documentation


---


### Configuration
You can modify the following parameters in main.cpp to suit your requirements:

PORT: Default port number (e.g., 8080).
MAX_CONNECTION: Maximum allowed client connections (e.g., 10).
MAX_THREAD: Number of threads in the thread pool (e.g., 4).

### Using Telnet
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

### Running the Server:
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
