TODO
http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=dynProg

http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/DynProg/money-change.html

http://www.algorithmist.com/index.php/Min-Coin_Change

given denominations d1...dm
find min num of coins which make up N cents

C (N,m) = min(C(N,m - 1), C(N - Sm,m) + 1)

with the base cases:

    C(N,m) = 1,N = 0
    C(N,m) = 0,N < 0
    C( N, m ) = 0, N \geq 1, m \leq 0 
