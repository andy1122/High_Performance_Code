#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <memory>

struct Node {
    int data;
    std::shared_ptr<Node> next;
};

class CacheFriendlyLinkedList {
private:
    std::vector<Node> memoryPool;
    std::shared_ptr<Node> head;

public:
    CacheFriendlyLinkedList() : head(nullptr) {}

    // Insert method
    void insert(int val) {
        memoryPool.emplace_back(Node{val, nullptr});
        std::shared_ptr<Node> newNode = std::make_shared<Node>(memoryPool.back());

        if (!head) {
            head = newNode;
        } else {
            std::shared_ptr<Node> current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
};

int main() {
    const int numElements = 10000;

    // Benchmark CacheFriendlyLinkedList insertion
    auto start_cfll = std::chrono::steady_clock::now();
    CacheFriendlyLinkedList cfll;
    for (int i = 0; i < numElements; ++i) {
        cfll.insert(i);
    }
    auto end_cfll = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_cfll = end_cfll - start_cfll;

    std::cout << "Time taken to insert " << numElements << " elements into CacheFriendlyLinkedList: " << elapsed_cfll.count() << " seconds\n";

    // Benchmark std::list insertion
    auto start_list = std::chrono::steady_clock::now();
    std::list<int> stdList;
    for (int i = 0; i < numElements; ++i) {
        stdList.push_back(i);
    }
    auto end_list = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_list = end_list - start_list;

    std::cout << "Time taken to insert " << numElements << " elements into std::list: " << elapsed_list.count() << " seconds\n";

    return 0;
}
