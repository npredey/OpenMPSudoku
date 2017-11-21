include <stdio.h>

//The value for an unassigned cell
#define UNASSIGNED 0
 
// Size of grid -- This will have to change when we consider 16
#define N 9
 
// This function finds an entry in grid that is still unassigned
bool findUnassignedCell(int grid[N][N], int &row, int &col);
 
// Checks whether it will be legal to assign num to the given row,col
bool isValidMove(int grid[N][N], int row, int col, int num);
 
//Attempt to solve the sudoku the naive way, using backtracking
bool bruteForceSolve(int grid[N][N])
{
    int row, col;
 
    // If there is no unassigned location, we are done
    if (!findUnassignedCell(grid, row, col))
       return true;
 
    for (int num = 1; num <= 9; num++)
    {
        if (isValidMove(grid, row, col, num))
        {
            grid[row][col] = num;

            //call this recursively TODO May change this for parallelization reasons
            if (bruteForceSolve(grid))
                return true;
            //if this is not a valid move, then re-unassign it.
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; // trigger backtracking
}
 
bool findUnassignedCell(int grid[N][N], int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}
 
bool checkRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
bool checkColumn(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}
 
bool checkBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}
 
bool isValidMove(Sudoku grid[N][N], int row, int col, int num)
{
    return !checkColumn(grid, row, num) &&
           !checkRow(grid, col, num) &&
           !checkBox(grid, row - row%3 , col - col%3, num);
}
 
//Print out the grid.
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
       for (int col = 0; col < N; col++)
             printf("%2d", grid[row][col]);
        printf("\n");
    }
}
