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
	RightValue a = GetRightValue();// getA()��һ����ֵ

	//RightValue: Constructor
	//RightValue : Copy Constructor

	//���Կ���A�Ĺ��캯������һ�Σ��������캯��������һ�Σ����캯���Ϳ������캯�������ıȽϴ�ģ�
	//�����Ƿ���Ա��⿽�����죿C++11��������һ�㡣��ע�⣬������������У���ȻgetA()��һ����ֵ��
	//��������û���Զ���move constructor�����Ե�����Ĭ�ϵ�copy constructor������������ж��ڴ����
	//���붨��move constructor��

	// �����ƶ����캯��֮��
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
	A(const A& src) :pb(new B(*(src.pb)))//���
	{
		cout << "A Copy Constructor" << endl;
	}
	A(A&& src) :pb(src.pb)
	{
		src.pb = nullptr;//�����ǹؼ��������Ժ󣬵�src.pb��deleteʱ��������Ϊ��ָ�룬�������ͷ�ԭ���Ķ��ڴ�
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
		//�����ǹؼ��������Ժ󣬵�src.pb��deleteʱ��������Ϊ��ָ�룬�������ͷ�ԭ���Ķ��ڴ�
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
	//A a = getA();���õ���A���ƶ����죬A a1(a); ���õ���A�Ŀ������졣A�Ŀ���������Ҫ�Գ�Ա����B�����������A���ƶ����첻��Ҫ�������ԣ�A���ƶ�����Ч�ʸߡ�

	// std::move�����Խ���ֵ��Ϊ��ֵ�����⿽������
	// A a2(std::move(a));��aת��Ϊ��ֵ�����a2���õ����ƶ���������ǿ�������
	A a2(move(a));

	// !!!��Ҫ
	// ��֮������������ƶ�������ƶ���ֵ�����������ٿ�������Ϳ�����ֵ�����ġ� �ƶ����죬�ƶ���ֵҪ����noexcept������֪ͨ��׼�ⲻ�׳��쳣��
	a2 = getA();//�ƶ���ֵ����ΪgetA()����ֵ��
}

void RightValueTest() {
	RightValueTest_1();
	RightValueTest_2();
}