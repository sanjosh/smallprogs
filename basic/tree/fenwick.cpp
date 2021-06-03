#include <iostream>
#include <assert.h>

using namespace std;
//https://en.wikipedia.org/wiki/Fenwick_tree


// For simplicity, this example assumes a single, fixed-size array
const int SIZE = 4;
int A[SIZE];

#define LSBIT(i) ((i) & -(i)) // Return the least-significant set bit in i

// The following identities allow additional optimization,
// but are omitted from this example code for clarity:
// i - LSBIT(i)   == i & (i - 1)
// i + LSBIT(i+1) == i | (i + 1)

// Returns the sum of the first i elements (indices 0 to i-1)
// Equivalent to range_sum(0, i)
int prefix_sum(unsigned int i)
{
	int sum = 0;
	assert(0 <= i && i <= SIZE);
	for (; i > 0; i -= LSBIT(i))
		sum += A[i-1];
	return sum;
}

// Add delta to element with index i (zero-based)
void add(unsigned int i, int delta)
{
	assert(0 <= i && i < SIZE);
    cout << "adding:";
	for (; i < SIZE; i += LSBIT(i+1)) {
		A[i] += delta;
        cout << i << ",";
    }
    cout << endl;
}

void init(void)
{
	for (unsigned int i = 0; i < SIZE; i++) {
		unsigned int j = i + LSBIT(i+1);
		if (j < SIZE)
			A[j] += A[i];
	}
}

void printall()
{
    for (int i = 0; i < SIZE; i++)
    {
        cout << A[i] << ",";
    }
    cout << endl;
}

void prefixAll()
{
    for (int i = 1; i < SIZE + 1; i++)
    {
        cout << prefix_sum(i) << ",";
    }
    cout << endl;
}

int main()
{
    for (int i = 0; i < SIZE; i++)
    {
        cout << i << ":" << LSBIT(i) << endl;
        A[i] = 1;
    }
    init();
    cout << "lsbit ends" << endl;

    printall();
    prefixAll();

    add(1, 3);
    printall();
    prefixAll();

    add(2, 5);
    printall();
    prefixAll();

    cout << endl;
}
