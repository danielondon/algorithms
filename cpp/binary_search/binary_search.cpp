
#include "common.h"

using namespace std;

bool debug = false;

bool binarySearch(vector<int> myArray, int element, int start, int end)
{
    if (start > end)
        return false;
    int midIndex = (start + end) / 2;
    
    if (debug)
    {
        cout<<"Start index is "<<start<<endl;
        cout<<"End index is "<<end<<endl;
        cout<<"Mid index is "<<midIndex<<endl;
    }
    
    if (myArray[midIndex] == element)
        return true;
    
    if (element > myArray[midIndex])
        return binarySearch(myArray, element, midIndex + 1, end);
    else
        return binarySearch(myArray, element, start, midIndex - 1);
}


int main()
{
    cout<<"Binary Search "<<endl<<endl;
    auto elementsToFind = { -9, -7, 6, -8, 0};
    
    for (auto elementToFind : elementsToFind)
    {
        vector<int> myArray = { 2, 1, -9, -7, -8, 2, -8, 2, 3, -8, 6 };
        sort(myArray.begin(), myArray.end());
        
        cout<<"Vector is: ";
        printVector(myArray);
        
        cout<<"Element "<<elementToFind;
        
        bool found = binarySearch(myArray,  elementToFind, 0, myArray.size());
        if (found)
            cout<<" founded."<<endl;
        else 
            cout<<" not founded."<<endl;
    }
}