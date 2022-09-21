/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:55:43 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/21 11:57:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.hpp"
#include <sys/time.h>

static inline size_t	getMillisecDifference(const struct timeval& begin, const struct timeval& end)
{
	return ((end.tv_sec * 1000 + end.tv_usec / 1000) - (begin.tv_sec * 1000 + begin.tv_usec / 1000));
}

namespace test
{
	timestamp_t	bench()
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
}
