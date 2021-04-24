#!/usr/bin/python3

import sys
from collections import defaultdict

def checkInclWithSorting(s1 : str, s2 : str) -> bool:
    found = False
    sorted_s1 = sorted(s1)
    for indx, c in enumerate(s2):
        if indx + len(s1) > len(s2):
            break
        ss = s2[indx : indx + len(s1)]
        if sorted_s1 == sorted(ss):              
            found = True
            break
    return found

def checkInclWithDictCompare(pattern : str, s2 : str) -> bool:

    found = False

    d = defaultdict(int)
    for c in pattern:
        d[c] = d[c] + 1
    e = defaultdict(int)

    for indx, c in enumerate(s2):

        e[c] = e[c] + 1

        if indx >= len(pattern):
            prev_char = s2[indx - len(pattern)]
            e[prev_char] = e[prev_char] - 1

        if indx + 1 >= len(pattern):
            found = True
            for k, v in d.items():
                if not k in e or e[k] != v:
                    found = False
                    break
            if found:
                break
               
    return found

def main():
    print(' its ', checkInclWithSorting(sys.argv[1], sys.argv[2]))
    print(' its ', checkInclWithDictCompare(sys.argv[1], sys.argv[2]))

if __name__ == "__main__":
    main()
             
