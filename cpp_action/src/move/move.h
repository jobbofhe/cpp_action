#include <iostream>
#include "base.h"

// move 的使用情况
// 1）是什么？
//	1. 将一个不在使用的字符串赋给其他变量，原来变量生命周期结束；
// 2）为什么这么做？
//	避免不必要的拷贝，提高性能

static void MoveConstString() {
	std::string src_str("Hello Xuxing...");

	std::cout << "before move: &src_str: [" << &src_str << "]" << std::endl;

	std::string dst_str = std::move(src_str);

	std::cout << "&src_str: [" << &src_str << "]" << std::endl;
	std::cout << "&dst_str: [" << &dst_str << "]" << std::endl;

	std::cout << "src_str: [" << src_str << "]" <<  std::endl;
	std::cout << "dst_str: [" << dst_str << "]" << std::endl;

	//before move : &src_str : [000000591696F7E8]
	//& src_str : [000000591696F7E8]
	//& dst_str : [000000591696F828]
	//src_str : []
	//dst_str : [Hello Xuxing...]
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
		
		for (size_t i = 0; i < num; i++) {
			vec_str_dst.push_back(vec_str_src[i]);
		}
	}
	{
		TimeDuration task("MoveStringPerfTest - 2-reserve");
		std::vector<std::string> vec_str_dst;
		vec_str_dst.reserve(num);

		for (size_t i = 0; i < num; i++) {
			vec_str_dst.push_back(vec_str_src[i]);
		}
	}
	{
		TimeDuration task("MoveStringPerfTest - 3-move");
		std::vector<std::string> vec_str_dst;
		
		for (size_t i = 0; i < num; i++) {
			vec_str_dst.push_back(std::move(vec_str_src[i]));
		}
	}
	//[Task]:MoveStringPerfTest - 1  [Time cost]: 710/ms
	//[Task]:MoveStringPerfTest - 2 - reserve[Time cost] : 219 / ms
	//[Task] : MoveStringPerfTest - 3 - move[Time cost] : 723 / ms
}

void MoveTest() {
	// 1.
	MoveConstString();

	// 2. 
	MoveStringPerfTest();
}
