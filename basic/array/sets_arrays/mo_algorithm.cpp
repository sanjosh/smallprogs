
/*
https://www.hackerearth.com/practice/notes/mos-algorithm/
https://www.geeksforgeeks.org/mos-algorithm-query-square-root-decomposition-set-1-introduction/

The idea of MO’s algorithm is to pre-process all queries so that result of one query can be used in next query. Below are steps.

Sort all queries in a way that queries with L values from 0 to √n – 1 are put together, 
then all queries from √n to 2*√n – 1, and so on. 
All queries within a block are sorted in increasing order of R values.

query takes O(n * √n) + O(m * √n) 


*/
