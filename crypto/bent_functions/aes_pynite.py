import pyfinite
from pyfinite import ffield

def main():
    F = ffield.FField(3)
    generator_poly = F.ConvertListToElement(l=[1, 0, 1  , 1])
    F = ffield.FField(3, gen=generator_poly)
    print(F.ShowPolynomial(11))
    x = F.Inverse(3)
    y = F.Inverse(x)
    assert y == 3
    for i in range(pow(2, 3) + 100):
        print(F.ShowPolynomial(F.Add(i, 1)))

if __name__ == '__main__':
    main()
