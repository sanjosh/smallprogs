
/*
http://www.careercup.com/question?id=401540

TODO

Given a cube. A ant is placed in a corner and cannot move. 

A spider starts from the opposite corner, and can move along cube edges 
in any direction (x,y,z) with probablity 1/3. 

What is the expected number of steps for this spider to get to the ant?

===========

Let x represent the expected number of moves it takes to reach the ant 
when the spider is one move away (i.e., at any one of the three vertices of the cube adjacent to the ant). 

Let y represent the expected number of moves it takes to reach the ant 
when the spider is two moves away, and 

let z represent the expected number of moves it takes to reach the ant 
when the spider is three moves away (at the opposite vertex on the cube).

Then z = 1 + y, since after the first move, the spider will be one move away. 

From this point, there is a (2/3) chance that the spider will move to a vertex 

adjacent to the ant and there is a (1/3) chance he will move back to his starting position, 3 moves from the ant. 

Thus, y = 1 + (2/3)x + (1/3)z.

Similarly, x = (1/3)(1) + (2/3)(y + 1). 

This system of 3 equations with 3 unknowns has solution z=10, y=9, and x=7. 

So, it will take 10 steps to reach the ant, on average, from the spider's initial position.

TODO
*/

