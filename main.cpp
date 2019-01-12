
#include "Matrices.h"
#include "BestFirstSearch.h"
#include "Solution.h"
#include <iostream>

#define SIZE 3

int main() {

    vector<vector<double>> matrix1;

    matrix1.resize(SIZE);
    for (int i=0; i<SIZE; i++) {
        matrix1[i].resize(SIZE);
    }

    matrix1[0][0] = double(5);
    matrix1[0][1] = double(1);
    matrix1[0][2] = double(5);
    matrix1[1][0] = double(4);
    matrix1[1][1] = double(1);
    matrix1[1][2] = double(500);
    matrix1[2][0] = double(0);
    matrix1[2][1] = double(1);
    matrix1[2][2] = double(5);

    vector<int> initial;
    initial.push_back(0);
    initial.push_back(0);
    vector<int> goal;
    goal.push_back(2);
    goal.push_back(2);

    Searchable<vector<int>>* m = new Matrices<vector<int>>(matrix1, initial, goal);
    Searcher<vector<int>> * s = new BestFirstSearch<vector<int>>();
  //  Searcher<int>* s = new CommonSearcher<int>(new BestFirstSearch<int>());
    Solution<vector<int>> solution = s->search(m);
    cout << solution.getSolution() << endl;
    return 0;
}