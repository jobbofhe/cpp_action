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
	TestCharPointor(const char* str) {
		std::cout << "TestCharPointor: Construction..." << std::endl;
		str_ = str;
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
	const char*  str_;
};

TestCharPointor ReturnTestCharPointor() {
	TestCharPointor test_string("Task TestCharPointor");
	std::cout << "ReturnTestCharPointor End..." << std::endl;
	return test_string;

}

void ReturnValueTest_Test() {
	// string
	{
		StartEndLine line("ReturnTestString().GetString()");
		std::cout << "test_string------------: " << ReturnTestString().GetString() << std::endl;
	}
	{
		StartEndLine line("test_string.GetString()");
		TestString test_string = ReturnTestString();
		std::cout << "test_string------------: " << test_string.GetString() << std::endl;
	}

	// char *
	{
		StartEndLine line("ReturnTestCharPointor().GetString()");
		std::cout << "test_string============: " << ReturnTestCharPointor().GetString() << std::endl;
	}
	{
		StartEndLine line("test_string.GetString()");
		TestCharPointor test_string = ReturnTestCharPointor();
		std::cout << "test_string============: " << test_string.GetString() << std::endl;
	}
}

#endif // !RETURN_VALUE_H_
