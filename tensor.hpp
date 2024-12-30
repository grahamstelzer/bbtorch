#include <iostream>
#include <ctime>


// NOTE: something I did not realize until starting this is that 
// generally matmults are bounded by memory not computation ability
// 
// This leaves me with 2 options (though not mutually exclusive):
// - build fast matmutls for cpu calcualtions
// - work on memory bounding > supposedly large enough matmutls are bounded
//   by computation considering n^3 growth 


// tensor creation syntax in python
// import torch
// # Create a tensor from a list
// data = [1, 2, 3]
// tensor = torch.tensor(data)
// # Create a tensor with specified shape and values
// tensor = torch.zeros((2, 3))  # Tensor of zeros
// tensor = torch.ones((2, 3))   # Tensor of ones
// tensor = torch.randn((2, 3))  # Tensor with random values

// also, https://en.wikipedia.org/wiki/Strassen_algorithm


template <typename T, short N> // short? might be better later for bitwise operations
class Tensor {
    public:
        Tensor(const T(&arr)[N]) { // input array of dim_sizes 

            short mem_block_size = 1;

            for(short i = 0; i < N; ++i) {
                mem_block_size *= arr[i];
            }

            unsigned int seed = static_cast<unsigned int>(time(0));
            
            // LCG ??
            unsigned long a = 1664525UL;  // multiplier
            unsigned long c = 1013904223UL;  // increment
            unsigned long m = 4294967296UL;  // 2^32

            // TODO: check bounds, currently [-1,1] but > 1 when??
            float* mem_block = new float[mem_block_size];
            for(short i = 0; i < mem_block_size; ++i) {
                seed = (a * seed + c) % m;
                mem_block[i] = 2.0f * (static_cast<float>(seed) / static_cast<float>(m)) - 1.0f;
                // std::cout << mem_block[i] << " ";
            }
            
            
            this->_dim = N;
            this->_dim_sizes = arr;
            this->_mem_block_size = mem_block_size;
            this->_mem_block = mem_block;
        }

        int getDim() { return this->_dim; }
        const int* getDimSizes() { return this->_dim_sizes; }
        short getMemBlockSize() { return this->_mem_block_size; }

        ~Tensor() {
            std::cout << "deletion called\n";
            delete[] this->_mem_block;
        }


        Tensor operator*(Tensor t2) {
            int t2_dim = t2.getDim();
            std::cout << t2_dim << std::endl;

            // base matmult will be AxB * BxC = A*C
            // since max 4 dims for these, 2d matrix dimensions will be last 2
            // values in _dim_sizes for both input tensors

            // top tensor dimension should stay the same?
            // (2 groups of 3 groups of 4 by 512 matrices) * (2 groups of 3 groups of 4 by 512 matrices) = 

            Tensor ret_tensor()

            return ret_tensor;
        }

    private:
        int _dim; // 1 to 4 TODO: implement 5
        const int* _dim_sizes; // [2, 3, 4, 5] steps for each
        short _mem_block_size;
        float* _mem_block;
};