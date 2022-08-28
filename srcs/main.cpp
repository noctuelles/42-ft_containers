#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Iterator.hpp"
#include "vector.hpp"
#include <typeinfo>
#include <stdio.h>

class	Dummy
{
	public:
		Dummy()
		{
			std::cout << "Dummy constructor called." << std::endl;
		}
		~Dummy()
		{
			std::cout << "Dummy destructor called." << std::endl;
		}
};

int main(void)
{
	ft::vector<int> v;
	std::vector<int> v1;
	ft::vector<int>::iterator beg, last, end;

	v.push_back(12);
	v.push_back(16);
	v.push_back(24);
	v.push_back(42);

	v.insert(v.begin() + 2, 3, 99);
	for (ft::vector<int>::iterator i = v.begin(); i != v.end(); i++)
	{
		std::cout << *i << '\n';
	}

	std::cout << "Current allocated size : " << v.capacity() << '\n';
	std::cout << "Current           size : " << v.size() << '\n';

	return (EXIT_SUCCESS);
}
