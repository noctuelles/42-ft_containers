#include "map.hpp"
#include <map>

#include <utility>
#include <algorithm>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

template <class Key, class T>
	void	print_map(const NAMESPACE::map<Key, T>& m, bool print_content = true)
	{
		std::cout << "## map content ##\n";
		std::cout << "size: " << m.size() << '\n';
		std::cout << "is empty ? " << std::boolalpha << m.empty() << '\n';
		if (print_content)
		{
			std::cout << "content:\n";
			for (typename NAMESPACE::map<Key, T>::const_iterator it = m.begin(); it != m.end(); it++)
				std::cout << "key: " << it->first << " content: " << it->second << '\n';
		}
	}

void	modifiers_test()
{
	std::cout << "####### MODIFIERS TEST #######\n\n";
	NAMESPACE::map<int, std::string>	m, m2;
	NAMESPACE::pair<NAMESPACE::map<int, std::string>::const_iterator, bool> returned_pair;
	NAMESPACE::pair<NAMESPACE::map<int, std::string>::const_iterator, bool> comp_pair;

	m.insert(NAMESPACE::make_pair(1, "i'm first"));
	m.insert(NAMESPACE::make_pair(32, "i'm second"));
	m.insert(NAMESPACE::make_pair(73, "i'm third"));
	m.insert(NAMESPACE::make_pair(128, "i'm last"));
	returned_pair = m.insert(NAMESPACE::make_pair(-1, "i'm inserted last but i'm first!"));
	comp_pair = m.insert(NAMESPACE::make_pair(-1, "i'm a duplicate"));

	if (comp_pair.first != returned_pair.first || comp_pair.second != false)
		std::cout << "Bad return value for duplicate.\n";
	else
		std::cout << "Good return value for duplicate.\n";

	m.insert(m.end()--, NAMESPACE::make_pair(786, "i'm inserted last but i'm very effective !"));
	print_map(m);

	m.clear();
	print_map(m);

	m.insert(NAMESPACE::make_pair(2, "Make"));
	m.insert(NAMESPACE::make_pair(23, "it"));
	m.insert(NAMESPACE::make_pair(83, "funny"));
	m.insert(NAMESPACE::make_pair(88, "PlEaSeeeEEE"));
	m.insert(NAMESPACE::make_pair(-9999999, "Could you!?"));
	m2 = m;

	m.erase(--m.end());
	m.erase(++(++m.begin()), m.end());
	if (m.erase(2) != 1)
		std::cout << "Bad return size for erase.\n";
	else
		std::cout << "Good return size for erase.\n";
	if (m.erase(83) != 0)
		std::cout << "Bad return size for erase.\n";
	else
		std::cout << "Good return size for erase.\n";
	m.erase(--m.end());
	print_map(m);
	m2.swap(m);
	print_map(m);
	print_map(m2);
	m2.insert(NAMESPACE::make_pair(21, "just one little element please"));
	m2.swap(m);
	print_map(m);
	print_map(m2);
	m.clear();
	m2.clear();
	m.swap(m2);
	print_map(m);
	print_map(m2);
	std::cout << "####### MODIFIERS TEST DONE #######\n\n";
}

void	element_access_test()
{
	std::cout << "####### ELEMENT ACCESS TEST #######\n\n";
	NAMESPACE::map<int, std::string>	m;

	m.insert(NAMESPACE::make_pair(1, "i'm first"));
	m.insert(NAMESPACE::make_pair(32, "i'm second"));
	m.insert(NAMESPACE::make_pair(73, "i'm third"));
	m.insert(NAMESPACE::make_pair(128, "i'm last"));
	try
	{
		m.at(99999);
		std::cout << "Exception not catched.\n";
	}
	catch(const std::out_of_range& ofr)
	{
		std::cout << "Exception catched.\n";
	}
	std::cout << (m[99999] = "Hello life") << '\n';
	std::cout << (m[99999]) << '\n';
	std::cout << (m[32]) << '\n';
	std::cout << (m[32] = "i feel like a new man") << '\n';
	std::cout << (m[666]) << '\n';
	print_map(m);
	std::cout << "####### END OF ELEMENT ACCESS TEST #######\n\n";
}

int main(void)
{
	modifiers_test();
	element_access_test();
}
