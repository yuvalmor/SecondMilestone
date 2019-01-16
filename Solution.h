
#ifndef SECONDMILESTONE_SOLUTION_H
#define SECONDMILESTONE_SOLUTION_H

#include <string>
#include <list>
#include <queue>

#include "State.h"

using namespace std;

template <class T>
class CommonSearcher;
template <class T>
class Solution {

private:
    string solution;
public:

    Solution() {
        this->solution = "";
    }

    string getSolution() {
        if (this->solution.size() == 0) {
            this->solution = "no path from initial to goal";
        }
        return this->solution;
    }

    void setSolution(const string& solution) {
        this->solution = solution;
    }
};

#endif
