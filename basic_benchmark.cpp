#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <algorithm>

int main() {
    const int container_size = 10000;
    const int delete_size = 5;

    // Generate unique values for both vector and list
    std::vector<int> vec(container_size);
    std::list<int> lst;

    // Fill vector and list with unique values
    for (int i = 0; i < container_size; ++i) {
        vec[i] = i + 10;
        lst.push_back(i + 10);
    }

    // Shuffle the vector for random access
    std::random_shuffle(vec.begin(), vec.end());

    // Benchmark vector deletion
    auto start_vec = std::chrono::steady_clock::now();
    for (int i = 0; i < delete_size; ++i) {
        vec.erase(std::remove(vec.begin(), vec.end(), i + 10), vec.end());
    }
    auto end_vec = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_vec = end_vec - start_vec;

    // Benchmark list deletion
    auto start_lst = std::chrono::steady_clock::now();
    for (int i = 0; i < delete_size; ++i) {
        lst.remove(i + 10);
    }
    auto end_lst = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_lst = end_lst - start_lst;

    // Output results
    std::cout << "Time taken to delete " << delete_size << " values from containers with size " << container_size << ":\n";
    std::cout << "Vector: " << elapsed_vec.count() << " seconds\n";
    std::cout << "List: " << elapsed_lst.count() << " seconds\n";

    return 0;
}
