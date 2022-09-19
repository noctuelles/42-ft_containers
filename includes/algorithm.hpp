/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:16:39 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/19 16:44:47 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	template <class InputIterator1, class InputIterator2>
		bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
		{
			for (; *first1 != *last1; first1++, first2++)
			{
				if (*first1 != *first2)
					return (false);
			}
			return (true);
		}

	/*template <class InputIterator1, class InputIterator2>
		bool	lexicographical_compare(InputIterator1 first1, InputIterator2 last1,
				InputIterator2 first2, InputIterator2 last2)
		{
		}*/
}

#endif
