#ifndef _SUDOKU_GRID_H
#define _SUDOKU_GRID_H

class SudokuGrid {
  private:

  	//grid
  	//TODO boards of various sizes, must change print() as well
	int board[9][9];

  public:
    // Constructor
	SudokuGrid();

	//TEMP TODO
	short **data;
	short **fixed;

		// TODO
	// tests validity of cell value
    //returns true if rules are followed, false if any are broken
	bool testValidity(int x, int y);
 
    //TODO
	// bruteForce solving attempt
	//bool bruteForceSolve(SudokuGrid grid);

    // cleanly and nicely print out the sudoku board to the terminal
    void print();
	
	// enterBoardValue
	void writeCellValue(int x, int y, int value);
  
  	// TODO
    // readCellValue
	int readCellValue(int x, int y);
	
	// TODO
	// Returns true if solved state, returns false if unsolvable.
	//bool solve();

	//Nick's New Code To Merge
	bool findUnassignedCell(SudokuGrid grid, int x, int y);
    
    void readArray(int[][9]);
    
    void readStringToBoard(std::string board);
    
    void readFromFileToBoard(std::string filename);
	
};

#endif
