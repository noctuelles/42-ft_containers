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
#include "iterators.hpp"
#include "type_traits.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include <typeinfo>
#include <stdio.h>
#include <sys/time.h>
#include "Dummy.hpp"

std::ostream&	operator<<(std::ostream& rhs, const Dummy& dummy)
{
	(void) dummy;
	rhs << "Hello i'm dummy " << dummy.getName() << '\n';
	return (rhs);
}

int	Dummy::count = 0;

bool	vectorTest_Constructors()
{
	return (true);
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

void	insertTest()
{
	struct timeval	begin, end;

	{
		ft::vector<Dummy>	dummyVector;

		gettimeofday(&begin, NULL);
		dummyVector.insert(dummyVector.begin(), Dummy("Test"));
		gettimeofday(&end, NULL);

		//std::cout << "Your vector took " << getMillisecDifference(begin, end) << '\n';
		std::for_each(dummyVector.begin(), dummyVector.end(), print<Dummy>);
	}

	{
		std::vector<Dummy>	dummyVector;

		gettimeofday(&begin, NULL);
		dummyVector.insert(dummyVector.begin(), Dummy("Test"));
		gettimeofday(&end, NULL);
		//std::cout << "Standard vector took " << getMillisecDifference(begin, end) << '\n';
		std::for_each(dummyVector.begin(), dummyVector.end(), print<Dummy>);
	}

	{
		ft::vector<Dummy>	dummyVector;
		ft::vector<Dummy>	anotherDummyVector;

		dummyVector.push_back(Dummy("Bonjour1"));
		dummyVector.push_back(Dummy("Bonjour2"));
		dummyVector.push_back(Dummy("Bonjour3"));
		dummyVector.push_back(Dummy("Bonjour4"));

		anotherDummyVector.push_back(Dummy("Bonjour2"));
		anotherDummyVector.push_back(Dummy("Bonjour2"));

		dummyVector.insert(dummyVector.begin() + 2, anotherDummyVector.begin() + 1, anotherDummyVector.end());
		std::for_each(dummyVector.begin(), dummyVector.end(), print<Dummy>);
	}
}

int main(void)
{
	insertTest();
	/*{
		ft::vector<Dummy> dummyVector;

		std::cout << "INSERTING ELEMENTS\n";
		dummyVector.insert(dummyVector.begin() + 1, 3, Dummy("Intru!"));

		std::cout << "Final size : " << dummyVector.size() << '\n';
		std::cout << "Final capacity : " << dummyVector.capacity() << '\n';
		std::cout << "Value :\n\n";
		for (ft::vector<Dummy>::iterator it = dummyVector.begin(); it != dummyVector.end(); it++)
		{
			std::cout << *it;
		}
	}
	std::cout << "\n\n";
	{
		std::vector<Dummy> dummyVector;

		std::cout << "INSERTING ELEMENTS\n";
		dummyVector.insert(dummyVector.begin(), 3, Dummy("Intru!"));

		std::cout << "Final size : " << dummyVector.size() << '\n';
		std::cout << "Final capacity : " << dummyVector.capacity() << '\n';
		std::cout << "Value :\n\n";
		for (std::vector<Dummy>::iterator it = dummyVector.begin(); it != dummyVector.end(); it++)
		{
			std::cout << *it;
		}
	}*/

	return (EXIT_SUCCESS);
}
