#include "common.h"

using namespace std;

int getAmountOfPossibleCombinations(int desiredSum, const vector<int> & numbers)
{    
    return 0;
}

// Assume numbers is sorted otherwise sorted first

// Example 1
// desiredSum = 16
// denominaciones [2, 4, 6, 10]
// res = 2
// 1: {2, 4, 10} 2: {6, 10}

int main() {
    int desiredSum = 6;
    vector<int> numbers = {2, 4, 6, 10};
    printCollection(numbers);

    int res = getAmountOfPossibleCombinations(desiredSum, numbers);
    cout << "The amount of sets of numbers that add to "<<desiredSum<<" is: " <<res<< endl;
    return 0;
}
