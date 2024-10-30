#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "thread_pool.hpp"


int main() 
{

    // Initialize a thread pool with 4 threads
    ThreadPool pool(4);

    // Test tasks with return values
    std::vector<std::future<int>> results;
    for (int i = 0; i < 20; ++i) {
        results.emplace_back(pool.enqueue([i] {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return i * i;
        }));
    }

    // Wait and print results for tasks
    for (auto& result : results) {
        std::cout << "Result: " << result.get() << std::endl;
    }

    // Test task that doesn't return a value
    for (int i = 0; i < 10; ++i) {
        pool.enqueue([] {
            std::this_thread::sleep_for(std::chrono::milliseconds(500 + rand() % 501));
            std::cout << "Task being executed by thread " << std::this_thread::get_id() << std::endl;
        });
    }

    for (int i = 0; i < 15; ++i)
    {
        std::cout << "---------------------------------" << std::endl;
    std::cout << "busy threads: " << pool.GetBusyThreadCount() << std::endl;
    std::cout << "waiting threads: " << pool.GetWaitingThreadCount() << std::endl;
     std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}