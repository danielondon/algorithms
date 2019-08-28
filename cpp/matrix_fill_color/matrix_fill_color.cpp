#include "common.h"
using namespace std;

bool debug = false;

struct ColorResult
{
    Color color = Color::Invalid;
    int amountCells = 0;
};

int getMaxColorInMatrix(const Matrix<Color> & matrix, Coordinates coordinates, Color colorToSearch, unordered_set<Coordinates> & visitedCells)
{
    if (visitedCells.count(coordinates))
        return 0;

    if (!inBounds(coordinates, matrix))
        return 0;

    if (colorToSearch == matrix[coordinates.i][coordinates.j])
    {
        visitedCells.insert(coordinates);
        return 1 + getMaxColorInMatrix(matrix, goUp(coordinates), colorToSearch, visitedCells)
                + getMaxColorInMatrix(matrix, goDown(coordinates), colorToSearch, visitedCells)
                + getMaxColorInMatrix(matrix, goLeft(coordinates), colorToSearch, visitedCells)
                + getMaxColorInMatrix(matrix, goRight(coordinates), colorToSearch, visitedCells);
    }
    else
        return 0;
}

ColorResult getMaxColorInMatrix(const Matrix<Color> & matrix)
{
    if (matrix.empty())
    {
        return  {Color::Invalid, 0 };
    }

    ColorResult colorResult;

    unordered_set<Coordinates> visitedCells;

    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix.front().size(); ++j)
        {
            auto color = matrix[i][j];
            int count = getMaxColorInMatrix(matrix, {i, j}, color, visitedCells);
            if (count > colorResult.amountCells)
            {
                colorResult.amountCells = count;
                colorResult.color = color;
            }
        }
    }

    return colorResult;
}

int main()
{
    // Expected result = Blue(1), count 8
    Matrix<Color> matrix =         {{Color::Red,  Color::Red,  Color::Red,  Color::Green, Color::Green},
                                    {Color::Blue, Color::Blue, Color::Red,  Color::Red,   Color::Green},
                                    {Color::Blue, Color::Blue, Color::Red,  Color::Red,   Color::Green},
                                    {Color::Blue, Color::Blue, Color::Blue, Color::Blue, Color::Green}};

    cout<<"Find the maximum adjancent cells with the same color"<<endl;
    printMatrix(matrix);
    auto result = getMaxColorInMatrix(matrix);
    cout<<"Max color is "<< result.color<<" with "<<result.amountCells<<" cells."<<endl;
}
