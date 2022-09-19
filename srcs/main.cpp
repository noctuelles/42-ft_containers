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
#include <sstream>
#include "Dummy.hpp"
#include "print.hpp"
#include "vector.hpp"
#include "stack.hpp"

std::ostream&	operator<<(std::ostream& rhs, const Dummy& dummy)
{
	(void) dummy;
	rhs << "Hello i'm dummy " << dummy.getName() << '\n';
	return (rhs);
}

static inline size_t	getMillisecDifference(const struct timeval& begin, const struct timeval& end)
{
	return ((end.tv_sec * 1000 + end.tv_usec / 1000) - (begin.tv_sec * 1000 + begin.tv_usec / 1000));
}

void	insertTest()
{
	struct timeval begin, end;

	{
		ft::vector<Dummy>	v(10000000, Dummy("42"));
		ft::vector<Dummy>	v0(50000, Dummy("21"));

		gettimeofday(&begin, NULL);
		v0.insert(v0.begin() + 2000, v.begin(), v.end());
		gettimeofday(&end, NULL);
		std::cout << "Your vector took " << getMillisecDifference(begin, end) << " ms.\n";
	}
	{
		namespace ft = std;

		ft::vector<Dummy>	v(100000000, Dummy("42"));
		ft::vector<Dummy>	v0(50000, Dummy("21"));

		gettimeofday(&begin, NULL);
		v0.insert(v0.begin() + 2000, v.begin(), v.end());
		gettimeofday(&end, NULL);
		std::cout << "Standard vector took " << getMillisecDifference(begin, end) << " ms.\n";
	}
}

int Dummy::count = 0;

int main(void)
{
	std::list<Dummy>	listI(10, Dummy("yo"));

	try
	{
		insertTest();
		/*std::cout << "Size " << v.size() << " and capacity " << v.capacity() << '\n';
		std::for_each(v.begin(), v.end(), print<Dummy>);*/
	}
	catch(...)
	{
	}
	return (EXIT_SUCCESS);
}
