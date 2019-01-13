
#ifndef SECONDMILESTONE_COMMONSEARCHER_H
#define SECONDMILESTONE_COMMONSEARCHER_H

#include <queue>
#include <stack>
#include "Searcher.h"

using namespace std;

template <class T>
class CommonSearcher : public Searcher<T> {

private:

    int evaluatedNodes;
    priority_queue<State<T>> openQueue;

public:

    // ctor
    CommonSearcher() {
        this->evaluatedNodes=0;
    };

    bool isStateInOpenQueue(State<T> s) {

        priority_queue<State<T>> temp;

        temp = openQueue;

        while (!temp.empty()) {
            if (s.Equals(temp.top())) {
                return true;
            } else{
                temp.pop();
            }
        }
        return false;
    }

    void addToOpenQueue(State<T> s) {
        this->openQueue.push(s);
    }

    bool isNewPathShorter(State<T> s) {

        priority_queue<State<T>> temp = this->openQueue;

        while (!temp.empty()) {
            State<T>* olderState = new State<T>(temp.top());
            if (olderState->Equals(s)) {
                return olderState->getCost() > s.getCost();
            } else {
                temp.pop();
            }
        }

        return false;
    }

    void updateOpenQueue(State<T> s) {

        priority_queue<State<T>> temp;
        while (!this->openQueue.empty()) {
            State<T> top = this->openQueue.top();
            if (top.Equals(s)) {
                this->openQueue.pop();
            } else {
                temp.push(top);
                this->openQueue.pop();
            }
        }
        temp.push(s);
        this->openQueue = temp;
    }

    State<T> popOpenQueue() {

        // increase the path visited nodes
        this->evaluatedNodes++;

        // get that top priority state from the queue
        State<T> s = this->openQueue.top();

        // remove the best state from the queue
        this->openQueue.pop();

        return s;
    }

    int openQueueSize() {
        return (int)this->openQueue.size();
    };

    // Searcher functions

    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }


    virtual Solution<T> search(Searchable<T>* s)=0;

    stack<State<T>> getSolutionStack(Searchable<T>* a,
            queue<State<T>> closedQueue) {

        stack<State<T>> aidStack;
        while (!closedQueue.empty()) {
            aidStack.push(closedQueue.front());
            closedQueue.pop();
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

    string getSolution(Searchable<T>* a, queue<State<T>> closedQueue) {

        if (closedQueue.empty()) {
            return "";
        }

        string solution = "{";

        stack<State<T>> solutionStack = getSolutionStack(a, closedQueue);

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

#endif //SECONDMILESTONE_COMMONSEARCHER_H
