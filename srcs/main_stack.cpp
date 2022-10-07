/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:54:14 by plouvel           #+#    #+#             */
/*   Updated: 2022/10/07 16:11:11 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include "vector.hpp"
#include <stack>
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

template <class T>
	void	print_stack(const NAMESPACE::stack<T>& vec)
	{
		std::cout << "#### stack content ####\n";
		std::cout << "size : " << vec.size() << '\n';
	}

int	main(void)
{
	NAMESPACE::stack<int>	s0;
	NAMESPACE::stack<int>	s1;

	std::cout << "empty: " << std::boolalpha << s0.empty() << '\n';
	s0.push(1);
	s0.push(2);
	s0.push(3);
	s0.push(4);
	std::cout << "empty: " << std::boolalpha << s0.empty() << '\n';
	s0.pop();
	s0.pop();
	const int& val = s0.top();
	std::cout << val << '\n';
	print_stack<int>(s0);
	s1 = s0;
	s1.pop();
	std::cout << "== : " << std::boolalpha << (s0 == s1) << '\n';
	std::cout << "!= : " << std::boolalpha << (s0 != s1) << '\n';
	std::cout << "< : " << std::boolalpha << (s0 < s1) << '\n';
	std::cout << "> : " << std::boolalpha << (s0 > s1) << '\n';
	std::cout << "<= : " << std::boolalpha << (s0 <= s1) << '\n';
	std::cout << ">= : " << std::boolalpha << (s0 >= s1) << '\n';
}
