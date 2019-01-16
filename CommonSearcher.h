
#ifndef SECONDMILESTONE_COMMONSEARCHER_H
#define SECONDMILESTONE_COMMONSEARCHER_H

#include <queue>
#include <stack>
#include <list>
#include "Searcher.h"

#define DOWN "Down,"
#define UP "Up,"
#define LEFT "Left,"
#define RIGHT "right,"



using namespace std;

template <class T>
class CommonSearcher : public Searcher<T> {

protected:

    // members
    double chosenPathWeight;
    int evaluatedNodes;
    priority_queue<State<T>> openQueue;
    queue<State<T>> openRegularQueue;

public:

    // ctor
    CommonSearcher() {
        this->evaluatedNodes=0;
    };

    // search implemented in specific searchers
    virtual Solution<T> search(Searchable<T>* s)=0;

    // getters and setters
    double getChosenPathCost() const {
        return this->chosenPathWeight;
    }

    void setChosenPathWeight(double weight) {
        this->chosenPathWeight = weight;
    }

    void increaseEvaluatedNodes() {
        this->evaluatedNodes++;
    }

    void addToOpenRegularQueue(State<T> s) {
        this->openRegularQueue.push(s);
    }

    void addToOpenQueue(State<T> s) {
        this->openQueue.push(s);
    }

    int openQueueRegularSize() {
        return (int) this->openRegularQueue.size();
    }

    int openQueueSize() {
        return (int)this->openQueue.size();
    }

    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }

    // check if a specific node is in the closed queue
    bool isStateInClosedQueue(State<T> s, queue<State<T>> closedQueue) {
        queue<State<T>> temp = closedQueue;
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

    // check if a specific node is in the open queue
    bool isStateInOpenRegularQueue(State<T> s) {

        queue<State<T>> temp;

        temp = openRegularQueue;

        while (!temp.empty()) {
            if (s.Equals(temp.front())) {
                return true;
            } else{
                temp.pop();
            }
        }
        return false;
    }

    // check if a specific node is in the priority queue
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

    /*
     * function returns true if we have a shorter path in
     * thee open queue to s and false if not.
     */
    bool isNewPathShorterThanOpen(State<T> s) {

        list<State<T>*> memoryHandle;
        priority_queue<State<T>> temp = this->openQueue;

        while (!temp.empty()) {

           State<T>* olderState = new State<T>(temp.top());
           memoryHandle.push_back(olderState);

           if (olderState->Equals(s)) {
               State<T> local = *olderState;
               freeMemory(memoryHandle);
               return local.getCost() > s.getCost();
            } else {
                temp.pop();
            }
        }

        freeMemory(memoryHandle);
        return false;
    }

    /*
    * function returns true if we have a shorter path in
    * thee open queue to s and false if not.
    */
    bool isNewPathShorterThanClosed(State<T> s, queue<State<T>> q) {

        list<State<T>*> memoryHandle;

        while (!q.empty()) {
            State<T>* olderState = new State<T>(q.front());
            memoryHandle.push_back(olderState);

            if (olderState->Equals(s)) {

                State<T> local = *olderState;
                freeMemory(memoryHandle);
                return local.getCost() > s.getCost();
            } else {
                q.pop();
            }
        }

        freeMemory(memoryHandle);
        return false;
    }

    /*
     * function updates s in the priority queue by
     * pulling it out and inserting it back in
     */
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

    // get the first element in the open queue
    State<T> popOpenRegularQueue() {

        // increase the path visited nodes
        increaseEvaluatedNodes();

        // get that top priority state from the queue
        State<T> s = this->openRegularQueue.front();

        // remove the best state from the queue
        this->openRegularQueue.pop();

        return s;
    }

    // get the best element in the open priority queue
    State<T> popOpenQueue() {

        // increase the path visited nodes
        increaseEvaluatedNodes();

        // get that top priority state from the queue
        State<T> s = this->openQueue.top();

        // remove the best state from the queue
        this->openQueue.pop();

        return s;
    }

    /*
     * function creates a stack with the best path member nodes,
     * by back tracking the 'cameFrom' member from the goal
     * to the initial
     */
    stack<State<T>> getSolutionStack(Searchable<T>* a,
                                     queue<State<T>> closedQueue) {

        // turn the queue into a stack
        stack<State<T>> aidStack;
        while (!closedQueue.empty()) {
            aidStack.push(closedQueue.front());
            closedQueue.pop();
        }

        stack<State<T>> secondStack;

        // omitting nodes before goal node in the stack
        State<T> goal = aidStack.top();
        while ( !goal.Equals(a->isStateGoal(goal))) {
            aidStack.pop();
            goal = aidStack.top();
        }

        secondStack.push(goal);

        // creating the path using 'comefrom'
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

    /*
     * function creates a path string from initial state
     * to the goal state by inverting the path to directions
     * of travel.
     */
    string calculateBackTrace(stack<State<T>> solutionStack) {

        string solution;

        // loop over solution stack elements
        while (!solutionStack.empty()) {

            State<T> s = solutionStack.top();
            solutionStack.pop();

            // check the relationship between the node and
            // the node before it and turn into an action
            if (!solutionStack.empty()) {
                State<T> n = solutionStack.top();
                if (n.getState()[0] > s.getState()[0] ) {
                    solution += DOWN;
                    continue;
                }
                if (n.getState()[0] < s.getState()[0] ) {
                    solution += UP;
                    continue;
                }
                if (n.getState()[0] == s.getState()[0] ) {
                    if (n.getState()[1] > s.getState()[1]) {
                        solution += RIGHT;
                        continue;
                    }
                    solution += LEFT;
                }
            }
        }

        return solution.substr(0, solution.size()-1);
    }

    /*
     * function returns the path solution in a string
     * formation
     */
    string getSolution(Searchable<T>* a, queue<State<T>> closedQueue) {

        if (closedQueue.empty()) {
            return "";
        }

        stack<State<T>> solutionStack = getSolutionStack(a, closedQueue);

        return calculateBackTrace(solutionStack);

    }

    /*
     * function deletes all the allocated memory in the
     * memory object list
     */
    void freeMemory(list<State<T>*> list) {

        while (!list.empty()) {
            delete(list.front());
            list.pop_front();
        }
    }

    /*
     * function receives a reference to a queue
     * and pops the elements (happens at the end
     * of the algorithm)
     */
    void cleanQueue(queue<State<T>>* queue) {
        while (!queue->empty()) {
            queue->pop();
        }
        while (!this->openQueue.empty()) {
            this->openQueue.pop();
        }
        while (!this->openRegularQueue.empty()) {
            this->openRegularQueue.pop();
        }
    }

};



#endif //SECONDMILESTONE_COMMONSEARCHER_H
