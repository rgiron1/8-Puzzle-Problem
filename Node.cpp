#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include<math.h>
#include<iostream>
#include "Problem.cpp"
#include "Tree.cpp"
using namespace std;
//containing the different states
class Node{
    private:
        vector<vector<int>> state;
        Node* parent;
        Node* up;
        Node* down;
        Node* left;
        Node* right;

    public:
        Node(vector<vector<int>> input_state){
            state = input_state;
            parent = nullptr;
            up = nullptr;
            down = nullptr;
            left = nullptr;
            right = nullptr;
        }

        Node(vector<vector<int>> input_state, Node* parent){
            state = input_state;
            this->parent = parent;
            up = nullptr;
            down = nullptr;
            left = nullptr;
            right = nullptr;
        }
    
    

};