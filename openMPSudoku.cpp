#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "SudokuGrid.h"
#include "my_timer.h"

using namespace std;

SudokuGrid::SudokuGrid() {
	//set board to all zeroes. This causes the print function below to print out '.'
	//OR swap to read in files to grid directly for testing
	for (int y=0; y<9; y++) {
		for (int x=0; x<9; x++) {
			board[x][y] = 0;
		}
	}
}

//Reads a two dimensional matrix into the grid
void SudokuGrid::readArray(int b[][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << "Reading value: " << b[i][j] << endl;
            board[i][j] = b[i][j];
        }
    }
}

/*void SudokuGrid::readStringToBoard(std::string board) {
    if (board.length() != 81) {
        return -1;
    }
    for (int i = 0; i < 81; i+=8) {
        
    }
}*/

//TODO fix print for various sizes, right now only works for 9x9 sudoku puzzle
void SudokuGrid::print() {
	//for every row
    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0) {
            std::cout << "-------------------------------" << std::endl;
        }
        for (int col = 0; col < 9; col++) {
            if (col % 3 == 0) {
                std::cout << "|";
            }
            if (board[row][col] != 0) {
                std::cout << " " << board[row][col] << " ";
            } else {
                std::cout << " . ";
            }
        }
        // Draw columns between blocks
        std::cout << "|" << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

void SudokuGrid::writeCellValue(int row, int col, int value) {
  board[row][col] = value;
}

int SudokuGrid::readCellValue(int row, int col) {
	return board[row][col];
}

//Nick's Code Merge

bool findUnassignedCell(SudokuGrid* grid, int &row, int &col)
{
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (grid->readCellValue(row,col) == 0)
                return true;
    return false;
}

bool checkRow(SudokuGrid* grid, int row, int num)
{
    for (int col = 0; col < 9; col++)
        if (grid->readCellValue(row,col) == num)
            return true;
    return false;
}

bool checkColumn(SudokuGrid* grid, int col, int num)
{
    for (int row = 0; row < 9; row++)
        if (grid->readCellValue(row,col) == num)
            return true;
    return false;
}

bool checkBox(SudokuGrid* grid, int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid->readCellValue(row+boxStartRow,col+boxStartCol) == num)
                return true;
    return false;
}

bool isValidMove(SudokuGrid* grid, int row, int col, int num)
{
    return !checkRow(grid, row, num) &&
    !checkColumn(grid, col, num) &&
    !checkBox(grid, row - row%3 , col - col%3, num);
}

bool bruteForceSolve(SudokuGrid* grid, int &numAttempts)
{
    int row, col;
 
    // If there is no unassigned location, we are done
    if (!findUnassignedCell(grid, row, col))
       return true;
    //this loop are the actual values to consider entering in the grid
    for (int num = 1; num <= 9; num++)
    {
        numAttempts++;
        if (isValidMove(grid, row, col, num)) {
            
            //we want to write the cell value here, tentatively, because the move is valid. this is sort of the basis for the backtracking because we are making an educated guess that the value will work, based solely off the fact that it is a valid move. this does not mean it will remain valid, though.
            
            grid->writeCellValue(row,col,num);

            //call this recursively TODO May change this for parallelization reasons
            if (bruteForceSolve(grid, numAttempts))
                return true;
            
            //we make the recursive call. afterwards, if it doesn't return true, then we know that the tentative assignment above was incorrect. so, we set it back to 0 and move on.
            grid->writeCellValue(row, col, 0);
            //grid->print();
        }
    }
    return false; // trigger backtracking
}
 

int main (int argc, char * const argv[]) {
	SudokuGrid puzzle;

	//myfile.open("data/cleanedUpFiles/xab");
	//char ch;
	//fstream fin("data/cleanedUpFiles/xaa", fstream::in);
	//while (fin >> noskipws >> ch) {
	//    cout << ch; // Or whatever I need this to do
	// 	puzzle.writeCellValue(0,0,ch); }

	// code to set values on grid to the test boards starting values. Not implemented fully.
	//example below sets value 5 to the cell with coordinates (0,0)
	//this requires the initialized default for SudokuGrid puzzle to be all zeroes at every location
	//puzzle.writeCellValue(0,0,5);
	/*puzzle.writeCellValue(0,0,0);
	puzzle.writeCellValue(1,0,0);
	puzzle.writeCellValue(2,0,3);
	puzzle.writeCellValue(3,0,0);
	puzzle.writeCellValue(4,0,2);
	puzzle.writeCellValue(5,0,0);
	puzzle.writeCellValue(6,0,6);
	puzzle.writeCellValue(7,0,0);
	puzzle.writeCellValue(8,0,0);
	puzzle.writeCellValue(0,1,9);
	puzzle.writeCellValue(1,1,0);
	puzzle.writeCellValue(2,1,0);
	puzzle.writeCellValue(3,1,3);
	puzzle.writeCellValue(4,1,0);
	puzzle.writeCellValue(5,1,5);
	puzzle.writeCellValue(6,1,0);
	puzzle.writeCellValue(7,1,0);
	puzzle.writeCellValue(8,1,1);
	puzzle.writeCellValue(0,2,0);
	puzzle.writeCellValue(1,2,0);
	puzzle.writeCellValue(2,2,1);
	puzzle.writeCellValue(3,2,8);
	puzzle.writeCellValue(4,2,0);
	puzzle.writeCellValue(5,2,6);
	puzzle.writeCellValue(6,2,4);
	puzzle.writeCellValue(7,2,0);
	puzzle.writeCellValue(8,2,0);
	puzzle.writeCellValue(0,3,0);
	puzzle.writeCellValue(1,3,0);
	puzzle.writeCellValue(2,3,8);
	puzzle.writeCellValue(3,3,1);
	puzzle.writeCellValue(4,3,0);
	puzzle.writeCellValue(5,3,2);
	puzzle.writeCellValue(6,3,9);
	puzzle.writeCellValue(7,3,0);
	puzzle.writeCellValue(8,3,0);
	puzzle.writeCellValue(0,4,7);
	puzzle.writeCellValue(1,4,0);
	puzzle.writeCellValue(2,4,0);
	puzzle.writeCellValue(3,4,0);
	puzzle.writeCellValue(4,4,0);
	puzzle.writeCellValue(5,4,0);
	puzzle.writeCellValue(6,4,0);
	puzzle.writeCellValue(7,4,0);
	puzzle.writeCellValue(8,4,8);
	puzzle.writeCellValue(0,5,0);
	puzzle.writeCellValue(1,5,0);
	puzzle.writeCellValue(2,5,6);
	puzzle.writeCellValue(3,5,7);
	puzzle.writeCellValue(4,5,0);
	puzzle.writeCellValue(5,5,8);
	puzzle.writeCellValue(6,5,2);
	puzzle.writeCellValue(7,5,0);
	puzzle.writeCellValue(8,5,0);
	puzzle.writeCellValue(0,6,0);
	puzzle.writeCellValue(1,6,0);
	puzzle.writeCellValue(2,6,2);
	puzzle.writeCellValue(3,6,6);
	puzzle.writeCellValue(4,6,0);
	puzzle.writeCellValue(5,6,9);
	puzzle.writeCellValue(6,6,5);
	puzzle.writeCellValue(7,6,0);
	puzzle.writeCellValue(8,6,0);
	puzzle.writeCellValue(0,7,8);
	puzzle.writeCellValue(1,7,0);
	puzzle.writeCellValue(2,7,0);
	puzzle.writeCellValue(3,7,2);
	puzzle.writeCellValue(4,7,0);
	puzzle.writeCellValue(5,7,3);
	puzzle.writeCellValue(6,7,0);
	puzzle.writeCellValue(7,7,0);
	puzzle.writeCellValue(8,7,9);
	puzzle.writeCellValue(0,8,0);
	puzzle.writeCellValue(1,8,0);
	puzzle.writeCellValue(2,8,5);
	puzzle.writeCellValue(3,8,0);
	puzzle.writeCellValue(4,8,1);
	puzzle.writeCellValue(5,8,0);
	puzzle.writeCellValue(6,8,3);
	puzzle.writeCellValue(7,8,0);
	puzzle.writeCellValue(8,8,0);
	puzzle.writeCellValue(0,0,0);*/

    int grid[9][9] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    
    int attempts;
    
    puzzle.readArray(grid); //read from the grid above, or any other grid we define
	//print grid, if empty the cells are filled with '.'
	puzzle.print();

    //TODO time this. getting a linker error when importing the header. should talk to Dr. Stone about this
    //myTimer_t t0 = getTimeStamp();
    if (bruteForceSolve(&puzzle, attempts)) {
        cout << "Solution exists ";
    } else {
        cout << "Solution does not exist ";
    }
    //myTimer_t t1 = getTimeStamp();
    cout << "after " << attempts << " attempts and " << /*getElapsedTime(t0,t1)*1000 << " seconds." <<*/ endl;
    puzzle.print();
    return 0;
}
