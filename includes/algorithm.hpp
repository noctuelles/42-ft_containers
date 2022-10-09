/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:16:39 by plouvel           #+#    #+#             */
/*   Updated: 2022/10/09 17:46:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	/* Check if the range [first1, last1) is equal to the range [first2, (last1 - first1)) */
	template <class InputIterator1, class InputIterator2>
		bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
		{
			for (; first1 != last1; first1++, first2++)
			{
				if (*first1 != *first2)
					return (false);
			}
			return (true);
		}

	template <class InputIt1, class InputIt2>
		bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2)
		{
			for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
			{
				if (*first1 < *first2)
					return (true);
				if (*first2 < *first1)
					return (false);
			}
			return ((first1 == last1) && (first2 != last2));
		}
}

#endif
