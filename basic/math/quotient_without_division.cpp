#include <iostream>
#include <climits>

using namespace std;

int divide(int dividend, int divisor) {
    int mult = 1;
    if (!(divisor < 0) != !(dividend < 0)) {

        mult = -1;
    }
    if (abs(divisor) == abs(dividend)) {
        return mult;
    }
    if (abs(divisor) == 1) {
        if (dividend == INT_MAX) {
            if (mult == -1) return -INT_MAX;
            return INT_MAX;
        } else if (dividend == INT_MIN) {
            if (mult == -1) return INT_MIN;
            return INT_MAX;
        }
        if (mult == -1) {
            return -abs(dividend);
        }

        return abs(dividend);
    }
    unsigned int quotient = 0;
    unsigned int abs_dividend = abs(dividend);
    unsigned int abs_divisor = abs(divisor);
    int new_divisor_count = 1;
    int new_divisor = abs_divisor;

    while (abs_dividend >= abs_divisor) {
        while (abs_dividend >= new_divisor) {
            abs_dividend -= new_divisor;
            quotient += new_divisor_count;
            if (new_divisor < (INT_MAX >> 1)) {
                new_divisor += new_divisor;
                new_divisor_count += new_divisor_count;
            }
        }
        if (new_divisor_count > 1) {
            while (abs_dividend < new_divisor) {
                new_divisor_count = new_divisor_count >> 1;
                new_divisor = new_divisor >> 1;
            }
        }
    }

    if (mult == -1) {
        return -quotient;
    } else {
        return quotient;
    }
}


int find_best_divisor_first(int dividend, int divisor)
{
        int mult = 1;
        if (!(divisor < 0) != !(dividend < 0)) {

            mult = -1;
        }
        if (abs(divisor) == abs(dividend)) {
            return mult;
        }
        if (abs(divisor) == 1) {
            if (dividend == INT_MAX) {
                if (mult == -1) return -INT_MAX;
                return INT_MAX;
            } else if (dividend == INT_MIN) {
                if (mult == -1) return INT_MIN;
                return INT_MAX;
            }
            if (mult == -1) {
                return -abs(dividend);
            }

            return abs(dividend);
        }
        unsigned int quotient = 0;
        unsigned int abs_dividend = abs(dividend);
        unsigned int abs_divisor = abs(divisor);

        int new_divisor_count = 1;
        int new_divisor = abs_divisor;

        while (abs_dividend >= new_divisor) {
                if (new_divisor < (INT_MAX >> 1)) {
                    new_divisor += new_divisor;
                    new_divisor_count += new_divisor_count;
                } else {
                    break;
                }
        }
        while (abs_dividend >= abs_divisor) {
            if (abs_dividend >= new_divisor) {
                abs_dividend -= new_divisor;
                quotient += new_divisor_count;
            } 
            new_divisor -= abs_divisor;
            new_divisor_count --;
        }

        if (mult == -1) {
            return -quotient;
        } else {
            return quotient;
        }
}

int main()
{
    cout << f(INT_MIN, -1) << endl;
    cout << f(INT_MIN, 1) << endl;
    cout << f(INT_MAX, -1) << endl;
    cout << f(INT_MAX, 1) << endl;
    cout << f(2590, 10) << endl;
}
