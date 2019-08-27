#include "common.h"
using namespace std;

bool debug = false;

// Get MAx sum of a contiguous subarray

// 4  3  -5  5   1     = [4 3  -5  5  1]
// 4  3  -5  3   1     = [4 3]
//-2  5   6 -7  10  -1 = [5 6 -7 10]
//-2  3  -1  5  -1  10 = [3 -1 5 -1 10]
//-2  5   6 -11 10 -1  = [5 6]
//-2  5   6  12 10 -1  = [5 6 12 10]
// 5 -1  -1 -2  5


int maxSubArray(const std::vector<int> & A)
{
    int maxSum = INT_MIN;
    map<int, int> currentSumPerIndex;
    size_t size = A.size();
    
    for (int i = 0; i < size; ++i)
    {
        // Get Current Value
    	int currentValue = A[i];
    	// Set Current Sum at index
    	// Do not discard negatives, because we need to consider
    	// when all values are negative
    	currentSumPerIndex[i] = currentValue;
    	
    	auto it = currentSumPerIndex.begin();
        auto endIter = currentSumPerIndex.end();

        // Update Other Hypothesis
    	for(; it != endIter;)
    	{
    	    bool toDelete = false;
    	    // Check sum only for other values than current index
    	    // Increase Current Value 
    	    if (it->first != i)
		        it->second += currentValue;
		
			// Check if is greater than zero, then discard hypothesis
			if (it->second < 0)
				toDelete = true;
		    
		    // Check Max Sum
		    if (it->second > maxSum)
        		maxSum = it->second;
        	
        	// Delete Item or increase it
        	if (toDelete)
        	    currentSumPerIndex.erase(it++);
        	else
        	    ++it;
        }
        if (debug)
            cout<<"Size Map "<< currentSumPerIndex.size()<<endl;
    }
    
    return maxSum;
}

int maxSubArray2(const std::vector<int> & myArray)
{
    auto currentSum = myArray.front();
    auto maxSum = currentSum;
    auto possibleMaxSum = maxSum;
    for (size_t i = 1; i < myArray.size(); ++i)
    {
        auto currentValue = myArray[i];
        if (currentSum < 0)
        {
            currentSum = currentValue;
            possibleMaxSum = currentSum;
        }
        else
        {
            currentSum += currentValue;
            possibleMaxSum += currentValue;
        }

        maxSum = max(max(maxSum, currentSum), possibleMaxSum);

        if (currentValue < 0)
        {
            if (possibleMaxSum < 0)
            {
                // preserve hypothesis
                possibleMaxSum =  min(0, maxSum);
            }
            currentSum = min(0, maxSum);
        }
    }

    return maxSum;
}

// Print the max sum of the contiguous array
int main()
{
    cout<<"Max Sum of Array"<<endl<<endl;
 
    vector< vector<int> > testNumbers;
    testNumbers.push_back({4,3,-5,5,1}); // 8
    testNumbers.push_back({4,3,-9,3,1}); // 7
    testNumbers.push_back({-2,5,6,-7,10,-1}); // 14
    testNumbers.push_back({-2,3,-1,5,-1,10}); // 16
    testNumbers.push_back({-2,5,6,-11,10,-1}); // 11
    testNumbers.push_back({-2,5,6,-12,10,-1}); // 11
    testNumbers.push_back({5,-1,-1,-2,5}); // 6
    testNumbers.push_back({-2,1,-3,4,-1,2,1,-5,4}); //6
    testNumbers.push_back({-2,-1,-3,-4,-1,-2,-1,-5,-4}); //-1
    testNumbers.push_back({10,-1, 4, -1, 1, -1, 4});


    for (auto const & listNumbers : testNumbers)
    {
        printVector(listNumbers);
        cout<< "Max sum is: "<<maxSubArray(listNumbers)<<endl;
        cout<< "Max sum is: "<<maxSubArray2(listNumbers)<<endl;
    }
    return 0;
}
