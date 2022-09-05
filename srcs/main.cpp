#include <algorithm>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Iterator.hpp"
#include "vector.hpp"
#include "pair.hpp"
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
	std::vector<int> std_v;
	std::vector<int>::iterator std_it;
	std::vector<int>::const_iterator std_c_it;
	ft::vector<int>::const_iterator c_it;
	ft::vector<int>::iterator cat;

	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	std_v.push_back(2);
	std_v.push_back(3);
	std_v.push_back(4);
	std_v.push_back(5);

	std_it = std_it + 2;
	cat += 2;
	c_it = v.begin();

	ft::reverse_iterator<ft::vector<int>::iterator> ri (v.rbegin());
	ft::reverse_iterator<ft::vector<int>::iterator> ri2 = ri - 2;
	std::reverse_iterator<std::vector<int>::iterator> std_ri(std_v.rbegin());
	std::reverse_iterator<std::vector<int>::iterator> std_ri2 = std_ri;

	for ( ; ri != v.rend(); ri++)
		std::cout << *ri << '\n';

	std::cout << "Current allocated size : " << v.capacity() << '\n';
	std::cout << "Current           size : " << v.size() << '\n';

	return (EXIT_SUCCESS);
}
