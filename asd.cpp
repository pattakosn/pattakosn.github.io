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

