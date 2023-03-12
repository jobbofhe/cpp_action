#ifndef MOVE_R_VALUE_H
#define MOVE_R_VALUE_H

#include <iostream>
#include "base.h"

using namespace std;

class RightValue
{
public:
	RightValue() { std::cout << "RightValue: Constructor" << std::endl; }
	RightValue(const RightValue&) { std::cout << "RightValue: Copy Constructor" << std::endl; }
	RightValue(const RightValue&&) {
		std::cout << "RightValue: Move Constructor" << std::endl;
	}
	~RightValue() {}
};

RightValue GetRightValue()
{
	RightValue a;
	return a;
}

void RightValueTest_1() {
	RightValue a = GetRightValue();// getA()是一个右值

	//RightValue: Constructor
	//RightValue : Copy Constructor

	//可以看到A的构造函数调用一次，拷贝构造函数调用了一次，构造函数和拷贝构造函数是消耗比较大的，
	//这里是否可以避免拷贝构造？C++11做到了这一点。（注意，上面这个例子中，虽然getA()是一个右值，
	//但是由于没有自定义move constructor，所以调用了默认的copy constructor。如果对象中有堆内存管理，
	//必须定义move constructor。

	// 增加移动构造函数之后
	//RightValue: Constructor
	//RightValue : Move Constructor
}


class B
{
public:
	B() {}
	B(const B&) { cout << "B Copy Constructor" << endl; }
};

class A
{
public:
	A() : pb(new B()) { cout << "A Constructor" << endl; }
	A(const A& src) :pb(new B(*(src.pb)))//深拷贝
	{
		cout << "A Copy Constructor" << endl;
	}
	A(A&& src) :pb(src.pb)
	{
		src.pb = nullptr;//这里是关键，这样以后，当src.pb被delete时，由于其为空指针，并不会释放原来的堆内存
		cout << "A Move Constructor" << endl;
	}
	
	// deep copy
	A& operator=(const A& src) {
		if (this == &src) {
			return *this;
		}
		delete pb;
		pb = new B(*(src.pb));
		cout << "operator=(const A& src)" << endl;
		return *this;
	}

	A& operator=(A&& src) {
		if (this == &src) {
			return *this;
		}
		delete pb;
		pb = src.pb;
		//这里是关键，这样以后，当src.pb被delete时，由于其为空指针，并不会释放原来的堆内存
		src.pb = nullptr;
		cout << "operator=(const A&& src)" << endl;
		return *this;
	}

	~A() { delete pb; }

private:
	B* pb;
};

static A getA()
{
	A a;
	cout << "================================================1" << endl;
	return a;
}

void RightValueTest_2() {
	A a = getA();
	cout << "================================================2" << endl;
	A a1(a);

	//A Constructor
	//================================================1
	//A Move Constructor
	//================================================2
	//B Copy Constructor
	//A Copy Constructor
	//A a = getA();调用的是A的移动构造，A a1(a); 调用的是A的拷贝构造。A的拷贝构造需要对成员变量B进行深拷贝，而A的移动构造不需要，很明显，A的移动构造效率高。

	// std::move语句可以将左值变为右值而避免拷贝构造
	// A a2(std::move(a));将a转换为右值，因此a2调用的是移动构造而不是拷贝构造
	A a2(move(a));

	// !!!重要
	// 总之尽量给类添加移动构造和移动赋值函数，而减少拷贝构造和拷贝赋值的消耗。 移动构造，移动赋值要加上noexcept，用于通知标准库不抛出异常。
	a2 = getA();//移动赋值（因为getA()是右值）
}

void RightValueTest() {
	RightValueTest_1();
	RightValueTest_2();
}

#endif // MOVE_R_VALUE_H