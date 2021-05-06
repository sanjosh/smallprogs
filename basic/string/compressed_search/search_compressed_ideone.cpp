
#include<iostream>
#include<algorithm>
#include<assert.h>
#include<ctype.h>
#include<string>
 

// http://ideone.com/nzSNCm

using namespace std;
typedef long long ll;
main()
{
    string str;
    cin>>str;

    int n=str.length();

    int len[n];

    len[0]=1;

    ll ii=0;

//len[i] is the length of string till ith element

    for(int i=1;i<n;i++)
    {
        if (!(isdigit(str[i])))
        {
            // char
            len[i]=len[i-1]+1;  
            ii=0;
        }
        else
        {
            // digit
            ii= ii*10 + (str[i]-'0');

            if(i+1<n)
            {
                    if(!(isdigit(str[i+1])))        
                    {
                        // digit followed by char
                        len[i]=len[i-1]*ii;
                        ii=0;
                    }
                    else 
                    {
                        // digit followed by digit
                        len[i]=len[i-1];
                    }
            }
        }
    }

    len[n-1]=len[n-2]*ii;

    for(int i=0;i<n;i++)
    {
        cout<< len[i] << endl;
    }
 
    for (ll index = 1; index <= len[n-1]; index++)
    {
        ll k = index;

        //cout << "for k =" << k << endl;
        bool flag=1;

        for(int i = n-1;i >= 0; i--)
        {
            // TODO : doesnt work for multi-digit repetitions
            if (isdigit(str[i]) && flag)
            {
                  k = k % len[i-1];

                  //cout << "k is decr to=" << k << " after len=" << len[i-1] << endl;

                  flag=0;

                  if(k==0)
                  {
                       cout<<str[i-1]<<" ";
                       break;  
                  }
            }
            else if(!(isdigit(str[i]))) 
            {
                flag = 1;

                if (k==len[i])
                {
                    cout<<str[i]<<" ";
                }
            }
        }
    }
    cout << endl;
}
