
// Quick Sort
// avg = nlogn
// Worst = n^2
// space = n
// stable = no

#include "common.h"
using namespace std;
bool debug = false;

int partition(vector<int> & myArray, int start, int end)
{
    int pivotIndex = end - 1;    
    for (int j = start; j < pivotIndex;)
    {
        if ( myArray[j] >  myArray[pivotIndex])
        {
            swap(myArray[pivotIndex], myArray[pivotIndex - 1]);
            if ( j != (pivotIndex - 1)) // avoid swapping again
                swap(myArray[pivotIndex], myArray[j]);
            --pivotIndex;
        }
        else
        {
            ++j;
        }
        
        if (debug)
        {
            cout<<"j "<< j<< " pivotIndex "<< pivotIndex<< endl;
            printVector(myArray);
        }
    }

    if (debug)
    {
        cout<<"Start index is "<<start<<endl;
        cout<<"End index is "<<end<<endl;
        cout<<"Partition ";
        printVector(myArray);
    } 

    return pivotIndex;
}

void quickSort(vector<int> & myArray, int start, int end)
{
    if (start < end)
    {
        int pivot = partition(myArray, start, end);
        if (debug)
        {
            cout<<"Pivot "<< pivot<<endl;
        }
        quickSort(myArray, start, pivot);
        quickSort(myArray, pivot + 1, end);
        
    }
}

void quickSort(vector<int> & myArray)
{
    vector<int> auxArray(myArray.size());
    quickSort(myArray, 0, myArray.size());
}


int main()
{
    cout<<"Quick Sort "<<endl<<endl;
    
    {
        vector<int> myArray = { 2, 1, -9, -7, 0, 5, 1, -8, -20, 2, -8, 2, 3, -8 };
        
        cout<<"Vector is: ";
        printVector(myArray);
        
        quickSort(myArray);
        
        cout<<"Vector is: ";
        printVector(myArray);
    }
}
