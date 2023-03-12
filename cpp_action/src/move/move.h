#ifndef MOVE_MOVE_H_
#define MOVE_MOVE_H_

#include <iostream>
#include "base.h"

// move 的使用情况
// 1. 将一个不在使用的字符串赋给其他变量，原来变量生命周期结束；
// a）为什么这么做？
//	避免不必要的拷贝，提高性能

// 2. move 性能测试

// 3. move 做形参才能出发 move 语义

// 4. move 转移 shared_ptr 所有权 
// TODO 

static void MoveConstString() {
	std::string src_str("Hello Xuxing...");

	std::cout << "before move: &src_str: [" << &src_str << "]" << std::endl;

	std::string dst_str = std::move(src_str);

	std::cout << "&src_str: [" << &src_str << "]" << std::endl;
	std::cout << "&dst_str: [" << &dst_str << "]" << std::endl;

	std::cout << "src_str: [" << src_str << "]" <<  std::endl;
	std::cout << "dst_str: [" << dst_str << "]" << std::endl;

	// //before move : &src_str : [000000591696F7E8]
	// //& src_str : [000000591696F7E8]
	// //& dst_str : [000000591696F828]
	// //src_str : []
	// //dst_str : [Hello Xuxing...]
	// move 的功能就是，将原来的内存的所有者进行转移。原来的所有者在 move 之后不在拥有当前内存。
}

void MoveStringPerfTest() {
	int num = 100000;
	std::vector<std::string> vec_str_src;
	for (size_t i = 0; i < num; i++) {
		vec_str_src.push_back(std::to_string(i));
	}

	{
		TimeDuration task("MoveStringPerfTest - 1");
		std::vector<std::string> vec_str_dst;
		std::string str = "zxcvbnm";
		for (size_t i = 0; i < num; i++) {
			vec_str_dst.push_back(str);
		}
	}
	{
		TimeDuration task("MoveStringPerfTest - 2-reserve");
		std::vector<std::string> vec_str_dst;
		vec_str_dst.reserve(num);
		std::string str = "zxcvbnm";
		for (size_t i = 0; i < num; i++) {
			vec_str_dst.push_back(str);
		}
	}
	{
		TimeDuration task("MoveStringPerfTest - 3-move");
		std::vector<std::string> vec_str_dst;
		std::string str = "zxcvbnm";
		for (size_t i = 0; i < num; i++) {
			vec_str_dst.push_back(std::move(str));
		}
	}
	//[Task]:MoveStringPerfTest - 1  [Time cost]: 710/ms
	//[Task]:MoveStringPerfTest - 2 - reserve[Time cost] : 219 / ms
	//[Task] : MoveStringPerfTest - 3 - move[Time cost] : 723 / ms
	// TODO
	// 并没有发现 move 性能会好一点， 还需要在验证
}

// 3. 
// CORE
// 在函数内部的形参，即使它被声明为右值引用类型，并被绑定一个右值引用类型的实参，但它本身仍然是左值
// 无法由它触发移动XX函数，除非对它再次使用move函数或者forward函数。因此，如果你在移动构造函数里
// 面想要再次触发移动语义，那么就必须放在move里用，比如移动构造函数的入参对象里面有个string类型的成
// 员变量，想移动到*this对象的对应string成员变量，就得包在move里面

void DefineRightRef() {
	std::string str = "DefineRightRef";
	std::string&& r = std::move(str); 
	std::cout << r << std::endl;
	std::cout << str << std::endl;
	std::string t(r);
	std::cout << t << std::endl;
	std::cout << str << std::endl;
	// output 说明，仅仅是定义右值引用，那么obj本身不会被移走
		//DefineRightRef
		//DefineRightRef
		//DefineRightRef
		//DefineRightRef

	std::string move_t(move(str));
	std::cout << "move_t:" << move_t << std::endl;
	std::cout << "str : " << str << std::endl;
	//move_t:DefineRightRef
	//str :
	// str 输出为空，说明： 在作为参数时会发生obj被移走
}

void MoveTest() {
	// 1.
	MoveConstString();

	// 2. 
	MoveStringPerfTest();

	// 3.
	DefineRightRef();
}

#endif // !MOVE_MOVE_H_