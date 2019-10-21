/*--------------------------------------------------------------
 * File MyClasses.h
 * Date 27/09/2019
 * Author Matsoukas George
 * Description : Its the Definition file for my classes
 * -----------------------------------------------------------*/

using namespace std;

/* -----------------------------------------------------------
 * Class        : square  
 * Desecription : The base class, represents a single square
 * ---------------------------------------------------------*/

class square
{
    private:
        int value;	        		                    // current value of the squrare
        int  possibles[10] = {0,0,0,0,0,0,0,0,0,0};     // Hold All possible values ( has 1 in [index] if exists )
        int colNum;			                            // Column number of the square
        int rowNum; 		                            // Row number of the square
        int block;                                      // The 3x3 square that it belongs (0-9)
        int NumOfPossibles;                             // The Number of Possible Values that can take
    public:
        square();                                       // Default Constructor
        ~square();                                      // Default Destructor
        void SetValue(int val);                         // Set value
        void DeletePossible(int val);                   // delete val from posibilities

        friend class Sudoku;
};


/* -----------------------------------------------------------
 * Class        : Sudoku  
 * Desecription : The Master class, represents a Sudoku
 * ---------------------------------------------------------*/

class Sudoku
{
    private:
        square m_square[82];
    public:
        Sudoku();
        ~Sudoku();
        void printSudoku();
        void ReadFile(string fname);
        void SetPuzzle(string aPuzzle);
        void solveSudoku(string aPuzzle);
        void Find_Possibe_Values();
        void Print_Possibe_Value(int asqr);
        void Find3x3(int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int asqr);
        void ScanUniq();
        void SetValue(int sqr);
};
