/*--------------------------------------------------------------
 * File SudokuSolver.cpp
 * Date 27/09/2019
 * Author Matsoukas George
 * Description : Implementation of Classes square,Sudoku
 * -----------------------------------------------------------*/

#include <iostream>
#include "MyClasses.h"

int main()
{
    Sudoku InitSudoku;
    InitSudoku.ReadFile("/home/george/Development/cplus/SudokuSolver/Data/sudoku.csv");
    return 0;
}