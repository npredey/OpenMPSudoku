#ifndef _SUDOKU_GRID_H
#define _SUDOKU_GRID_H

class SudokuGrid {
  private:

  	//grid
  	//TODO boards of various sizes, must change print() as well
	short int board[9][9];

	//TODO
	// bruteForce solving attempt
	bool bruteForceSolve(int x, int y);
	
	// TODO
	// tests validity of cell value
	bool verifyValue(int x, int y);

  public:
    // Constructor
	SudokuGrid();
  
  	// TODO
    // cleanly and nicely print out the sudoku board to the terminal
    void print();
	
	// TODO
	// enterBoardValue
	//void writeCellValue(int x, int y, int value);
  
  	// TODO
    // readCellValue
	//int readCellValue(int x, int y);
	
	// TODO
	// Returns true if solved state, returns false if unsolvable.
	//bool solve();
	
};

#endif