#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>


class Client{
public:

    Client(std::string clientName, int port);
    ~Client();

void run();

private:
int client_fd ;
int port ;
std::string clientName ;

};



#endif // End CLIENT_H