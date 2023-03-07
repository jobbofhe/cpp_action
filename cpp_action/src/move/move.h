#include <iostream>
#include "base.h"

// move ��ʹ�����
// 1����ʲô��
//	1. ��һ������ʹ�õ��ַ�����������������ԭ�������������ڽ�����
// 2��Ϊʲô��ô����
//	���ⲻ��Ҫ�Ŀ������������

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
	// move �Ĺ��ܾ��ǣ���ԭ�����ڴ�������߽���ת�ơ�ԭ������������ move ֮����ӵ�е�ǰ�ڴ档
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
