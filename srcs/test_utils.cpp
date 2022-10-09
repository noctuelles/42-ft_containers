/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:39:50 by plouvel           #+#    #+#             */
/*   Updated: 2022/10/09 16:41:25 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.hpp"
#include <sys/time.h>
#include <cstdlib>

static inline size_t	getMillisecDifference(const struct timeval& begin, const struct timeval& end)
{
	return ((end.tv_sec * 1000 + end.tv_usec / 1000) - (begin.tv_sec * 1000 + begin.tv_usec / 1000));
}

uint64_t	bench()
{
	static struct timeval	begin, end;
	static bool	isEnd = false;

	if (!isEnd)
	{
		gettimeofday(&begin, NULL);
		isEnd = true;
	}
	else
	{
		gettimeofday(&end, NULL);
		isEnd = false;
		return (getMillisecDifference(begin, end));
	}
	return (0);
}
