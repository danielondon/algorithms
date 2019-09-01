// Heap Sort
// avg = nlogn
// Worst = nlogn
// space = 1
// stable = no

#include "common.h"
using namespace std;
bool debug = false;

int findLeftChild(vector<int> const & myArray, int index)
{
    int res =  2*index + 1; 
    if (res >= myArray.size() )
        return -1;
    return res;
}

int findRightChild(vector<int> const & myArray, int index)
{
    int res =  2*index + 2; 
    if (res >= myArray.size() )
        return -1;
    return res;
}

void heapify(vector<int> & heap, int size, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < size && heap[l] > heap[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < size && heap[r] > heap[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(heap[i], heap[largest]);

        // Recursively heapify the affected sub-tree
        heapify(heap, size, largest);
    }
}

int main()
{
    cout<<"Heap Sort "<<endl<<endl;

    vector<int> myArray = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

    cout<<"Vector is: ";
    printVector(myArray);

    for (int i = myArray.size() / 2 - 1; i >= 0; --i)
    {
        heapify(myArray, myArray.size(), i);
    }
    cout<<"heap: "<<endl;
    printAsBinaryTree(myArray);

    if (debug)
    {
        for (int index = 0; index < myArray.size(); ++index)
        {
            auto leftIndex = findLeftChild(myArray, index);
            auto rightIndex = findRightChild(myArray, index);

            cout<<"For node "<<myArray[index]<<" with index "<< index<< " ";
            
            cout<<"left Children is "<<leftIndex;
            if (leftIndex != -1)
                cout<<" with value "<<myArray[leftIndex];
            cout<<" ";
            
            cout<<"and right Children is "<<rightIndex;
            if (rightIndex != -1)
                cout<<" with value "<<myArray[rightIndex];
            cout<<endl;
        }
    }
    cout<<endl;
}
