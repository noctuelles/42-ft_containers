/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:20:05 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/19 16:44:48 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_HPP
# define PRINT_HPP

#include <iostream>

template <class T>
	void	print(const T& arg)
	{
		std::cout << arg;
	}

template <>
void	print<int>(const int& i)
{
	std::cout << i << '\n';
}

#endif
