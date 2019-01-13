#ifndef SECONDMILESTONE_ASTAR_H
#define SECONDMILESTONE_ASTAR_H

#include "CommonSearcher.h"
#include <map>
#include <math.h>
#include <set>


template <class T>
class Aster : public CommonSearcher<T> {

private:
    queue<State<T>> closedQueue;
    map<T, double> cleanCostMap;

public:
    // ctor
    Aster<T>():CommonSearcher<T>(){}

    Solution<T> search(Searchable<T>* s) override {

        // initialize member 'openQueue' (priority Queue)
        // with initialCost + heuristicCost
        State<T>* initial = new State<T>(s->getInitialState());
        this->cleanCostMap[initial->getState()] = initial->getCost();
        CommonSearcher<T>::addToOpenQueue(*initial);

        // initialize solution
        Solution<T> sol;

        while (CommonSearcher<T>::openQueueSize() > 0) {

            // get the next best node from priority queue
            State<T>* n = new State<T>(CommonSearcher<T>::popOpenQueue());

            // push current best node to closed queue
            this->closedQueue.push(*n);

            // check if we have come to goal node
            if (n->Equals(s->isStateGoal(*n))) {
                sol.setSolution(CommonSearcher<T>::getSolution(s,this->closedQueue));
                return sol;
            }

            // get the neighbors of 'n'
            set<State<T>> neighbors = s->getAllPossibleStates(*n);

            // loop over 'n'/s neighbors
            for (State<T> cState : neighbors) {

                State<T>* neighbor = new State<T>(cState);

                bool isStateInClosed = isStateInClosedQueue(*neighbor);
                bool isStateInOpen = CommonSearcher<T>::isStateInOpenQueue(*neighbor);

                double tentative = this->cleanCostMap[n->getState()] + neighbor->getCost();

                int neighborInMap = (int)this->cleanCostMap.count(neighbor->getState());

                if (( neighborInMap > 0 && tentative > this->cleanCostMap[neighbor->getState()])
                                || isStateInClosed) {
                    continue;
                }
                if (( neighborInMap > 0 && tentative <= this->cleanCostMap[neighbor->getState()])
                                 || !isStateInOpen ) {

                    neighbor->setCameFrom(n);
                    this->cleanCostMap[neighbor->getState()] = tentative;

                    double neighborHeuristic = heuristicEvaluation(*neighbor, s);
                    double newCost = tentative + neighborHeuristic;
                    neighbor->setCost(newCost);

                    if (!isStateInOpen ) {
                        CommonSearcher<T>::addToOpenQueue(*neighbor);
                    }
                }

            }
        }

        return sol;

    }

    double heuristicEvaluation(State<T> current, Searchable<T> * s) {

        State<T> goal = s->isStateGoal(current);

        if (current.Equals(goal)) {
            return 0;
        }

        int currentX = current.getState()[0];
        int currentY = current.getState()[1];

        int goalX = goal.getState()[0];
        int goalY = goal.getState()[0];

        return sqrt(pow((goalX-currentX),2) + pow((goalY-currentY),2));

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

};


#endif //SECONDMILESTONE_ASTAR_H
