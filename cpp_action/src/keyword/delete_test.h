#ifndef DELETE_DELETE_TEST_H_
#define DELETE_DELETE_TEST_H_
/*  */
#include "base.h"

class DeleteTest {
public:
	DeleteTest() {}

    DeleteTest(DeleteTest&) = delete;
    DeleteTest& operator=(const DeleteTest&) = delete;
};

class DeleteTest2 {
public:
	DeleteTest2() {}

private:
    DeleteTest2(DeleteTest2&) {}
    DeleteTest2& operator=(const DeleteTest2&) {}
};

void KeywordDeleteTest() {
	DeleteTest t1; 
	// DeleteTest t2 = t1; // error C2280: “DeleteTest::DeleteTest(DeleteTest &)”: 尝试引用已删除的函数

	DeleteTest2 tt1;
	// DeleteTest2 tt2 = tt1; // error C2248: “DeleteTest2::DeleteTest2”: 无法访问 private 成员(在“DeleteTest2”类中声明)
}

#endif // DELETE_DELETE_TEST_H_