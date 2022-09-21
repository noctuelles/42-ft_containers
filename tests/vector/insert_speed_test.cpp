/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_speed_test.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:01:01 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/21 12:55:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.hpp"
#include <sstream>
#include <iterator>

int	main(void)
{
	NAMESPACE::vector<TYPE> v(10);
	NAMESPACE::vector<TYPE> v1(90000000);

	v.reserve(100000000);
	test::bench();
	v.insert(v.begin() + 5, v1.begin(), v1.end());
	test::printVector(v, test::bench(), false);

	v.reserve(1);
	test::bench();
	v.insert(v.begin(), v1.begin(), v1.end());
	test::printVector(v, test::bench(), false);
}
