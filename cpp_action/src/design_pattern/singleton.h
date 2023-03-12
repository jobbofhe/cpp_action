#ifndef DESIGN_PATTERN_SINGLETON_H_
#define DESIGN_PATTERN_SINGLETON_H_

#include "base.h"

// 懒汉模式单例，使用局部静态变量

class Singleton {
private:
	Singleton() {
		std::cout << "Singleton: constructor called\n";
	}
	~Singleton() {
		std::cout << "Singleton: destructor called\n";
	}
	Singleton(Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

public:
	static Singleton& GetInstance() {
		static Singleton instance_;
		return instance_;
	}
};

void DesignPatternTest_1() {
	Singleton& inst_1 = Singleton::GetInstance();
	Singleton& inst_2 = Singleton::GetInstance();
	std::cout << "inst_1 address: " << &inst_1 << std::endl;
	std::cout << "inst_2 address: " << &inst_2 << std::endl;
}

void DesignTestSingle() {
	DesignPatternTest_1();
}

#endif // !DESIGN_PATTERN_SINGLETON_H_
