#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator> // for ostream_iterator
#include <algorithm>
#include <stack>
#include <cmath>

using namespace std;

// Calculate the prime numbers that sum to X
// X is even number greater than two)

bool isPrime(int n)
{
    if (n < 1)
        return false;
    if (n == 1 || n ==2)
        return true;
    // All even numbers greater than two are not prime
    if (n % 2 == 0)
        return false;
    
    int checkLimit = sqrt(n) + 1;
    
    for (int i = 3; i < checkLimit; i+=2)
    {
        if (n % i == 0)
            return false;
    }
    
    return true;
}

bool getSumOfPrimeNumbers(int number, int & firstPrimeNumber, int & secondPrimeNumber)
{
    if (number <= 2 || number % 2 != 0)
        return false;
    
    secondPrimeNumber = 0;
    firstPrimeNumber = 0;
    
    // We start at 3
    int checkLimit = number / 2;
    for (int i = 3; i < checkLimit; i+=2)
    {
        int res = number - i;
        if (isPrime(i) && isPrime(res))
        {
            firstPrimeNumber = i;
            secondPrimeNumber = res;
            return true;
        }
    }
    
    return false;
}


int main()
{
    cout<<"Sum of primes are X (X is even number greater than two)"<<endl<<endl;
    int number = 187654;
    int firstPrimeNumber, secondPrimeNumber;
    cout<<"Number is "<< number<<endl;
    
    bool res = getSumOfPrimeNumbers(number, firstPrimeNumber, secondPrimeNumber);
    if (res)
        cout<<"The two prime numbers are "<<firstPrimeNumber<<" + "<<secondPrimeNumber<<endl;
    else
        cout<<"The number "<<number<<" is not even or is not greater than two"<<endl;
        
    return 0;
}