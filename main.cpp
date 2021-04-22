#include "Node.cpp"
#include "Problem.cpp"
//#include "Tree.cpp"
#include <string>
#include <iostream>
#include <queue>
#include <map>
using namespace std;

int AStarMisplaceHeuristic(vector<vector<int>> state){
    return 0;
}

int AStarEuclidianHeuristic(vector<vector<int>> state){
    return 0;
}



void uniformCostSearch(Problem p){
    map<vector<vector<int>>, bool> visited;
    Node *curNode = new Node(p.currentState);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(p.currentState[i][j] == 0){
                curNode->zeroI = i;
                curNode->zeroJ = j;
                cout << curNode->zeroI << " " << curNode->zeroJ << endl;
            }
        }
    }

    struct compareTotalCost{
        bool operator() (Node a, Node b){
            return (a.totalCost < b.totalCost);
        }
    };

    priority_queue<Node, vector<Node>,  compareTotalCost> q;
    
    //UP
    if(curNode->zeroI > 0){
        vector<vector<int>> upState = p.currentState;
        swap(upState[curNode->zeroI][curNode->zeroJ], upState[curNode->zeroI - 1][curNode->zeroJ]);
        Node *upNode = new Node(upState, curNode, 0);
        upNode->zeroI = curNode->zeroI - 1;
        upNode->zeroJ = curNode->zeroJ;
        curNode->up = upNode;
        visited[upNode->state] = true;
        //cout << "UP " << upNode->zeroI << "," << upNode->zeroJ << endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << upNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    } else {
        cout << "Invalid state" << endl;
    }
    //DOWN
    if(curNode->zeroI < 2){
        vector<vector<int>> downState = p.currentState;
        swap(downState[curNode->zeroI][curNode->zeroJ], downState[curNode->zeroI + 1][curNode->zeroJ]);
        Node *downNode = new Node(downState, curNode, 0);
        downNode->zeroI = curNode->zeroI + 1;
        downNode->zeroJ = curNode->zeroJ;
        curNode->down = downNode;
        visited[downNode->state] = true;
        //cout << "DOWN " << downNode->zeroI << "," << downNode->zeroJ<< endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << downNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    } else {
        cout << "Invalid state" << endl;
    }
    //LEFT
    if(curNode->zeroJ > 0){
        vector<vector<int>> leftState = p.currentState;
        swap(leftState[curNode->zeroI][curNode->zeroJ], leftState[curNode->zeroI][curNode->zeroJ - 1]);
        Node *leftNode = new Node(leftState, curNode, 0);
        leftNode->zeroJ = curNode->zeroJ - 1;
        leftNode->zeroI = curNode->zeroI;
        curNode->left = leftNode;
        visited[leftNode->state] = true;
        //cout << "LEFT " << leftNode->zeroI << "," << leftNode->zeroJ << endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << leftNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    } else {
        cout << "Invalid state" << endl;
    }
    //RIGHT
    if(curNode->zeroJ < 2){
        vector<vector<int>> rightState = p.currentState;
        swap(rightState[curNode->zeroI][curNode->zeroJ], rightState[curNode->zeroI][curNode->zeroJ + 1]);
        Node *rightNode = new Node(rightState, curNode, 0);
        rightNode->zeroJ = curNode->zeroJ + 1;
        rightNode->zeroI = curNode->zeroI;
        curNode->right = rightNode;
        visited[rightNode->state] = true;
        //cout << "RIGHT " << rightNode->zeroI << "," << rightNode->zeroJ << endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << rightNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    } else {
        cout << "Invalid state" << endl;
    }
}



int main(){
    cout << "Please enter a number between 1 - 6 to select the difficulty that the AI should solve." << endl;
    int difficulty = 0;
    int tmp;
    cin >> difficulty;
    Problem p;

    
    //difficulty = stoi(tmp);
    
    
    switch(difficulty){
        case 1: 
            p.initialState = p.trivialState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            uniformCostSearch(p);
            break;
        case 2: 
            p.initialState = p.veryEasyState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            uniformCostSearch(p);
            break;
        case 3: 
            p.initialState = p.easyState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            uniformCostSearch(p);
            break;
        case 4: 
            p.initialState = p.doableState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            uniformCostSearch(p);
            break;
        case 5: 
            p.initialState = p.ohBoyState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            uniformCostSearch(p);
            break;
        case 6: 
            p.initialState = p.impossibleState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            uniformCostSearch(p);
            break;
            
        default: 
        cout << "Please rerun the program and enter a correct number" << endl;
            break;
}

    return 0;
}