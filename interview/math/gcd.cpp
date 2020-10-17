
int gcd(int a, int b)
{
    int temp;

    while(b)
    {
        temp = a % b;
        a = b;
        b = temp;
    }

    return(a);
}


