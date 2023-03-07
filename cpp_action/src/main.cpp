#include <iostream>

#include "vector/vector_test_base.h"
#include "return_value/return_value.h"
#include "move/move.h"

int main() {
	{
		VectorTest();	
	}
	{
		ReturnValueTest_Test();
	}
	{
		MoveTest();
	}
}