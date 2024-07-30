#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
// We will create a data structure which goes out of the cache and then check for the cache misses in it.
 

 // create a small and big object, offcourse the big object will go out of cache and will lead to cache thrashing or cache miss

 struct  smallobject // 8 bytes
 {
    std::array<char, 4> data_{};
    int score_{std::rand()};
 };

 struct bigobject   // 260 bytes
 {
    std::array<char, 256> data_{};
    int score_{std::rand()};
 };

 // we will create a function to just sum the socre_ arttribute of both the smallobject and bigobject

 // even though we will do just the same sum operation on score on both the smallobjects and bigobjects, but the performance will be staggering 

 template <class T>
 auto sum_score(const std::vector<T>& vec){
     int sum = 0;
     for (const auto& x: vec) {
        sum+= x.score_;
     }
    
 }
 
template <class T>
auto sum_int(std::vector<T> vec ){
    int sum = 0;
    for (auto& x: vec) {
        sum+= x;
    }
}

 int main(){
    //std::cout << sizeof(smallobject) << std::endl;
    //std::cout << sizeof(bigobject) << std::endl;
    // create a vecotr of these objects
    std::vector<smallobject> small(1'000'000);
    std::vector<bigobject> big(1'000'000);
    std::vector<int> int_val(1'000'000, 1);
    // profile these function with both of the objects
    /*
    auto start = std::chrono::high_resolution_clock::now();
    
    // End the timer
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    auto duration_small = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    auto start1 = std::chrono::high_resolution_clock::now();
    sum_score(big);
    auto end1 = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    auto duration_big = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    */
    //std::cout << duration_big.count() << std::endl;
    //std::cout << duration_small.count() << std::endl; 
    sum_score(small);
    //sum_score(big);
    //sum_int(int_val);

 }

// Then we will optimise that data structure to fit in the cache and then check the speed and the cache miss.


// This code results in lot of cache thrashing, but not in the cache misses.


// But still i ddidnot get let a 10 times perfomrcane improvement, i have gotten like 2.5 time which is decent but nowhere clsoe to 10 times.

// perf stat -e mem_load_retired.l1_miss, mem_load_retired.l2_hit,mem_load_retired.l2_miss -- 