/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_input_it.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:48:42 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/21 12:00:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.hpp"
#include <sstream>
#include <iterator>

int	main(void)
{
	NAMESPACE::vector<TYPE> v(10);

	std::stringstream ss("0 1 2 3 4 5    7 8    10");
	std::istream_iterator<TYPE> it(ss);

	test::bench();
	v.insert(v.begin(), 42);
	v.insert(v.end(), -42);
	v.insert(v.begin() + 2, it, std::istream_iterator<TYPE>());
	test::printVector(v, test::bench());
}
