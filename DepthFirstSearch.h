
#ifndef SECONDMILESTONE_DEPTHFIRSTSEARCH_H
#define SECONDMILESTONE_DEPTHFIRSTSEARCH_H

#include <map>
#include "CommonSearcher.h"
#include "stack"
#include "map"

template <class T>
class DepthFirstSearch: public CommonSearcher<T> {

private:

<<<<<<< HEAD
=======
    // members
>>>>>>> origin/master
    stack<State<T>> theStack;
    stack<State<T>> pathStack;
    map<T, bool> visited;

public:

<<<<<<< HEAD
    // ctor
    DepthFirstSearch<T>():CommonSearcher<T>(){}

    // function operation - setting all the cell of the visited
    // nodes to false
    void setNodesToVisited(Searchable<T>* s) {

        vector<vector<State<T>>> structure = s->returnStructure();

=======
    // function sets all the cells of the visited
    // nodes map to false, uses the structure of the problem
    void setNodesToVisited(Searchable<T>* s) {

        vector<vector<State<T>>> structure = s->returnStructure();
>>>>>>> origin/master
        for(int i=0; i<structure.size(); i++) {
            vector<State<T>> row = structure[i];
            for( int j=0; j<row.size(); j++) {
                State<T> pos = row[j];
                visited[pos.getState()] = false;
            }
        }
    }

    // searching for some path from initial to goal node
    Solution<T> search(Searchable<T>* s) {

<<<<<<< HEAD
        Solution<T> sol;

=======
        // list of memory allocated
        list<State<T>*> memoryHandle;

        Solution<T> sol;

        // set nodes to false
>>>>>>> origin/master
        setNodesToVisited(s);

        // push the initial node to the stack
        State<T> initial = s->getInitialState();
        this->theStack.push(initial);

        // loop over the nodes of the stack
        while (!theStack.empty()) {

            // get the top of the stack to n
            State<T>* n = new State<T>(theStack.top());
<<<<<<< HEAD
=======
            memoryHandle.push_back(n);

            // by 1
>>>>>>> origin/master
            CommonSearcher<T>::increaseEvaluatedNodes();

            // check if we have come to goal node and return solution
            if (n->Equals(s->isStateGoal(*n))) {

<<<<<<< HEAD
                CommonSearcher<T>::setChosenPathWeight(n->getCost());
                this->pathStack.push(*n);
                sol.setSolution(getSolution());
=======
                // create the solution path as string
                this->pathStack.push(*n);
                sol.setSolution(getSolution());
                string solutionString = sol.getSolution();

                // set the solution weight
                if (solutionString.empty()) {
                    CommonSearcher<T>::setChosenPathWeight(-1);
                } else {
                    CommonSearcher<T>::setChosenPathWeight(n->getCost());
                }

                // free memory and structures
                CommonSearcher<T>::freeMemory(memoryHandle);
                freeStacks();
>>>>>>> origin/master
                return sol;
            }

            // push 'n' to the path stack and pop it from the working stack
            this->pathStack.push(*n);
            this->theStack.pop();

            // if n is not visited
            if (!visited[n->getState()]) {

                // set n to visited
                visited[n->getState()] = true;

                // get 'n' neighbors
                multiset<State<T>> neighbors = s->getAllPossibleStates(*n);

                // loop over 'n'/s neighbors
                for (auto neighbor : neighbors) {

                    // set that we have come to neighbor from n
                    neighbor.setCameFrom(n);
                    // set path cost (not needed for path finding)
                    neighbor.setCost(neighbor.getPathCost());

                    // if neighbor is not visited push it to the stack
                    if (!visited[neighbor.getState()]) {
                        this->theStack.push(neighbor);
                    }
                }
            }

        }
<<<<<<< HEAD
=======

        CommonSearcher<T>::freeMemory(memoryHandle);
        freeStacks();
        return sol;
    }

    /*
     * function omits all the elements from the stacks
     * and map (at the end of the run)
     */
    void freeStacks() {
        this->visited.clear();
        while(!theStack.empty()) {
            theStack.pop();
        }
        while (!pathStack.empty()) {
            pathStack.pop();
        }
>>>>>>> origin/master
    }

    // function operation - create the back track from goal
    // to initial based on the pathStack
    string getSolution() {

        // for the empty stack there is no path
<<<<<<< HEAD
        if (this->theStack.empty()) {
            return "no path from initial to goal";
=======
        if (this->pathStack.empty()) {
            return "";
>>>>>>> origin/master
        }

        // pushing the goal to the solution stack
        State<T> goal = this->pathStack.top();
        this->pathStack.pop();
        stack<State<T>> solutionStack;
        solutionStack.push(goal);

        // looping over the path stack
        while (!this->pathStack.empty()) {
            State<T> s = this->pathStack.top();
            // omit nodes that do not create a path
            if (goal.getCameFrom()->Equals(s)) {
                solutionStack.push(s);
                goal = s;
            }
            this->pathStack.pop();
        }

        // set directions.
        return CommonSearcher<T>::calculateBackTrace(solutionStack);
    }


<<<<<<< HEAD
};


#endif
=======

};


#endif //SECONDMILESTONE_DEPTHFIRSTSEARCH_H
>>>>>>> origin/master
