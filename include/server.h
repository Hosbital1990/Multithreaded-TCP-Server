#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <cstring>
#include "ThreadPool.h"
//#include "message_queue.h"

class Server {
public:
    Server(int port, int maxConnections, int maxThreads);
    ~Server();

    void start();
    void stop();

private:
    void handleClient(int clientSocket);
    void processEvents();
    void echoMessage(const std::string &message, int clientSocket);

    int serverSocket;
    int epollFd;
    int port;
    int maxConnections;
    ThreadPool threadPool;
    //MessageQueue<std::pair<int, std::string>> messageQueue;

    std::atomic<bool> running;
};

#endif // SERVER_H
