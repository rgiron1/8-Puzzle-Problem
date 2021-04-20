//#include "Node.cpp"
#include "Problem.cpp"
//#include "Tree.cpp"
#include <string>
#include <iostream>
using namespace std;

int main(){
    cout << "Please enter a number between 1 - 6 to select the difficulty that the AI should solve." << endl;
    int difficulty = 0;
    int tmp;
    cin >> difficulty;
    Problem p; //= new Problem();
    //enter #1-6
    
    //difficulty = stoi(tmp);
    
    
    switch(difficulty){
        case 1: 
            p.initialState = p.trivialState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            break;
        case 2: 
            p.initialState = p.veryEasyState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            break;
        case 3: 
            p.initialState = p.easyState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            break;
        case 4: 
            p.initialState = p.doableState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            break;
        case 5: 
            p.initialState = p.ohBoyState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            break;
        case 6: 
            p.initialState = p.impossibleState;
            p.setCurrentState(p.initialState);
            p.printCurrentState();
            break;
            
        default: 
        cout << "Please rerun the program and enter a correct number" << endl;
            break;
}

    return 0;
}