#include <iostream>
#include <cmath>
#include <strings.h>

// https://people.sc.fsu.edu/~jburkardt/c_src/haar/haar.c
//
#define NUM 16

void haar(double input[], int sz)
{
  double s = sqrt(2.0);
  int k = sz;

  while (k > 1)
  {
    k = k >> 1;

    double temp[sz];
    bzero(temp, sizeof(double) * sz);

    for (int i = 0; i < k; i++)
    {
      // average
      temp[i] = (input[2*i] + input[2*i + 1])/s;
      // diff
      temp[i + k] = (input[2*i] - input[2*i + 1])/s;
    }
    for (int i = 0; i < k*2; i ++)
    {
      input[i] = temp[i];
    }
  }
}

void inv_haar(double input[], int sz)
{
  double s = sqrt(2.0);

  int k = 1;
  while (k * 2 <= sz)
  {
    double temp[sz];
    bzero(temp, sizeof(double) * sz);

    for (int i = 0; i < k; i++)
    {
      temp[2*i] = (input[i] + input[i + k])/s; 
      temp[2*i + 1] = (input[i] - input[i + k])/s; 
    }
    for (int i = 0; i < k*2; i ++)
    {
      input[i] = temp[i];
    }
    k = k << 1;
  }
}

void printme(double arr[], int sz)
{
  for (int i = 0; i < sz; i++)
  {
    std::cout << arr[i] << ",";
  }
  std::cout << std::endl;
}

int main()
{
  // create CDF first
  // implement range query
  double input[NUM] = {1, 12, 3, 4,
    6, 9, 121, 3,
    2, 33, 54, 45,
    1, 3, 4, 6};

  printme(input, NUM);

  haar(input, NUM);

  printme(input, NUM);

  for (int i = 0; i < NUM; i++)
  {
    // zero out smaller coeff 
    if (abs(input[i]) < 3.0)
    {
      input[i] = 0;
    }
  }

  printme(input, NUM);

  inv_haar(input, NUM);

  printme(input, NUM);
}

