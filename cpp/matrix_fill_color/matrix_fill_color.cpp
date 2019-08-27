#include "common.h"
using namespace std;

bool debug = false;

struct ColorResult
{
    int color;
    int amountCells;
};

ColorResult getMaxColorInMatrix(vector<vector<int>> & matrix)
{
    return { 0, 2 };
}

int main()
{
    vector<vector<int>> matrix = {{0,0,0,2,2},
                                  {1,1,0,0,2},
                                  {1,1,0,0,0},
                                  {1,1,1,2,2}};
    cout<<"Find the maximum adjancent cells with the same color"<<endl;
    printMatrix(matrix);
    auto result = getMaxColorInMatrix(matrix);
    cout<<"Max color is "<< result.color<<" with "<<result.amountCells<<" cells."<<endl;
}
