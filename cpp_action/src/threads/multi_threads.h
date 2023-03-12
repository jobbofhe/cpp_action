/* Copyright 2023 The cpp_action Author jobbofhe. All Rights Reserved. */
#ifndef MULTI_THREADS_H_
#define MULTI_THREADS_H_

#include "base.h"
#include <thread>

int g_number = 0;

static void Func_1(int number) {
	std::cout << "\nthread 1 running...\n";
	for (size_t i = 0; i < 5; ++i) {
		g_number++;
		std::cout << "1-g_number: " << g_number << std::endl;
	}
}

static void Func_2(int number) {
	std::cout << "\nthread 2 running...\n";
	for (size_t i = 0; i < 5; ++i) {
		g_number--;
		std::cout << "2-g_number: " << g_number << std::endl;
	}
	
}

static void Test_1() {
	std::thread thread1(Func_1, 10);
	std::thread thread2(Func_2, 20);

	std::cout << "thread 1 get pid() : " << thread1.get_id() << std::endl;
	std::cout << "thread 2 get pid() : " << thread2.get_id() << std::endl;

	std::thread::id t1_id = thread1.get_id();
	std::cout << "t1_id : " << t1_id << std::endl;

	thread1.join();
	thread2.join();
}

void MultiThreadTest() {
	Test_1();
}

// CORE
// 1. 默认构造函数	
// 	thread() noexcept;
// 2. 初始化构造函数	
// 	template <class Fn, class... Args>
// 	explicit thread(Fn&& fn, Args&&... args);
// 3. 拷贝构造函数 [deleted]	
// 	thread(const thread&) = delete;
// 4. Move 构造函数	
// 	thread(thread&& x) noexcept;

// 默认构造函数，创建一个空的 std::thread 执行对象。
// 初始化构造函数，创建一个 std::thread 对象，该 std::thread 对象可被 joinable，新产生的线程会调用 fn 函数，该函数的参数由 args 给出。
// 拷贝构造函数(被禁用)，意味着 std::thread 对象不可拷贝构造。
// Move 构造函数，move 构造函数(move 语义是 C++11 新出现的概念，详见附录)，调用成功之后 x 不代表任何 std::thread 执行对象。

// 注意：可被 joinable 的 std::thread 对象必须在他们销毁之前被主线程 join 或者将其设置为 detached.


#endif // !MULTI_THREADS_H_

