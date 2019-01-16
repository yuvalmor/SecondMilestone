#ifndef SECONDMILESTONE_CACHEMANAGER_H
#define SECONDMILESTONE_CACHEMANAGER_H

#include "Searchable.h"
#include "Solution.h"
#include <unordered_map>

/**
 * CacheManager- holds problem and solution that we already calculate.
 */
class CacheManager{
protected:
    // Holds all the problems and theirs solution that we already solved
    unordered_map<string,string> cache;
public:
    // Return true if the given problem exist in the "cache", and false otherwise
    virtual bool isProblemExist(string problem)=0;
    // Return the solution for the given problem;
    virtual string getSolution(string problem)=0;
    // Save the problem and the solution in some data base
    virtual void saveProblemAndSolution(string problem,string solution)=0;
};

#endif
