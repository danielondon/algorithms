#include "common.h"

using namespace std;

string convertVectorToString(const std::vector<int> numbers)
{
    ostringstream ssNum;
    for (vector<int>::const_iterator it = numbers.cbegin(); it != numbers.cend(); ++it)
        ssNum<<*it;
    return ssNum.str();
}

bool sortCriteria (int num1, int num2) 
{
    ostringstream ossNum1;
    ostringstream ossNum2;

    ossNum1<<num1<<num2;
    ossNum2<<num2<<num1;
    
    istringstream issNum1(ossNum1.str());
    istringstream issNum2(ossNum2.str());
    
    int num1_num2;
    if ( !(issNum1 >> num1_num2) )
        num1_num2 = 0;
    int num2_num1;
    if ( !(issNum2 >> num2_num1) )
        num2_num1 = 0;
    
    return (num1_num2 > num2_num1);
}

string getMaxNumber(std::vector<int> numbers)
{
    string res = "";
    sort(numbers.begin(), numbers.end(), sortCriteria);
    return convertVectorToString(numbers);
}


// Example 1
// numbers [90, 9, 8]
// res = "9908"

// Example 2
// numbers [59, 5, 8]
// res = "8595"
int main() 
{
    vector<vector<int>> numbersArrayAll = {{90, 9, 8}, {59, 5, 8}};

    for (auto & numbersArray : numbersArrayAll)
    {
        cout << "Numbers Array is " << endl;
        printCollection(numbersArray);;
        string res = getMaxNumber(numbersArray);
        cout<<"Max Number possible is "<<res<<endl;
    }
    return 0;
}
