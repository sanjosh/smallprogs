
#include <sys/uio.h>
#include <map>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>

char* buffer = NULL;
#define NUMBLKS 10

using namespace std;
typedef map <int, char*> AnchorMap;
typedef AnchorMap::iterator AnchorMapIter;
AnchorMap anchorMap;

int insert(int id, char* data)
{
    pair<AnchorMapIter, bool> res = anchorMap.insert(make_pair(id, data));
    if (res.second == true)
    {
        cout << "success " << id << endl;
    }
    else
    {
        cout << "fail " << id << endl;
    }
    return 0;
}

int flush()
{
    AnchorMapIter iter = anchorMap.begin();
    struct iovec *vec = (iovec*)malloc(sizeof(struct iovec) * NUMBLKS);
    int i = 0;
    while (iter != anchorMap.end())
    {
        vec[i].iov_base = iter->second;
        vec[i].iov_len = 4096;
        i++;
        iter ++;
    }
    int fd = open("/tmp/testme", O_CREAT | O_TRUNC | O_WRONLY,
                    S_IRWXU | S_IRWXG);
    ssize_t err = writev(fd, vec, i);
    cout << "writev return =" << errno << endl;
    close(fd);
}

int main(int argc, char* argv[])
{
    buffer = (char*)malloc(4096 * NUMBLKS);

    srand(76);
    for (int i = 0; i < NUMBLKS; i++)
    {
        char* data = buffer + (i * 4096);
        int id = rand() % NUMBLKS;
        //int id = NUMBLKS - i;
        sprintf(data, "cache=%d iter=%d", id, i);
        insert(id, data);
    }
    flush();
}
