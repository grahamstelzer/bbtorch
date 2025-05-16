// tutorial via: https://developer.nvidia.com/blog/even-easier-introduction-cuda/
//   intro to cuda, add two elements of arrays with a million elements in each

#include <iostream>
#include <math.h>



__global__
void add(int n, float* x, float* y) {
    for(int i = 0; i < n; i++) {
        y[i] = x[i] + y[i];
    }
}



int main(int argc, char* argv[]) {

    int N = 1<<20; // 1M elements (i think 1048576? 2^20)
    // std::cout << N << std::endl;

    float *x, *y;
    cudaMallocManaged(&x, N*sizeof(float));
    cudaMallocManaged(&y, N*sizeof(float));

    // init arrays on host
    for(int i = 0; i < N; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    // Run kernel on 1m elements on cpu
    // !!NOTE!!: syntax change here, global function call with <<>>
    add<<<1, 1>>>(N, x, y);
    // first 1: number of blocks
    // second 1: number of threads per block
    // add: is the __global__ kernel function
    // <<<1, N>>> is the launch configuration

    // wait for gpu to finish
    cudaDeviceSynchronize();

    // error check, array should be full of 3.0
    float maxError = 0.0f;
    for(int i = 0; i < N; i++) {
        maxError = fmax(maxError, fabs(y[i] - 3.0f));
    }
    std::cout << "max err: " << maxError << std::endl;

    // free mem
    cudaFree(x);
    cudaFree(y);

    return 0;
}