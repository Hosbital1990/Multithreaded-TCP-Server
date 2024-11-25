#include "ThreadPool.h"
#include <iostream>
#include <chrono>
#include "server.h"
#include "client.h"

#define PORT 8080
#define MAX_CONNECTION 100
#define MAX_THREAD 4
#define MAX_CLIENT 20


int main() {

    try {


        Server server(PORT, MAX_CONNECTION, MAX_THREAD);

        std::jthread serverThread(&Server::start, &server);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        Client client("AmiNIC", PORT);
        std::jthread clientThread(&Client::run, &client);

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    std::cout << "Execution Normally Ends." << std::endl;


    return 0;
}
