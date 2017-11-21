#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "SudokuGrid.h"

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

void SudokuGrid::writeCellValue(int x, int y, int value) {
  board[x][y] = value;
}

bool SudokuGrid::testValidity(int x, int y) {
    //returns true if all tests pass, otherwise returns false

    int gridLocation = board[x][y];
    //compare inputted x value for doubles in the y column
    //compared inpuuted y value for doubles in the x column
    for (int xValidity=0; xValidity<9; xValidity++) {
        //keeps breaking on itself, this fixes that
        if (xValidity == x) {
            continue;
        }
        
        //actual test for doubles
        int testValue = board[xValidity][y];
        if (testValue == gridLocation) {
            return false;
        }
    }

    for (int yValidity=0; yValidity<9; yValidity++) {
        //keeps breaking on itself, this fixes that
        if (yValidity == y) {
            continue;
        }

        //actual test for doubles
        int testValue = board[x][yValidity];
        if (testValue == gridLocation) {
            return false;    
        }
    }

    //test 3x3 box (will not work with larger sizes)
    int boxX = x/3;
    int boxY = y/3;

    for (int yValidity =boxY * 3; yValidity < boxY * 3 + 3; yValidity++) {
    for (int xValidity=boxX * 3; xValidity < boxX * 3 + 3; xValidity++) {
        //stop from breaking on itself
        if (xValidity == x && yValidity == y) {
            continue;
            }
        //fail if repeated values
        int testValue = board[xValidity][yValidity];
        if (testValue == gridLocation) {
            return false;
            }
    }
    }
    //if all tests passed, return true
    return true;
}

int main (int argc, char * const argv[]) {
	SudokuGrid puzzle;

	int arraysize = 80;
    char myArray[arraysize];
	char current_char;
	int num_characters = 0;
	int i = 0;
	int value;

//	ifstream myfile ("data/cleanedUpFiles/xab");
//	if (myfile.is_open())
//		{
//		  while ( !myfile.eof())
//		  {
		  		//this part seems to save the contents of the input file to the array correctly 
		        //myfile >> myArray[i];
		        //i++;
		        //num_characters ++;

		        //TODO this section does not populate the grid correctly
//		        for (int y=0; y<9; y++) {
//					for (int x=0; x<9; x++) {
//						//value = myArray[i] - '0';
//						//cout << "this is myArray" << endl;
//						//cout << myArray[i];
//						//puzzle.writeCellValue(x,y,value);
//		  				}
//		  		}
//		  	}      
//
//		for (int i = 0; i <= num_characters; i++)
//			{
//				//cout << myArray[i];
//				//std::cout << "break" << std::endl;
//				} 
//			}
//
	//myfile.open("data/p096_sudoku.txt");
	//char ch;
	//fstream fin("data/cleanedUpFiles/xaa", fstream::in);
	//while (fin >> noskipws >> ch) {
	//    cout << ch; // Or whatever I need this to do
	// 	puzzle.writeCellValue(0,0,ch); }

	// code to set values on grid to the test boards starting values. Not implemented fully.
	//example below sets value 5 to the cell with coordinates (0,0)
	//this requires the initialized default for SudokuGrid puzzle to be all zeroes at every location
	//puzzle.writeCellValue(0,0,5);
	puzzle.writeCellValue(0,0,0);
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
	puzzle.writeCellValue(0,0,0);


	//print grid, if empty the cells are filled with '.'
	puzzle.print();
    std::cout << std::boolalpha << testValidity(2,8) <<endl;
    //if else statement calling print if puzzle is solvable and exiting if not
    //puzzle.solve is not written yet TODO
//    if (puzzle.solve()) {
//        std::cout << "Puzzle Solved Solution Below" << std::endl;
//        puzzle.print();
//    } else {
//        std::cout << "Unsolvable Puzzle" << std::endl;
//    }
    return 0;
}
