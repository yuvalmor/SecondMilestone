#ifndef SECONDMILESTONE_MYSOLVER_H
#define SECONDMILESTONE_MYSOLVER_H

#include "Solver.h"
#include "Solution.h"
#include "Searcher.h"

/**
 * MySolver - solve search problems,
 * Has the algorithm as data member, and use it to solve the problem.
 */
class MySolver:public Solver{
    Searcher<vector<int>>* searcher;
public:
    // Constructor
    MySolver( Searcher<vector<int>>* algorithm){
        this->searcher = algorithm;
    }
    // Solve the problem using the method search
    Solution<vector<int>> solve(Searchable<vector<int>>* problem){
        Solution<vector<int>> solution = this->searcher->search(problem);
        return solution;
    }
};

#endif
