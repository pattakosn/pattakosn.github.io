---
title: "Multidimensional arrays in C/C++"
date: 2022-12-09T00:01:06+01:00
draft: true
---
# Multidimensional arrays in C
In my first post I wrote about dynamic allocation of multidimensional arrays (2D, 3D, etc).
While writing it, I realized that multidimensional arrays in C are worth discussing.
So, here it comes!


I will use the same example:

```C++
#include <cstddef>
#include <ctime>
#include <cstdlib>

int main(int, char*[])
{
    const size_t N = 1024;
    double data[N][N];

    srand (static_cast <unsigned> (time(0)));
    for( size_t i = 0; i < N; ++i )
        for( size_t j = 0; j < N; ++j )
            data[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
```

## Arrays as function argument
In C, arrays are not passed as arguments to functions directly, instead "they decay to pointers" but they only do so once, so arrays of dimension N are passed as pointer to an array of size N-1.
This means that this works:
```C++
#include <stdio.h>
void func(int array[], int size) {
    printf("%i %i %i\n", array[0],array[1], array[2]);
}
int main(int, char*[]) {
    int array[3] = {1,2,3};
    func(array, sizeof(array));
}

```
but this doesn't:
```C++
#include <stdio.h>
void func(int array[][], int size) {
    printf("%i %i %i\n", array[0][0],array[1][1], array[2][2]);
}
int main(int, char*[]) {
    int array[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    func(array, sizeof(array[0]));
}
```
and one has to either explicitelly specify higher dimensions' sizes:
```C++
void func(int (*array)[3], int size) {
  ...
}
int main() {
    int array[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    func(array,sizeof(array[0]);
}
```
which is usually not acceptable as we need overloaded functions for arrays of different sizes or use C99:
```C++
void func(int x, int y, int array[x][y]) {
    printf("%i %i %i\n", array[0][0],array[1][1], array[2][2]);
}
int main(int argc, char*[]) {
    int array[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    func(3, 3, array);
}
```
One final solution is to pass a pointer to the beginning of the memory block and the dimensions' sizes:
```C++
void func(int *p, size_t M, size_t N) {
  size_t i, j;
  ...
  p[i*N+j] = ...;
}
int main() {
    int array[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    func(&array[0][0], 3, 3);
}
```
This one has often been the prefered solution and I also like it best as it can also be used with `malloc`ed arrays.
It's main drawback is that the `i*N+j` notation is not very easy to use and implement algorithms but one can use macros to simplify it.

