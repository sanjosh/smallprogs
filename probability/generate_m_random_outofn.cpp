
Bentley Programming Pearls

how to generate m random numbers in range [1..n] where m < n
dont want same number repeated

============

for (i = 1..n)
{
    //select an m from remaining n-i
    if (rand % n-i) < m
    {
        print i;
        m --
    }
}

recursive which prints random ints in decreasing order

randselect(m, n)
    if (m > 0)
        if (bigrand % n) < m
            print -1   
            randselect (m-1, n-1)
        else
            randselect(m,  n-1)

============

while (m)
{
    if (!set.find(num=rand())
        set.insert(num)
    m--
}

===============

shuffle n-elem array and output first m elem

shuffle()
{
    for i = 0..n-1
        j = randint(i, n-1)
        swap(x[i], x[j])
    sort (x, x+m)
    output first m elem of x
}
==============
