from sympy import fwht, ifwht
from itertools import product

'''
http://man.hubwiz.com/docset/SymPy.docset/Contents/Resources/Documents/_modules/sympy/discrete/transforms.html

The Walsh spectrum of a Boolean function is the product of its binary string (as a row vector) with a Walsh matrix.
https://en.wikiversity.org/wiki/3-ary_Boolean_functions

https://mathworld.wolfram.com/BooleanFunction.html

https://commons.wikimedia.org/wiki/Category:2-ary_Boolean_functions
https://math.stackexchange.com/questions/415152/is-it-possible-to-derive-all-the-other-boolean-functions-by-taking-other-primiti

total 16 = 2^2^k (where k = 2) functions for 2-ary
'''

# list of 16 2-variable boolean func
y0 = lambda x,y : 0  # linear
y1 = lambda x,y : x & y  # bent
y2 = lambda x,y : x & ~y  # bent
y3 = lambda x,y : x  #linear
y4 = lambda x,y : ~x & y  # bent
y5 = lambda x,y : y  # linear
y6 = lambda x,y : x ^ y  #(x & ~y) | (~x & y)   #linear (XOR)
y7 = lambda x,y : x | y # linear
y8 = lambda x,y : ~(x | y)  # bent
y9 = lambda x,y : (x & y) | ( ~x & ~y)  # affine = y6 + 1
y10 = lambda x,y : ~y  # affine  = y5 + 1
y11 = lambda x,y : x | ~y
y12 = lambda x,y : ~x  # affine = y3 + 1
y13 = lambda x,y : ~x | y
y14 = lambda x,y : ~(x & y)
y15 = lambda x,y : 1   # affine

'''
A bent function is a Boolean function in n variables (n is even) 
such that for any nonzero vector y its derivative 
Dyf(x) = f(x) ⊕ f(x ⊕ y) is balanced—that is, 
it takes values 0 and 1 equally often
'''


'''

There are 8 linear and affine
(00, 01, 10, 11)
0000
0101 - 
0011 - 
0110

1111 - 
1010
1100
1001

there are 4 bent (0001, 0010, 0100, 1000)
every bent func in 2-ary has hamming weight of 1

For n binary variables, the total number of affine Boolean function is exp(2, n+1) out of which exp(2, n) are linear
the 16 affine Boolean functions for 3-variable are 0, 60, 90, 102, 150, 170, 204, 240, 15, 51, 85, 105, 153, 165, 195, 255
out of which first eight are linear

'''

func_list = [y0, y1, y2, y3, y4, y5, y6, y7, y8, y9, y10, y11, y12, y13, y14, y15]

affine_func_set = frozenset([y9, y10, y12, y15])
linear_func_set = frozenset([y0, y3, y5, y6])
bent_func_set = frozenset([y1, y2, y4, y8])

'''
The Walsh-Hadamard transform returns sequency values. 
Sequency is a more generalized notion of frequency and is defined as one half of the average number of zero-crossings per unit time interval. 
https://in.mathworks.com/help/signal/ug/walshhadamard-transform.html

Walsh coefficient is atmost +/- exp(2, n)

Bent if absolute value of all Walsh coefficients is exp(2, n/2)

Linear has some Walsh coefficients as zero
'''


bits = list(range(2))
nums = (list(product(bits, repeat=2)))

truth_table = lambda  f : [f(x, y) % 2 for x, y in nums]

def hamming_distance(f1_seq, f2_seq):
    count = 0
    for s1, s2 in zip(f1_seq, f2_seq):
        count += (s1 != s2)
    return count

def main():
    print(nums)
    print("Function           :  Transform   :   Is Bent ")
    for idx, f in enumerate(func_list):
        seq = truth_table(f)
        transform_seq = fwht(seq)
        is_bent = len(list(filter(lambda x : abs(x) != 1, transform_seq))) == 0
        cseq = ifwht(transform_seq)
        assert seq == cseq
        print(idx, ":", seq, ":", transform_seq, ":", is_bent)

    print(" All bent functions ")
    for idx, f in enumerate(bent_func_set):
        seq = truth_table(f)
        transform = fwht(seq)
        affine_dist = [hamming_distance(seq, truth_table(af)) for af in affine_func_set]
        linear_dist = [hamming_distance(seq, truth_table(linear)) for linear in linear_func_set]
        min_dist = min(10, min(linear_dist), min(affine_dist))
        print(seq, transform, min_dist)

    print("all other nonlinear")
    for idx, f in enumerate(func_list):
        if f not in bent_func_set and f not in affine_func_set and f not in linear_func_set:
            seq = truth_table(f)
            transform = fwht(seq)
            affine_dist = [hamming_distance(seq, truth_table(af)) for af in affine_func_set]
            linear_dist = [hamming_distance(seq, truth_table(linear)) for linear in linear_func_set]
            min_dist = min(10, min(linear_dist), min(affine_dist))
            print(seq, transform, min_dist)

if __name__ == '__main__':
    main()

'''
F(X, Y) = F1(X) + F2(Y) : this is linear

F(X, Y) - terms which are higher degree = (x&y) + (y&z) 

XOR = add mod 2 = linear
'''
