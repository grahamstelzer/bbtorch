// tutorial via: https://developer.nvidia.com/blog/even-easier-introduction-cuda/
//   intro to cuda, add two elements of arrays with a million elements in each


// NOTE: tutorial is dumb lowkey
//  the cpp file compile with g++ or w/e
//  the cu file compile with nvcc (there are differences, run diff)

#include <iostream>
#include <math.h>



void add(int n, float* x, float* y) {
    for(int i = 0; i < n; i++) {
        y[i] = x[i] + y[i];
    }
}



int main(int argc, char* argv[]) {

    int N = 1<<20; // 1M elements (i think 1048576? 2^20)
    std::cout << N << std::endl;

    float* x = new float[N];
    float* y = new float[N];

    // init arrays on host
    for(int i = 0; i < N; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    // Run kernel on 1m elements on cpu
    add(N, x, y);

    // error check, array should be full of 3.0
    float maxError = 0.0f;
    for(int i = 0; i < N; i++) {
        maxError = fmax(maxError, fabs(y[i] - 3.0f));
    }
    std::cout << "max err: " << maxError << std::endl;

    // free mem
    delete [] x;
    delete [] y;

    return 0;
}