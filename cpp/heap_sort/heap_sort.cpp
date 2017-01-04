// Heap Sort
// avg = nlogn
// Worst = nlogn
// space = 1
// stable = no

#include "common.h"
using namespace std;
bool debug = true;

int findLeftChild(vector<int> const & myArray, int index)
{
    int res =  2*index + 1; 
    if (res >= myArray.size() )
        return -1;
    return res;
}

int findRightChild(vector<int> const & myArray, int index)
{
    int res =  2*index + 2; 
    if (res >= myArray.size() )
        return -1;
    return res;
}

int main()
{
    cout<<"Heap Sort "<<endl<<endl;
    
    vector<int> indexes = { 0, 1, 2, 3, 4, 5, 9, 13 };
    
    for (auto index : indexes)
    {
        vector<int> myArray = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
        
        cout<<"Vector is: ";
        printVector(myArray);
        
        auto leftIndex = findLeftChild(myArray, index);
        auto rightIndex = findRightChild(myArray, index);
        
        if (true)
        {
            cout<<"For node "<<myArray[index]<<" with index "<< index<< " ";
            
            cout<<"left Children is "<<leftIndex;
            if (leftIndex != -1)
                cout<<" with value "<<myArray[leftIndex];
            cout<<" ";
            
            cout<<"and right Children is "<<rightIndex;
            if (rightIndex != -1)
                cout<<" with value "<<myArray[rightIndex];
            cout<<endl;
        }
    }
}