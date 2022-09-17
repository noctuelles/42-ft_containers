#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <ostream>
#include <utility>
#include <list>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <typeinfo>
#include <stdio.h>
#include <sys/time.h>
#include "Dummy.hpp"
#include "vector_new.hpp"

std::ostream&	operator<<(std::ostream& rhs, const Dummy& dummy)
{
	(void) dummy;
	rhs << "Hello i'm dummy " << dummy.getName() << '\n';
	return (rhs);
}

/*static inline size_t	getMillisecDifference(const struct timeval& begin, const struct timeval& end)
{
	return ((end.tv_sec * 1000 + end.tv_usec / 1000) - (begin.tv_sec * 1000 + begin.tv_usec / 1000));
}*/

template <class T>
void	print(const T& arg)
{
	std::cout << arg;
}

int Dummy::count = 0;

int main(void)
{
	try
	{
		ft::vector<Dummy> v;

		v.push_back(Dummy("1"));
		v.push_back(Dummy("2"));
		v.push_back(Dummy("3"));
		v.push_back(Dummy("4"));

		v.insert(v.begin(), 10000, Dummy("-2"));

		std::cout << "Size " << v.size() << " and capacity " << v.capacity() << '\n';
		std::for_each(v.begin(), v.end(), print<Dummy>);
	}
	catch(...)
	{
	}
	return (EXIT_SUCCESS);
}
