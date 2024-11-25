#include "server.h"

Server::Server(int port, int maxConnections, int maxThreads)
    : port(port), maxConnections(maxConnections), threadPool(maxThreads), running(false) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        throw std::runtime_error("Socket creation failed.");
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Bind failed.");
    }

    if (listen(serverSocket, maxConnections) < 0) {
        throw std::runtime_error("Listen failed.");
    }

    epollFd = epoll_create1(0);
    if (epollFd < 0) {
        throw std::runtime_error("Epoll creation failed.");
    }

    epoll_event event{};
    event.events = EPOLLIN;
    event.data.fd = serverSocket;

    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, serverSocket, &event) < 0) {
        throw std::runtime_error("Epoll control failed.");
    }
}

Server::~Server() {
    stop();
}

void Server::start() {
    running.store(true);
    threadPool.start();
                std::cout << "Server started waiting for client!\n" ;
                std::cout << "can use this command in terminal: telnet 127.0.0.1 8080\n";

    while (running) {
        processEvents();
    }
}

void Server::stop() {
    running.store(false);
    close(serverSocket);
    close(epollFd);
    threadPool.stop();
}

void Server::processEvents() {
    const int maxEvents = 10;
    epoll_event events[maxEvents];

    int eventCount = epoll_wait(epollFd, events, maxEvents, -1);
    if (eventCount < 0) {
        throw std::runtime_error("Epoll wait failed.");
    }

    for (int i = 0; i < eventCount; ++i) {
        if (events[i].data.fd == serverSocket) {
            sockaddr_in clientAddr{};
            socklen_t clientLen = sizeof(clientAddr);
            int clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &clientLen);
            if (clientSocket >= 0) {
                epoll_event event{};
                event.events = EPOLLIN;
                event.data.fd = clientSocket;
                epoll_ctl(epollFd, EPOLL_CTL_ADD, clientSocket, &event);
            }
        } else {
            char buffer[1024];
            ssize_t bytesRead = read(events[i].data.fd, buffer, sizeof(buffer) - 1);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0';
                std::cout << "Message From client: "<< buffer << std::endl ;
                int clientSocket = static_cast<int>(events[i].data.fd);
                std::string echoMsg = std::string(buffer);

                threadPool.taskEnqueuer([this,clientSocket,echoMsg ]() {
                    echoMessage(echoMsg, clientSocket );
                });
            } else {
                close(events[i].data.fd);
            }
        }
    }
}

void Server::echoMessage(const std::string &message, int clientSocket) {
    send(clientSocket, message.c_str(), message.size(), 0);
}
