/*#include <pthread.h>
#include "GeneralServer.h"

void Error(const char* errorMassage){
    perror(errorMassage);
    exit(1);
}

void GeneralServer::open(int portNum, ClientHandler *clientHandler) {
    this->toListen = true;
    serverData* serverDat = new serverData(portNum,clientHandler,&this->toListen);
    pthread_t serverThread;
    pthread_create(&serverThread,nullptr,openServerThread,serverDat);
}

void GeneralServer::stop() {
    this->toListen= false;
}

void* GeneralServer::openServerThread(void *param) {
    serverData* serverDat = (serverData*)param;
    // The variables store the values returned by the socket and accept system calls
    int sockfd, newsockfd;
    // Store the size of the address of the client
    int clilen;
    struct sockaddr_in serv_addr, cli_addr;
    // The socket system call creates new socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        perror("Error opening socket\n");
        exit(1);
    }
    // Initialize serv_addr to zero
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(serverDat->portNun);
    // Binds a socket to an address
    if(bind(sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr))<0){
        perror("Error in binding\n");
        exit(1);
    }
    
}*/