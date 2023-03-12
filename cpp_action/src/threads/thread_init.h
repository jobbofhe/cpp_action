#ifndef THREADS_THREAD_INIT_H_
#define THREADS_THREAD_INIT_H_

#include "base.h"
#include <thread>
#include <chrono>
#include <utility>
#include <functional>
#include <atomic>

static void Func1(int  n) {
    for (size_t i = 0; i < 5; ++i) {
		std::cout << "Thread Func1: " << n << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

static void Func2(int& n) {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void TestThreadInit() {
    int n = 0;
    std::thread t1; // t1 is not a thread
    std::thread t2(Func1, n + 1); // pass by value
    std::thread t3(Func2, std::ref(n)); // pass by reference
    std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
    t2.join();
    t4.join();
    std::cout << "Final value of n is " << n << '\n';
}

#endif // THREADS_THREAD_INIT_H_