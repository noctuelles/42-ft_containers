#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <ostream>
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
		static int count;

		Dummy()
		{
			std::cout << "Dummy default constructor called." << std::endl;
			count++;
		}

		Dummy(const std::string& name) : _name(name), _anInt(new int)
		{
			std::cout << "Dummy parametric constructor called. _anInt:" << _anInt << '\n';
		}

		Dummy(const Dummy& src) : _name(src._name), _anInt(new int)
		{
			*_anInt = *src._anInt;
			std::cout << "Dummy copy constructor called. _anInt :" << _anInt << '\n';
		}

		Dummy&	operator=(const Dummy& lhs)
		{
			std::cout << "Dummy copy assignment called. Destroying _anInt:" << _anInt << '\n';
			delete _anInt;
			_anInt = new int;
			*_anInt = *lhs._anInt;
			std::cout << "Replacing with " << _anInt << '\n';
			_name = lhs._name;
			return (*this);
		}

		int	operator&()
		{
			return (2);
		}

		~Dummy()
		{
			std::cerr << "Dummy destructor called. _anInt : " << _anInt << '\n';
			delete _anInt;
		}

		const std::string&	getName(void) const
		{
			return (_name);
		}

	private:
		std::string _name;
		int*		_anInt;
};
std::ostream&	operator<<(std::ostream& rhs, const Dummy& dummy)
{
	(void) dummy;
	rhs << "Hello i'm dummy " << dummy.getName() << '\n';
	return (rhs);
}

int	Dummy::count = 0;

int main(void)
{
	{
		ft::vector<Dummy> dummyVector;

		dummyVector.push_back(Dummy("Benoit"));
		dummyVector.push_back(Dummy("Paul"));
		dummyVector.push_back(Dummy("Felix"));
		dummyVector.push_back(Dummy("Christophe"));
		std::cout << "REMOVING ONE ELEM\n";
		dummyVector.erase(dummyVector.begin() + 1);
		std::cout << "Final size : " << dummyVector.size() << '\n';
		for (ft::vector<Dummy>::iterator it = dummyVector.begin(); it != dummyVector.end(); it++)
		{
			std::cout << *it;
		}
	}
	std::cout << "\n\n";
	{
		std::vector<Dummy> dummyVector;

		dummyVector.push_back(Dummy("Benoit"));
		dummyVector.push_back(Dummy("Paul"));
		dummyVector.push_back(Dummy("Felix"));
		dummyVector.push_back(Dummy("Christophe"));
		std::cout << "REMOVING ONE ELEM\n";
		dummyVector.erase(dummyVector.begin() + 1);
		std::cout << "Final size : " << dummyVector.size() << '\n';

		for (std::vector<Dummy>::iterator it = dummyVector.begin(); it != dummyVector.end(); it++)
		{
			std::cout << *it;
		}
	}

	return (EXIT_SUCCESS);
}
