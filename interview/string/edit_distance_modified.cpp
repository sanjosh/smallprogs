
Question 2. There is a string whose characters can only be either ‘a’, ‘b’ or ‘_’ (there can be only one ‘_’ in the string). At each step, we can modify the string as follows:
1. ‘_’ can be swapped with its adjacent character, example “a_ba” can be changed to either “_aba” or “ab_a”.
2. Two characters adjacent to ‘_’ (both on the same side of ‘_’) can be reversed along with the ‘_’ if both characters are different, example, “aa_ba” can be changed to “aaab_” but not to “_aaba” because both characters are ‘a’.
You are given two strings, the initial state and the final state (lengths will be same), you have to output the minimum number of steps required to change the string in initial state to the string in the final state.
example:
input: a_b ab_
output: 1
input: abaa_a b_aaaa
output: 4
reason for example 2:- abaa_a -> aba_aa -> ab_aaa -> _baaaa -> b_aaaa

Hint: Use Breadth first search
