#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "iterators.hpp"
#include "type_traits.hpp"
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
	ft::vector<int>::const_reverse_iterator n;
	ft::vector<int>::const_iterator const_it;

	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	std_v.push_back(2);
	std_v.push_back(3);
	std_v.push_back(4);
	std_v.push_back(5);

	std_it.base();
	v.insert(v.end(), 3, 99);

	v.push_back(299);
	v.pop_back();

	std::cout << ft::is_integral<std::ptrdiff_t>() << "\n\n";


	for (ft::vector<int>::iterator it = v.begin(); it < v.end(); it++)
		std::cout << *it << '\n';

	std::cout << '\n';
	std::cout << "Current allocated size : " << v.capacity() << '\n';
	std::cout << "Current           size : " << v.size() << '\n';

	return (EXIT_SUCCESS);
}
