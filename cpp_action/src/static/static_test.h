/* Copyright 2023 The cpp_action Author jobbofhe. All Rights Reserved. */

#ifndef STATIC_TEST_H_
#define STATIC_TEST_H_

#include "base.h"
#include <mutex>
#include <unordered_map>

#include "static_init_test.h"

class TestSingleton {
public:
	static TestSingleton*GetInstance() {
		if (nullptr == instance_) {
			std::lock_guard<std::mutex> _(mtx_);
			std::cout << "GetInstance: " << std::endl;
			instance_ = new TestSingleton();
		}
		return instance_;
	}

	void DeleteTestSingleton() {
		if (instance_) {
			delete instance_;
			instance_ = nullptr;
		}
	}

	void SetMapMember(int order, std::string name) {
		std::lock_guard<std::mutex> _(mtx_);
		order_map_.emplace(order, name);
	}
	std::string GetMapMemberNameByKey(int order) {
		std::lock_guard<std::mutex> _(mtx_);
		return order_map_[order];
	}
	void Print() {
		for (auto iter = order_map_.begin(); iter != order_map_.end(); iter++) {
			std::cout << "order: " << iter->first << " name: " << iter->second << std::endl;
		}
	}

private:
	// CORE
	TestSingleton() {}
	// 阻止 copy, 将构造函数和赋值构造函数，设置为 private 成员可以阻止拷贝
	TestSingleton(const TestSingleton&);
	TestSingleton& operator=(const TestSingleton&);

private:
	std::unordered_map<int, std::string> order_map_;
	static std::mutex mtx_;
	static TestSingleton* instance_;
};

TestSingleton* TestSingleton::instance_ = nullptr;
std::mutex TestSingleton::mtx_;

void TestSingletonInit() {
	TestSingleton* inst = TestSingleton::GetInstance();
	inst->SetMapMember(1, "Xuxing");
	inst->SetMapMember(2, "Fanlu");
	inst->SetMapMember(3, "Linzhonglu");

	inst->Print();

	inst->DeleteTestSingleton();
}

void TestMultiThreadsAccess() {
// TODO
}

void StaticTest() {
	TestSingletonInit();

	StaticInit_Test();
}

#endif // !STATIC_TEST_H_