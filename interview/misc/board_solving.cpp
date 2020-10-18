
//http://www.cis.upenn.edu/~matuszek/cit594-2012/Pages/backtracking.html

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;

int BOARD_SIZE = 5;
char* myboard = NULL;

#define WHITE ('w')
#define BLACK ('b')
#define SPACE (' ')

void printBoard(char* board)
{
    for (int position = 0; position < BOARD_SIZE; position++) 
    {
        cout << board[position] << " ";
    }
    cout << endl;
}

bool puzzleSolved(char* oldBoard)
{
    int white = 0;
    int black = 0;
    int space = 0;

    bool solved = true;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (oldBoard[i] == WHITE)
        {
            if (space || black) {solved = false; break; }
            white ++;
        }
        else if (oldBoard[i] == SPACE)
        {
            if ((white != BOARD_SIZE/2) || black) {solved = false; break; }
            space ++;
        }
        else if (oldBoard[i] == BLACK)
        {
            if ((white != BOARD_SIZE/2) || (space != 1)) {solved = false; break; }
            black ++;
        }
    }
    return solved;
}

char* makeMove(char* board, int position, int choice)
{
    int state = 0;
    char* newBoard = new char[BOARD_SIZE];
    memcpy(newBoard, board, sizeof(char) * BOARD_SIZE);

    
    if (board[position] == WHITE)
    {
        if ((choice == 0x01) && (position >= 1) && (board[position - 1] == SPACE))
        {
            newBoard[position] = SPACE;
            newBoard[position-1] = WHITE;
            state = 1;
        }
        else if ((choice == 0x02) && (position >= 2) && 
            (board[position - 1] == BLACK) && 
            (board[position - 2] == SPACE))
        {
            newBoard[position] = SPACE;
            newBoard[position-2] = WHITE;
            state = 2;
        }
    }
    else if (board[position] == BLACK)
    {
        if ((choice == 0x01) && (position < (BOARD_SIZE - 1)) && (board[position + 1] == SPACE))
        {
            newBoard[position] = SPACE;
            newBoard[position+1] = BLACK;
            state = 3;
        }
        else if ((choice == 0x02) && (position < (BOARD_SIZE-2)) && 
            (board[position + 1] == WHITE) && 
            (board[position + 2] == SPACE))
        {
            newBoard[position] = SPACE;
            newBoard[position+2] = BLACK;
            state = 4;
        }
    }
    else
    {
        assert(0);
    }
    //cout << newBoard << ":" << position << ":" << choice << endl;
    return newBoard;
}

/*
    If the position is empty, no move is possible;
    If the position contains a black marble, the method checks for a move or jump to the right;
    If the position contains a white marble, the method checks for a move or jump to the left.
*/
int canMove(char* board, int position)
{
    if (board[position] == SPACE) return false;

    int choice = 0;
    if (board[position] == WHITE)
    {
        if ((position >= 1) && (board[position - 1] == SPACE))
            choice |= 0x01;
        if ((position >= 2) && 
            (board[position - 1] == BLACK) && 
            (board[position - 2] == SPACE))
            choice |= 0x02;
    }
    else if (board[position] == BLACK)
    {
        if ((position < (BOARD_SIZE-1)) && (board[position + 1] == SPACE))
            choice |= 0x01;
        if ((position < (BOARD_SIZE -2)) && 
            (board[position + 1] == WHITE) && 
            (board[position + 2] == SPACE))
            choice |= 0x02;
    }
    return choice;
}

bool solvable(char* board) 
{
    if (puzzleSolved(board)) 
    {
        return true;
    }

    for (int position = 0; position < BOARD_SIZE; position++) 
    {
        int choice = canMove(board, position);
        if (choice & 0x01)
        {
            char* newBoard = makeMove(board, position, choice & 0x01);
            if (solvable(newBoard)) 
            {
                printBoard(newBoard);
                delete []newBoard;
                return true;
            }
            delete []newBoard;
        }
        if (choice & 0x02)
        {
            char* newBoard = makeMove(board, position, choice & 0x02);
            if (solvable(newBoard)) 
            {
                printBoard(newBoard);
                delete []newBoard;
                return true;
            }
            delete []newBoard;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        BOARD_SIZE = atoi(argv[1]);
    }

    myboard = new char[BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE/2; i++)
    {
        myboard[i] = BLACK;
        myboard[BOARD_SIZE - i - 1] = WHITE;
    }
    myboard[(BOARD_SIZE/2)] = SPACE;
    
    printBoard(myboard);

    bool ans = solvable(myboard);
    cout << ans << endl;
}
