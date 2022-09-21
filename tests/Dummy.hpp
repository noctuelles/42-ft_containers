#include <exception>
#include <iostream>

#ifndef DUMMY_CLASS_HPP
# define DUMMY_CLASS_HPP

class	Dummy
{
	public:
		Dummy() : _name("DFLT"), _anInt(NULL)
		{
		}

		Dummy(const std::string& name) : _name(name), _anInt(new int)
		{
		}

		Dummy(const Dummy& src) : _name(src._name), _anInt(new int)
		{
			if (src._anInt)
				*_anInt = *src._anInt;
		}

		Dummy&	operator=(const Dummy& lhs)
		{
			int*	pTmp;

			if (this != &lhs)
			{
				pTmp = _anInt;
				_anInt = new int;
				if (pTmp)
					delete pTmp;
				*_anInt = *lhs._anInt;
				_name = lhs._name;
			}
			return (*this);
		}

		bool	operator==(const Dummy& rhs)
		{
			return (_name == rhs._name);
		}

		int	operator&()
		{
			return (42);
		}

		~Dummy()
		{
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
