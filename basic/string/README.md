
* Boyer-Moore
* KMP
* Factorization algo 
* Suffix tree
* Trie
* Burrows-Wheeler

find substr & its anagram in longer string

find palindromes in string

edit distance

rabin fingerprint

regular expr search

reverse words in string

print all permutations of string

eliminate duplicate char from str

find if string is interleaving of 2 other strings

reverse min number of elem to get lexicographically smaller string

edit distance

longest common subsequence

# pattern search

Three approaches

1. prefix : KMP
2. suffix : Boyer-Moore, Horspool
3. factor match :

---

strings

    depends on size of alphabet, needle size

http://www-igm.univ-mlv.fr/~lecroq/string/index.html

    strstr : gnulibc uses two-way matching (factor pattern into 2), use machine words, dont compare after pos > (len(str) - len(substr))
     "Simple Real-Time Constant-Space String Matching" algorithm by Dany Breslauer, Roberto Grossi, and Filippo Mignosi.

    longest subsequence

    how to elim duplicates inplace (keep 2 ptrs)

---

Boyer-Moore

bad character rule - form array which contains rightmost position of every char in pattern

Given text T and pattern P
 if T[k] letter mismatched with P[i] letter
   shift P along by max[1,i-RightMost(T[k])] 

http://somemoreacademic.blogspot.in/2012/09/boyer-moore-string-matching-algorithm.html

worst case when pattern has all same char
    
---

## suffix tree

## suffix array ( sorted on suffixes)

## LCP array (longest common prefix between 2 entries in suffix array)

Augmenting the suffix array with the LCP array allows one to efficiently simulate top-down and bottom-up 
traversals of the suffix tree,[1][2] speeds up pattern matching on the suffix array[3] and is a 
prerequisite for compressed suffix trees.[4]

---

## multiple patterns search (fixed len)

Rabin-Karp algo

Commentz-Walter - used in gnu grep

---

## match based on reg exp - use FSA

---

## smallest window

https://www.geeksforgeeks.org/find-the-smallest-window-in-a-string-containing-all-characters-of-another-string/

---

## longest common extension

https://www.geeksforgeeks.org/longest-common-extension-lce-set-2-reduction-rmq/