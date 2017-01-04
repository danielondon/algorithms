
// Merge Sort
// avg = nlogn
// worst = nlogn
// space = n
// stable = yes


#include "common.h"

using namespace std;

bool debug = false;

void copy(vector<int> & source, vector<int> & destination, int start, int end)
{
    for (int i = start; i < end; ++i)
        destination[i] = source[i];
}

void merge(vector<int> & myArray, vector<int> & auxArray, int start, int end, int middle)
{
    if (debug)
    {
        cout<<"Start index is "<<start<<endl;
        cout<<"End index is "<<end<<endl;
        cout<<"Mid index is "<<middle<<endl;
    }
    
    int i = start;
    int j = middle;
    for (int k = start; k < end; ++k)
    {
		if (i < end && j < end)
		{
			// Copy Left, when left has not overrun and when left item is lower
			//  than item from right. Also when right has overrun.
			if ((myArray[i] < myArray[j] || j >= end) && i < middle)
			{
				auxArray[k] = myArray[i];
				++i;
			}
			else
			{
				auxArray[k] = myArray[j];
				++j;
			}
		}
    }
}

void mergeSort(vector<int> & myArray, vector<int> & auxArray, int start, int end)
{
    // when size is 1 or 0
    if (end - start < 2)
        return;
    
    int middle = (start + end) / 2;
    mergeSort(myArray, auxArray, start, middle);
    mergeSort(myArray, auxArray, middle, end);
    merge(myArray, auxArray, start, end, middle);
    copy(auxArray, myArray, start, end);

    if (debug)
    {
        cout<<"AuxArray is: ";
        printVector(auxArray);
        cout<<"Array is: ";
        printVector(myArray);
    }
}

void mergeSort(vector<int> & myArray)
{
    vector<int> auxArray(myArray.size());
    mergeSort(myArray, auxArray, 0, myArray.size());
}


int main()
{
    cout<<"Merge Sort "<<endl<<endl;
    
    {
        vector<int> myArray = { 2, 1, -9, -7, -8, 2, -8, 2, 3, -8 };
        
        cout<<"Vector is: ";
        printVector(myArray);
        
        mergeSort(myArray);
        
        cout<<"Vector is: ";
        printVector(myArray);
    }
}