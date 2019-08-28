#include "common.h"
using namespace std;

bool debug = false;



size_t rearrangeArray(vector<int> & myArray, size_t startIndex, size_t endIndex)
{
    for (auto i = startIndex; i < endIndex;)
    {
        // Set greater elements to the right
        if (myArray[i] > myArray[endIndex])
        {
            // Create space to the right, swappint with adjacent position
            swap(myArray[endIndex], myArray[endIndex - 1]);
            // Avoid double swapping
            if (i != (endIndex - 1))
                // Swap position with element
                swap(myArray[endIndex], myArray[i]);
            // move end
            --endIndex;
        }
        else
        {
            // move to next element
            ++i;
        }
        if (debug)
        {
            printVector(myArray);
        }
    }

    return endIndex;
}

int maxNthElement(vector<int> & myArray, size_t start, size_t end, size_t nth)
{
    size_t index = rearrangeArray(myArray, start, end);
    if (debug)
    {
        printVector(myArray);
        cout<<"index "<<index<<" start "<<start<<" end "<<end<<endl;
    }

    if((index + 1) > nth)
    {
        return maxNthElement(myArray, start, index - 1, nth);
    }
    else if((index + 1) < nth)
    {
        return maxNthElement(myArray, index + 1, end, nth);
    }

    return myArray[index];
}

int maxNthElement(vector<int> myArray, size_t nth)
{
    return maxNthElement(myArray, 0, myArray.size() - 1, nth);
}

int main()
{
    vector<int> elements = { 10, 2, 5, 6, 11, 3, 15};
    auto n = 5;
    cout<<"*****"<<endl;
    printVector(elements);
    cout<<"Max "<<n<<"th element is "<<maxNthElement(elements, n)<<endl;
}
