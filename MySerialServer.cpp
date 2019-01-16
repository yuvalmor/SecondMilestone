/*#define BUFFER_SIZE 256
#include "MySerialServer.h"
#include <chrono>

void MySerialServer::open(int portNum, ClientHandler* clientHandler) {
    this->toListen=true;
    // The variables store the values returned by the socket and accept system calls
    int sockfd, newsockfd;
    // Store the size of the address of the client
    int clilen;
    struct sockaddr_in serv_addr, cli_addr;
    // The socket system call creates new socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        Error("Error opening socket");
    }
    // Initialize serv_addr to zero
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNum);
    // Binds a socket to an address
    if(bind(sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr))<0){
        Error("Error in binding");
    }
    // until here we opened the server and the sockets!!!!!!!!!!!!
    listen(sockfd,SOMAXCONN);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,(struct sockaddr*)&cli_addr,(socklen_t*)&clilen);
    if(newsockfd < 0){
        close(sockfd);
        Error("Error on accept");
    }
    clientHandler->handleClient(newsockfd);
    timeval timeout;
    fd_set fs;
    FD_ZERO(&fs);
    FD_SET(sockfd,&fs);
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    while (this->toListen && select(sockfd+1,&fs, nullptr, nullptr,&timeout)){
        cout << "im inside the while loop" <<endl;
        newsockfd = accept(sockfd,(struct sockaddr*)&cli_addr,(socklen_t*)&clilen);
        if(newsockfd < 0){
            close(sockfd);
            if(errno == EWOULDBLOCK){
                this->stop();
                Error("Time out!");
            }
            Error("Error on accept");
        }
        clientHandler->handleClient(newsockfd);
        cout << "im done with client handler!!" <<endl;
    }
    close(newsockfd);
}

void MySerialServer::stop() {
    this->toListen = false;
}*/