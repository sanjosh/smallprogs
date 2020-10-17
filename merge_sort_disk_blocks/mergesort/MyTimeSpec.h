#ifndef MYTIMESPEC_H
#define MYTIMESPEC_H

#define ONE_SEC 1000000000

#include <time.h>
#include <string.h> // for memcpy
#include <strings.h> // for bzero
#include <stdint.h> // for uint64
#include <iostream>
#include <math.h> // for sqrt

struct MyTimeSpec
{
	uint64_t a;
	MyTimeSpec() 
	{
		a = 0;
	}
	MyTimeSpec(timespec& in) 
	{ 
		a = (in.tv_sec * ONE_SEC) + in.tv_nsec;
	}

	MyTimeSpec& operator += (unsigned long nsecs)
	{
		a += nsecs;
		return *this;
	}
	MyTimeSpec& operator += (const MyTimeSpec& other)
	{
		a += other.a;
		return *this;
	}

	MyTimeSpec& operator -= (unsigned long nsecs)
	{
		a -= nsecs;
		return *this;
	}

	unsigned long operator / (unsigned long nsec) const
	{
		return (a / nsec);
	}

	int operator > (const MyTimeSpec& other) const
	{
		return other.operator<(*this);
	}

	int operator < (const MyTimeSpec& other) const
	{
		if (a < other.a) return 1;
		return 0;
	}

	MyTimeSpec (const MyTimeSpec& other)
	{
		a = other.a;
	}
	
	void operator = (uint64_t other)
	{
		a = other;
	}
	void operator = (const MyTimeSpec& other)
	{
		a = other.a;
	}
	
	MyTimeSpec operator + (unsigned long timeval) const
	{
		MyTimeSpec sum;
		sum.a = a + timeval;
		return sum;
	}
	MyTimeSpec operator + (const MyTimeSpec& other) const
	{
		MyTimeSpec sum;
		sum.a = a + other.a;
		return sum;
	}
	MyTimeSpec operator - (const MyTimeSpec& other) const
	{
		MyTimeSpec diff;
		diff.a = a - other.a;
		return diff;
	}
	int isZero() const
	{
		return (a == 0);
	}
	void setZero() 
	{
		a = 0;
	}
	void getCurrentTime() 
	{
		struct timespec atime;
		clock_gettime(CLOCK_MONOTONIC, &atime);
		a = (atime.tv_sec * ONE_SEC) + atime.tv_nsec;
	}
	void setTime(struct timespec* settime)
	{	
		a = (settime->tv_sec * ONE_SEC) + settime->tv_nsec;
	}
	void setTime(unsigned long sec, unsigned long nsec) 
	{
		a = (sec * ONE_SEC) + nsec;
	}
	void getTimeSpec(struct timespec* ret) const
	{
		ret->tv_sec = a/ONE_SEC;
		ret->tv_nsec = a%ONE_SEC;
	}
    static void computeStats(MyTimeSpec& oldave, 
           const MyTimeSpec& newnum, 
           int numExecs, 
           MyTimeSpec* deltaSquarePtr = NULL,
           MyTimeSpec* variancePtr = NULL,
           MyTimeSpec* stddeviationPtr = NULL)
    {
        int64_t delta = newnum.a - oldave.a; // can be negative
        oldave += (delta/numExecs);
        if (!deltaSquarePtr) return;
        deltaSquarePtr->a +=  (delta) * (delta);
        if (!variancePtr) return;
        *variancePtr += (*deltaSquarePtr)/(numExecs);
        if (!stddeviationPtr) return;
        stddeviationPtr->a = sqrt(variancePtr->a);
    }
	friend std::ostream& operator << (std::ostream& ostr, const MyTimeSpec& me);
};

inline std::ostream& operator << (std::ostream& ostr, const MyTimeSpec& me)
{
	ostr <<	me.a/ONE_SEC << ":" << me.a%ONE_SEC;
	return ostr;
}

#endif // MYTIMESPEC_H
