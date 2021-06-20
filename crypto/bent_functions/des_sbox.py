from itertools import product
from sympy import fwht, ifwht

'''
each s-box has 6 input bits and 4 output bits
6 input bits are result of XOR of key and data
4 rows and 16 columns
6 input bits : 2 select row, 4 select column
each entry in S-box is a 4-bit number

decryption : same keys used in reverse order in different rounds in key schedule
'''

# For any even , a Boolean function f(x) = x1x2 ⊕ x3x4 ⊕⋯ ⊕ xn−1xn is a classic example of a bent function

bits = list(range(2))
b4 = list(product(bits, bits, bits, bits))

def bent_4(x0, x1, x2, x3):
    return (x0&x1) + (x2&x3)

def bent_4_1(x0, x1, x2, x3):
    return (x0 & x3) + ((x0 + x2) & x1) + x2 + x0

def normal(x0, x1, x2, x3):
    return x1 ^ x3 ^ x2 ^ x0

def main():
    truth_table = [ bent_4(*x)%2 for x in b4]
    transform_seq = fwht(truth_table)
    is_bent = len(list(filter(lambda x: abs(x) != 2, transform_seq))) == 0
    print(truth_table)
    print(transform_seq)
    print(is_bent)

if __name__ == '__main__':
    main()