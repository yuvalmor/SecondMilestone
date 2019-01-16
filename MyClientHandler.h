#ifndef SECONDMILESTONE_MYCLIENTHANDLER_H
#define SECONDMILESTONE_MYCLIENTHANDLER_H

#include <string>
#include <vector>
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
using namespace std;

class MyClientHandler:public ClientHandler{
    // Solve the problems that the client give
    Solver* solver;
    // Save the solutions to all of the problems
    CacheManager* cacheManager;
public:
    // Constructor
    MyClientHandler(Solver* solver,CacheManager* cacheManager){
        this->solver= solver;
        this->cacheManager= cacheManager;
    };
    /**
     * The function matrixLine - get line that represent line in matrix,
     * And turn it to vector that contain the values in the line
     */
    vector<double> matrixLine(string line);
    // assistent function, prepare the line
    string prepareLine(char* str, int size);
    // handle the client, get search problem and return the answer.
    void handleClient(int socket) override;
    // The function update the client about the errors that appeared
    void Error(const char* errorMassage){
        perror(errorMassage);
        exit(1);
    }
};

#endif
