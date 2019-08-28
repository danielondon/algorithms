#include "common.h"
bool debug = false;
using namespace std;

int getAmountOfPossibleCombinations(int desiredSum, const vector<int> & numbers, size_t start, int currentSum)
{
    if (debug)
    {
        cout<<"start "<<start<< " currentSum "<<currentSum<<endl;
    }

    if (currentSum == desiredSum)
        return 1;

    if (currentSum > desiredSum)
        return 0;

    if (start >= numbers.size())
        return 0;

    return getAmountOfPossibleCombinations(desiredSum, numbers, start + 1, currentSum + numbers[start]) +
            getAmountOfPossibleCombinations(desiredSum, numbers, start + 1, currentSum);
}

int getAmountOfPossibleCombinations(int desiredSum, const vector<int> & numbers)
{
    return getAmountOfPossibleCombinations(desiredSum, numbers, 0, 0);
}

// Assume numbers is sorted otherwise sorted first

// Example 1
// desiredSum = 16
// numbers [2, 4, 6, 10]
// res = 2
// 1: {2, 4, 10} 2: {6, 10}

// Example
// {2, 4, 6, 10, 8, 1, 7, 8, 20, 16}
// desiredSum: 16, res = 9
// (4) {2, 4, 10}, {2 , 6 , 8}, {2, 6, 1, 7}, {2, 6, 8}
// (1) {6, 10}
// (2) {8, 1, 7} , {8, ,8}
// (1) {1, 7, 8}
// (1) {16}
int main() {
    int desiredSum = 16;
    //vector<int> numbers = {2, 4, 6, 10};
    vector<int> numbers = {2, 4, 6, 10, 8, 1, 7, 8, 20, 16};
    printCollection(numbers);

    int res = getAmountOfPossibleCombinations(desiredSum, numbers);
    cout << "The amount of sets of numbers that add to "<<desiredSum<<" is: " <<res<< endl;
    return 0;
}
