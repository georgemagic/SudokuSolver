/*--------------------------------------------------------------
 * File MyClasses.cpp
 * Date 27/09/2019
 * Author Matsoukas George
 * Description : Implementation of Classes square,Sudoku
 * -----------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include "MyClasses.h"


//#include "MyClasses.h"

using namespace std;


/*---------------------------------------------------------------
 * Implementation  : Class square 
 * Member Function : square consrtructor : squeare()
 * -------------------------------------------------------------*/

square::square()
{
    colNum = 0;
    rowNum = 0;	
    value  = 0;
    NumOfPossibles = 0;
}

/*---------------------------------------------------------------
 * Implementation  : Class square
 * Member Function : Sudoku destructor   : ~Sudoku()
 * -------------------------------------------------------------*/

square::~square()
{
}

/*---------------------------------------------------------------
 * Implementation  : Class square
 * Member Function : Sudoku destructor   : ~Sudoku()
 * -------------------------------------------------------------*/

void square::SetValue(int val)
{
    value = val;
    DeletePossible(val);
}

/*---------------------------------------------------------------
 * Implementation  : Class square
 * Member Function : Sudoku destructor   : ~Sudoku()
 * -------------------------------------------------------------*/

 void square::DeletePossible(int val)
 {
     possibles[val] = 1;
     NumOfPossibles--;
 }

/*---------------------------------------------------------------
 * Implementation  : Class Sudoku 
 * Member Function : Sudoku destructor : ~Sudoku()
 * -------------------------------------------------------------*/

Sudoku::~Sudoku()
{
}

/*---------------------------------------------------------------------
 * Implementation  : Class Sudoku 
 * Member Function : Sudoku consrtructor : Sudoku()
 * Description     : Intialize squares with rowNumber,columnNumber
 *                 : 0 as value and also the 3x3 block that belongs
 * -------------------------------------------------------------------*/

Sudoku::Sudoku()
{
    int count = -1;
    for ( int r=0; r<9 ; r++)
    {
        for ( int c=0; c<9 ; c++)
        {
            count++;
            m_square[count].colNum = c;         // Set Column Number
            m_square[count].rowNum = r;         // Set Row Number
            m_square[count].value  = 0;         // Set Value to 0
            
            if (r < 3 && c < 3)                      m_square[count].block = 0;    // Belongs to block 0
            if (r < 3 && c > 2 && c < 6)             m_square[count].block = 1;    // Belongs to block 1
            if (r < 3 && c > 5)                      m_square[count].block = 2;    // Belongs to block 2

            if (r > 2 && r < 6 && c < 3)             m_square[count].block = 3;    // Belongs to block 3
            if (r > 2 && r < 6 && c > 2 && c < 6)    m_square[count].block = 4;    // Belongs to block 4
            if (r > 2 && r < 6 && c > 5)             m_square[count].block = 5;    // Belongs to block 5

            if (r > 5 && c < 3)                      m_square[count].block = 6;    // Belongs to block 6
            if (r > 5 && c > 3 && c < 6)             m_square[count].block = 7;    // Belongs to block 7
            if (r > 5 && c > 5)                      m_square[count].block = 8;    // Belongs to block 8
        }
    }
}

/*---------------------------------------------------------------
 * Implementation  : Class Sudoku 
 * Member Function : Sudoku printSudoku  : printSudoku()
 * Description     : Prints a sudoku to 9x9 format
 * -------------------------------------------------------------*/

void Sudoku::printSudoku()
{
    int count = -1;
    for ( int r=0; r<9 ; r++)
    {
        cout << endl ;
        for ( int c=0; c<9 ; c++)
        {
            count++;
            cout << m_square[count].value << " ";
        }
    }
    cout << endl;
}

/*---------------------------------------------------------------
 * Implementation  : Class Sudoku 
 * Member Function : Sudoku ReadFile  : ReadFile(fname)
 * Description     : Reads a delimted file with sodokus 
 *                 : and their solution and calls solveSudoku
 * -------------------------------------------------------------*/

void Sudoku::ReadFile(string fname)
{
    ifstream infile(fname);

    if(!infile)
    {
        cout << "Cannot open input file." << endl;
    }
    else
    {
        string str;
        while(getline(infile,str)) 
        {
            int delim = str.find(",");
            string puzzle   = str.substr(0,delim);
            string solution = str.substr(delim + 1);
            //cout << str << endl;
            //cout << puzzle << endl;
            //cout << solution << endl;

            solveSudoku(puzzle);
        }
        infile.close();
    }
}

/*---------------------------------------------------------------
 * Implementation  : Class Sudoku 
 * Member Function : solveSudoku(string aPuzzle)
 * -------------------------------------------------------------*/

void Sudoku::solveSudoku(string aPuzzle)
{
    SetPuzzle(aPuzzle);
    printSudoku();
    Find_Possibe_Values();
    cout << "I Have found All Possible Values" << endl;
    

    ScanUniq();
    int a;
    cout << "Press any Key to Continue ....." << endl;
    cin >> a;
    exit(0);
}

/*---------------------------------------------------------------
 * Implementation  : Class Sudoku 
 * Member Function : Sudoku consrtructor : Sudoku()
 * Member Function : Sudoku destructor   : ~Sudoku()
 * Member Function : Sudoku printSudoku  : printSudoku()
 * -------------------------------------------------------------*/

void Sudoku::SetPuzzle(string aPuzzle)
{
    for ( int count=0; count<81 ; count++)
    {
        m_square[count].value = (int) aPuzzle[count] - 48;
    }
}

/*---------------------------------------------------------------
 * Implementation  : Class Sudoku Print_Possibe_Value
 * Member Function : Sudoku consrtructor : Sudoku()
 * Member Function : Sudoku destructor   : ~Sudoku()
 * Member Function : Sudoku printSudoku  : printSudoku()
 * -------------------------------------------------------------*/

void Sudoku::Print_Possibe_Value(int asqr)
{
    cout << " Square " << asqr << " possible values : ";
    for ( int t=1 ; t<10 ; t++)
    {
        if (m_square[asqr].possibles[t] == 0 )
            cout << t;
    }
    cout << endl;
    cout << "Number of Posibilities " << m_square[asqr].NumOfPossibles << endl;
}

/*---------------------------------------------------------------
 * Implementation  : Class Sudoku 
 * Member Function : Sudoku consrtructor : Sudoku()
 * Member Function : Sudoku destructor   : ~Sudoku()
 * Member Function : Sudoku printSudoku  : printSudoku()
 * -------------------------------------------------------------*/

void Sudoku::Find_Possibe_Values()
{
    for ( int asqr = 0 ; asqr < 81 ; asqr++)
    {

        if (m_square[asqr].value == 0)
        {
            int cc = (asqr % 9);
            int rr = asqr / 9;

            // ------   Collect all Numbers from Row -----------

            for ( int count =  9*rr ; count <=  9*rr + 8 ; count++)
            {
                if ( m_square[count].value != 0 )
                {
                    m_square[asqr].possibles[m_square[count].value] = 1;
                    //cout << " Adding from Row " << m_square[count].value << endl;
                }
            }

            // -------- Collect all Numbers from Column -------------

            for (int count1 = cc ; count1 < 81 ; count1 = count1 + 9)
            {
                if ( m_square[count1].value != 0 )
                {
                    m_square[asqr].possibles[m_square[count1].value] = 1;
                    //cout << " Adding from Column " << m_square[count1].value << endl;
                }
            }

            // -------- Collect all Numbers from 3x3 block ----------

            switch (m_square[asqr].block)
            {
                case 0 : Find3x3(0,1,2,9,10,11,18,19,20,asqr);
                break;
                case 1 : Find3x3(3,4,5,12,13,14,21,22,23,asqr);
                break;
                case 2 : Find3x3(6,7,8,15,16,17,24,25,26,asqr);
                break;
                case 3 : Find3x3(27,28,29,36,37,38,45,46,47,asqr);
                break;
                case 4 : Find3x3(30,31,32,39,40,41,48,49,50,asqr);
                break;
                case 5 : Find3x3(33,34,35,42,43,44,51,52,53,asqr);
                break;
                case 6 : Find3x3(54,55,56,63,64,65,72,73,74,asqr);
                break;
                case 7 : Find3x3(57,58,59,66,67,68,75,76,77,asqr);
                break;
                case 8 : Find3x3(60,61,62,69,70,71,78,79,80,asqr);
                break;
            }
        }

        // Count the Number of Possible Values

        int NumOfPossibles = 0;
        for (int count = 0 ; count < 10 ; count++)
        {
            if (m_square[asqr].possibles[count] != 0 ) NumOfPossibles++;
        }         
        m_square[asqr].NumOfPossibles = 9 - NumOfPossibles;
    }
}

/*---------------------------------------------------------------
 * Implementation  : Class Sudoku 
 * Member Function : Find3x3
 * -------------------------------------------------------------*/

void Sudoku::Find3x3(int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9,int asqr)
{
    if (m_square[a1].value != 0 ) m_square[asqr].possibles[m_square[a1].value] = 1;
    if (m_square[a2].value != 0 ) m_square[asqr].possibles[m_square[a2].value] = 1;
    if (m_square[a3].value != 0 ) m_square[asqr].possibles[m_square[a3].value] = 1;
    if (m_square[a4].value != 0 ) m_square[asqr].possibles[m_square[a4].value] = 1;
    if (m_square[a5].value != 0 ) m_square[asqr].possibles[m_square[a5].value] = 1;
    if (m_square[a6].value != 0 ) m_square[asqr].possibles[m_square[a6].value] = 1;
    if (m_square[a7].value != 0 ) m_square[asqr].possibles[m_square[a7].value] = 1;
    if (m_square[a8].value != 0 ) m_square[asqr].possibles[m_square[a8].value] = 1;
    if (m_square[a9].value != 0 ) m_square[asqr].possibles[m_square[a9].value] = 1;
}

void Sudoku::ScanUniq()
{
    // ------------ Scan for Unique possible value
    for (int count1=0 ; count1<81 ; count1++)
    {   
        Print_Possibe_Value(count1);
        if (m_square[count1].NumOfPossibles == 1 )
        {
            cout << "Found Unique  " << count1 <<endl;
            SetValue(count1);
        }   
    } 
}

void Sudoku::SetValue(int sqr)
{
    //Set value to sqr
    //Delete that value from all row column 3x3
}
