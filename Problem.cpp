#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
//#include "Tree.cpp"
using namespace std;
//Problem class will have all the intial states, the goal state, and the current state. 
class Problem{
    public: 
//-----------------------------------States-----------------------------------------------
        vector<vector<int>> trivialState = {{1,2,3},
                                                {4,5,6},
                                                {7,8,0}};

        vector<vector<int>> veryEasyState = {{1,2,3},
                                                 {4,5,6},
                                                 {7,0,8}};

        vector<vector<int>> easyState = {{1,2,0},
                                             {4,5,3},
                                             {7,8,6}};

        vector<vector<int>> doableState = {{0,1,2},
                                               {4,5,3},
                                               {7,8,6}};

        vector<vector<int>> ohBoyState = {{8,7,1},
                                              {6,0,2},
                                              {5,4,3}};
                                              
        vector<vector<int>> impossibleState = {{1,2,3},
                                                   {4,5,6},
                                                   {8,7,0}};

        vector<vector<int>> initialState;
        //Goal State:
        vector<vector<int>> goalState = {{1,2,3}, 
                                         {4,5,6},
                                         {7,8,0}};

        //current State:
        vector<vector<int>> currentState;

//-------------------------Operations---------------------------------------


enum Operations{
    up,
    down,
    left,
    right
};


//-------------------------Functions---------------------------------------

    void setCurrentState(vector<vector<int>> state){
        currentState = state;
    }

    void printCurrentState(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                cout << currentState[i][j] << " ";
            }
            cout << endl ;
        }
    }


};
