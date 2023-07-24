#include <iostream>
#include "MyVector.h"
#include <vector>
#include <algorithm>

int main()
{
	//MyVector<int> v = { 3, 4, 1, 2, 5 };
	//for (auto i = v.cbegin(); i != v.cend(); i++)
	//{
	//	std::cout << *i << std::endl;
	//}
	//std::reverse(v.begin(), v.end());
	//std::cout << std::endl;
	//for (auto i : v)
	//{
	//	std::cout << i << std::endl;
	//}
	//std::cout << std::endl;
	////std::fill(v.begin(), v.end(), 228);
	//std::sort(v.begin(), v.end());

	//for (auto i = v.rbegin(); i != v.rend(); i++)
	//	std::cout << *i << std::endl;

	std::vector<int> f = { 1, 2, 3, 4 };
	std::cout << *(f.insert(f.begin()+1, 0));

	for (auto i : f)
		std::cout << i << ' ';

	return 0;
}