#define BUFFER_SIZE 1024
#define END_OF_INPUT "end"

#include <iostream>
#include <strings.h>
#include <unistd.h>
#include <regex>
#include "MyClientHandler.h"


string MyClientHandler::splitString(char *str, int size) {
    string line;
    for(int i=0;i<size;i++){
        if(str[i]=='\n'){
            return line;
        }
        line+=str[i];
    }
    return str;
}

vector<double> MyClientHandler::matrixLine(string line) {
    vector<double> matrixLine;
    regex pattern ("[^,]+");
    smatch match;
    string buffer;
    while (regex_search(line,match,pattern)){
        buffer = match.str(0);
        matrixLine.push_back(stod(buffer));
        line = match.suffix().str();
    }
    return matrixLine;
}

void MyClientHandler::handleClient(int socket) {
    cout << "im inside handelClient" << endl;
    // Contains the number of characters read or written
    ssize_t n;
    // The server reads characters from the socket connection into this buffer
    char buffer[BUFFER_SIZE];
    string line;
    do {
        bzero(buffer,BUFFER_SIZE);
        n = read(socket,buffer,BUFFER_SIZE-1);
        if(n < 0){
            this->Error("Error reading from socket");
        }
        line = splitString(buffer,sizeof(buffer));
        if (line!=END_OF_INPUT){
            this->matrix.push_back(matrixLine(line));
        }
        cout << "line = " << line <<endl;
    } while (line != END_OF_INPUT);
    this->end = this->matrix.at(matrix.size()-1);
    this->matrix.pop_back();
    this->initial = this->matrix.at(matrix.size()-1);
    this->matrix.pop_back();
    cout << "done" <<endl;
}