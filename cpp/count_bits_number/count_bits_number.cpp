#include <iostream>
#include <cmath>

using namespace std;

// Write a function that takes an unsigned integer and returns the number of 1 bits it has


int numSetBits(unsigned int A) {
    if (A <= 0)
        return 0;
    
    int countBits = 1;
    int i = 1;
    // Find the exponential which is the next number greater than A
    // what happens when A is the greatest unsigned int? Used a big number for powOf2
    long long powOf2 = pow(2, i);
    while (A >= powOf2)
    {
        ++i;
        powOf2 = pow(2, i);
    }
    
    --i;
    long long mod = A - pow(2, i);
    while(mod > 0 && i > 0)
    {
        --i;
        powOf2 = pow(2, i);
        //cout<<"mod "<< mod<< " exp "<< i<< " powOf2 "<< powOf2<<endl;
        
        if (mod / powOf2 > 0)
        {
            countBits ++;
            mod -= powOf2;
        }
    }
    
    return countBits;
}


// Print the max sum of the contiguous array
int main()
{
    cout<<"Num of Bits"<<endl<<endl;
 
    unsigned int number = 111593685; // 14
    //unsigned int number = 27; // 4
    auto res = numSetBits(number);
    cout<<"Num of bits in "<<number<<" is: "<<res<<endl;
}
