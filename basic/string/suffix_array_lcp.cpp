#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    string in = "ababaa";

    vector<string> suff;

    for (int i = 0; i < in.size(); i ++)
    {
        suff.push_back(in.substr(i, in.size() - i));
    }

    std::sort(suff.begin(), suff.end());

    int rank[suff.size()];
    int start_pos[suff.size()];

    for (int i = 0; i < suff.size(); i ++)
    {
        int posi = in.size() - suff[i].size();
        start_pos[i] = posi;
        rank[posi] = i;  // overall rank of suffix starting at this pos is same as index of for loop
    }

    vector<int> lcp(suff.size(), 0);
    int h = 0;
    for (int i = 0; i < suff.size(); i ++)
    {
        if (rank[i] > 0) { // implies it has preceding suffix
            int prev_suffix_pos = start_pos[rank[i] - 1]; // prev suffix
            cout << "start=" << i << ":" << prev_suffix_pos << ":" << h << endl;
            while (i + h < suff.size() && prev_suffix_pos + h < suff.size()
                && in[i + h] == in[prev_suffix_pos + h]) {
                h ++;
            }
            cout << "ended=" << h << endl;
            lcp[rank[i]] = h;    
            if (h > 0) {
                h = h - 1;
                // why decrement - sandwiching of suffix
                /*
                     When we go from iteration i to iteration i+1, 
                     for the suffix in iteration i+1 

                     the direct predecessor in the suffix array is sandwiched between 
                     the suffix from iteration i+1 and 
                     the predecessor from iteration i with the first character removed
                */
                // https://stackoverflow.com/questions/57748988/kasai-algorithm-for-constructing-lcp-array-practical-example/63104083#63104083
            }
        }
    }

    for (int i = 0; i < suff.size(); i ++)
    {
        cout << rank[i] << "," << lcp[i] << "," << suff[i] << endl;
    }

}
