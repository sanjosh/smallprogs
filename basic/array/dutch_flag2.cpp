
#include <iostream>
using namespace std;

int swap(int& one, int& two) {
    int tmp = one;
    one = two;
    two = tmp;
    return 0;
}

int sort012(int arr[], int arr_size) {

    int lo = 0;
    int hi = arr_size - 1;
    int mid = 0;

        while (arr[hi] == 2) {
            hi --;
        }
        while (arr[lo] == 0) {
            lo ++;
        }
        mid = lo;

    while (mid <= hi) {
        if (arr[mid] == 0) {
            swap(arr[lo], arr[mid]);
            cout << "loswap: " << lo << "," << mid << endl;
            lo ++;
        }
        else if (arr[mid] == 2) {
            swap(arr[hi], arr[mid]);
            cout << "hiswap: " << hi << "," << mid << endl;
            hi --;
        }
        mid ++;
    }
    return 0;
}

int main() {
    int a[] = {0, 2, 0, 2, 1, 2};
    int len = sizeof(a)/sizeof(a[0]);
    sort012(a, len);
    for (int i = 0; i < len; i++)
        cout << a[i] << ",";
    cout << endl;

}
