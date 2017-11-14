#include <iostream>
#include "SudokuGrid.h"

SudokuGrid::SudokuGrid() {
	//set board to all zeroes. This causes the print function below to print out '.'
	for (int y=0; y<9; y++) {
		for (int x=0; x<9; x++) {
			board[x][y] = 0;
		}
	}
}

//TODO fix print for various sizes, right now only works for 9x9 sudoku puzzle
void SudokuGrid::print() {
	//for every row
	for (int y=0; y<9; y++) {
		if (y%3==0) {
			std::cout << "-------------------------------" << std::endl;
		}

	//for every cell in the row
	for (int x=0; x<9; x++) {
		if (x%3==0) {
			std::cout << "|";
		}	
	    if (board[x][y] != 0) {
			std::cout << " " << board[x][y] << " ";
		} else {
			std::cout << " . ";
		}		
	}	
	// Draw columns between blocks
	std::cout << "|" << std::endl;
	}
	std::cout << "-------------------------------" << std::endl;

}



int main (int argc, char * const argv[]) {
	SudokuGrid puzzle;

	// code to set values on grid to the test boards starting values. Not implemented fully.
	//example below sets value 5 to the cell with coordinates (0,0)
	//this requires the initialized default for SudokuGrid puzzle to be all zeroes at every location
	//puzzle.writeCellValue(0,0,5);

	//print grid, if empty the cells are filled with '.'
	puzzle.print();

	}