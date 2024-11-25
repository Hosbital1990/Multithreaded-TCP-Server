#include"client.h"
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

Client::Client(std::string clientName, int port)
: clientName(clientName), client_fd(-1), port(port)
{}

Client::~Client(){

    if (client_fd != -1) 
        close(client_fd);
        }

void Client::run(){

// Create socket
client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    //Bind socket to address
 sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid server address");
        close(client_fd);
        exit(EXIT_FAILURE);
    }


    //try connect to server
        if (connect(client_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Failed to connect to server");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected to server"  << std::endl;

    std::string message = "Hello from client: " + clientName;
    send(client_fd, message.c_str(), message.size(), 0);

    char buffer[1024];
    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        std::cout << "Server response: " << buffer << std::endl;
    }

    close(client_fd);



}


