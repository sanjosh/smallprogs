
#include <iostream>
#include <iomanip>
#include <assert.h>
using namespace std;

int MAXJ  = 100;

#define MIN(a,b) ((a < b) ? a : b)

/*

Input Format

The first line contains the number of tests, T. T testcases follow.

For each testcase, there are 3 lines.

The first line contains the number of ladders and snakes, separated by a comma.
The second is a list of comma separated pairs indicating the starting and ending squares of the ladders. The first point is the square from which a player can ascend and the second point is his final position.
The third is a list of comma separated pairs indicating the starting and ending (mouth and tail) squares of the snakes. the first point is the position of the mouth of the snake and the second one is the tail.
Multiple comma separated pairs of snakes and ladders are separated by a single space.

Constraints
The board is always of the size 10 x 10
1 <= T <= 10
1 <= Number of Snakes <= 15
1 <= Number of Ladders <= 15
Squares are always numbered 1 to 100 and the order can be seen in the image above.

Output Format

For each of the T test cases, output one integer, each of a new line, which is the least number of moves (or rolls of the die) in which the player can reach the target square (Square Number 100) after starting at the base (Square Number 1). This corresponds to the ideal sequence of faces which show up when the die is rolled.

Sample Input

3
3,7
32,62 42,68 12,98
95,13 97,25 93,37 79,27 75,19 49,47 67,17
5,8
32,62 44,66 22,58 34,60 2,90
85,7 63,31 87,13 75,11 89,33 57,5 71,15 55,25
4,9
8,52 6,80 26,42 2,72
51,19 39,11 37,29 81,3 59,5 79,23 53,7 43,33 77,21

Sample Output

3
3
5

Explanation

For the first test: To traverse the board via the shortest route, the player first rolls the die to get a 5, and ends up at square 6. He then rolls the die to get 6. He ends up at square 12, from where he climbs the ladder to square 98. He then rolls the die to get '2', and ends up at square 100, which is the target square. So, the player required 3 rolls of the die for this shortest and best case scenario. So the answer for the first test is 3.

For the second test: Rolls the die to get 1, reaches square 2. Then, climbs the ladder to square 90. Rolls the die to get 4, reaches square 94. Rolls the die to get 6, reaches square 100, which is the target square. So the answer for the second test is also 3.
*/


struct SnakeLadder
{
    int* board;
    int* jump;
    int* numdices;
    int NumSnakes;
    int NumLadders;

    virtual ~SnakeLadder()
    {
        delete [] board;
        delete [] jump;
        delete []numdices;
    }

    SnakeLadder()
    {
        board = new int[MAXJ];
        jump = new int[MAXJ];
        numdices = new int[MAXJ];

        for (int i = 0; i < MAXJ; i++)
        {       
            jump[i] = i;
            board[i] = 1;
            numdices[i] = (i/6) + (i%6 > 0 ? 1 : 0);
        }
    }
    void print()
    {
        for (int i = 0; i < MAXJ; i++)
        {       
            if (i%10 == 0) cout << i << ": " ;
            cout << setw(3) << board[i] << " ";
            if ((i+1)%10 == 0) cout << endl;
        }
        cout << endl;
        for (int i = 0; i < MAXJ; i++)
        {       
            if (i%10 == 0) cout << i << ": " ;
            cout << setw(3) << jump[i] << " ";
            if ((i+1)%10 == 0) cout << endl;
        }
        cout << endl;
        for (int i = 0; i < MAXJ; i++)
        {       
            if (i%10 == 0) cout << i << ": " ;
            cout << setw(3) << numdices[i] << " ";
            if ((i+1)%10 == 0) cout << endl;
        }
        cout << endl;
    }

    void solve()
    {
        for (int i = 1; i < MAXJ; i++)  
        {
            if (board[i] != 1) // snake or ladder
            {
                int idx = i + board[i]; // find where it leads to
                //cout << "setting entry=" << idx << " to " << jump[i] << endl;
                for (int j = idx; j < MAXJ; j++) // for all those
                {
                    // set their jump pts to be jump[current] + differece
                    if ((jump[i] + (j-idx)) < jump[j])
                    {
                        jump[j] = jump[i] + (j - idx);
                        numdices[j] = numdices[i] + 
                            ((j - idx) / 6) + (((j-idx)%6 > 0) ? 1 : 0);
                    }
                }
            }
        }
    }
};

int main(int argc, char* argv[])
{
    int NumCases;
    cin >> NumCases;

    while (NumCases --)
    {
        SnakeLadder game;
        int NumSnakes;
        int NumLadders;
        char separator;
    
        cin >> NumLadders >> separator >> NumSnakes;
    
        for (int i = 0; i < NumLadders; i++)
        {
            int start, end;
            cin >> start >> separator >> end;
            assert(start < end);
            game.board[start] = end - start;
        } 
        for (int i = 0; i < NumSnakes; i++)
        {
            int start, end;
            cin >> start >> separator >> end;
            assert(start > end);
            game.board[start] = end - start;
        } 
        //cout << "BEFORE:";
        //game.print();
     
        game.solve();
        //game.print();
        //cout << "-------------" << endl;
        cout << game.numdices[MAXJ - 1] << endl;
    }
}
