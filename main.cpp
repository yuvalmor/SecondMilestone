#define NO_PARAMETERS_TO_MAIN 2

#include <iostream>
#include "MySerialServer.h"
#include "ClientHandler.h"
#include "MyClientHandler.h"

using namespace server_side;

int main(int argc,char* argv[]) {
    if(argc<NO_PARAMETERS_TO_MAIN){
        cout << "Error - no port provided" <<endl;
        exit(1);
    }
    ClientHandler* clientHandler = new MyClientHandler();
    Server* server = new MySerialServer();
    int portNumber = atoi(argv[1]);
    server->open(portNumber,clientHandler);
    cout<<"end of program"<<endl;
    return 0;
}