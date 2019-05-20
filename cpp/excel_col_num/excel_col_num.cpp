#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Given a column title as appears in an Excel sheet, return its corresponding column number.

int titleToNumber(string A) {
    int res = 0;
    
    const int startInt = (int)'A';
    const int startIntValue = 1;
    const int endInt = (int)'Z';
    const int endIntValue = 26;
    
    const int offset = startInt - 1;
    const int size = endIntValue - startIntValue + 1;
    const int countCharacters = A.length();
    //cout<<"Amoung of characters "<<countCharacters<<endl;
    //cout<<"Size is "<<size<<endl;
    int i = 1;
    
    for(auto c : A)
    {
        int intRepresentation = (int)c;
        // If invalid character break
        if (intRepresentation < startInt || intRepresentation > endInt)
        {
            res = 0;
            break;
        }
        int realInt = (intRepresentation - offset);
        //cout<<"realInt "<<realInt<<endl;
        res += pow(size, countCharacters - i)*realInt ;
        i++;
    }
    return res;
}

// Print the max sum of the contiguous array
int main()
{
    cout<<"Column Number"<<endl<<endl;
 
    string title = "ACVDZ"; //524706
    //string title = "ABC"; //731
    //string title = "AAA"; //703
    auto res = titleToNumber(title);
    cout<<"Column Title "<<title<< " has a representation of "<<res<<endl;
}
