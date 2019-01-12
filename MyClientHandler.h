#ifndef SECONDMILESTONE_MYCLIENTHANDLER_H
#define SECONDMILESTONE_MYCLIENTHANDLER_H

#include <string>
#include <vector>
#include "ClientHandler.h"
using namespace std;

class MyClientHandler:public ClientHandler{
    vector<vector<double>> matrix;
    vector<double> initial;
    vector<double> end;
public:
    vector<double> matrixLine(string line);
    string splitString(char* str, int size);
    void handleClient(int socket) override;
    void Error(const char* errorMassage){
        perror(errorMassage);
        exit(1);
    }
};

#endif
