#ifndef RETURN_VALUE_H_

#include <iostream>
#include <string>

#include "base.h"


// 讲解一个 返回值 的问题

class TestString {
public:
	TestString(std::string str) {
		std::cout << "TestString: Construction..." << std::endl;
		str_ = str;
	}

	std::string GetString() {
		return str_;
	}

	TestString& operator=(const TestString& obj) {
		std::cout << "TestString: Copy Construction..." << std::endl;
		str_ = obj.str_;
		return *this;
	}

	~TestString() {
		std::cout << "TestString: Destructor..." << std::endl;
	}
private:
	std::string str_;
};

TestString ReturnTestString() {
	TestString test_string("Task TestString");
	std::cout << "ReturnTestString End..." << std::endl;
	return test_string;
}


//
class TestCharPointor {
public:
	TestCharPointor(std::string str) {
		std::cout << "TestCharPointor: Construction..." << std::endl;
		str_ = str.c_str();
	}

	const char*  GetString() {
		return str_;
	}

	//TestCharPointor& operator=(const TestCharPointor& obj) {
	//	std::cout << "TestCharPointor: Copy Construction..." << std::endl;
	//	str_ = obj.str_;
	//	return *this;
	//}

	~TestCharPointor() {
		std::cout << "TestCharPointor: Destructor..." << std::endl;
	}
private:
	const char* str_;
};

TestCharPointor ReturnTestCharPointor() {
	TestCharPointor test_string("Task TestCharPointor");
	return test_string;
}

std::string ReturnStringTest() {
	std::string str("ReturnStringTest");
	return str;
}

std::string TestReturnString()
{
	//std::string strTest = "This is a test.";
	std::string strTest("This is a test.");
	return strTest;
}

std::string& TestStringReference()
{
	//std::string strTest = "This is a test.";
	std::string strTest("This is a test.");
	return strTest;
}

void ReturnValueTest_Test() {
	// string
	{
		StartEndLine line("ReturnTestString - 1");
		std::cout << "test_string------------: " << ReturnTestString().GetString() << std::endl;
	}
	{
		StartEndLine line("ReturnTestString - 2");
		TestString test_string = ReturnTestString();
		std::cout << "test_string------------: " << test_string.GetString() << std::endl;
	}

	// char *
	{
		StartEndLine line("ReturnTestCharPointor - 1");
		std::cout << "test_string============: " << ReturnTestCharPointor().GetString() << std::endl;
	}
	{
		StartEndLine line("ReturnTestCharPointor - 2");
		TestCharPointor test_char = ReturnTestCharPointor();
		std::cout << "test_char============[" << test_char.GetString() << "]" << std::endl;
	}
	{
		StartEndLine line("ReturnStringTest - 3");
		std::cout << "ReturnStringTest().c_str() : [ " << ReturnStringTest().c_str() << "]" << std::endl;
		
		// 正确做法
		std::string str = ReturnStringTest();
		std::cout << "ReturnStringTest().c_str() : [ " << ReturnStringTest().c_str() << "]" << std::endl;
		std::cout << "str : [" << str.c_str() << "]" << std::endl;

		// 错误做法
		const char* pc = ReturnStringTest().c_str();
		std::cout << "pc===========[" << pc << "]" << std::endl;

		// **************************************************************************************
		// CORE
		// 核心问题：我们没有将 ReturnStringTest() 的结果赋给一个string对象就直接获取其指针了，
		// 这时，系统并不会为string调用拷贝构造函数或是赋值函数，返回的string仍然只是一个临
		// 时对象的状态，它会在完成对pc的赋值后被销毁，这时其内部的数据也不会存在了。
		// **************************************************************************************

	}
	{
		// TODO 
		// CORE
		std::string tmp = TestReturnString();
		std::cout << "tmp: " << tmp << std::endl;

		// error C2440: “初始化”: 无法从“std::string”转换为“std::string &”
		//std::string& strRefer = TestReturnString();
		//std::cout << "strRefer:" << strRefer << std::endl;
		
		// 常量引用的初始值必须是左值
		const std::string& strRefer = TestReturnString();
		std::cout << "strRefer:" << strRefer << std::endl;

		//// 直接挂掉
		//std::string& strRefer2 = TestStringReference();
		//std::cout << "strRefer2:" << strRefer2 << std::endl;
	}
}

#endif // !RETURN_VALUE_H_
