
#include <queue>
#include <iostream>

using namespace std;

/**
	https://www.hackerrank.com/challenges/find-the-median
 */

std::priority_queue<long> q;

int main()
{
	long n;
	cin >> n;

	int qsize = (n+1)/2;

	int i = 0;
	for (; i < qsize; i++) {
		long a;
		cin >> a;
		q.push(a);
	}
	for (;i < n; i++) {
		long a;
		cin >> a;
		if (q.top() > a) {
			q.pop();
			q.push(a);
		} 
	}
	cout << q.top() << endl;
}
