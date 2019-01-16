#ifndef SECONDMILESTONE_FILECACHEMANAGER_H
#define SECONDMILESTONE_FILECACHEMANAGER_H

#include "CacheManager.h"

class FileCacheManager:public CacheManager{
    // In order to lock the shared information(unorded_map)
    pthread_mutex_t mutex;
public:
   /**
    * Constructor - load from the file all the problems and the solutions to the cache.
    */
    FileCacheManager();
    /**
    * The function lineInterpreter - interpreter the line,
    * create the appropriate problem and solution, and store them inside our "cache".
    */
    void lineInterpreter(string line);
    /**
     * Return true if the given problem is inside the cache,
     * And false otherwise.
     */
    bool isProblemExist(string problem) override;
    /**
     * Return the solution to the given problem in O(1) from the cache.
     */
    string getSolution(string problem) override;
    /**
     * Save the problem and the solution inside the cache and the file.
     */
    void saveProblemAndSolution(string problem,string solution) override;
    /**
     * Destructor.
     */
    ~FileCacheManager();
};

#endif
