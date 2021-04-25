#include "Node.cpp"
#include "Problem.cpp"
//#include "Tree.cpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
using namespace std;
//-------------------------------------Priority Queue------------------------------------------------
struct compareTotalCost{
    bool operator() (Node* a, Node* b){
        return (a->totalCost > b->totalCost);
    }
};
map<vector<vector<int>>, bool> visited;
priority_queue<Node*, vector<Node*>,  compareTotalCost> q;

//---------------------------------------------------Misplaced tile heurisitc---------------------------------------------
int AStarMisplaceHeuristic(vector<vector<int>> state, Problem p){
    int heurisitc = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(state[i][j] != p.goalState[i][j]){
                heurisitc++;
            }
        }
        return heurisitc;
    }
    return 0;
}
//-----------------------------------------------------Eucldian distance heurisitc--------------------------------------------------
int AStarEuclidianHeuristic(vector<vector<int>> state){
    int heuristic = 0;
    for(int i = 0; i < state.size(); i++){
        for(int j = 0; j < state[i].size(); j++){
            if(state[i][j] == 1){
                heuristic += sqrt(pow((i - 0),2) + pow((j - 0), 2));
            } else if(state[i][j] == 2){
                heuristic += sqrt(pow((i - 0),2) + pow((j - 1), 2));
            } else if(state[i][j] == 3){
                heuristic += sqrt(pow((i - 0),2) + pow((j - 2), 2));
            } else if(state[i][j] == 4){
                heuristic += sqrt(pow((i - 1),2) + pow((j - 0), 2));
            } else if(state[i][j] == 5){
                heuristic += sqrt(pow((i - 1),2) + pow((j - 1), 2));
            } else if(state[i][j] == 6){
                heuristic += sqrt(pow((i - 1),2) + pow((j - 2), 2));
            } else if(state[i][j] == 7){
                heuristic += sqrt(pow((i - 2),2) + pow((j - 0), 2));
            } else if(state[i][j] == 8){
                heuristic += sqrt(pow((i - 2),2) + pow((j - 1), 2));
            } else if(state[i][j] == 0){
                heuristic += sqrt(pow((i - 2),2) + pow((j - 2), 2));
            }
        }
    }
    return heuristic;
}
//-----------------------------------------------------------------------Print--------------------------------------------------
void Print(vector<vector<int>> input){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << input[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------------------------------" << endl;
}


//---------------------------------------------------------UP FUNCTION---------------------------------------------------------------------
void moveUp(vector<vector<int>> state, Node* n, int heurisitc){
    if(n->zeroI > 0){
        vector<vector<int>> upState = state;
        swap(upState[n->zeroI][n->zeroJ], upState[n->zeroI - 1][n->zeroJ]);
        if(!visited.count(upState)){
            Node *upNode = new Node(upState, n, heurisitc);
            upNode->zeroI = n->zeroI - 1;
            upNode->zeroJ = n->zeroJ;
            n->up = upNode;
            visited[upNode->state] = true;
            q.push(upNode);
        }
    } 
}
    //--------------------------------------------------------------------DOWN----------------------------------------------------------------------------
void moveDown(vector<vector<int>> state, Node* n, int heurisitc){
    if(n->zeroI < 2){
        vector<vector<int>> downState = state;
        swap(downState[n->zeroI][n->zeroJ], downState[n->zeroI + 1][n->zeroJ]);
        if(!visited.count(downState)){
            Node *downNode = new Node(downState, n, heurisitc);
            downNode->zeroI = n->zeroI + 1;
            downNode->zeroJ = n->zeroJ;
            n->down = downNode;
            visited[downNode->state] = true;
            q.push(downNode);
        }
    }
}
    //--------------------------------------------------------------LEFT-----------------------------------------------------------------------
void moveLeft(vector<vector<int>> state, Node* n, int heurisitc){
    if(n->zeroJ > 0){
        vector<vector<int>> leftState = state;
        swap(leftState[n->zeroI][n->zeroJ], leftState[n->zeroI][n->zeroJ - 1]);
        if(!visited.count(leftState)){
            Node *leftNode = new Node(leftState, n, heurisitc);
            leftNode->zeroJ = n->zeroJ - 1;
            leftNode->zeroI = n->zeroI;
            n->left = leftNode;
            visited[leftNode->state] = true;
            q.push(leftNode);
        }
    }
}
    //--------------------------------------------------------------------RIGHT-------------------------------------------------------------------------
void moveRight(vector<vector<int>> state, Node* n, int heurisitc){
    if(n->zeroJ < 2){
        vector<vector<int>> rightState = state;
        swap(rightState[n->zeroI][n->zeroJ], rightState[n->zeroI][n->zeroJ + 1]);
        if(!visited.count(rightState)){
            Node *rightNode = new Node(rightState, n, heurisitc);
            rightNode->zeroJ = n->zeroJ + 1;
            rightNode->zeroI = n->zeroI;
            n->right = rightNode;
            visited[rightNode->state] = true;
            q.push(rightNode);
        }
    }
}
//-------------------------------------------------------------BackTracing---------------------------------------------------------------
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
    //cout << "It took " << steps << " moves to solve the puzzle"<< endl;
}
//---------------------------------------------------Uniform Cost Search ----------------------------------------------------------
bool uniformCostSearch(Problem p){
    int totalStates = 0;
    int maxInQ = 0;
    Node *root = new Node(p.currentState);
    totalStates++;
    if(p.currentState == p.goalState){
        cout << "Total states expanded is: " << totalStates << endl;
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
    
    moveUp(p.currentState, root, 0);
    moveDown(p.currentState, root, 0);
    moveLeft(p.currentState, root, 0);
    moveRight(p.currentState, root, 0);

    while(!q.empty()){
        Node* curr = q.top();
        maxInQ = max(maxInQ, int(q.size()));
        totalStates++;
        Print(curr->state);
        if(curr->state == p.goalState){
            cout << endl << "STEPS TO GET TO SOLUTION: " << endl;
            backTracing(curr); //FOR BACKTRACKING AND EXTRA CREDIT
            cout << "To solve this problem the search algorithm expanded a total of: " << totalStates << " nodes" << endl;
            cout << "The maximum number of nodes in the queue at any one time: " << maxInQ << endl;
            return true;
        }
        q.pop();
        moveUp(curr->state, curr, 0);
        //DOWN
        moveDown(curr->state, curr, 0);
        //LEFT
        moveLeft(curr->state, curr, 0);
        //RIGHT
        moveRight(curr->state, curr, 0);
    }
    return false;
}

//---------------------------------------A * Misplaced tile herusitic -------------------------------------------------------------
bool AStarMisplace(Problem p){
    int totalStates = 0;
    int maxInQ = 0;
    Node *root = new Node(p.currentState);
    totalStates++;
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
    
    moveUp(p.currentState, root, AStarMisplaceHeuristic(p.currentState, p));
    moveDown(p.currentState, root, AStarMisplaceHeuristic(p.currentState, p));
    moveLeft(p.currentState, root, AStarMisplaceHeuristic(p.currentState, p));
    moveRight(p.currentState, root, AStarMisplaceHeuristic(p.currentState, p));

    while(!q.empty()){
        Node* curr = q.top();
        maxInQ = max(maxInQ, int(q.size()));
        totalStates++;
        Print(curr->state);
        if(curr->state == p.goalState){
            cout << endl << "STEPS TO GET TO SOLUTION: " << endl;
            backTracing(curr); //FOR BACKTRACKING AND EXTRA CREDIT
            cout << "To solve this problem the search algorithm expanded a total of: " << totalStates << " nodes" << endl;
            cout << "The maximum number of nodes in the queue at any one time: " << maxInQ << endl;
            return true;
        }
        q.pop();
        moveUp(curr->state, curr, AStarMisplaceHeuristic(curr->state, p));
        //DOWN
        moveDown(curr->state, curr, AStarMisplaceHeuristic(curr->state, p));
        //LEFT
        moveLeft(curr->state, curr, AStarMisplaceHeuristic(curr->state, p));
        //RIGHT
        moveRight(curr->state, curr, AStarMisplaceHeuristic(curr->state, p));
    }
    return false;
}
//------------------------------------------A* Euclidean distance------------------------------------------
bool AStarEuclidean(Problem p){
    int totalStates = 0;
    int maxInQ = 0;
    Node *root = new Node(p.currentState);
    totalStates++;
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
    
    moveUp(p.currentState, root, AStarEuclidianHeuristic(p.currentState));
    moveDown(p.currentState, root, AStarEuclidianHeuristic(p.currentState));
    moveLeft(p.currentState, root, AStarEuclidianHeuristic(p.currentState));
    moveRight(p.currentState, root, AStarEuclidianHeuristic(p.currentState));

    while(!q.empty()){
        Node* curr = q.top();
        maxInQ = max(maxInQ, int(q.size()));
        totalStates++;
        Print(curr->state);
        if(curr->state == p.goalState){
            cout << endl << "STEPS TO GET TO SOLUTION: " << endl;
            backTracing(curr); //FOR BACKTRACKING AND EXTRA CREDIT
            cout << "To solve this problem the search algorithm expanded a total of: " << totalStates << " nodes" << endl;
            cout << "The maximum number of nodes in the queue at any one time: " << maxInQ << endl;
            return true;
        }
        q.pop();
        moveUp(curr->state, curr, AStarEuclidianHeuristic(curr->state));
        //DOWN
        moveDown(curr->state, curr, AStarEuclidianHeuristic(curr->state));
        //LEFT
        moveLeft(curr->state, curr, AStarEuclidianHeuristic(curr->state));
        //RIGHT
        moveRight(curr->state, curr, AStarEuclidianHeuristic(curr->state));
    }
    return false;
}



int main(){
    cout << "Please enter a number between 1 - 6 to select the difficulty that the AI should solve, or press 7 to make your own puzzle." << endl;
    int difficulty = 0;
    bool success = false;
    cin >> difficulty;
    Problem p;

    string first = "";
    string second = "";
    string third = "";
    vector<int> firstRow;
    vector<int> secondRow;
    vector<int> thridRow;
    vector<vector<int>> inputProb;
    
    
    switch(difficulty){
        case 1: 
            p.initialState = p.trivialState;
            p.setCurrentState(p.initialState);
            break;
        case 2: 
            p.initialState = p.veryEasyState;
            p.setCurrentState(p.initialState);
            break;
        case 3: 
            p.initialState = p.easyState;
            p.setCurrentState(p.initialState);
            break;
        case 4: 
            p.initialState = p.doableState;
            p.setCurrentState(p.initialState);
            break;
        case 5: 
            p.initialState = p.ohBoyState;
            p.setCurrentState(p.initialState);
            break;
        case 6: 
            p.initialState = p.impossibleState;
            p.setCurrentState(p.initialState);
            break;
        case 7: 
            cout << "Please enter the first row: ";
            cin >> first;
            cout << "Please enter the second row: ";
            cin >> second;
            cout << "Please enter the third row: ";
            cin >> third;

            for(auto x : first){
                firstRow.push_back(int(x) - 48);
            } 
            inputProb.push_back(firstRow);

            for(auto x : second){
                secondRow.push_back(int(x) - 48);
            } 
            inputProb.push_back(secondRow);

            for(auto x : third){
                thridRow.push_back(int(x) - 48);
            } 
            inputProb.push_back(thridRow);
            p.initialState = inputProb;
            p.setCurrentState(p.initialState);

        break;

        default: 
        cout << "Please rerun the program and enter a correct number" << endl;
            break;
    }

    cout << "Please enter the the number of the algorithm" << endl << "1. Uniform Cost Search" << endl << "2. A* Misplaced Tile Heurisitc" << endl << "3. A* Euclidean Distance Heurisitc" << endl;
    int algo = 0;
    cin >> algo;

    switch (algo)
    {
    case 1:
         cout << "INITIAL STATE" << endl;
            p.printCurrentState();
            cout << "------------------------------------" << endl;
            success = uniformCostSearch(p);
        break;
    case 2:
            cout << "INITIAL STATE" << endl;
            p.printCurrentState();
            cout << "------------------------------------" << endl;
            success = AStarMisplace(p);
        break;
    case 3:  
            cout << "INITIAL STATE" << endl;
            p.printCurrentState();
            cout << "------------------------------------" << endl;
            success = AStarEuclidean(p);
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