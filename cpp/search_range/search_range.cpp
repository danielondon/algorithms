#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Given a sorted array of integers, find the starting and ending position of a given target value.
// Your algorithm’s runtime complexity must be in the order of O(log n).
// If the target is not found in the array, return [-1, -1].
// Example:
// Given [5, 7, 7, 8, 8, 10] and target value 8,
// return [3, 4].


void printVector(const vector<int> & numbers)
{
    std::for_each(numbers.cbegin(), numbers.cend(), [] (const int c) {std::cout << c << " ";} );
    cout<<endl;
}

int findNumberBinarySearch(size_t start, size_t end, const vector<int> &A, int valueToSearch, bool checkLeft)
{
    size_t mid = (start + end) / 2;
    if (start >= end )
        return -1;
    
    //cout<<"mid "<<mid<< endl;
    bool goLeft = false;
    if (A[mid] == valueToSearch)
    {
        if (checkLeft)
        {
            if (mid == 0)
                return mid;
            else if (A[mid - 1] < valueToSearch)
                return mid;
            else // Go Left
                goLeft = true;
        }
        else
        {
            if (mid == A.size() - 1)
                return mid;
            else if (A[mid + 1] > valueToSearch)
                return mid;
            
        }
    }

    if (A[mid] > valueToSearch || goLeft)
    {
        // Go Left
        return findNumberBinarySearch(start , mid, A, valueToSearch, checkLeft);
    } 
    else // When is not possible to go left or simply A[mid] < valueToSearch
    {
        // Go Right
        return findNumberBinarySearch(mid+1, end, A, valueToSearch, checkLeft);
    }
}


vector<int> searchRange(const vector<int> &A, int B)
{
    int leftIndex = findNumberBinarySearch(0, A.size(), A, B, true);
    int rightIndex = findNumberBinarySearch(0, A.size(), A, B, false);
    return {leftIndex, rightIndex};
}

// Print the max sum of the contiguous array
int main()
{
    cout<<"Search Range"<<endl<<endl;
    std::vector<int> numbersSorted = {5, 7, 7, 8, 8, 10};
    int valueToSearch = 8;
    //std::vector<int> numbersSorted = {1, 1, 1, 1, 1, 1};
    //int valueToSearch = 1;
    //std::vector<int> numbersSorted = { 4, 7, 7, 7, 8, 10, 10};
    //int valueToSearch = 3;
    //std::vector<int> numbersSorted = { 3 };
    //int valueToSearch = 3;
    //std::vector<int> numbersSorted = git 
    //int valueToSearch = 4;
    //std::vector<int> numbersSorted = { 1, 1, 3, 3};
    //int valueToSearch = 2;
    auto res = searchRange(numbersSorted, valueToSearch);
    cout<<"Vector is: ";
    printVector(numbersSorted);
    cout<<"The range for value "<< valueToSearch<<" is ";
    printVector(res);
}