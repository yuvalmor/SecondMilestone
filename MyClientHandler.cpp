#define BUFFER_SIZE 1024
#define END_OF_INPUT "end"
#define SEPERATE_LINE "$"
#define SEPRATE_COORDINATE "$$"

#include <strings.h>
#include <unistd.h>
#include <regex>
#include "MySolver.h"
#include "MyClientHandler.h"
#include "MatricesProblem.h"
#include "Solution.h"

/**
 * The function prepareLine- get the buffer information;
 * And set it to line format
 */
string MyClientHandler::prepareLine(char *str, int size) {
    string line;
    for(int i=0;i<size;i++){
        if(str[i]=='\n'){
            return line;
        }
        line+=str[i];
    }
    return str;
}

/**
 * The function matrixLine - get line that represent line in matrix,
 * And turn it to vector that contain the values in the line
 */
vector<double> MyClientHandler::matrixLine(string line) {
    vector<double> matrixLine;
    // The pattern in order to get the numbers only
    regex pattern ("[^,]+");
    smatch match;
    string buffer;
    while (regex_search(line,match,pattern)){
        buffer = match.str(0);
        // Turn the value from string to int and push it to the vector
        matrixLine.push_back(stod(buffer));
        line = match.suffix().str();
    }
    return matrixLine;
}

/**
 * SetProblem - prepare our problem,
 * It gets the initial and the goal coordinates,
 * And turns the problem to its representation as string.
 */
void setProblem(vector<vector<double>>* matrix,vector<int>* initial,vector<int>* goal,string& p){
    // Coordinate in the matrix
    int x,y;
    // Save and pop the vector represent the goal location from the matrix
    vector<double> end = matrix->at(matrix->size()-1);
    matrix->pop_back();
    // Save and pop the vector represent the start location from the matrix
    vector<double> start = matrix->at(matrix->size()-1);
    matrix->pop_back();
    /**
     * Get the coordinate represent the goal location from the vector,
     * and convert it to int
     **/
    y = (int)end.at(end.size()-1);
    end.pop_back();
    x = (int)end.at(end.size()-1);
    end.pop_back();
    goal->push_back(x);
    goal->push_back(y);
    /**
    * Get the coordinate represent the initial location from the vector,
    * and convert it to int
    **/
    y = (int)start.at(start.size()-1);
    start.pop_back();
    x = (int)start.at(start.size()-1);
    start.pop_back();
    initial->push_back(x);
    initial->push_back(y);
    // Adding dollar sign to the initial and the goal description
    p = p.substr(0,p.size()-1);
    int index = p.find_last_of(SEPERATE_LINE);
    string firstCoordinate;
    string secondCoordinate;
    string temp;
    temp = p.substr(0,index);
    secondCoordinate = p.substr(index+1,p.size());
    index = temp.find_last_of(SEPERATE_LINE);
    firstCoordinate = temp.substr(index+1,temp.size());
    temp = temp.substr(0,index);
    // Initial the string
    p = "";
    // Insert the problem in the right format to the string
    p=temp+SEPRATE_COORDINATE+firstCoordinate+SEPRATE_COORDINATE+secondCoordinate;
}

/**
 * handle the client, get search problem and return the answer.
 */
void MyClientHandler::handleClient(int socket) {
    vector<vector<double>> matrix;
    vector<int> goal;
    vector<int> initial;
    string problemString;
    string solutionString;
    // Contains the number of characters read or written
    ssize_t n;
    // The server reads characters from the socket connection into this buffer
    char buffer[BUFFER_SIZE];
    string line;
    do {
        // Initial the buffer to zero
        bzero(buffer,BUFFER_SIZE);
        // read from the socket the client problem
        n = read(socket,buffer,BUFFER_SIZE-1);
        if(n < 0){
            Error("Error reading from socket\n");
        }
        // prepare the line
        line = prepareLine(buffer,sizeof(buffer));
        // as long as its not end line, push it to the matrix
        if (line!=END_OF_INPUT){
            problemString+=line+SEPERATE_LINE;
            matrix.push_back(matrixLine(line));
        }
        // keep reading the from the client as long he didnt insert end
    } while (line != END_OF_INPUT);
    // set the problem
    setProblem(&matrix,&initial,&goal,problemString);
    // checks if the problem exist in the cache, if it does take ot solution
    if(this->cacheManager->isProblemExist(problemString)){
        solutionString = this->cacheManager->getSolution(problemString);
        write(socket,solutionString.c_str(),solutionString.size()+1);
    } else {
        // create the problem as searchable problem
        Searchable<vector<int>>* problem = new MatricesProblem<vector<int>>(matrix,initial,goal);
        // solve the problem using the solver
        Solution<vector<int>> solution = this->solver->solve(problem);
        solutionString = solution.getSolution();
        // save the problem and the solution inside the cache and the file
        this->cacheManager->saveProblemAndSolution(problemString,solutionString);
        write(socket,solutionString.c_str(),solutionString.size()+1);
        // free the problem
        delete(problem);
    }
    // close the socket, the connection with the client ended
    close(socket);
}