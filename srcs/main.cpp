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
#include <iomanip>
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

size_t	bench()
{
	static struct timeval	begin, end;
	static bool	isEnd = false;

	if (!isEnd)
	{
		gettimeofday(&begin, NULL);
		isEnd = true;
	}
	else
	{
		gettimeofday(&end, NULL);
		isEnd = false;
		return (getMillisecDifference(begin, end));
	}
	return (0);
}

void	insertTest()
{
	std::cout << "** ft_containers: vector::insert **\n\n";

	{
		ft::vector<Dummy>	v(1000000, Dummy("42"));
		ft::vector<Dummy>	v0(50000, Dummy("21"));

		bench();
		v0.insert(v0.begin() + 2000, v.begin(), v.end());
		std::cout << "\tYour vector took " << bench() << " ms.\n";

		namespace ft = std;

		ft::vector<Dummy>	v1(1000000, Dummy("42"));
		ft::vector<Dummy>	v2(50000,  Dummy("21"));

		bench();
		v2.insert(v2.begin() + 2000, v1.begin(), v1.end());
		std::cout << "\tStandard vector took " << bench() << " ms.\n";

		std::equal(v2.begin(), v2.end(), v0.begin()) == true ? std::cout << "\t\tTest passed!\n\n" : std::cout << "\t\tTest failed!\n\n";
	}

	{
		std::list<int>	l(420, 84);

		ft::vector<int>	v(4200000, 42);

		std::stringstream ss("0 1 2 3 4 5    7 8    10");
		std::istream_iterator<int> it(ss);

		bench();
		v.insert(v.begin(), -42);
		v.insert(v.end(), -42);
		v.insert(v.begin() + 3, it, std::istream_iterator<int>());
		v.insert(v.end() - 1, l.begin(), l.end());
		std::cout << "\tYour vector took " << bench() << " ms.\n";

		namespace ft = std;

		ft::vector<int>	v0(4200000, 42);

		std::stringstream ss0("0 1 2 3 4 5       7 8   10");
		std::istream_iterator<int> it0(ss0);

		bench();
		v0.insert(v0.begin(), -42);
		v0.insert(v0.end(), -42);
		v0.insert(v0.begin() + 3, it0, std::istream_iterator<int>());
		v0.insert(v0.end() - 1, l.begin(), l.end());
		std::cout << "\tStandard vector took " << bench() << " ms.\n";

		std::equal(v.begin(), v.end(), v0.begin()) == true ? std::cout << "\t\tTest passed!\n\n" : std::cout << "\t\tTest failed! Did you implement insert with input iterator correctly ?\n\n";

		std::cout << "\tTraversal using reverse_iterator...\n";
		std::equal(v.rbegin(), v.rend(), v0.rbegin()) == true ? std::cout << "\t\tTest passed!\n\n" : std::cout << "\t\tTest failed!\n\n";
	}
}

int Dummy::count = 0;

int main(void)
{
	std::list<Dummy>	listI(10, Dummy("yo"));

	try
	{
		ft::vector<int>	v(20, 123);
		ft::vector<int>::iterator	it_n;
		ft::vector<int>::const_iterator it;

		it = v.begin();
		it += 2;
	}
	catch(...)
	{
	}
	return (EXIT_SUCCESS);
}
