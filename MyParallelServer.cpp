#define TIMEOUT_SEC 1
#define TIMEOUT_MIL_SEC 0

#include "MyParallelServer.h"

/**
 * Thread that call the function client handler in order to handle clients in parallel
 */
void* MyParallelServer::clientHandlerThread(void *param) {
    clientData* clientDat;
    clientDat = (clientData*)param;
    clientDat->clientHandler->handleClient(clientDat->sockfd);
}

/**
 * Thread that open the server, and connect to clients.
 * The first connection is unlimited in time and afterwards limit in one second
 */
void* MyParallelServer::openServerThread(void *param) {
    bool firstClient = true;
    vector<pthread_t> threads;
    vector<clientData*> clients;
    serverData* serverDat;
    serverDat = (serverData*)param;
    // The variables store the values returned by the socket and accept system calls
    int sockfd, newsockfd;
    // Store the size of the address of the client
    int clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket\n");
        exit(1);
    }
    // Initialize serv_addr to zero
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // INADDR_ANY contains the IP address of the host
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // Convert the port number to a port number in network byte order
    serv_addr.sin_port = htons(serverDat->portNum);
    // Binds a socket to an address
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error in binding\n");
        exit(1);
    }
    // Listen to the maximum clients possible
    listen(sockfd,SOMAXCONN);
    clilen = sizeof(cli_addr);
    /**
     * Set the timeout
     */
    struct timeval timeout;
    fd_set fdS;
    FD_ZERO(&fdS);
    FD_SET(sockfd,&fdS);
    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = TIMEOUT_MIL_SEC;
    while(firstClient||(*serverDat->toListen && select(sockfd+1,&fdS,nullptr,nullptr,&timeout))){
        firstClient=false;
        // set the timeout
        FD_ZERO(&fdS);
        FD_SET(sockfd,&fdS);
        timeout.tv_sec = TIMEOUT_SEC;
        timeout.tv_usec = TIMEOUT_MIL_SEC;
        // accept the client
        newsockfd = accept(sockfd,(struct sockaddr*)&cli_addr,(socklen_t *)&clilen);
        if (newsockfd < 0){
            perror("Error on accept\n");
            exit(1);
        }
        // creat the information needed in struct for the handleCLientThread
        clientData* clientDat;
        clientDat = new clientData();
        clientDat->sockfd = newsockfd;
        clientDat->clientHandler = serverDat->clientHandler;
        pthread_t clientThread;
        // Creating the pthread that will handle the client
        pthread_create(&clientThread, nullptr,clientHandlerThread,clientDat);
        // push the thread into the vector
        threads.push_back(clientThread);
        // push the client data to the vector
        clients.push_back(clientDat);
    }
    // join all the open threads
    for (int i=0; i<threads.size();i++){
       pthread_join(threads[i],nullptr);
    }
    // free the clients data
    for(auto c:clients){
        delete (c);
    }
    delete(serverDat);
    // close the main socket
    close(sockfd);
    return nullptr;
}

void MyParallelServer::open(int portNum, ClientHandler *clientHandler) {
    this->toListen = true;
    // prepare all the information needed to the openServerThread in struct
    serverData* serverDat = new serverData();
    serverDat->portNum=portNum;
    serverDat->clientHandler=clientHandler;
    serverDat->toListen=&this->toListen;
    pthread_t serverThread;
    // create the thread
    pthread_create(&serverThread,nullptr,openServerThread,serverDat);
    // push the thread to the vector
    this->threads.push_back(serverThread);
    // join all the open threads
    for(int i=0;i<(this->threads.size());i++){
        pthread_join(this->threads[i],nullptr);
    }
}

void MyParallelServer::stop(){
    this->toListen = false;
}