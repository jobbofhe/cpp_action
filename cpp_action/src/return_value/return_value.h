#ifndef RETURN_VALUE_H_

#include <iostream>
#include <string>

#include "base.h"


// ����һ�� ����ֵ ������

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
		
		// ��ȷ����
		std::string str = ReturnStringTest();
		std::cout << "ReturnStringTest().c_str() : [ " << ReturnStringTest().c_str() << "]" << std::endl;
		std::cout << "str : [" << str.c_str() << "]" << std::endl;

		// ��������
		const char* pc = ReturnStringTest().c_str();
		std::cout << "pc===========[" << pc << "]" << std::endl;

		// **************************************************************************************
		// CORE
		// �������⣺����û�н� ReturnStringTest() �Ľ������һ��string�����ֱ�ӻ�ȡ��ָ���ˣ�
		// ��ʱ��ϵͳ������Ϊstring���ÿ������캯�����Ǹ�ֵ���������ص�string��Ȼֻ��һ����
		// ʱ�����״̬����������ɶ�pc�ĸ�ֵ�����٣���ʱ���ڲ�������Ҳ��������ˡ�
		// **************************************************************************************

	}
	{
		// TODO 
		// CORE
		std::string tmp = TestReturnString();
		std::cout << "tmp: " << tmp << std::endl;

		// error C2440: ����ʼ����: �޷��ӡ�std::string��ת��Ϊ��std::string &��
		//std::string& strRefer = TestReturnString();
		//std::cout << "strRefer:" << strRefer << std::endl;
		
		// �������õĳ�ʼֵ��������ֵ
		const std::string& strRefer = TestReturnString();
		std::cout << "strRefer:" << strRefer << std::endl;

		//// ֱ�ӹҵ�
		//std::string& strRefer2 = TestStringReference();
		//std::cout << "strRefer2:" << strRefer2 << std::endl;
	}
}

#endif // !RETURN_VALUE_H_
