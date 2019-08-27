#include <iostream>
#include <vector>
#include <iterator> // for ostream_iterator
#include <algorithm>
#include <cmath>

using namespace std;

// Print all factors of a number

void printVector(const vector<int> & numbers)
{
    //for (int i : numbers)
    //    cout << i << " ";
    //std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::for_each(numbers.cbegin(), numbers.cend(), [] (const int c) {std::cout << c << " ";} );
    cout<<endl;
}

vector<int> allFactors(int A)
{
    vector<int> factors;
    if (A > 0)
	{
        int limit = sqrt(A);
        int i = 2; 
        for (; i <= limit; ++i)
        {
            if ( A % i == 0){
                int offset = ceil(factors.size() / 2);
                auto itPos = factors.begin() + offset;
                int divisor =  A / i;
                factors.insert(itPos,  i);
                if (divisor != i)
                {
                    itPos = factors.begin() + offset + 1;
                    factors.insert(itPos, divisor);
                }
            }            
        }
        
        factors.insert(factors.begin(), 1);
        if (A > 1)
            factors.push_back(A);
    }
    return factors;
    
}

int main()
{
	int number = 144;
    cout<<"Factors for "<<number<<endl;
 
    auto res = allFactors(number);
    printVector(res);
}
