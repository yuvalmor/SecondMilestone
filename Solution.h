
#ifndef SECONDMILESTONE_SOLUTION_H
#define SECONDMILESTONE_SOLUTION_H


#include <list>
#include <queue>
#include <string>

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

    string getSolution() const {
        return this->solution;
    }

    void setSolution(const string& solution) {
        this->solution = solution;
    }
};


#endif //SECONDMILESTONE_SOLUTION_H
