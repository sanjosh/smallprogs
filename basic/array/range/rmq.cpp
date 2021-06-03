
class RMQ
{
    // number of columns = log2(N)
    // first column store original values
    // entry[0, 1] = min(0, 0) and (1, 0)
    // entry[1, 1] = min(1, 0) and (2, 0)

    // [0, 2] = [0, 1] and [2, 1]
    // [1, 2] = [1, 1] and [3, 1]
    int lookup[log2N][N]

    RMQ(int arr[], int n)
    {
        int max_x = (int) log2(n);
    }

    void preprocess(int arr[n], int n)
    {
    }
};
