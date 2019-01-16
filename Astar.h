#ifndef SECONDMILESTONE_ASTAR_H
#define SECONDMILESTONE_ASTAR_H
<<<<<<< HEAD
=======

>>>>>>> origin/master
#include "CommonSearcher.h"
#include <map>
#include <math.h>
#include <set>

template <class T>
class Astar : public CommonSearcher<T> {

private:

    // queue for processed nodes.
    queue<State<T>> closedQueue;
    // map for dry weight of nodes (no heuristic)
    map<T, double> cleanCostMap;

public:

<<<<<<< HEAD

=======
>>>>>>> origin/master
    // searching for the cheapest path from initial to goal node
    Solution<T> search(Searchable<T>* s) override {

        // list of memory allocated
        list<State<T>*> memoryHandle;

        // adding the initial node to the open queue
        State<T>* initial = new State<T>(s->getInitialState());
        this->cleanCostMap[initial->getState()] = initial->getCost();
        CommonSearcher<T>::addToOpenQueue(*initial);
        memoryHandle.push_back(initial);

        // initialize solution
        Solution<T> sol;

        // loop over openQueue states
        while (CommonSearcher<T>::openQueueSize() > 0) {

            // get the best state from the queue to 'n' (and remove from open)
            State<T>* n = new State<T>(CommonSearcher<T>::popOpenQueue());
            memoryHandle.push_back(n);

            // push current best node to closed queue
            this->closedQueue.push(*n);

            // check if we have come to goal node and return solution
            if (n->Equals(s->isStateGoal(*n))) {

<<<<<<< HEAD
                sol.setSolution(CommonSearcher<T>::getSolution(s,this->closedQueue));
                string solutionString = sol.getSolution();
=======
                // set path solution as string
                sol.setSolution(CommonSearcher<T>::getSolution(s,this->closedQueue));
                string solutionString = sol.getSolution();

                // set path total  weight
>>>>>>> origin/master
                if (solutionString.empty()) {
                    CommonSearcher<T>::setChosenPathWeight(-1);
                } else {
                    CommonSearcher<T>::setChosenPathWeight(this->cleanCostMap[n->getState()]);
                }

<<<<<<< HEAD
=======
                // free memory and structures
>>>>>>> origin/master
                CommonSearcher<T>::freeMemory(memoryHandle);
                CommonSearcher<T>::cleanQueue(&this->closedQueue);
                this->cleanCostMap.clear();
                return sol;
            }

            // get the neighbors of 'n'
            multiset<State<T>> neighbors = s->getAllPossibleStates(*n);

            // loop over 'n'/s neighbors
            for (State<T> cState : neighbors) {

                State<T>* neighbor = new State<T>(cState);
                memoryHandle.push_back(neighbor);

                // checking if neighbor is in closed or open queue
                bool isStateInClosed = CommonSearcher<T>::isStateInClosedQueue(*neighbor, this->closedQueue);
                bool isStateInOpen = CommonSearcher<T>::isStateInOpenQueue(*neighbor);

                // calculating cost from n to neighbor without heuristic
                double tentative = this->cleanCostMap[n->getState()] + neighbor->getCost();

                // checking if the neighbor is in the map
                int neighborInMap = (int)this->cleanCostMap.count(neighbor->getState());

                // if this path to neighbor is worst than a path we had
                // or neighbor is in the closed list - do nothing
                if (( neighborInMap > 0 && tentative > this->cleanCostMap[neighbor->getState()])
                    || isStateInClosed) {
                    continue;
                }

                // if this path to neighbor is better or same as old path we had
                // and the neighbor is not in the open queue
                if (( neighborInMap > 0 && tentative <= this->cleanCostMap[neighbor->getState()])
                    || !isStateInOpen ) {

                    // set that we have come to neighbor from n
                    neighbor->setCameFrom(n);
                    // set the value of the path
                    this->cleanCostMap[neighbor->getState()] = tentative;

                    // calculate heuristic estimation from neighbor to goal
                    double neighborHeuristic = heuristicEvaluation(*neighbor, s);

                    // set new cost of neighbor
                    double newCost = tentative + neighborHeuristic;
                    neighbor->setCost(newCost);

                    // if the neighbor is not in the open queue we add it
                    if (!isStateInOpen ) {
                        CommonSearcher<T>::addToOpenQueue(*neighbor);
                    }
                }

            }
        }
<<<<<<< HEAD
=======

>>>>>>> origin/master
        CommonSearcher<T>::freeMemory(memoryHandle);
        CommonSearcher<T>::cleanQueue(&this->closedQueue);
        return sol;

    }

    // function operation - calculate a heuristic estimation of the
    // distance from current node to the goal node
    double heuristicEvaluation(State<T> current, Searchable<T> * s) {

        // if the node is the goal, distance is 0
        State<T> goal = s->isStateGoal(current);
        if (current.Equals(goal)) {
            return 0;
        }

        /*
         * calculation of distance based on air distance,
         * achieved by pythagorean theorem in a triangle
         * where current to goal is the hypotenuse
         */
        int currentX = current.getState()[0];
        int currentY = current.getState()[1];

        int goalX = goal.getState()[0];
        int goalY = goal.getState()[0];

        return sqrt(pow((goalX-currentX),2) + pow((goalY-currentY),2));

    }


};

<<<<<<< HEAD
#endif
=======


#endif //SECONDMILESTONE_ASTAR_H
>>>>>>> origin/master
