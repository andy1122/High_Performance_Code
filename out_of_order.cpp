#include <iostream>
#include <chrono>

void dependent_instructions(int iterations) {
    int a = 1, b = 2, c = 3, d = 4;
    for (int i = 0; i < iterations; ++i) {
        a = b + c; // 'a' depends on 'b' and 'c'
        d = a * c; // 'd' depends on 'a' which is updated in the previous instruction
    }
}

void independent_instructions(int iterations) {
    int a = 1, b = 2, c = 3, d = 4, e = 8, f = 4, g = 0, h = 9;
    for (int i = 0; i < iterations; ++i) {
        a = b + c; // Independent of 'd'
        d = b * c; // Independent of 'a'
        e = b * c;
        f = g*h;
    }
}

int main() {
    const int iterations = 1'000'000'000;

    auto start = std::chrono::high_resolution_clock::now();
    dependent_instructions(iterations);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Dependent instructions elapsed time: " << elapsed.count() << " seconds\n";

    start = std::chrono::high_resolution_clock::now();
    independent_instructions(iterations);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Independent instructions elapsed time: " << elapsed.count() << " seconds\n";

    return 0;
}
