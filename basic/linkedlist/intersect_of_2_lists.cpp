
http://www.geeksforgeeks.org/write-a-function-to-get-the-intersection-point-of-two-linked-lists/

1) turn one list into a circular list - then find loop in another
2) reverse first list 
 x + z = c1
 y + z = c2
 x + y = c3
solve to get z 


3) push nodes into 2 stacks; pop common nodes; last common is intersection

4) use difference of node counts
5) mark visited nodes
