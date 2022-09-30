/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:01:26 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/30 18:28:33 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "../Dummy.hpp"
#include "../common.hpp"
#include <iterator>

int	main(void)
{
	NAMESPACE::vector<Dummy> v;

	test::bench();
	v.push_back(Dummy("1"));
	v.push_back(Dummy("2"));
	v.push_back(Dummy("4"));
	v.push_back(Dummy("2"));
	v.push_back(Dummy("42"));
	v.push_back(Dummy("84"));
	v.push_back(Dummy("21"));
	v.pop_back();
	v.pop_back();
	test::printVector(v, test::bench(), true);
}
