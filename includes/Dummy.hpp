#include <exception>
#include <iostream>

#ifndef DUMMY_CLASS_HPP
# define DUMMY_CLASS_HPP

class	Dummy
{
	public:
		static int count;

		Dummy() : _name("DFLT"), _anInt()
		{
			//std::cout << "Dummy default constructor called." << std::endl;
		}

		Dummy(const std::string& name) : _name(name), _anInt(new int)
		{
			//std::cout << "Dummy parametric constructor called. _anInt:" << _anInt << '\n';
		}

		Dummy(const Dummy& src) : _name(src._name), _anInt(new int)
		{
			if (src._anInt)
				*_anInt = *src._anInt;
			count++;
			//std::cout << "Dummy copy constructor called. _anInt :" << _anInt << '\n';
		}

		Dummy&	operator=(const Dummy& lhs)
		{
			int*	pTmp;

			//std::cout << "Dummy copy assignment called. Destroying _anInt:" << _anInt << '\n';
			if (this != &lhs)
			{
				pTmp = _anInt;
				_anInt = new int;
				delete pTmp;
				*_anInt = *lhs._anInt;
				//std::cout << "Replacing with " << _anInt << '\n';
				_name = lhs._name;
			}
			return (*this);
		}

		int	operator&()
		{
			return (2);
		}

		~Dummy()
		{
			//std::cerr << "Dummy destructor called. _anInt : " << _anInt << '\n';
			if (_anInt)
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

#endif
