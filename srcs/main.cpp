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

int main(void)
{
	/*{
		ft::vector<Dummy> dummyVector;
		ft::vector<Dummy> anotherDummyVector;

		anotherDummyVector.push_back(Dummy("BONJOUR1"));
		anotherDummyVector.push_back(Dummy("BONJOUR2"));
		anotherDummyVector.push_back(Dummy("BONJOUR3"));
		dummyVector = anotherDummyVector;

		std::cout << "INSERTING ELEMENTS\n";
		dummyVector.insert(dummyVector.begin() + 1, 3, Dummy("Intru!"));

		std::cout << "Final size : " << dummyVector.size() << '\n';
		std::cout << "Final capacity : " << dummyVector.capacity() << '\n';
		std::cout << "Value :\n\n";
		for (ft::vector<Dummy>::iterator it = dummyVector.begin(); it != dummyVector.end(); it++)
		{
			std::cout << *it;
		}
	}*/
	std::cout << "\n\n";
	{
		std::vector<Dummy> dummyVector;
		std::vector<Dummy> anotherDummyVector;

		anotherDummyVector.push_back(Dummy("BONJOUR1"));
		anotherDummyVector.push_back(Dummy("BONJOUR2"));
		anotherDummyVector.push_back(Dummy("BONJOUR3"));
		dummyVector = anotherDummyVector;
		dummyVector.reserve(20);

		std::cout << "INSERTING ELEMENTS\n";
		dummyVector.insert(dummyVector.begin() + 1, 3, Dummy("Intru!"));

		std::cout << "Final size : " << dummyVector.size() << '\n';
		std::cout << "Final capacity : " << dummyVector.capacity() << '\n';
		std::cout << "Value :\n\n";
		for (std::vector<Dummy>::iterator it = dummyVector.begin(); it != dummyVector.end(); it++)
		{
			std::cout << *it;
		}
	}

	return (EXIT_SUCCESS);
}
