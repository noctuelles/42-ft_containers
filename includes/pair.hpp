/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:33:09 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/29 15:08:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_TEMPLATE_HPP
# define PAIR_TEMPLATE_HPP

namespace ft
{
	/*	Reference : https://en.cppreference.com/w/cpp/utility/pair */

	template <class T1, class T2>
	struct pair
	{
		/*	Default constructor.
		 *	Value-initializes both elements of the pair, first and second. */

		pair() : first(), second() {}

		/*	Initializes first with x and second with y. */

		pair(const T1& x, const T2& y) : first(x), second(y) {}

		/*	Initializes first with p.first and second with p.second. */

		template <class U1, class U2>
		pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {};

		/* Copy assignment operator. Replaces the contents with a copy of the contents of other. */

		pair&	operator=(const pair& other)
		{
			if (*this != other)
			{
				this->first = other.first;
				this->second = other.second;
			}
			return (*this);
		}

		/*	Member objects. */

		T1	first;
		T2	second;

		/*	Member types. */

		typedef T1	first_type;
		typedef T2	second_type;
	};

	template <class T1, class T2>
	bool	operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.first == rhs.first);
	}

	template <class T1, class T2>
	bool	operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return !(lhs == rhs);
	}

	/* If lhs.first < rhs.first, returns true.
	 * If one of the two value (first or second) is < to rhs, return true.
	 * If rhs.first < lhs.first, return false.
	 * Consider two pairs : x1 x2 , y1 y2
	 *
	 * 4 5 | 4 5 : equals
	 * 3 5 | 4 5 : true
	 * 5 5 | 4 5 : false
	 * 4 5 | 3 5 : false
	 * 4 5 | 4 6 : false
	 *
	 * If x1 < y1, return true, if x1 > y1 : return false. */

	template <class T1, class T2>
	bool	operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool	operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool	operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool	operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	ft::pair<T1,T2> make_pair(T1 t, T2 u)
	{
		return (ft::pair<T1, T2> (t, u));
	}
}

#endif
