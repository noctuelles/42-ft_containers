/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:01:26 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/21 13:05:34 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"
#include <sstream>
#include <iterator>

int	main(void)
{
	NAMESPACE::vector<Dummy> v;
	test::bench();
	v.push_back(Dummy("1"));
	v.push_back(Dummy("2"));
	v.push_back(Dummy("4"));
	v.push_back(Dummy("2"));
	v.pop_back();
	v.pop_back();
	test::printVector(v, test::bench(), true);
}
