#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <chrono>


// unoptimised way, where we will have a big structure of 7 attributes (name, username, password, security_question, securtiy_ans, level, is_playing)

struct User
{
    std::string name;
    std::string user_name;
    std::string password;
    std::string security_ques;
    std::string security_ans;
    short level{std::rand()%11};
    bool is_playing{};
};   // bit confused because the last block for short and bool is given 8 bytes compared to the 32 bytes which is biggest element of struct.

// Write two fucntions to calculate the num_users_at_level and num_user_playing
void num_users_level(std::vector<User>& user, short level){
    int cnt = 0;
    for (auto& x: user){
        if (x.level == level){
            cnt++;
        }
    }
}

void num_user_playing(std::vector<User>& user){
    std::count_if(user.begin(), user.end(), 
    [](const auto& x){return x.is_playing;});
}



struct MyStruct {
    __int128 myInt128;  // 16 bytes
    short val;          // 16 bytes
};  // size is 32 bytes, which is ok according to structural padding

int main() {
    User u1;
    std::cout << sizeof(u1)<<std::endl;  // 168 bytes 160(5 strings) + 8 bytes(for short & bool)
    MyStruct my1;
    std::cout << sizeof(my1) << std::endl;
    std::vector<User> user(1'000'000);

    // profile the time of the funcitons

    auto start = std::chrono::high_resolution_clock::now();
    num_users_level(user, 3);
    // End the timer
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    auto duration_level = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    auto start1 = std::chrono::high_resolution_clock::now();
    num_user_playing(user);
    auto end1 = std::chrono::high_resolution_clock::now();
    // Calculate the duration
    auto duration_play = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);

    std::cout << duration_play.count() <<  " aaa " << duration_level.count() << std::endl;
}
