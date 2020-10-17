#include <iostream>
#include <stdlib.h>
using namespace std;

class ChunkCopy
{
    int start_;
    int len_;
    int blockSize_;
    int cur_;

    public:

    ChunkCopy(int start, int len, int blockSize)
    {
        start_ = start;
        len_ = len;
        blockSize_ = blockSize;
        cur_ = start;
    }
    
    bool isValid() const
    {
        return (start_ + len_ - cur_) > 0;
    }

    int next(int& offset, int& size) 
    {
        int remaining = start_ + len_ - cur_;

        size = blockSize_ - (cur_ % blockSize_);
        if (size > remaining) size = remaining; 

        offset = cur_;

        cur_ += blockSize_ - (cur_ % blockSize_);
    }
};

int main(int argc, char* argv[])
{
    int start = atoi(argv[1]);
    int len = atoi(argv[2]);
    int blockSize = atoi(argv[3]);

    ChunkCopy cp(start, len, blockSize);

    while (cp.isValid())
    {
        int off; 
        int readSize;
        cp.next(off, readSize);
        cout << "cur=" << off << ":size=" << readSize << endl;
    }   
}
