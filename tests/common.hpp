/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:54:52 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/21 12:56:18 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_HPP
# define COMMON_HPP

# ifndef TYPE
#  define TYPE      unsigned long long
# endif

# define SPEED_CNT 9999999

# ifdef USING_STD
#  define NAMESPACE std
#  include <vector> 
# else
#  define NAMESPACE ft
#  include "vector.hpp"
# endif

# include <cctype>
# include <algorithm>
# include <iostream>

typedef size_t timestamp_t;

namespace test
{
	timestamp_t	bench();

	template <class T>
		void print(const T& arg)
		{
			std::cout << arg << '\n';
		}

	template <class T>
		void	printVector(const NAMESPACE::vector<T>& v, timestamp_t timestamp, bool print_content = true)
	{
		bool capacityOK = (v.capacity() >= v.size()) ? true : false;

		std::cout << "Capacity: " << std::boolalpha << capacityOK << '\n';
		std::cout << "Size: " << v.size() << '\n';
		if (print_content)
		{
			std::cout << "Content: \n";
			std::for_each(v.begin(), v.end(), print<T>);
		}
		std::cerr << "DONE IN " << timestamp << "ms" << '\n';
	}
}

#endif
