/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:34:04 by plouvel           #+#    #+#             */
/*   Updated: 2022/10/06 16:32:25 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <list>

#include <algorithm>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

#define CHUNK_SIZE 299999999

template <class T>
	void	print(const T& val)
	{
		std::cout << val << '\n';
	}

template <class T>
	void	print_vec(const NAMESPACE::vector<T>& vec, bool print_content = true)
	{
		std::cout << "#### vector content ####\n";
		std::cout << "size : " << vec.size() << '\n';
		std::cout << "capacity : " << vec.capacity() << '\n';
		if (print_content)
		{
			std::cout << "contains : " << '\n';
			std::for_each(vec.begin(), vec.end(), print<T>);
		}
	}

void	print_banner(const std::string& str)
{
	std::cout << "#### " << str << " ####\n";
}

void	insertion_test()
{
	print_banner("Insertion testing");
	/* Testing standard insertion */

	{
		NAMESPACE::vector<std::string>	v;

		v.insert(v.begin(), 21, "42");
		NAMESPACE::vector<std::string>::iterator i = v.insert(v.begin() + 3, "HI");
		std::cout << *i << '\n';
		v.insert(v.begin() + 11, "###");
		print_vec(v);
	}

	/* Testing input iterator insertion */

	{
		NAMESPACE::vector<int>	v;
		std::stringstream ss("1 2 3 4 5 6        8   666");
		std::istream_iterator<int>	ss_it(ss);

		v.insert(v.begin(), 21, 42);
		v.insert(v.end() - 15, ss_it, std::istream_iterator<int>());
		print_vec(v);
	}

	/* Insertion from another container */

	{
		NAMESPACE::vector<int>	v;
		std::list<int>	l;

		l.push_back(42);
		l.push_back(21);
		v.insert(v.begin(), l.begin(), l.end());
		print_vec(v);
	}
}

void	access_test()
{
	print_banner("Access testing");
	NAMESPACE::vector<int>	v;
	
	v.push_back(42);
	v.insert(v.begin() + 1, 10, 66);
	v.push_back(84);
	std::cout << v[1] << '\n';
	std::cout << v[9] << '\n';
	std::cout << v.front() << '\n';
	std::cout << v.back() << '\n';
	std::cout << v.data()[9] << '\n';
	try
	{
		v.at(99999);
		std::cout << "Exception not catched.\n";
	}
	catch (const std::out_of_range& ofr)
	{
		std::cout << "Exception catched.\n";
	}
}

typedef NAMESPACE::vector<int> int_vec;

void	iterators_test()
{
	{
		int_vec	v;

		for (int i = 0; i < 42; i++)
			v.push_back(i);
		for (int_vec::const_iterator it = v.begin(); it != v.end(); it++)
			std::cout << *it << '\n';
		for (int_vec::const_reverse_iterator it = v.rbegin(); it != v.rend(); it++)
			std::cout << *it << '\n';
		v.resize(1);
		for (int_vec::const_reverse_iterator it = v.rbegin(); it != v.rend(); it++)
			std::cout << *it << '\n';

		int_vec::iterator it = v.begin();
		it = (it + 3 - 3 + 1)--;
		int_vec::const_iterator c_it = it;
		std::cout << *c_it << '\n';
		int_vec::reverse_iterator r_it = v.rbegin();
		int_vec::const_reverse_iterator cr_it = r_it;
		(void) cr_it;
		print_vec(v);
	}
}

void	capacity_test()
{
	NAMESPACE::vector<std::string>	v;

	v.resize(42, "BONJOUR TOIII");
	std::cout << v.size() << '\n';
	std::cout << v.max_size() << '\n';
	std::cout << std::boolalpha << v.empty() << '\n';
	v.clear();
	std::cout << std::boolalpha << v.empty() << '\n';
	v.reserve(5000);
	std::cout << v.capacity() << '\n';
}

void	construct_assign_test()
{

}

int	main()
{
	std::cout << "## THIS TEST SHOULD BE DIFF, YOU'VE BEEN WARNED ##\n\n";
	insertion_test();
	access_test();
	iterators_test();
	capacity_test();
	construct_assign_test();
}
