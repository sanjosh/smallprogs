'''
https://stackoverflow.com/questions/45442396/a-pure-python-way-to-calculate-the-multiplicative-inverse-in-gf28-using-pytho
'''

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

def gf_degree(a) :
    res = 0
    a >>= 1
    while (a != 0):
        a >>= 1
        res += 1
    return res

def gf_invert(a, mod=0x1B) :
    v = mod
    g1 = 1
    g2 = 0
    j = gf_degree(a) - 8

    while (a != 1):
        if (j < 0):
            a, v = v, a
            g1, g2 = g2, g1
            j = -j

        a ^= v << j
        g1 ^= g2 << j

        a %= 256  # Emulating 8-bit overflow
        g1 %= 256 # Emulating 8-bit overflow

        j = gf_degree(a) - gf_degree(v)

    return g1

def main():
    grid = np.zeros((256, 256))
    x = []
    y = []
    df_list = []
    for i in range(1, 256):
        inv = gf_invert(i)
        inv_inv = gf_invert(inv)
        assert(inv_inv == i)
        #print(i, " -> ", inv)
        x.append(i)
        y.append(inv)
        grid[x, y] = 1
        grid[y, x] = 1
    df = pd.DataFrame(list(zip(x, y)), columns=["x", "y"])
    sns.scatterplot(data=df, x="x", y="y")
    plt.show()

if __name__ == '__main__':
    main()