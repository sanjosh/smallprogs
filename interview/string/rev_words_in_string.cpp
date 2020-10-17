
TODO
That is, given a sentence like this


I am a good boy


The in place reverse would be


boy good a am I



Method1

First reverse the whole string and then individually reverse the words


I am a good boy
<------------->

yob doog a ma I
<-> <--> <-> <-> <->

boy good a am I



Here is some C code to do the same ....


/*
Algorithm..

1. Reverse whole sentence first.
2. Reverse each word individually.

All the reversing happens in-place.
*/

#include

void rev(char *l, char *r);


int main(int argc, char *argv[])
{
char buf[] = "the world will go on forever";
char *end, *x, *y;

// Reverse the whole sentence first..
for(end=buf; *end; end++);
rev(buf,end-1);


// Now swap each word within sentence...
x = buf-1;
y = buf;

while(x++ < end)
{
if(*x == '\0' || *x == ' ')
{
rev(y,x-1);
y = x+1;
}
}

// Now print the final string....
printf("%s\n",buf);

return(0);
}


// Function to reverse a string in place...
void rev(char *l,char *r)
{
char t;
while(l < r)
{
t = *l;
*l++ = *r;
*r-- = t;
}
}





Method2
Another way to do it is, allocate as much memory as the input for the final output. Start from the right of the string and copy the words one by one to the output.


Input : I am a good boy
< --
< -------
< ---------
< ------------
< --------------


Output : boy
: boy good
: boy good a
: boy good a am
: boy good a am I


The only problem to this solution is the extra space required for the output and one has to write this code really well as we are traversing the string in the reverse direction and there is no null at the start of the string to know we have reached the start of the string!. One can use the strtok() function to breakup the string into multiple words and rearrange them in the reverse order later.


Method3

Create a linked list like



| I | -> | < spaces > | -> | am | -> | < spaces > | -> | a | -> | < spaces > | -> | good | -> | < spaces > | -> | boy | -> | NULL |



Now its a simple question of reversing the linked list!. There are plenty of algorithms to reverse a linked list easily. This also keeps track of the number of spaces between the words. Note that the linked list algorithm, though inefficient, handles multiple spaces between the words really well. 
