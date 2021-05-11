
/*

http://www.geeksforgeeks.org/channel-assignment-problem/

There are M transmitter and N receiver stations. 

Given a matrix that keeps track of the number of packets to be transmitted from a given transmitter to a receiver. 

If the (i; j)-th entry of the matrix is k, it means at that time the station i has k packets for transmission to station j.

During a time slot, a transmitter can send only one packet and a receiver can receive only one packet. 

Find the channel assignments so that maximum number of packets are transferred from transmitters to receivers during the next time slot.

Example:

0 2 0
3 0 1
2 4 0

The above is the input format. We call the above matrix M. 

Each value M[i; j] represents the number of packets Transmitter ‘i’ has to send to Receiver ‘j’. The output should be:

The number of maximum packets sent in the time slot is 3
T1 -> R2
T2 -> R3
T3 -> R1 

Note that the maximum number of packets that can be transferred in any slot is min(M, N).

Algorithm:
The channel assignment problem between sender and receiver can be easily transformed into Maximum Bipartite Matching(MBP) 
problem that can be solved by converting it into a flow network.

Step 1: Build a Flow Network
There must be a source and sink in a flow network. So we add a dummy source and add edges from source to all senders. 
Similarly, add edges from all receivers to dummy sink. The capacity of all added edges is marked as 1 unit.

Step 2: Find the maximum flow.
We use Ford-Fulkerson algorithm to find the maximum flow in the flow network built in step 1. 
The maximum flow is actually the maximum number of packets that can be transmitted without bandwidth interference in a time slot.

Implementation:
Let us first define input and output forms. Input is in the form of Edmonds matrix which is a 2D array ‘table[M][N]‘ with M rows (for M senders) and N columns (for N receivers). The value table[i][j] is the number of packets that has to be sent from transmitter ‘i’ to receiver ‘j’. Output is the maximum number of packets that can be transmitted without bandwidth interference in a time slot.
A simple way to implement this is to create a matrix that represents adjacency matrix representation of a directed graph with M+N+2 vertices. Call the fordFulkerson() for the matrix. This implementation requires O((M+N)*(M+N)) extra space.
Extra space can be reduced and code can be simplified using the fact that the graph is bipartite. The idea is to use DFS traversal to find a receiver for a transmitter (similar to augmenting path in Ford-Fulkerson). We call bpm() for every applicant, bpm() is the DFS based function that tries all possibilities to assign a receiver to the sender. In bpm(), we one by one try all receivers that a sender ‘u’ is interested in until we find a receiver, or all receivers are tried without luck.
For every receiver we try, we do following:
If a receiver is not assigned to anybody, we simply assign it to the sender and return true. If a receiver is assigned to somebody else say x, then we recursively check whether x can be assigned some other receiver. To make sure that x doesn’t get the same receiver again, we mark the receiver ‘v’ as seen before we make recursive call for x. If x can get other receiver, we change the sender for receiver ‘v’ and return true. We use an array maxR[0..N-1] that stores the senders assigned to different receivers.
If bmp() returns true, then it means that there is an augmenting path in flow network and 1 unit of flow is added to the result in maxBPM().

Time and space complexity analysis:
In case of bipartite matching problem, F ? |V| since there can be only |V| possible edges coming out from source node. So the total running time is O(m’n) = O((m + n)n). The space complexity is also substantially reduces from O ((M+N)*(M+N)) to just a single dimensional array of size M thus storing the mapping between M and N.
*/

#include <iostream>
#include <string.h>
#include <vector>
#define M 3
#define N 4
using namespace std;
 
// A Depth First Search based recursive function that returns true
// if a matching for vertex u is possible
bool bpm(int table[M][N], int u, bool seen[], int matchR[])
{
    // Try every receiver one by one
    for (int v = 0; v < N; v++)
    {
        // If sender u has packets to send to receiver v and
        // receiver v is not already mapped to any other sender
        // just check if the number of packets is greater than '0'
        // because only one packet can be sent in a time frame anyways
        if (table[u][v]>0 && !seen[v])
        {
            seen[v] = true; // Mark v as visited
 
            // If receiver 'v' is not assigned to any sender OR
            // previously assigned sender for receiver v (which is
            // matchR[v]) has an alternate receiver available. Since
            // v is marked as visited in the above line, matchR[v] in
            // the following recursive call will not get receiver 'v' again
            if (matchR[v] < 0 || bpm(table, matchR[v], seen, matchR))
            {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}
 
// Returns maximum number of packets that can be sent parallely in 1
// time slot from sender to receiver
int maxBPM(int table[M][N])
{
    // An array to keep track of the receivers assigned to the senders.
    // The value of matchR[i] is the sender ID assigned to receiver i.
    // the value -1 indicates nobody is assigned.
    int matchR[N];
 
    // Initially all receivers are not mapped to any senders
    memset(matchR, -1, sizeof(matchR));
 
    int result = 0; // Count of receivers assigned to senders
    for (int u = 0; u < M; u++)
    {
        // Mark all receivers as not seen for next sender
        bool seen[N];
        memset(seen, 0, sizeof(seen));
 
        // Find if the sender 'u' can be assigned to the receiver
        if (bpm(table, u, seen, matchR))
            result++;
    }
 
    cout << "The number of maximum packets sent in the time slot is "
         << result << "\n";
 
    for (int x=0; x<N; x++)
        if (matchR[x]+1!=0)
            cout << "T" << matchR[x]+1 << "-> R" << x+1 << "\n";
    return result;
}
 
// Driver program to test above function
int main()
{
    int table[M][N] = {{0, 2, 0}, {3, 0, 1}, {2, 4, 0}};
    int max_flow = maxBPM(table);
    return 0;
}

/*
Output:

The number of maximum packets sent in the time slot is 3
T3-> R1
T1-> R2
T2-> R3
*/
