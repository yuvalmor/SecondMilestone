#define BUFFER_SIZE 256
#include "MySerialServer.h"

void Error(const char* errorMassage){
    perror(errorMassage);
    exit(1);
}

void MySerialServer::open(int portNum) {
    // The variables store the values returned by the socket and accept system calls
    int sockfd, newsockfd;
    /*
    // Store the port number on which the server accepts connections
    int pronto;*/
    // Store the size of the address of the client
    int clilen;
    // Contains the number of characters read or written
    int n;
    // The server reads characters from the socket connection into this buffer
    char buffer[BUFFER_SIZE];
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
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,(struct sockaddr*)&cli_addr,(socklen_t*)&clilen);
    if(newsockfd<0){
        Error("Error on accept");
    }
    bzero(buffer,BUFFER_SIZE);
    n=read(newsockfd,buffer, sizeof(buffer)-1);
    if(n<0){
        Error("Error reading from socket");
    }
    printf("massage %s\n",buffer);
}

void MySerialServer::stop() {
    cout << "stop the program" <<endl;
}