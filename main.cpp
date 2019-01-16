#define NO_PARAMETERS_TO_MAIN 2
#define PORT_NUMBER_LOC 1
#include <iostream>
#include "MySerialServer.h"
#include "ClientHandler.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "MySolver.h"
#include "Astar.h"

using namespace server_side;

int main(int argc,char* argv[]) {
    // Checks if we got input to main
    if(argc<NO_PARAMETERS_TO_MAIN){
        cout << "Error - no port provided\n" <<endl;
        exit(1);
    }
    // Save the port number from argv
    int portNumber = atoi(argv[PORT_NUMBER_LOC]);
    // Create the solver with the A* the faster algorithm
    Solver* solver = new MySolver(new Astar<vector<int>>());
    // Create file cache manager
    CacheManager* cacheManager = new FileCacheManager();
    ClientHandler* clientHandler = new MyClientHandler(solver,cacheManager);
    // Create parallel server that handle clients in parallel
    Server* server = new MyParallelServer();
    server->open(portNumber,clientHandler);
    server->stop();
    return 0;
}