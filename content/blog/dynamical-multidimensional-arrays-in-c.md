---
title: "Dynamically allocated multidimensional arrays in C/C++"
date: 2022-12-05T23:16:05+01:00
draft: true
---
# Solved problem! Boring...
Multidimensional arrays might sound like a solved problem and definitelly not a 2022 thing.
Yet, it is more complex than it seems - as I found out quite a number of years ago - and there are several details involved.
I will try to present them along with some benchmarks.

# Problem statement: static allocation
Multidimensional arrays (ie arrays of dimension > 1) are provided by C/C++ so one can simply use sth like:
```C++
#include <cstddef>
#include <ctime>
#include <cstdlib>
//#include <iostream>

int main(int, char*[])
{
    const size_t N = 1024;
    double data[N][N];

    srand (static_cast <unsigned> (time(0)));
    for( size_t i = 0; i < N; ++i )
        for( size_t j = 0; j < N; ++j )
            data[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    //data[0][0] = 0;
    //data[1023][1023] = 0;
    //std::cout << data[0][0] << data[1023][1023];
}
```
Multidimensional arrays can be allocated like this but there are issues about it.
There are workarounds and practices for these but there is an even worst issue.

## stack limits/pressure
Anyone who has ever tried sth similar to the code aboveis very likely to have had a `segmentaion fault(core dumped)`. 
This is a "stack allocated" array and there are often stack limits.
That's right, an array of *1Mb * sizeof(double)* (most likely 8Mb) might be too much!
Now, one might be able to solve this by simply asking his system to increase this limit (eg on linux by `ulimit -s unlimited`) but this is not always allowed and not a good technical solution as one should not use the stack for memory allocation.

(fun fact, linux uses "lazy allocation" so declaring the array without initializing all its values wouldn't result in a crash, try the commented code to see for yourself).

# Going dynamic
So, how do we allocate 2D, 3D, etc arrays on the heap (ie dynamically)?
