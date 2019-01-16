#ifndef SECONDMILESTONE_SOLVER_H
#define SECONDMILESTONE_SOLVER_H

#include "Solution.h"
#include "Searchable.h"

/**
 * Interface solver - responsible to solve given problems
 */
class Solver{
public:
    // Solve the given problem and return its solution
    virtual Solution<vector<int>> solve(Searchable<vector<int>>* problem)=0;
};

#endif
