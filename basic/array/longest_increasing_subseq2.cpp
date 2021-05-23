#include <iostream>
#include <vector>

using namespace std;

int32_t LIS(const std::vector<int32_t> &v)
{
    std::vector<int32_t> highest_in_sequence(v.size());
    std::vector<int32_t> length_of_sequence(v.size());

    highest_in_sequence[0] = v[0];
    length_of_sequence[0] = 1;
    int num_sequences = 1;

    for (size_t i = 1; i < v.size(); i ++)
    {
        if (v[i] < highest_in_sequence[0]) {
            highest_in_sequence[0] = v[i]; // new smallest
        } else if (v[i] > highest_in_sequence[num_sequences - 1]) {
            highest_in_sequence[num_sequences] = v[i];
            length_of_sequence[num_sequences] = length_of_sequence[num_sequences - 1] + 1;
            num_sequences ++;
        } else {
            // find sequence which has value less than v[i]
            // SOME PROBLEM IN USAGE
            auto iter = std::lower_bound(highest_in_sequence.begin(), highest_in_sequence.end(), v[i]);
            int32_t found = std::distance(highest_in_sequence.begin(), iter);
            cout << "bin: " << *iter << "," << found << endl;
            highest_in_sequence[found] = v[i];
            length_of_sequence[found] ++;
        }
    }
    for (int i = 0; i < num_sequences; i++) {
        cout << highest_in_sequence[i] << "," << length_of_sequence[i] << endl;
    }
    return 0;
}

int main()
{
    std::vector<int32_t> v = { 1, 4, 8, 0, 3, 12 };
    LIS(v);
}
