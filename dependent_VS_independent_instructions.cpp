#include <iostream>
#include <chrono>

// for loop with
void dependent_instructions(int iterations) {
    // dependency among all the instruction
    int x = 1;
    for (int i = 0; i< iterations; i++) {
        // addition, mulitplication, subtractuion and division(most costly operation)
        x = x + 1; // Instruction 1
        x = x * 2; // Instruction 2, depends on Instruction 1
        x = x + 3; // Instruction 3, depends on Instruction 2
        //x = x / 4; // Instruction 4, depends on Instruction 3
    }
    std:: cout << "dependent result " << x << std::endl;
}

void independent_instruction(int iterations) {
    // changes the variables(registers), such that no dependency on instructions
    int a = 1, b = 2, c = 4; //d = 4;
    for (int i = 0; i<iterations; i++) {
        a = a + 1; // Independent of b, c, d
        b = b * 2; // Independent of a, c, d
        c = c + 3; // Independent of a, b, d
        //d = d / 4; // Independent of a, b, c
    }
    int res = a+b+c;
    std::cout << "independent resutl " << res << std::endl;

}

int main() {

    // execute and calcuate the time for the dependent_instructions and independent_instructions
    const int iterations = 100000000;

    auto start = std::chrono::high_resolution_clock::now();
    dependent_instructions(iterations);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Dependent instructions elapsed time: " << elapsed.count() << " seconds\n";


    auto start1 = std::chrono::high_resolution_clock::now();
    independent_instruction(iterations);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1 = end1 - start1;
    std::cout << "Independent instructions elapsed time: " << elapsed1.count() << " seconds\n";


}

//  g++ -O3 -std=c++17 -pthread dependent_VS_independent_instructions.cpp  -o dependent_VS_independent_instructions.o 
// -O3 flag is used here for the optimisation
