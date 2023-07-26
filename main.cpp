#include <iostream>
#include <algorithm>
#include <cassert>
#include <random>
#include "MyVector.h"

void test() 
{
	MyVector<int> v1, v2;
	// Two empty vectors
	assert(v1 == v2);

	// Two random vectors
	std::srand(1);
	for (size_t i = 0; i < 10; i++)
	{
		v1.push_back(std::rand() % 300);
		v2.push_back(std::rand() % 300);
	}	
	assert(v1 != v2);

	// Removing elements
	for (size_t i = 0; i < 10; i++)
	{
		v1.pop_back();
	}
	v2.clear();
	assert(v1 == v2);

	// Sorting vector
	v1 = { 1, 2, 3, 4, 5 };
	v2 = { 5, 4, 3, 1, 2 };
	std::sort(v2.begin(), v2.end());
	assert(v1 == v2);

	// Revesring vector
	v1 = { 1, 3, 5 };
	v2 = { 5, 3, 1 };
	std::reverse(v2.begin(), v2.end());
	assert(v1 == v2);

	// Using std::remove
	auto lend = std::remove(v1.begin(), v1.end(), 3);
	MyVector<int> v3(v1.begin(), lend);
	assert(v3 == MyVector<int>({ 1, 5 }));
}

int main()
{
	test();
	std::cout << "All tests completed!" << std::endl;
	return 0;
}