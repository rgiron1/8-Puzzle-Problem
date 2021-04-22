#include "Node.cpp"
#include "Problem.cpp"
//#include "Tree.cpp"
#include <string>
#include <iostream>
#include <queue>
#include <stack>
#include <map>
using namespace std;

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
    map<vector<vector<int>>, bool> visited;
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

    struct compareTotalCost{
        bool operator() (Node* a, Node* b){
            return (a->totalCost > b->totalCost);
        }
    };

    priority_queue<Node*, vector<Node*>,  compareTotalCost> q;
    
    //UP
    if(root->zeroI > 0){
        vector<vector<int>> upState = p.currentState;
        swap(upState[root->zeroI][root->zeroJ], upState[root->zeroI - 1][root->zeroJ]);
        Node *upNode = new Node(upState, root, 0);
        upNode->zeroI = root->zeroI - 1;
        upNode->zeroJ = root->zeroJ;
        root->up = upNode;
        visited[upNode->state] = true;
        q.push(upNode);
        //cout << "UP " << upNode->zeroI << "," << upNode->zeroJ << endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << upNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    } 
    //DOWN
    if(root->zeroI < 2){
        vector<vector<int>> downState = p.currentState;
        swap(downState[root->zeroI][root->zeroJ], downState[root->zeroI + 1][root->zeroJ]);
        Node *downNode = new Node(downState, root, 0);
        downNode->zeroI = root->zeroI + 1;
        downNode->zeroJ = root->zeroJ;
        root->down = downNode;
        visited[downNode->state] = true;
        q.push(downNode);
        //cout << "DOWN " << downNode->zeroI << "," << downNode->zeroJ<< endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << downNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    }
    //LEFT
    if(root->zeroJ > 0){
        vector<vector<int>> leftState = p.currentState;
        swap(leftState[root->zeroI][root->zeroJ], leftState[root->zeroI][root->zeroJ - 1]);
        Node *leftNode = new Node(leftState, root, 0);
        leftNode->zeroJ = root->zeroJ - 1;
        leftNode->zeroI = root->zeroI;
        root->left = leftNode;
        visited[leftNode->state] = true;
        q.push(leftNode);
        //cout << "LEFT " << leftNode->zeroI << "," << leftNode->zeroJ << endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << leftNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    }
    //RIGHT
    if(root->zeroJ < 2){
        vector<vector<int>> rightState = p.currentState;
        swap(rightState[root->zeroI][root->zeroJ], rightState[root->zeroI][root->zeroJ + 1]);
        Node *rightNode = new Node(rightState, root, 0);
        rightNode->zeroJ = root->zeroJ + 1;
        rightNode->zeroI = root->zeroI;
        root->right = rightNode;
        visited[rightNode->state] = true;
        q.push(rightNode);
        //cout << "RIGHT " << rightNode->zeroI << "," << rightNode->zeroJ << endl;
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         cout << rightNode->state[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    } 
//-----------------------------------------------------------------------QUEUE--------------------------------------------------------------------
    while(!q.empty()){
        Node* curr = q.top();
        Print(curr->state);
        if(curr->state == p.goalState){
            //backTracing(curr); FOR BACKTRACKING AND EXTRA CREDIT
            return true;
        }
        q.pop();
        if(curr->zeroI > 0){
        vector<vector<int>> upState = curr->state;
        swap(upState[curr->zeroI][curr->zeroJ], upState[curr->zeroI - 1][curr->zeroJ]);
        if(!visited.count(upState)){
            Node *upNode = new Node(upState, curr, 0);
            upNode->zeroI = curr->zeroI - 1;
            upNode->zeroJ = curr->zeroJ;
            curr->up = upNode;
            visited[upNode->state] = true;
            q.push(upNode);
        }
        } 
        //DOWN
        if(curr->zeroI < 2){
            vector<vector<int>> downState = curr->state;
            swap(downState[curr->zeroI][curr->zeroJ], downState[curr->zeroI + 1][curr->zeroJ]);
            if(!visited.count(downState)){
                Node *downNode = new Node(downState, curr, 0);
                downNode->zeroI = curr->zeroI + 1;
                downNode->zeroJ = curr->zeroJ;
                curr->down = downNode;
                visited[downNode->state] = true;
                q.push(downNode);
            }
        } 
        //LEFT
        if(curr->zeroJ > 0){
            vector<vector<int>> leftState = curr->state;
            swap(leftState[curr->zeroI][curr->zeroJ], leftState[curr->zeroI][curr->zeroJ - 1]);
            if(!visited.count(leftState)){
                Node *leftNode = new Node(leftState, curr, 0);
                leftNode->zeroJ = curr->zeroJ - 1;
                leftNode->zeroI = curr->zeroI;
                curr->left = leftNode;
                visited[leftNode->state] = true;
                q.push(leftNode);
            }
        }
        //RIGHT
        if(curr->zeroJ < 2){
            vector<vector<int>> rightState = curr->state;
            swap(rightState[curr->zeroI][curr->zeroJ], rightState[curr->zeroI][curr->zeroJ + 1]);
            if(!visited.count(rightState)){
                Node *rightNode = new Node(rightState, curr, 0);
                rightNode->zeroJ = curr->zeroJ + 1;
                rightNode->zeroI = curr->zeroI;
                curr->right = rightNode;
                visited[rightNode->state] = true;
                q.push(rightNode);
            }
        }
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
            p.printCurrentState();
            success = uniformCostSearch(p);
            break;
        case 2: 
            p.initialState = p.veryEasyState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            success = uniformCostSearch(p);
            break;
        case 3: 
            p.initialState = p.easyState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            success = uniformCostSearch(p);
            break;
        case 4: 
            p.initialState = p.doableState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            success = uniformCostSearch(p);
            break;
        case 5: 
            p.initialState = p.ohBoyState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            success = uniformCostSearch(p);
            break;
        case 6: 
            p.initialState = p.impossibleState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            success = uniformCostSearch(p);
            break;
            
        default: 
        cout << "Please rerun the program and enter a correct number" << endl;
            break;
}
    if(success){
        cout << "SUCCESS" << endl;
    } else {
        cout << "FAILED" << endl;
    }
    return 0;
}