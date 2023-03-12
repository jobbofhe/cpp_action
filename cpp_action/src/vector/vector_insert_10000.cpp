//// vector 插入 10000 个数字，怎么保证性能较高
//#include <vector>
//#include "base.h"
//
//#define VEC_INSERT_NUMBER_COUNT (100000)
//
//static void VectorInsert() {
//	std::vector<int> vec;
//
//	for (size_t i = 0; i < VEC_INSERT_NUMBER_COUNT; ++i) {
//		vec.push_back(i);
//		//std::cout << i << std::endl;
//	}
//}
//
//static void VectorInsertReserve() {
//	std::vector<int> vec;
//	vec.reserve(VEC_INSERT_NUMBER_COUNT);
//
//	for (size_t i = 0; i < VEC_INSERT_NUMBER_COUNT; ++i) {
//		vec.push_back(i);
//		//std::cout << i << std::endl;
//	}
//}
//
//static void VectorInsertEmplaceBack() {
//	std::vector<int> vec;
//	vec.reserve(VEC_INSERT_NUMBER_COUNT);
//
//	for (size_t i = 0; i < VEC_INSERT_NUMBER_COUNT; ++i) {
//		vec.emplace_back(i);
//		//std::cout << i << std::endl;
//	}
//}
//
//void VectorTest() {
//	// [Task]:Vector insert VEC_INSERT_NUMBER_COUNT number 1[Time cost] : 10 / ms
//
//	{
//		TimeDuration test("Vector insert 10000 number 1");
//		VectorInsert();
//	}
//	{
//		TimeDuration test2("Vector insert 10000 number 2 reserve:");
//		VectorInsertReserve();
//	}
//	{
//		TimeDuration test2("Vector insert 10000 number 3 emplace_back:");
//		VectorInsertEmplaceBack();
//	}
//}


// vector 插入 10000 个数字，怎么保证性能较高
#include <vector>
#include "base.h"

#define VEC_INSERT_NUMBER_COUNT (100000)

static void VectorInsert(std::vector<int>& vec) {
	for (size_t i = 0; i < VEC_INSERT_NUMBER_COUNT; ++i) {
		vec.push_back(i);
		//std::cout << i << std::endl;
	}
}

static void VectorInsertReserve(std::vector<int>& vec) {
	for (size_t i = 0; i < VEC_INSERT_NUMBER_COUNT; ++i) {
		vec.push_back(i);
		//std::cout << i << std::endl;
	}
}

static void VectorInsertEmplaceBack(std::vector<int> vec) {
	for (size_t i = 0; i < VEC_INSERT_NUMBER_COUNT; ++i) {
		vec.emplace_back(i);
		//std::cout << i << std::endl;
	}
}

void VectorTest() {
	std::vector<int> vec(1,2);
	{
		TimeDuration test("Vector insert 10000 number 1");
		VectorInsert(vec);
	}
	{
		TimeDuration test2("Vector insert 10000 number 2 reserve:");
		vec.reserve(VEC_INSERT_NUMBER_COUNT);
		VectorInsertReserve(vec);
	}
	{
		TimeDuration test2("Vector insert 10000 number 3 emplace_back:");
		VectorInsertEmplaceBack(vec);
	}
	// [Task] : Vector insert 10000 number 1[Time cost] : 58 / ms
	// [Task] : Vector insert 10000 number 2 reserve : [Time cost] : 105 / ms
	// [Task] : Vector insert 10000 number 3 emplace_back : [Time cost] : 129 / ms
	// TODO
}