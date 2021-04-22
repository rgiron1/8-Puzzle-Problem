#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include<math.h>
#include<iostream>
//#include "Problem.cpp"
//#include "Tree.cpp"
using namespace std;
//containing the different states
class Node{
    public:
        vector<vector<int>> state;
        int cost;
        int heuristic;
        int totalCost;
        int zeroI;
        int zeroJ;
        Node* parent;
        Node* up;
        Node* down;
        Node* left;
        Node* right;

        Node(vector<vector<int>> input_state){
            cost = 0;
            heuristic = 0;
            totalCost = cost + heuristic;
            state = input_state;
            parent = nullptr;
            up = nullptr;
            down = nullptr;
            left = nullptr;
            right = nullptr;
        }

        Node(vector<vector<int>> input_state, Node* parent, int heuristic){
            cost = parent->cost + 1;
            this->heuristic = heuristic;
            totalCost = cost + heuristic;
            state = input_state;
            this->parent = parent;
            up = nullptr;
            down = nullptr;
            left = nullptr;
            right = nullptr;
        }



};