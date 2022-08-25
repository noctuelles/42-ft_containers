#include <iterator>
#include <memory>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "vector.hpp"
#include <typeinfo>

int main(void)
{
	ft::vector<float>::iterator::reference z;

	std::cout << typeid(z).name() << std::endl;
	return (EXIT_SUCCESS);
}
