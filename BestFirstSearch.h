
#ifndef SECONDMILESTONE_BESTFIRSTSEARCH_H
#define SECONDMILESTONE_BESTFIRSTSEARCH_H

#include "CommonSearcher.h"

#include <set>

template <class T>
class BestFirstSearch: public CommonSearcher<T> {

private:
    queue<State<T>> closedQueue;

public:

    // ctor
    BestFirstSearch<T>():CommonSearcher<T>(){}

    Solution<T> search(Searchable<T>* s) override {

        // initialize member 'openQueue' (priority Queue) with A
        CommonSearcher<T>::addToOpenQueue(s->getInitialState());

        // initialize solution
        Solution<T> sol;

        // loop over openQueue states
        while (CommonSearcher<T>::openQueueSize() > 0) {

            // get the best state from the queue to 'n' (and remove from open)
            State<T>* n = new State<T>(CommonSearcher<T>::popOpenQueue());

            // add the n state to the set
            //CommonSearcher<T>::addStateToSet(n);
            this->closedQueue.push(*n);

            // check if the current state is the goal.
            // if yes return path (or path cost)
            if (n->Equals(s->isStateGoal(*n))) {
                sol.setSolution(getSolution(s));
                return sol;
            }

            // get the neighbors of 'n'
            set<State<T>> neighbors = s->getAllPossibleStates(*n);

            // loop over 'n'/s neighbors
            for (auto cState : neighbors) {

                // check if 'currentState' is in openQueue or closedSet
                bool isStateInOpen = CommonSearcher<T>::isStateInOpenQueue(cState);
                bool isStateInClosed = isStateInClosedQueue(cState);

                if (!isStateInClosed && !isStateInOpen) {

                    // update that you came to currentState from 'n'
                    // and update the cost, then add currentState to
                    // to the openQueue

                    cState.setCameFrom(n);
                    cState.setCost(cState.getPathCost());

                    CommonSearcher<T>::addToOpenQueue(cState);

                    // move on to next neighbor
                    continue;
                }

                cState.setCameFrom(n);
                cState.setCost(cState.getPathCost());

                if (CommonSearcher<T>::isNewPathShorter(cState)) {
                    CommonSearcher<T>::updateOpenQueue(cState);
                }

            }
        }
        return sol;
    }

    bool isStateInClosedQueue(State<T> s) {
        queue<State<T>> temp = this->closedQueue;
        while (!temp.empty()) {
            if (s.Equals(temp.front())) {
                return true;
            }
            else {
                temp.pop();
            }
        }
        return false;
    }

    stack<State<T>> getSolutionStack(Searchable<T>* a) {

        stack<State<T>> aidStack;
        while (!this->closedQueue.empty()) {
            aidStack.push(this->closedQueue.front());
            this->closedQueue.pop();
        }

        stack<State<T>> secondStack;
        State<T> goal = aidStack.top();
        aidStack.pop();
        secondStack.push(goal);

        while (!aidStack.empty()) {
            State<T> s = aidStack.top();
            if (goal.getCameFrom()->Equals(s)) {
                secondStack.push(s);
                goal = s;
            }
            aidStack.pop();
        }

        return secondStack;

    }

    string getSolution(Searchable<T>* a) {

        if (this->closedQueue.empty()) {
            return "";
        }

        string solution = "{";

        stack<State<T>> solutionStack = getSolutionStack(a);

        while (!solutionStack.empty()) {
            State<T> s = solutionStack.top();
            solutionStack.pop();

            if (!solutionStack.empty()) {
                State<T> n = solutionStack.top();
                if (n.getState()[0] > s.getState()[0] ) {
                    solution += "Down, ";
                    continue;
                }
                if (n.getState()[0] < s.getState()[0] ) {
                    solution += "Up, ";
                    continue;
                }
                if (n.getState()[0] == s.getState()[0] ) {
                    if (n.getState()[1] > s.getState()[1]) {
                        solution += "Right, ";
                        continue;
                    }
                    solution += "Left, ";
                }
            }
        }

        solution = solution.substr(0, solution.size()-2);
        solution+= "}";

        return solution;
    }

};


#endif //SECONDMILESTONE_BESTFIRSTSEARCH_H
