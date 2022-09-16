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

bool	vectorTest_Constructors()
{
	return (true);
}

static inline size_t	getMillisecDifference(const struct timeval& begin, const struct timeval& end)
{
	return ((end.tv_sec * 1000 + end.tv_usec / 1000) - (begin.tv_sec * 1000 + begin.tv_usec / 1000));
}

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
		ft::vector<ft::vector<Dummy> > lol;

		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));

		lol.push_back(dummyVector);

		gettimeofday(&begin, NULL);
		lol.insert(lol.begin(), 1999999, dummyVector);
		gettimeofday(&end, NULL);

		std::cout << "Your vector took " << getMillisecDifference(begin, end) << '\n';
		//std::for_each(dummyVector.begin(), dummyVector.end(), print<Dummy>);
	}

	{
		namespace ft = std;

		ft::vector<Dummy>	dummyVector;
		ft::vector<ft::vector<Dummy> > lol;

		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));
		dummyVector.push_back(Dummy("Bonjourss"));

		lol.push_back(dummyVector);

		gettimeofday(&begin, NULL);
		lol.insert(lol.begin(), 1999999, dummyVector);
		gettimeofday(&end, NULL);

		std::cout << "Standard vector took " << getMillisecDifference(begin, end) << '\n';
		//std::for_each(dummyVector.begin(), dummyVector.end(), print<Dummy>);
	}
}

int Dummy::count = 0;

int main(void)
{
	insertTest();
	/*
	{
		ft::vector<int> dummyVector;


		std::cout << "INSERTING ELEMENTS\n";
		try
		{
			dummyVector.push_back(1);
			dummyVector.push_back(2);
			dummyVector.push_back(3);
			dummyVector.push_back(4);
			dummyVector.push_back(5);
			dummyVector.push_back(6);

			dummyVector.insert(dummyVector.begin() + 5, 0);
		}
		catch(...)
		{

		}

		std::cout << "Final size : " << dummyVector.size() << '\n';
		std::cout << "Final capacity : " << dummyVector.capacity() << '\n';
		std::cout << "Value :\n\n";
		for (ft::vector<int>::iterator it = dummyVector.begin(); it != dummyVector.end(); it++)
		{
			std::cout << *it << '\n';
		}
	}
	std::cout << "\n\n";*/
	/*{
		std::vector<Dummy> dummyVector;
		dummyVector.push_back(Dummy("Bonjour1"));
		dummyVector.push_back(Dummy("Bonjour2"));
		dummyVector.push_back(Dummy("Bonjour3"));
		dummyVector.push_back(Dummy("Bonjour4"));
		dummyVector.push_back(Dummy("Bonjour5"));
		dummyVector.push_back(Dummy("Bonjour6"));
		dummyVector.push_back(Dummy("Bonjour7"));
		dummyVector.push_back(Dummy("Bonjour8"));

		std::cout << "INSERTING ELEMENTS\n";
		dummyVector.insert(dummyVector.begin(), 9, Dummy("Intru!"));

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
