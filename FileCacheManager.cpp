#define FILE_NAME "dataBase.txt"
#define SEPARATOR_FORM "$$$"
#define SEPARATOR_SIZE 3

#include "FileCacheManager.h"
#include "fstream"
#include <string>

/**
 * The function lineInterpreter - interpreter the line,
 * create the appropriate problem and solution, and store them inside our "cache".
 */
void FileCacheManager::lineInterpreter(string line) {
    string problem;
    string solution;
    string separator = SEPARATOR_FORM;
    // Search the separator sign between the problem and the solution
    size_t found = line.find(separator);
    if(found!= string::npos){
        // Separate them
        problem = line.substr(0,found);
        solution = line.substr(found+SEPARATOR_SIZE, line.size()-1);
        // Store them inside the "cache"
        this->cache.insert({problem,solution});
    }
}

/**
 * Constructor - load from the file all the problems and the solutions to the cache
 */
FileCacheManager::FileCacheManager() {
    ifstream file;
    string line;
    file.open(FILE_NAME);
    if(!file.is_open()){
        return;
    }
    file>>line;
    while(!file.eof()){
        lineInterpreter(line);
        file>>line;
    }
    file.close();
}

/**
 * Return true if the given problem is inside the cache,
 * And false otherwise.
 */
bool FileCacheManager::isProblemExist(string problem) {
    pthread_mutex_lock(&this->mutex);
    bool isExist = (bool)this->cache.count(problem);
    pthread_mutex_unlock(&this->mutex);
    return isExist;
}

/**
 * Return the solution to the given problem in O(1) from the cache.
 */
string FileCacheManager::getSolution(string problem) {
    pthread_mutex_lock(&this->mutex);
    string solution = cache[problem];
    pthread_mutex_unlock(&this->mutex);
    return solution;
}

/**
 * Save the problem and the solution inside the cache and the file
 */
void FileCacheManager::saveProblemAndSolution(string problem, string solution) {
    pthread_mutex_lock(&this->mutex);
    // Save the problem with its solution inside the "cache" data member
    this->cache.insert({problem,solution});
    /**
     * Save the problem and the solution in the appropriate format inside the file
     */
    string line;
    ofstream file;
    // Open the file for write
    file.open(FILE_NAME,ios::app);
    if(!file.is_open()){
        perror("Problems in file opening\n");
        exit(1);
    }
    // Insert the problem and the solution to the file format
    line=problem+SEPARATOR_FORM+solution+"\n";
    // Insert the problem and the sulution to the file
    file<<line;
    // Close the file
    file.close();
    pthread_mutex_unlock(&this->mutex);
}

// Destructor
FileCacheManager::~FileCacheManager() {
    // Destroy the mutex
    pthread_mutex_destroy(&this->mutex);
}