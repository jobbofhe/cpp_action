#include <iostream>

#include "vector/vector_test_base.h"
#include "return_value/return_value.h"
#include "move/move.h"
#include "move/r_value.h"
#include "static/static_test.h"
#include "design_pattern/singleton.h"
#include "threads/thread_test.h"
#include "keyword/keyword_test.h"
#include "smart_pointer/shared_ptr_impl.h"

int main() {
	//{
	//	VectorTest();	
	//}
	//{
	//	ReturnValueTest_Test();
	//}
	//{
	//	MoveTest();
	//}
	//{
	//	RightValueTest();
	//}
	// {
	// 	StaticTest();
	// }
	// {
	// 	DesignTestSingle();
	// }
	// {
	// 	ThreadTest();
	// }
	// {
	//	 KeyWordTest();
	// }
	{
		TestSmartPointer();
	}
}