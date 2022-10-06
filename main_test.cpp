/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:34:04 by plouvel           #+#    #+#             */
/*   Updated: 2022/10/06 16:24:47 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>

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
		std::cout << "Size : " << vec.size() << '\n';
		std::cout << "Capacity : " << vec.capacity() << '\n';
		if (print_content)
		{
			std::cout << "Contains : " << '\n';
			std::for_each(vec.begin(), vec.end(), print<T>);
		}
	}

int	main()
{
	/* Testing the vector ! */

	std::cout << "## THIS TEST SHOULD BE DIFF, YOU'VE BEEN WARNED ##\n\n";
	NAMESPACE::vector<int>	v;
	NAMESPACE::vector<int>	v2;
	std::stringstream ss("1 2 3 4 5 6        8   666");
	std::istream_iterator<int>	ss_it(ss);

	v.insert(v.begin(), 3, 42);
	v.push_back(21);
	v.push_back(42);
	v.push_back(98);
	v.insert(v.begin() + 2, 999);
	print_vec(v);
	std::cout << "\n### Erasing... ###\n\n";
	v.erase(v.begin(), v.end());
	std::cout << "Is Empty ? " << std::boolalpha << v.empty() << '\n';
	std::cout << "\n### Inserting input iterator... ###\n\n";
	v.insert(v.begin(), ss_it, std::istream_iterator<int>());
	print_vec(v);

	try
	{
		std::cout << "\nOut of bounds with at() : " << v.at(999);
		std::cout << "no exception...";
	}
	catch(const std::out_of_range& e)
	{
		std::cout << "exception catch !\n";
	}

	std::cout << "What's index 7 : " << v[7] << '\n';
	std::cout << "Reserve me a big chunk please....\n";
	v.reserve(CHUNK_SIZE);
	std::cout << "What's my capacity : " << v.capacity() << '\n';
	v.erase(--v.end());
	v.insert(v.end(), CHUNK_SIZE - v.size() - 3, 42);
	std::cout << "I'm chunky now : " << v.size() << "... let's loose some.\n";
	v.erase(++++v.begin()++, v.end() - CHUNK_SIZE / 2);
	print_vec(v, false);
	std::cout << "Popping out some element...\n";
	v.pop_back();
	v.pop_back();
	print_vec(v, false);
	std::cout << "I'm done being fat. Resize me !\n";
	v.resize(21, 666);
	print_vec(v);
	v2.insert(v2.begin(), v.begin() + 3, v.end() - 4);
	v2.swap(v);
	print_vec(v); print_vec(v2);
	v2.clear();
	v2.assign(v.begin(), v.end());
	print_vec(v); print_vec(v2);

}
