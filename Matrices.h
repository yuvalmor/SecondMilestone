
#ifndef SECONDMILESTONE_MATRICES_H
#define SECONDMILESTONE_MATRICES_H

#include "Searchable.h"
#include <vector>
#include <set>
#include <iostream>

template <class T>
class Matrices : public Searchable<T> {

private:
    vector<vector<State<T>>> matrix;
    State<T> initial;
    State<T> goal;
    int size;

public:

    // define matrix size

    Matrices(const vector<vector<double>>& input, T initial, T goal) {

        this->size = (int)input.size();

        this->matrix.resize(input.size());
        for (int i = 0; i < this->size; i++) {
            vector<State<T>> col;
            col.resize(input.size(), State<T>());
            this->matrix[i] = col;
        }

        initializeMatrixValues(input, initial, goal);

        this->initial = this->matrix[initial[0]][initial[1]];
        this->goal = this->matrix[goal[0]][goal[1]];

    }

    void initializeMatrixValues(vector<vector<double >> input, T initial, T goal) {

        for (int i=0; i<this->size; i++) {
            for (int j=0; j<this->size; j++) {

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

    State<T> getInitialState() override {

        return this->initial;
    }

    State<T> isStateGoal(State<T> s) override {

        if (this->goal.Equals(s)) {
            return s;
        }
        else {
            return this->goal;
        }

    };

    set<State<T>> getAllPossibleStates(State<T> s) override {

        set<State<T>> neighbors;
        int row = s.getState()[0];
        int column = s.getState()[1];

        // down
        if (row < this->size-1) {
            neighbors.insert(this->matrix[row + 1][column]);
        }

        // up
        if (row >0) {
            neighbors.insert(this->matrix[row - 1][column]);
        }

        // would not work if matrix is not cube
        // right
        if (column < this->size-1) {
            neighbors.insert(this->matrix[row][column + 1]);
        }

        // left
        if (column > 0) {
            neighbors.insert(this->matrix[row][column - 1]);
        }

        return neighbors;

    }
};


#endif //SECONDMILESTONE_MATRICES_H
