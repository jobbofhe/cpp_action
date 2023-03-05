#include <iostream>
#include "base.h"

#include "vector/vector_test_base.h"

int main() {
	{
		TimeDuration test("test");
	}

	{
		VectorTest();	
	}

	std::cout << "Hello world" << std::endl;
}