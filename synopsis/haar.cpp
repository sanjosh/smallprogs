#include <iostream>
#include <cmath>
#include <strings.h>

// https://people.sc.fsu.edu/~jburkardt/c_src/haar/haar.c
//
#define NUM 16

void haar(double input[], double output[], int sz)
{
  double s = sqrt(2.0);
  int k = sz;

  for (int i = 0; i < k; i++)
  {
    output[i] = input[i];
  }

  while (k > 1)
  {
    k = k >> 1;

    double temp[sz];
    bzero(temp, sizeof(double) * sz);

    for (int i = 0; i < k; i++)
    {
      // average
      temp[i] = (output[2*i] + output[2*i + 1])/s;
      // diff
      temp[i + k] = (output[2*i] - output[2*i + 1])/s;
    }
    for (int i = 0; i < k*2; i ++)
    {
      output[i] = temp[i];
    }
  }
}

void inv_haar(double input[], double output[], int sz)
{
  double s = sqrt(2.0);

  for (int i = 0; i < sz; i++)
  {
    output[i] = input[i];
  }

  int k = 1;
  while (k * 2 <= sz)
  {
    double temp[sz];
    bzero(temp, sizeof(double) * sz);

    for (int i = 0; i < k; i++)
    {
      temp[2*i] = (output[i] + output[i + k])/s; 
      temp[2*i + 1] = (output[i] - output[i + k])/s; 
    }
    for (int i = 0; i < k*2; i ++)
    {
      output[i] = temp[i];
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

int main(int argc, char* argv[])
{

  // create CDF first
  // implement range query
  double input[NUM] = {1, 1, 3, 4,
    6, 9, 121, 125,
    200, 233, 254, 396,
    400, 503, 544, 566};

  double output[NUM];

  printme(input, NUM);

  haar(input, output, NUM);

  printme(output, NUM);

  for (int thres = 1.0f; thres < 100.0f; thres += 5.0f)
  {
    for (int i = 0; i < NUM; i++)
    {
      // zero out smaller coeff 
      if (abs(output[i]) < thres)
      {
        output[i] = 0;
      }
    }
    std::cout << "thres=" << thres << "--";

    double input_back[NUM];
    inv_haar(output, input_back, NUM);
    printme(input_back, NUM);
  }
}

