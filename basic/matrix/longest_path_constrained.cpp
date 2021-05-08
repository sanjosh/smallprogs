
/*

https://www.geeksforgeeks.org/find-the-longest-path-in-a-matrix-with-given-constraints/


can there be 2 paths from a cell - no ?
numbers are distinct

paths starting from two cells cannot merge 
since we are going sorted, previous path will have covered it all

sort numbers 
start cell with smallest number
look for cell containing next number

each cell has "visited" 
if cell is visited, merge its following path

need count that all cells have been covered

next_number = find smallest number in matrix

while (total_count != NxN)
    count, max_path, next_number = traverser(next_number)
    max_so_far = max(max_path, max_so_far)
    total_count += count

traverser(number)
{
    cell = findCell(number)
    max_path = 1
    do
        next_number = number ++
        adj cell = matrix.adjacent(cell).stream().findAny(cell.value = next_number).else( return (-1, -1))
        if not adj cell
            return count, max_path, next_number
        else 
            max_path ++, 
            count ++
            cell = adj cell 
}

*/

struct Pos
{
    int row = -1;
    int col = -1;
};

struct Matrix
{
    int MAX_N = 4;

    int pos[MAX_N][MAX_N];

    AdjIter beginAdjIter()
    {
        Pos p;
        p.row = 0; p.col = 0;
        return AdjIter(*this, p);
    }

    endAdjIter()
    {
        Pos p;
        return AdjIter(*this, p);
    }
};

struct AdjIter
{
   int row_;
   int col_;
   const Matrix& m_;

   const int adjpos_[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
   int cur_pos_ = 0;

   AdjIter(const Matrix& m, const Pos& p) : m_(m)
   {
        this->row_ = p.row; 
        this->col_ = p.col;
   }

   AdjIter operator ++() 
   {
        this->cur_pos_ ++;
        return *this;
   }

   int operator *() const
   {
        int cur_row = this->row_ + this->adjpos_[this->cur_pos_][0];
        int cur_col = this->col_ + this->adjpos_[this->cur_pos_][1];
        return this->m_[cur_row][cur_col];
   }
};

int traverser(int &number)
{
    auto pos = findMatrixCell(number);
    for (off = mat.beginAdjIter(pos); off != mat.end(); off ++)
    {
    }
}
