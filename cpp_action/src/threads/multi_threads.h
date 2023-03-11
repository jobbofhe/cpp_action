/* Copyright 2023 The cpp_action Author jobbofhe. All Rights Reserved. */
#ifndef MULTI_THREADS_H_
#define MULTI_THREADS_H_

#include "base.h"
#include <thread>

void Func_1(int number) {
	std::cout << "thread 1 running...\n";
	std::cout << "number: " << number << std::endl;
}

void Func_2(int number) {
	std::cout << "thread 2 running...\n";
	std::cout << "number: " << number << std::endl;
}

void Test_1() {
	std::thread thread1(Func_1, 10);

	std::cout << "thread 1 get pid() : " << thread1.get_id() << std::endl;

	thread1.join();
}

void MultiThreadTest() {
	Test_1();
}

#endif // !MULTI_THREADS_H_

