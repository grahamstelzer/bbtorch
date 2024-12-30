#include <iostream>
#include "tensor.hpp"
#include <chrono> 

#include <fstream>
#include <string>
#include <sstream>


// TODO: using valgrind/massif right now but might switch to this kind of function
// size_t getCurrentMemoryUsage() {
//     std::ifstream proc("/proc/self/status");
//     std::string line;
//     size_t memory = 0;
//     while (std::getline(proc, line)) {
//         if (line.rfind("VmRSS:", 0) == 0) { // Look for Resident Set Size (VmRSS)
//             std::istringstream iss(line);
//             std::string key, value, unit;
//             iss >> key >> value >> unit;
//             memory = std::stoul(value); // Memory in kilobytes
//             break;
//         }
//     }
//     return memory; // Memory in KB
// }

int main() {
    std::cout << "test tensor constructor" << std::endl;
    // auto start = std::chrono::high_resolution_clock::now(); // Start time


    int arr[] = {2, 3, 4, 512};
    Tensor t1(arr);

    Tensor t2(arr);

    Tensor t3 = t1 * t2;
    // std::cout << "\n" << t1.getDim() << "\n";
    // std::cout << t1.getDimSizes() << "\n";
    // std::cout << t1.getMemBlockSize() << "\n";

    // this time calculation is wrong:
    // auto end = std::chrono::high_resolution_clock::now(); // End time
    // std::chrono::duration<double> elapsed = end - start;
    // std::cout << "\n\nExecution time: " << elapsed.count() << " seconds\n";

    // check randomness dist
    // check no repeats in randomness?


    return 0;
}