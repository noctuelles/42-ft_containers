#include "map.hpp"
#include "pair.hpp"
#include "test_utils.hpp"
#include <map>

#include <string>
#include <utility>
#include <algorithm>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include "stdint.h"

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

void	iterator_test()
{
	std::cout << "####### ITERATOR TEST #######\n\n";

	typedef NAMESPACE::map<int, std::string>::iterator					map_it;
	typedef NAMESPACE::map<int, std::string>::const_iterator			const_map_it;
	typedef NAMESPACE::map<int, std::string>::reverse_iterator			map_rev_it;
	typedef NAMESPACE::map<int, std::string>::const_reverse_iterator	const_map_rev_it;

	NAMESPACE::map<int, std::string>	m;

	m.insert(NAMESPACE::make_pair(1, "i'm first"));

	for (const_map_it it = m.begin(); it != m.end(); it++)
		std::cout << it->second << '\n';
	for (const_map_rev_it it = m.rbegin(); it != m.rend(); it++)
		std::cout << it->second << '\n';

	m.insert(NAMESPACE::make_pair(32, "i'm second"));
	m.insert(NAMESPACE::make_pair(73, "i'm third"));
	m.insert(NAMESPACE::make_pair(128, "i'm last"));

	for (const_map_it it = m.begin(); it != m.end(); it++)
		std::cout << it->second << '\n';
	for (const_map_rev_it it = m.rbegin(); it != m.rend(); it++)
		std::cout << it->second << '\n';

	map_rev_it			r_it = ++m.rend();
	const_map_rev_it	cr_it = r_it;
	std::cout << cr_it->second << '\n';

	map_it			it = ----m.end();
	const_map_it	c_it = it;
	std::cout << c_it->second << '\n';

	std::cout << "####### END OF ITERATOR TEST #######\n\n";
}

void	lookup_test()
{
	std::cout << "####### LOOKUP TEST #######\n\n";

	NAMESPACE::map<int, std::string>	m;
	NAMESPACE::map<int, std::string>::iterator			it;
	NAMESPACE::map<int, std::string>::const_iterator	c_it;

	m.insert(NAMESPACE::make_pair(12, "HI YOU"));
	std::cout << m.count(12) << '\n';
	std::cout << m.count(666) << '\n';
	it = m.find(12);
	c_it = m.find(666);
	std::cout << it->second << '\n';
	if (c_it != m.end())
		std::cout << "Bad return value for find.\n";
	else
		std::cout << "Good return value for find.\n";

	m.insert(NAMESPACE::make_pair(32, "B"));
	m.insert(NAMESPACE::make_pair(73, "C"));
	m.insert(NAMESPACE::make_pair(128, "D"));

	if (m.lower_bound(20) != m.find(32) || m.lower_bound(12) != m.find(12))
		std::cout << "Bad return value for lower_bound.\n";
	else
		std::cout << "Good return value for lower_bound.\n";

	if (m.upper_bound(32) != m.find(73) || m.upper_bound(73) != m.find(128))
		std::cout << "Bad return value for upper_bound.\n";
	else
		std::cout << "Good return value for upper_bound.\n";

	NAMESPACE::pair<NAMESPACE::map<int, std::string>::iterator,NAMESPACE::map<int, std::string>::iterator> it_pair;

	it_pair = m.equal_range(32);

	for (NAMESPACE::map<int, std::string>::iterator it = it_pair.first; it != it_pair.second; it++)
	{
		std::cout << it->second << '\n';
	}
	if (it_pair.second != m.find(73))
		std::cout << "Bad end-iterator of the pair returned by equal range.\n";
	else
		std::cout << "Good end-iterator of the pair returned by equal range.\n";
	std::cout << "####### END OF LOOKUP TEST #######\n\n";
}

void	constructor_and_assignement_test()
{
	{
		NAMESPACE::map<int, std::string>	m;

		m.insert(NAMESPACE::make_pair(1, "A"));
		m.insert(NAMESPACE::make_pair(32, "B"));
		m.insert(NAMESPACE::make_pair(73, "C"));
		m.insert(NAMESPACE::make_pair(128, "D"));

		NAMESPACE::map<int, std::string>	m2(m);
		NAMESPACE::map<int, std::string>	m3(m.find(73), m.end());

		print_map(m);
		print_map(m2);
		print_map(m3);

		m3 = m2;

		print_map(m3);
	}
}

void	speed_test()
{
	NAMESPACE::map<unsigned int, unsigned int>	m;

	for (unsigned int i = 0; i < 2999999; i++)
		m.insert(NAMESPACE::make_pair(i, i * 2));
	m.find(99999);
	m.insert(m.end(), NAMESPACE::make_pair(99999, 4242));

	NAMESPACE::map<unsigned int, unsigned int>	m2(m);
}

int main(void)
{
	bench();
	modifiers_test();
	element_access_test();
	iterator_test();
	lookup_test();
	constructor_and_assignement_test();
	speed_test();
	std::cout << "The test took " << bench() << "ms to complete.\n";
}
