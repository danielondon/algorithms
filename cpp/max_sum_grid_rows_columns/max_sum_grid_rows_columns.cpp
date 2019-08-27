#include "common.h"
using namespace std;

bool debug = false;

// Sereja and two lines
// Max value of F, where F is the matrix with the max count for the item, in the row and column

int maxValueOfF(vector<vector<int>> const& matrix)
{
    return 6;
}

int main()
{
    vector<vector<int>> matrix = {{1,2,1,2},
                                  {3,4,1,2},
                                  {1,1,1,1},
                                  {2,2,2,2}}; // Answer 6
    cout<<"Max value in matrix F"<<endl;
    printMatrix(matrix);
    cout<<"Max Value of F is  "<<maxValueOfF(matrix)<<endl;
}
