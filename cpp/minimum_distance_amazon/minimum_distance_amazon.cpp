#include "common.h"
using namespace std;

bool debug = false;
// INCLUDE HEADER FILES NEEDED BY YOUR PROGRAM
// SOME LIBRARY FUNCTIONALITY MAY BE RESTRICTED
// DEFINE ANY FUNCTION NEEDED
const int DESTINATION = 9;
const int ACCESIBLE = 1;
const int INACCESIBLE = 0;

int findMinimumDistance(int numRows, int numColumns, const Matrix<int> & area, Position pos, unordered_set<Position> & visitedCells)
{
    if (!inBounds(pos, numRows, numColumns))
    {
        return std::numeric_limits<int>::min();
    }
    
    if (visitedCells.count(pos))
        return std::numeric_limits<int>::min();

    visitedCells.insert(pos);
    
    if (area[pos.i][pos.j] == INACCESIBLE)
        return std::numeric_limits<int>::min();
        
    if (area[pos.i][pos.j] == DESTINATION)
    {
        return 1;
    }
    
    if (area[pos.i][pos.j] == ACCESIBLE)
    {
        int countLeft = 1 + findMinimumDistance(numRows, numColumns, area, pos.goLeft(), visitedCells);
        int countRight = 1 + findMinimumDistance(numRows, numColumns, area, pos.goRight(), visitedCells);
        int countUp = 1 + findMinimumDistance(numRows, numColumns, area, pos.goUp(), visitedCells);
        int countDown = 1 + findMinimumDistance(numRows, numColumns, area, pos.goDown(), visitedCells);
        
        return max(-1, max(countLeft,
                    max(countRight,
                        max(countUp, countDown)
                    )
                ));
    }
    
    return std::numeric_limits<int>::min();
}

bool isCellAccessible(Position pos, const Matrix<int> & area)
{
    if(inBounds(pos, area) && (area[pos.i][pos.j] == ACCESIBLE || area[pos.i][pos.j] == DESTINATION))
        return true;
    return false;
}

bool isPositionIsolated(Position pos, const Matrix<int> & area)
{
    // Check if the pos is ACCESSIBLE
    if (!isCellAccessible(pos, area))
    {
        return false;
    }

    int countAdjacentCells = 0;

    // Check adjacent cells
    if (isCellAccessible(pos.goLeft(), area))
        ++countAdjacentCells;
    if (isCellAccessible(pos.goRight(), area))
        ++countAdjacentCells;
    if (isCellAccessible(pos.goUp(), area))
        ++countAdjacentCells;
    if (isCellAccessible(pos.goDown(), area))
        ++countAdjacentCells;

    if(countAdjacentCells == 0)
        return true;
    return false;
}

// FUNCTION SIGNATURE BEGINS, THIS FUNCTION IS REQUIRED
int minimumDistance(int numRows, int numColumns, Matrix<int> area)
{
    // WRITE YOUR CODE HERE
    int minDistance = -1;
    
    int countStores = 0;
    int countDestinations = 0;


    unordered_set<Position> visitedCells;
    for (int i = 0; i < numRows; ++i)
    {
        for(int j = 0; j < numColumns; ++j)
        {
            Position pos = {i, j};

            if (area[pos.i][pos.j] == DESTINATION || area[pos.i][pos.j] == ACCESIBLE)
            {
                if (isPositionIsolated(pos, area))
                {
                    return -1;
                }
                if(area[pos.i][pos.j] == DESTINATION)
                {
                    ++countStores;
                }
                else
                {
                    ++countDestinations;
                }
            }

            int distance = findMinimumDistance(numRows, numColumns, area, pos,  visitedCells);
            if (distance > 0)
                minDistance = min(minDistance, distance);
        }
    }
    
    return minDistance;
}
// FUNCTION SIGNATURE ENDS

int main()
{
    Matrix<int> area = {{0, 0, 0, 0},
                        {1, 0, 0, 0},
                        {1, 0, 0, 0},
                        {1, 9, 0, 0}};
/*
    Matrix<int> area = {{1, 1, 0, 0},
                        {1, 1, 0, 0},
                        {1, 0, 0, 0},
                        {1, 0, 0, 0},
                        {1, 9, 0, 0}};*/


    cout<<"Find the maximum adjancent cells with the same color"<<endl;
    printMatrix(area);
    auto result = minimumDistance(area.size(), area.front().size(), area);
    cout<<"MInimum distance is "<< result <<endl;
}
