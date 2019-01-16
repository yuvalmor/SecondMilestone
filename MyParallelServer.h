#ifndef SECONDMILESTONE_MYPARALLELSERVER_H
#define SECONDMILESTONE_MYPARALLELSERVER_H
#include "ServerSide.h"
#include <thread>
#include <vector>

using namespace server_side;
using namespace std;

class MyParallelServer:public Server{
    vector<pthread_t> threads;
    bool toListen;
    static void* openServerThread(void* param);
    static void* clientHandlerThread(void* param);
public:
    void open(int port,ClientHandler* clientHandler) override;
    void stop()override;
};

// save the information necassery to the openServerThread
struct serverData{
    int portNum;
    ClientHandler* clientHandler;
    bool* toListen;
};

// save the information necassery to the clientHandlerThread
struct clientData{
    int sockfd;
    ClientHandler* clientHandler;
};

#endif
