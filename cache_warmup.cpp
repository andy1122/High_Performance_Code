#include <iostream>
#include <vector>
#include <chrono>

void cache_warmup(std::vector<int>& data) {
    // Access the data sequentially to warm up the cache
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = i;
    }
}

void measure_access_time(std::vector<int>& data) {
    int sum = 0;
    auto start = std::chrono::high_resolution_clock::now();

    // Access the data sequentially to measure access time
    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    std::cout << "Sum: " << sum << std::endl;  // Use the sum to prevent optimization
}

int main() {
    const size_t dataSize = 100000000;  // Size of the data to test cache warmup
    std::vector<int> data(dataSize);

    // Measure access time without cache warmup
    std::cout << "Measuring without cache warmup...\n";
    measure_access_time(data);

    // Perform cache warmup
    cache_warmup(data);

    // Measure access time after cache warmup
    std::cout << "Measuring with cache warmup...\n";
    measure_access_time(data);

    return 0;
}
