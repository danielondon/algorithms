#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator> // for ostream_iterator
#include <algorithm>
#include <stack>
#include <cmath>

using namespace std;

// Print a matrix with a sequence around A

void printMatrix(int ** matrix, size_t size)
{
    for (int i = 0; i < size ; ++i)
    {
        for (int j = 0; j < size ; ++j)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

int getValue(int i, int j, int A)
{
    // Increase i and j, to handle the index based in 1.
    ++i; ++j;
    return max( abs(i - A), abs(j - A) ) + 1;
    
}

int ** getSpecialMatrix(int numberA, size_t & size)
{
    size = numberA * 2 - 1;
    int ** matrix = new int*[size];
    for (int i = 0; i < size; ++i)
        matrix[i] = new int[size];
    
    for (int i = 0; i < size ; ++i)
    {
        for (int j = 0; j < size ; ++j)
        {
            matrix[i][j] = getValue(i, j, numberA);    
        }
    }
    return matrix;
}

int main()
{
    cout<<"Special Print Matrix"<<endl<<endl;
    int numberA = 6;
    cout<<"Number is "<<numberA<<endl;
    size_t size = 0; 
    int ** matrix = getSpecialMatrix(numberA, size);
    cout<<"Matrix is"<<endl<<endl;
    printMatrix(matrix, size);
    
    // Release Memory
    for (int i = 0; i < size; ++i)
        delete [] matrix[i];
    delete [] matrix;
    
    return 0;
}