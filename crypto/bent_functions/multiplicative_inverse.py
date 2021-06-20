'''
https://stackoverflow.com/questions/45442396/a-pure-python-way-to-calculate-the-multiplicative-inverse-in-gf28-using-pytho
'''

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
    print(gf_invert(5))   # 82
    print(gf_invert(1))   #  1
    print(gf_invert(255)) # 28

if __name__ == '__main__':
    main()