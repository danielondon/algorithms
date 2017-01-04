//Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. 
//Return the sum of the three integers. 
//You may assume that each input would have exactly one solution.
//
//Example: 
//given array S = {-1 2 1 -4}, 
//and target = 1.

//The sum that is closest to the target is 2. (-1 + 2 + 1 = 2)

// Example:
// A : [ -5, 1, 4, -7, 10, -7, 0, 7, 3, 0, -2, -5, -3, -6, 4, -7, -8, 0, 4, 9, 4, 1, -8, -6, -6, 0, -9, 5, 3, -9, -5, -9, 6, 3, 8, -10, 1, -2, 2, 1, -9, 2, -3, 9, 9, -10, 0, -9, -2, 7, 0, -4, -3, 1, 6, -3 ]
// B : -1

#include "common.h"

using namespace std;

int getSum(vector<int> const & myVector, int i1,  int i2,  int i3)
{
    return myVector[i1] + myVector[i2] + myVector[i3];
}

int find3sum(vector<int> const & myVector, int target)
{
    int i, j, k;
    int i_temp = 0;
    int min_i = abs(myVector[i_temp] - target);
    for (i_temp = 1; i_temp < myVector.size(); ++i_temp)
    {
        if (abs(myVector[i_temp] - target) < min_i)
        {
            min_i = abs(myVector[i_temp] - target);
            i = i_temp;
        }
        if (min_i == 0)
            break;
    }
 
    //for (int j = 0; j < myVector.size() - 1; ++j)
    // Set j and K
    j = (i != 0) ? 0 : 1;
    k = (i != myVector.size() - 1) ? myVector.size() - 1 : myVector.size() - 2;
    cout<<"Starting i "<<i<<" "<<j<<" "<<k<<endl;
    
    int closestSum = getSum(myVector, i, j, k);   
    while ( closestSum != target && j < k)
    {
        if (j != i)
        {
            //for (int k = j + 1; k < myVector.size(); ++k)
            {
                if (k != i)
                {
                    int sum = getSum(myVector, i, j, k);
                    cout<<"Sum is "<<sum<<endl;
                    if (abs(target - sum) < abs(target - closestSum) )
                    {
                        closestSum = sum;
                        cout<<"Closest Sum is "<<sum<< " with "<<myVector[i]<<" "<<myVector[j]<<" "<<myVector[k]<<endl;
                    }
                    
                    if (abs(target - sum) > 0)
                        --k;
                    else
                        ++j;
                }
                else
                    --k;
            }
        }
        else
        {
            ++j;
        }
    }
    return closestSum;
}

int threeSumClosest(vector<int> & A, int B)
{
    // Sort the array
    sort(A.begin(), A.end());
    cout<<"Sorted Array is ";
    printVector(A);
    
    int res = 0;
    if (A.size() > 2)
    {
        res = find3sum(A, B);
    }
    return res;
}

int main()
{
    cout<<"Sum of 3 "<<endl<<endl;
    //std::vector<int> myArray = {-1, 2, 1, -4};
    //int target = 1; // expected 2
    
    //std::vector<int> myArray = {-5, 1, 4, -7, 10, -7, 0, 7, 3, 0, -2, -5, -3, -6, 4, -7, -8, 0, 4, 9, 4, 1, -8, -6, -6, 0, -9, 5, 3, -9, -5, -9, 6, 3, 8, -10, 1, -2, 2, 1, -9, 2, -3, 9, 9, -10, 0, -9, -2, 7, 0, -4, -3, 1, 6, -3};
    //int target = -1; // expected -1
    
    {
        std::vector<int> myArray = { 2, 1, -9, -7, -8, 2, -8, 2, 3, -8 };
        int target = -1; // expected -2
        
        cout<<"Vector is: ";
        printVector(myArray);
        
        cout<<"Target is: "<<target<<endl;
        cout<<"====The Sum of 3 is "<<threeSumClosest(myArray, target)<<endl;
    }
    
    {
        std::vector<int> myArray = { -4, -8, -10, -9, -1, 1, -2, 0, -8, -2 };
        int target = 0; // expected 0
     
        cout<<"Vector is: ";
        printVector(myArray);
        
        cout<<"Target is: "<<target<<endl;
        cout<<"====The Sum of 3 is "<<threeSumClosest(myArray, target)<<endl;
    }
    
    {
        std::vector<int> myArray = {  7, 2, -5, 10, -3, 4, 9, 1, -6, -10 };
        int target = 2; // expected 2
        
        cout<<"Vector is: ";
        printVector(myArray);
        
        cout<<"Target is: "<<target<<endl;
        cout<<"====The Sum of 3 is "<<threeSumClosest(myArray, target)<<endl;
    }
    
    {
        std::vector<int> myArray = {  5, -2, -1, -10, 10 };
        int target = 5; // expected 5
        
        cout<<"Vector is: ";
        printVector(myArray);
        
        cout<<"Target is: "<<target<<endl;
        cout<<"====The Sum of 3 is "<<threeSumClosest(myArray, target)<<endl;
    }
}