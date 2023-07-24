#include <iostream>
#include "MyVector.h"
#include <vector>
#include <algorithm>

int main()
{

	//Example use of insert and erase methods

	MyVector<int> f = { 1, 2, 3, 4, 5 };
	f.insert(f.end(), 228);
	f.insert(f.end(), 228);
	f.insert(f.end(), 228);
	f.insert(f.end(), 228);
	f.insert(f.end(), 228);

	f.erase(f.end());

	for (auto i : f)
	{
		std::cout << i << std::endl;
	}

	return 0;
}