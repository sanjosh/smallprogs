

int pow(int x, int y)
{
    if(y == 1) return x ;
    return x * pow(x, y-1) ;
}


//Divide and Conquer C program


#include < stdio.h >
int main(int argc, char*argv[])
{
    printf("\n[%d]\n",pow(5,4));
}

int pow(int x, int n)
{
    if(n==0)    return(1);
    else if(n%2==0)
    {
        return(pow(x,n/2)*pow(x,(n/2)));
    }
    else
    {
        return(x*pow(x,n/2)*pow(x,(n/2)));
    }
}

