#include <iostream>

using namespace std;

class MinHeap
{
    // smallest on top

    static constexpr int32_t kMaxN = 8;
    int32_t arr_[kMaxN];
    int32_t last_ = 0; // holds data

    public:

    void HeapifyUp(int32_t cur)
    {
        int32_t parent = cur >> 1;
        if (cur == 1) return;
        while (arr_[cur] < arr_[parent])
        {
            std::swap(arr_[cur], arr_[parent]);
            cur = parent;
            parent = cur >> 1;
            if (cur == 1) {
                break;
            }
        }
    }

    void HeapifyDown(int32_t cur)
    {
        while (cur <= last_) 
        {
            int left_child = (cur << 1);
            int right_child = (cur << 1) + 1;
            int32_t new_cur = -1;
            if (left_child < last_ && arr_[cur] > arr_[left_child])
            {
                new_cur = left_child;
            } 
            if (right_child < last_ && arr_[cur] > arr_[right_child]) 
            {
                new_cur = right_child;
            }
            if (new_cur != -1) {
                std::swap(arr_[cur], arr_[new_cur]);
                cur = new_cur;
            } else {
                 break;
            }
        }
    }

    /**
     *  if cur >= kMaxN return
     *  arr[cur] = new
     *  HeapifyUp(cur) { while arr[parent(cur)] > arr[cur] swap }
     */
    int32_t Insert(int32_t num)
    {
        if (last_ >= kMaxN - 1) {
            return -1;
        }
        arr_[++last_] = num;
        HeapifyUp(last_);
        return 0;
    }

    /**
     * retval = arr[0]
     * exchange 0 and last 
     * delete last
     * HeapifyDown(0);
     */
    int32_t Pop()
    {
       if (last_ == 0) return -1;

       int32_t retval = arr_[1];
       std::swap(arr_[1], arr_[last_]);
       last_ = last_ - 1;
       HeapifyDown(1);
       return retval;
    }

    void Print()
    {
        cout << last_ << ":";
        for (int i = 1; i <= last_; i++)
        {
            cout << arr_[i] << ",";
        }
        cout << endl;
    }
};

int main()
{
    auto m = MinHeap();
    for (int i = 12; i > 0; i--)
    {
        if (m.Insert(i) == -1) {
            cout << "failed insert " << i << endl;
            break;
        }
        m.Print();
    }
    cout << "popping" << endl;
    while (1)
    {
        int ret = m.Pop();
        if (ret == -1) break;
        m.Print();
    }
}
