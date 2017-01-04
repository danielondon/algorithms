#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;


// In the classic problem of the Towers of Hanoi, you have 3 rods and N disks of different
// sizes which can slide onto any tower The puzzle starts with disks sorted in ascending
// order of size from top to bottom (e g , each disk sits on top of an even larger one) You
// have the following constraints:
// (A) Only one disk can be moved at a time 
// (B) A disk is slid off the top of one rod onto the next rod 
// (C) A disk can only be placed on top of a larger disk 

// Following solution tries to map the possibilities of move as a state machine
//  to avoid as well to enter in an infinite set of movemenst that cancel each other
// e.g move from tower 1 to 2, then from tower 2 to 1, then from tower 1 to 2, etc...

// Change the value MAX_VALUE_TOWER to try different rings in the hanoi towers

const int MAX_VALUE_TOWER = 9;

// THIS MUST NOT BE CHANGE. HANOI towers are alwazs 3
const int AMOUNT_TOWERS = 3;
static int amountCalls;

void printTower(stack<int> tower)
{
    cout<<"From Top to Bottom: ";
    while(!tower.empty())
    {
        cout<<tower.top()<< " ";
        tower.pop();
    }
    cout<<endl;
}

bool moveFromTower_i_ToTower_j(stack<int> towers [], int i_source, int i_target)
{
   // if tower 1 is empty
    if (towers[i_source].empty())
        return false;
    
    // if tower 2 not is empty, check that value will be inserted is not greater
    // than the current top
    if (!towers[i_target].empty())
        if (towers[i_source].top() > towers[i_target].top())
            return false;
    
    towers[i_target].push(towers[i_source].top());
    towers[i_source].pop();
    
    return true; 
}

// State 1
//int moveFromTower1ToTower2(stack<int> towers [])
int case1(stack<int> towers [])
{
    if ( moveFromTower_i_ToTower_j(towers, 0, 1))
        return 1;
    return -1;
}

// State 2
//int moveFromTower2ToTower3(stack<int> towers [])
int case2(stack<int> towers [])
{
    if ( moveFromTower_i_ToTower_j(towers, 1, 2))
        return 2;
    return -1;
}

// State 3
//int moveFromTower3ToTower2(stack<int> towers [])
int case3(stack<int> towers [])
{
    if ( moveFromTower_i_ToTower_j(towers, 2, 1))
        return 3;
    return -1;
}

// State 4
//int moveFromTower2ToTower1(stack<int> towers [])
int case4(stack<int> towers [])
{
   if ( moveFromTower_i_ToTower_j(towers, 1, 0))
        return 4;
    return -1;
}

void hanoi(stack<int> towers [], int currentState)
{
    amountCalls++;
    // If tower 1 is empty and one of the others is also empty
    // Or in other words, one of the others two contain all elements
    if (towers[1].size() == MAX_VALUE_TOWER || towers[2].size() == MAX_VALUE_TOWER)
        return;
    
    if (currentState == 0)
    {
        // state 1
        currentState = case1(towers);
    } else if (currentState == 1)
    {
        currentState = case2(towers);
        if (currentState == -1)
            currentState = case3(towers);
    } else if (currentState == 2)
    {
        currentState = case1(towers);
        if (currentState == -1)
            currentState = case4(towers);
            
    } else if (currentState == 3)
    {
        currentState = case1(towers);
        if (currentState == -1)
            currentState = case4(towers);
    } else if (currentState == 4)
    {
        currentState = case2(towers);
        if (currentState == -1)
            currentState = case3(towers);
    }
    
    if (currentState != -1)
        hanoi(towers, currentState);
    else 
        cout<<"ERROR"<<endl;
}

// KNOWN ISSUES: Stack overflow when MAX_VALUE_TOWER = 10

int main ()
{
    amountCalls = 0;
    cout<<"Hanoi"<<endl;
    stack<int> towers[AMOUNT_TOWERS];
    
    // Create the first hanoi tower
    for ( int i = MAX_VALUE_TOWER; i > 0 ; --i)
        towers[0].push(i);
        
    hanoi( towers, 0);
    
    for (int i = 0; i < AMOUNT_TOWERS; ++i)
    {
        cout<<"Tower " << i<< " ";
        printTower(towers[i]);
    }
    
    cout<<endl<<"Amount Calls "<< amountCalls<<endl;
    
}