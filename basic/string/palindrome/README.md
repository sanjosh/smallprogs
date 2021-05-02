
## palindrome in rotated string

find place where consecutive characters are same  
call it k and j=(k+1)   
from that point, check len/2 pairs (k--, j++) to see if they are same   

counterexample : if consecutive identical characters "aaaa", 
wait until all consecutive are identified
because you have to pick "a[aa]a" and not "[aa]aa"

counterexample : what if odd number of identical are found ?
then the center one could be the unpaired character
start from center

counterexample : what if one of the consecutive char is on other side of rotated string
ensure loop counts correctly

add rotated string to itself   
find if palindromic substring exists by manacher algo
if yes, rest should be another palindrome


---

## palindrome in substring

manacher algo

string S' = S with a bogus character (eg. '|')

becomes linear due to use of previously computed info (prev entries in LPS array)

palindromes 

https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-1/

https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-2/

https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-3-2/

https://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-4/

before starting next loop, see what u can reuse from previous computation

* MirroredCenter = OldCenter - (Center - OldCenter)
* palindrome at MirroredCenter lies completely inside the "Old" palindrome
* palindrome at MirroredCenter extends outside the "Old" palindrome. 
* palindrome at MirroredCenter extends exactly up to the border of the "Old" palindrome

https://en.wikipedia.org/wiki/Longest_palindromic_substring#Manacher.27s_algorithm

## center expansion algo

O(n^2) - inner loop can be N/2

https://www.geeksforgeeks.org/longest-palindromic-substring-set-2/

create hash index of char -> list of positions
only keep things which are 2 apart

if a[i] == a[i+1] 
    is possible center
if a[i] == a[i+2]:
   i+1 is possible center

possible center = each char with atleast dist = 0, 1 between occurences
e.g. g in pos={6, 7} or g in pos={6, 7, 8} 
e.g. g in pos={6, 8, 10, 12} - pick {6, 8}, {8, 10}, {10, 12}

for each possible center 
   window = [j, k]
   while window in array bounds
      if a[j] != a[k] break
      j ++ ; k --
   
complexity
length of string >> length of alphabet 
duplicates will always occur but how many at distance 1 or 2

how many max centers possible ?
string = aabbccdd
string = azabzbczc
about n/2 or n/3

how many comparisons across centers ?

how many successful comparisons

how many failed comparisons
prob (two char not being same) - birthday paradox

worst case : 
all char same
two char repeating

average case
zipf distribution
find quick elimination criteria

## palindrome formed by joining two pairs : LPS merger

quick checks a[0] == b[-1] or a[-1] == b[0]

use Manacher : 2 LPS arrays be merged ? 

let center = a[len1 + len2/2]

is LPS [center] > 1 ?

recompute center -> right of one
recompute left -> center of second

## palindrome by joining pairs : keep Trie of reversed words

if is substring and rest is palindrome

## detect palindrome in online : center check

if palindrome ending at A[cur index - 1] 
   if A[cur index] = A [ cur index - 1 - palindrome length ] 
      palindrome length += 2
      palindrome center = 

multiple palindromes possible ? yes

if A[cur] = A[cur-1] or A[cur] = A[cur-2]
  new palindrome detected


## detect palindrome in online : Rolling hash

rolling hash(reverse of first) = rolling hash(Second)

https://www.geeksforgeeks.org/online-algorithm-for-checking-palindrome-in-a-stream/

## count min number of insert to form palindrome

count occurence 

https://www.geeksforgeeks.org/minimum-insertions-to-form-a-palindrome-with-permutations-allowed/

## min insert to form palindrome

LCS (str, reverse(str))

https://www.geeksforgeeks.org/minimum-insertions-to-form-a-palindrome-dp-28/




