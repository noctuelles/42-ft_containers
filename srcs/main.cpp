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
	std::vector<Dummy>::iterator	i1;

	v.resize(10, 100);
	for (ft::vector<int>::iterator i = v.begin(); i != v.end() - 5; i++)
	{
		std::cout << *i << '\n';
	}
	

	std::cout << "Current allocated size : " << v.capacity() << '\n';
	std::cout << "Current           size : " << v.size() << '\n';

	return (EXIT_SUCCESS);
}
