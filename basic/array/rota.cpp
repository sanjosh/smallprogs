
class RotatedArrayIter
{
    void begin(int32_t idx) 
    {
        start = idx;
        j = idx 
        next_called = false;
    }

    const int32_t elem() const
    {
        return arr[j];
    }

    bool end() const
    {
       return next_called && (j == start) 
    }

    void next()
    {
        next_called = true;
        j = (j + 1) % N
    }
}
