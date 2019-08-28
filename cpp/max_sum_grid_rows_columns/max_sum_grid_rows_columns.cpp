#include "common.h"
using namespace std;

bool debug = false;

// Sereja and two lines
// Max value of F, where F is the matrix with the max count for the item, in the row and column

enum class Direction
{
    Up,
    Down,
    Left,
    Right,
    All
};

int maxValueOfF(Matrix<int> const& matrix, Coordinates pos, int valueToLookup, Direction direction)
{
    if (!inBounds(pos, matrix))
    {
        return 0;
    }
    int count = 0;
    if (debug)
    {
        cout<<"valueToLookup "<<valueToLookup<< " pos "<<pos.toString()<<endl;
    }

    if (matrix[pos.i][pos.j] == valueToLookup)
    {
        count = 1;
    }

    if (direction == Direction::All || direction == Direction::Up)
        count += maxValueOfF(matrix, goUp(pos), valueToLookup, Direction::Up);
    if (direction == Direction::All || direction == Direction::Down)
        count += maxValueOfF(matrix, goDown(pos), valueToLookup, Direction::Down);
    if (direction == Direction::All || direction == Direction::Left)
        count += maxValueOfF(matrix, goLeft(pos), valueToLookup, Direction::Left);
    if (direction == Direction::All || direction == Direction::Right)
        count += maxValueOfF(matrix, goRight(pos), valueToLookup, Direction::Right) ;
    return count;
}

int maxValueOfF(vector<vector<int>> const& matrix)
{
    if (matrix.empty())
        return 0;

    int maxValue = 0;

    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix.front().size(); ++j)
        {
            int count = maxValueOfF(matrix, {i,j}, matrix[i][j], Direction::All);
            if (debug)
            {
                cout<<"count "<<count<< " i "<<i<<" j "<<j<<endl;
            }
            maxValue = max(maxValue, count);
        }
    }
    return maxValue;
}

int main()
{
    Matrix<int> matrix = {{1,2,1,2,3},
                          {3,4,1,2,3},
                          {1,1,1,1,1},
                          {2,2,2,2,3}}; // Answer 7

    cout<<"Max value in matrix F"<<endl;
    printMatrix(matrix);
    cout<<"Max Value of F is  "<<maxValueOfF(matrix)<<endl;
}
