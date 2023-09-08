#include <iostream>
#include <vector>

using namespace std;

/* #region Creating Matrix */

/**
 * @brief Create a Matrix object
 *
 * @param rows
 * @param cols
 * @return vector<vector<double>>
 *
 * @complexity O(n^2)
 **/
vector<vector<double>> createMatrix(int rows, int cols)
{
    vector<vector<double>> matrix;

    cout << "Enter the elements of the matrix in this format: 0 0 0 0" << endl;
    for (int i = 0; i < rows; i++)
    {
        vector<double> row(cols);
        cout << "Enter elements for row " << i + 1 << ": ";
        for (int j = 0; j < cols; j++)
        {
            cin >> row[j];
        }
        matrix.push_back(row);
    }

    return matrix;
}

/**
 * @brief Print a Matrix object
 *
 * @param matrix
 *
 * @complexity O(n^2)
 **/
void printMatrix(vector<vector<double>> matrix)
{
    cout << "\nOrginal Matrix:" << endl;
    for (int i = 0; i < matrix.size(); i++)
    {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
/* #endregion */

/* #region Solving Maze Ramification*/

/**
 * @brief Print a Matrix object
 *
 * @param sol
 *
 * @complexity O(n^2)
 **/
void printSolution(vector<vector<double>> sol)
{
    cout << "\nRamification Method:" << endl;
    for (int i = 0; i < sol.size(); i++)
    {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < sol[i].size(); j++)
        {
            cout << sol[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * @brief Check if a cell is safe to move to
 *
 * @param maze
 * @param x
 * @param y
 * @return true
 * @return false
 *
 * @complexity O(1)
 **/
bool isSafe(vector<vector<double>> maze, int x, int y)
{
    if (x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && maze[x][y] == 1)
        return true;
    return false;
}

/**
 * @brief Solve the maze
 *
 * @param maze
 * @return true
 * @return false
 *
 * @complexity O(n^2)
 **/
bool solveMazeUtil(vector<vector<double>> maze, int x, int y, vector<vector<double>> &sol)
{
    if (x == maze.size() - 1 && y == maze[0].size() - 1 && maze[x][y] == 1)
    {
        sol[x][y] = 1;
        return true;
    }

    if (isSafe(maze, x, y) == true)
    {
        if (sol[x][y] == 1)
            return false;

        sol[x][y] = 1;

        if (solveMazeUtil(maze, x + 1, y, sol) == true)
            return true;

        if (solveMazeUtil(maze, x, y + 1, sol) == true)
            return true;

        // If neither of the above recursive calls leads to a solution, backtrack.
        sol[x][y] = 0;
        return false;
    }

    return false;
}

/**
 * @brief Solve the maze
 *
 * @param maze
 * @return true
 * @return false
 *
 * @complexity O(n^2)
 **/
bool solveMaze(vector<vector<double>> maze)
{
    vector<vector<double>> sol(maze.size(), vector<double>(maze[0].size(), 0));

    if (solveMazeUtil(maze, 0, 0, sol) == false)
    {
        cout << "Solution doesn't exist";
        return false;
    }
    printSolution(sol);
    return true;
}
/* #endregion */

/* #region Solving Maze Backtracking*/

/* #endregion */

int main()
{
    /*
    int rows, cols;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    if (rows <= 0 || cols <= 0)
    {
        cout << "Rows and columns must be positive integers." << endl;
        return 1;
    }
    */

    vector<vector<double>> matrix = {
        {1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1},
    };

    vector<vector<double>> matrix2 = {
        {1, 1, 1, 1, 0, 1},
        {1, 1, 0, 1, 1, 1},
        {1, 0, 0, 1, 0, 1},
        {1, 1, 0, 1, 0, 1},
        {0, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 0, 1},
    };

    vector<vector<double>> matrix3 = {
        {1, 0, 0, 1},
        {1, 1, 1, 0},
        {0, 1, 1, 1},
        {1, 0, 0, 1},
    };

    vector<vector<double>> matrix4 = {
        {1, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 0, 0, 0, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1, 1, 0, 1, 1},
        {1, 1, 0, 1, 1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 0, 1},
    };

    cout << "Maze 1:" << endl;
    printMatrix(matrix);
    solveMaze(matrix);

    cout << "--------------------------------------------------" << endl;
    cout << "\nMaze 2:" << endl;
    printMatrix(matrix2);
    solveMaze(matrix2);

    cout << "--------------------------------------------------" << endl;
    cout << "\nMaze 3:" << endl;
    printMatrix(matrix3);
    solveMaze(matrix3);

    cout << "--------------------------------------------------" << endl;
    cout << "\nMaze 4:" << endl;
    printMatrix(matrix4);
    solveMaze(matrix4);

    return 0;
}
