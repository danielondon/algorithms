#include "common.h"

using namespace std;

int getAmountOfPossibleCombinations(int desiredSum, vector<int> denominaciones, int currentSum)
{
    if (currentSum > desiredSum)
        return 0;
        
    if (currentSum == desiredSum)
    {
        return 1;
    }
    
    int res = 0 ;
    for (vector<int>::iterator it = denominaciones.begin(); it != denominaciones.end(); ++it)
    {
        res += getAmountOfPossibleCombinations(desiredSum, vector<int>(it, denominaciones.end()), currentSum + *it);
    }
    
    return res;
}

// Assume denominaciones is sorted otherwise sorted first

// Example 1
// desiredSum = 5
// denominaciones [1, 2, 3]
// res = 5
// 1: 5x1 2: 3x1 + 1x2 3: 2x1 + 1x3 4: 1x1 + 2x2 5: 1x2 + 1x3

// Example 2
// desiredSum = 6
// denominaciones [1, 2, 3]
// res = 7
// 1: 6x1 2: 4x1 + 1x2 3: 3x1 + 1x3 4: 2x1 + 2x2 5: 1x1 + 1x2 + 1x3 6: 3x2 7: 2x3 
int main() {
    int desiredSum = 6;
    int denominacionesArray[] = {1,2,3};
    vector<int> denominaciones(denominacionesArray, denominacionesArray + sizeof(denominacionesArray) / sizeof(int) );
    int res = getAmountOfPossibleCombinations(desiredSum, denominaciones, 0);
	
	cout << "Denominaciones son: " << endl;
	printCollection(denominacionesArray);
    cout<<"Numero of possible denominaciones for "<< desiredSum <<" is "<<res<<endl;
    
}
