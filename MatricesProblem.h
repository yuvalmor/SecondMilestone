
#ifndef SECONDMILESTONE_MATRICES_H
#define SECONDMILESTONE_MATRICES_H

#include "Searchable.h"
#include <set>
#include <iostream>

template <class T>
class MatricesProblem : public Searchable<T> {

private:
    // members
    int width;
    int height;

public:

    // ctor - initializes matrix size and values.
    MatricesProblem(const vector<vector<double>>& input, T initial, T goal) {

        this->height = (int)input.size();
        this->width = (int)input[0].size();

        // create a 'state' matrix from a double matrix
        this->matrix.resize(this->height);
        for (int i = 0; i < this->height; i++) {
            vector<State<T>> col;
            col.resize(this->width, State<T>());
            this->matrix[i] = col;
        }

        // insert values
        initializeMatrixValues(input, initial, goal);

        // set initial and goal states
        this->initial = this->matrix[initial[0]][initial[1]];
        this->goal = this->matrix[goal[0]][goal[1]];

    }

    /*
     * function creates states and add to this matrix
     * based on values given
     */
    void initializeMatrixValues(vector<vector<double >> input, T initial, T goal) {

        for (int i=0; i<this->height; i++) {
            for (int j=0; j<this->width; j++) {

                // set all states to their cost values and position
                State<T> current;
                current.setCameFrom(nullptr);
                current.setCost(input[i][j]);

                vector<int> pos;
                pos.push_back(i);
                pos.push_back(j);
                current.setState(pos);

                this->matrix[i][j] = current;

            }
        }
    }

    // getter
    State<T> getInitialState() override {
        return this->initial;
    }

    /*
     * function checks if a specific state is the goal
     * state, returns the given state if yes
     * and returns the actual goal state if not.
     */
    State<T> isStateGoal(State<T> s) override {

        if (this->goal.Equals(s)) {
            return s;
        }
        else {
            return this->goal;
        }

    };

    // function returns all the neighbors of a specific state
    multiset<State<T>> getAllPossibleStates(State<T> s) override {

        // set s's row and column
        multiset<State<T>> neighbors;
        int row = s.getState()[0];
        int column = s.getState()[1];

        // down - verify row position and not being a wall
        if (row < this->height-1) {
            State<T> nd = this->matrix[row + 1][column];
            if (nd.getCost() != -1) {
                neighbors.insert(nd);
            }
        }

        // up - verify row position and not being a wall
        if (row >0) {
            State<T> nu = this->matrix[row - 1][column];
            if (nu.getCost() != -1) {
                neighbors.insert(nu);
            }
        }

        // right - verify column position and not being a wall
        if (column < this->width-1) {
            State<T> nr = this->matrix[row][column + 1];
            if (nr.getCost() != -1) {
                neighbors.insert(nr);
            }
        }

        // left - verify column position and not being a wall
        if (column > 0) {
            State<T> nl = this->matrix[row][column - 1];
            if (nl.getCost() != -1) {
                neighbors.insert(nl);
            }
        }

        return neighbors;

    }
};

#endif //SECONDMILESTONE_MATRICES_H
