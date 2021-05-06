
/*

TODO
You are given a two dimension matrix of characters. 
You are also given a String (character pointer). 
You have to find whether that string could be formed in that grid. 
You can move in the following directions: namely right, left, up, down & diagonal (forward and backward). 
But you can search the word by moving in only one direction at a time 
(i.e. if after the first letter, the second letter has been found by moving right then the subsequent letters also must
be matched by moving right only. You cannot change the direction.). 

*/

#include <string>
#include <iostream>
#include <stdlib.h>
#include <strings.h>
using namespace std;

struct StringMatrixFinder
{

    static const int maxN = 5;
    char matrix[maxN][maxN];
    bool isVisited[maxN][maxN];
    string pattern;
    const int lut[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    StringMatrixFinder() {
        bzero(this->matrix, sizeof(char) * maxN * maxN);
        bzero(this->isVisited, sizeof(bool) * maxN * maxN);
    }

    bool findWord(int patternIndex, int in_row, int in_col)
    {
        if (patternIndex == pattern.size()) {
            return true;
        }
        for (int off = 0; off < 4; off ++)
        {
            int row = in_row + this->lut[off][0];
            int col = in_col + this->lut[off][1];
            {
                if (pattern[patternIndex] == this->matrix[row][col]) {
                    //cout << patternIndex << "," << row << "," << col << endl;
                    if (not this->isVisited[row][col]) {
                        this->isVisited[row][col] = true;
                        bool ret = findWord(patternIndex + 1, row, col);
                        if (ret == true) {
                            return true;
                        } else {
                            this->isVisited[row][col] = false;
                        }
                    }
                }
            }
        }
        return false;
    }
};

int main()
{
    auto s = new StringMatrixFinder();
    s->pattern = "wod";

    for (int row = 0; row < s->maxN; row++)
        for (int col = 0; col < s->maxN; col ++)
            s->matrix[row][col] = 'a';
    s->matrix[3][1] = 'w';
    s->matrix[3][2] = 'o';
    s->matrix[3][3] = 'd';
    for (int row = 0; row < s->maxN; row++)
        for (int col = 0; col < s->maxN; col ++)
            cout << s->findWord(1, row, col) << endl;
}
