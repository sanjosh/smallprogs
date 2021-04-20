

For first segment going to distance x
   Bananas left at x = N - (2N/C - 1).x
   cost of 5 bananas/km
   if x=100, N= 3000 - 5.100 = 2500
   if x=200, N= 3000 - 5.200 = 2000
   if x=300, N= 3000 - 5.300 = 1500
   if x=400, N= 3000 - 5.400 = 1000

For second segment going to y (i.e. total=x+y)
    Bananas left at y = N - (2N/C - 1).y
   cost of 3 bananas/km
    if y=333, N=2000 - 3.333 = 1000

For third segment
    Bananas left at z = N - (2N/C - 1).z
    cost of 1 banana/km
    if z=466, N=1000 - 1.466 = 533

    ====================

https://in.answers.yahoo.com/question/index?qid=20090114220238AAZHj9u

http://math.stackexchange.com/questions/53526/how-many-bananas-can-a-camel-deliver-without-eating-them-all


A banana plantation is located next to a desert. The plantation owner has 3000 bananas that he wants to transport to the market by camel, across a 1000 kilometre stretch of desert. The owner has only one camel, which carries a maximum of 1000 bananas at any moment in time, and eats one banana every kilometre it travels.

The Question: What is the largest number of bananas that can be delivered at the market?


The Solution: 533 1/3 bananas.

Explanation: Since there are 3000 bananas and the camel can carry at most 1000 bananas, at least five trips are needed to carry away all bananas from the plantation P (three trips away from the plantation and two return trips):




    P (plantation)

    ===forth===>
    <===back====
    ===forth===>
    <===back====
    ===forth===>

    A




    Point A in the abouve picture cannot be the market. This is because the camel can never travel more than 500 kilometres into the desert if it should return to the plantation (the camel eats a banana every kilometre it travels!). So point A lies somewhere in the desert between the plantation and the market. From point A to the next point, less than five trips must be used to transport the bananas to that next point. We arrive at the following global solution to the problem (P denotes the plantation, M denotes the market):




        P (plantation)

    ===forth===>
    <===back====
    ===forth===>
    <===back====
    ===forth===>

    A


    ===forth===>
    <===back====
    ===forth===>


    B



    ===forth===>



    M (market)




    Note that section PA must be in the solution (as explained above), but section AB or section BM might have a length of 0. Let us now look at the costs of each part of the route. One kilometre on section PA costs 5 bananas. One kilometre on section AB costs 3 bananas. One kilometre on section BM costs 1 banana. To save bananas, we should make sure that the length of PA is less than the length of AB and that the length of AB is less than the length of BM. Since PA is greater than 0, we conclude that AB is greater than 0 and that BM is greater than 0.

    The camel can carry away at most 2000 bananas from point A. This means the distance between P and A must be chosen such that exactly 2000 bananas arrive in point A. When PA would be chosen smaller, more than 2000 bananas would arrive in A, but the surplus can't be transported further. When PA would be chosen larger, we are losing more bananas to the camel than necessary. Now we can calculate the length of PA: 3000-5*PA=2000, so PA=200 kilometres. Note that this distance is less than 500 kilometres, so the camel can travel back from A to P.

    The situation in point B is similar to that in point A. The camel can't transport more than 1000 bananas from point B to the market M. Therefore, the distance between A and B must be chosen such that exactly 1000 bananas arrive in point B. Now we can calculate the length of AB: 2000-3*AB=1000, so AB=333 1/3. Note that this distance is less than 500 kilometres, so the camel can travel back from B to A. It follows that BM=1000-200-333 1/3=466 2/3 kilometres. As a result, the camel arrives at the market with 1000-466 2/3=533 1/3 bananas.

    The full scenario looks as follows: first, the camel takes 1000 bananas to point A. There it drops 600 bananas and returns with 200 bananas. Then the camel takes again 1000 bananas to point A. Again, it drops 600 bananas and returns with 200 bananas. After this, the camel takes the last 1000 bananas from the plantation to point A. From point A, it leaves with 1000 bananas to point B. In point B, it drops 333 1/3 bananas and returns with 333 1/3 bananas. Then it takes the second load of 1000 bananas from point A to point B. Finally, it carries the 1000 bananas from point B to the market, where it arrives with 533 1/3 bananas.

