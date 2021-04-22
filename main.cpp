#include "Node.cpp"
#include "Problem.cpp"
//#include "Tree.cpp"
#include <string>
#include <iostream>
#include <queue>
#include <stack>
#include <map>
using namespace std;

struct compareTotalCost{
    bool operator() (Node* a, Node* b){
        return (a->totalCost > b->totalCost);
    }
};
map<vector<vector<int>>, bool> visited;
priority_queue<Node*, vector<Node*>,  compareTotalCost> q;


int AStarMisplaceHeuristic(vector<vector<int>> state){
    return 0;
}

int AStarEuclidianHeuristic(vector<vector<int>> state){
    return 0;
}

void Print(vector<vector<int>> input){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << input[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------------------------------" << endl;
}



//UP FUNCTION
void moveUp(vector<vector<int>> state, Node* n){
    if(n->zeroI > 0){
        vector<vector<int>> upState = state;
        swap(upState[n->zeroI][n->zeroJ], upState[n->zeroI - 1][n->zeroJ]);
        if(!visited.count(upState)){
            Node *upNode = new Node(upState, n, 0);
            upNode->zeroI = n->zeroI - 1;
            upNode->zeroJ = n->zeroJ;
            n->up = upNode;
            visited[upNode->state] = true;
            q.push(upNode);
        }
        //cout << "UP " << upNode->zeroI << "," << upNode->zeroJ << endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << upNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    } 
}
    //DOWN
void moveDown(vector<vector<int>> state, Node* n){
    if(n->zeroI < 2){
        vector<vector<int>> downState = state;
        swap(downState[n->zeroI][n->zeroJ], downState[n->zeroI + 1][n->zeroJ]);
        if(!visited.count(downState)){
            Node *downNode = new Node(downState, n, 0);
            downNode->zeroI = n->zeroI + 1;
            downNode->zeroJ = n->zeroJ;
            n->down = downNode;
            visited[downNode->state] = true;
            q.push(downNode);
        }
        //cout << "DOWN " << downNode->zeroI << "," << downNode->zeroJ<< endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << downNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    }
}
    //LEFT
void moveLeft(vector<vector<int>> state, Node* n){
    if(n->zeroJ > 0){
        vector<vector<int>> leftState = state;
        swap(leftState[n->zeroI][n->zeroJ], leftState[n->zeroI][n->zeroJ - 1]);
        if(!visited.count(leftState)){
            Node *leftNode = new Node(leftState, n, 0);
            leftNode->zeroJ = n->zeroJ - 1;
            leftNode->zeroI = n->zeroI;
            n->left = leftNode;
            visited[leftNode->state] = true;
            q.push(leftNode);
        }
        //cout << "LEFT " << leftNode->zeroI << "," << leftNode->zeroJ << endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << leftNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    }
}
    //RIGHT
void moveRight(vector<vector<int>> state, Node* n){
    if(n->zeroJ < 2){
        vector<vector<int>> rightState = state;
        swap(rightState[n->zeroI][n->zeroJ], rightState[n->zeroI][n->zeroJ + 1]);
        if(!visited.count(rightState)){
            Node *rightNode = new Node(rightState, n, 0);
            rightNode->zeroJ = n->zeroJ + 1;
            rightNode->zeroI = n->zeroI;
            n->right = rightNode;
            visited[rightNode->state] = true;
            q.push(rightNode);
        }
        //cout << "RIGHT " << rightNode->zeroI << "," << rightNode->zeroJ << endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << rightNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    }
}
    
void backTracing(Node* node) {
    int steps = 0;
    stack<vector<vector<int>>> stack;
    while (node->parent != nullptr) {
        stack.push(node->state);
        node = node->parent;
    }
    while (!stack.empty()) {
        steps++;
        Print(stack.top());
        stack.pop();
    }
    cout << "It took " << steps << " moves to solve the puzzle"<< endl;
}

bool uniformCostSearch(Problem p){
    Node *root = new Node(p.currentState);
    if(p.currentState == p.goalState){
        return true;
    }
    visited[root->state] = true;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(p.currentState[i][j] == 0){
                root->zeroI = i;
                root->zeroJ = j;
            }
        }
    }
    
    moveUp(p.currentState, root);
    moveDown(p.currentState, root);
    moveLeft(p.currentState, root);
    moveRight(p.currentState, root);

//-----------------------------------------------------------------------QUEUE--------------------------------------------------------------------
    while(!q.empty()){
        Node* curr = q.top();
        Print(curr->state);
        if(curr->state == p.goalState){
            //backTracing(curr); //FOR BACKTRACKING AND EXTRA CREDIT
            return true;
        }
        q.pop();
        moveUp(curr->state, curr);
        //DOWN
        moveDown(curr->state, curr);
        //LEFT
        moveLeft(curr->state, curr);
        //RIGHT
        moveRight(curr->state, curr);
    }
    return false;
}

int main(){
    cout << "Please enter a number between 1 - 6 to select the difficulty that the AI should solve." << endl;
    int difficulty = 0;
    bool success = false;
    cin >> difficulty;
    Problem p;
    
    
    switch(difficulty){
        case 1: 
            p.initialState = p.trivialState;
            p.setCurrentState(p.initialState);
            cout << "INITIAL STATE" << endl;
            p.printCurrentState();
            cout << "------------------------------------" << endl;
            success = uniformCostSearch(p);
            break;
        case 2: 
            p.initialState = p.veryEasyState;
            p.setCurrentState(p.initialState);
            cout << "INITIAL STATE" << endl;
            p.printCurrentState();
            cout << "------------------------------------" << endl;
            success = uniformCostSearch(p);
            break;
        case 3: 
            p.initialState = p.easyState;
            p.setCurrentState(p.initialState);
            cout << "INITIAL STATE" << endl;
            p.printCurrentState();
            cout << "------------------------------------" << endl;
            success = uniformCostSearch(p);
            break;
        case 4: 
            p.initialState = p.doableState;
            p.setCurrentState(p.initialState);
            cout << "INITIAL STATE" << endl;
            p.printCurrentState();
            cout << "------------------------------------" << endl;
            success = uniformCostSearch(p);
            break;
        case 5: 
            p.initialState = p.ohBoyState;
            p.setCurrentState(p.initialState);
            cout << "INITIAL STATE" << endl;
            p.printCurrentState();
            cout << "------------------------------------" << endl;
            success = uniformCostSearch(p);
            break;
        case 6: 
            p.initialState = p.impossibleState;
            p.setCurrentState(p.initialState);
            cout << "INITIAL STATE" << endl;
            p.printCurrentState();
            cout << "------------------------------------" << endl;
            success = uniformCostSearch(p);
            break;
            
        default: 
        cout << "Please rerun the program and enter a correct number" << endl;
            break;
    }
    
    if(success){
        cout << "SUCCESS" << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}