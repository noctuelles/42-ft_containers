/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_base.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:14:52 by plouvel           #+#    #+#             */
/*   Updated: 2022/10/09 18:44:44 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_BASE_HPP
# define VECTOR_BASE_HPP

#include <memory>

namespace ft
{
	template <class T>
		struct	vector_base
		{
			std::allocator<T>	_allocator;
			T*					_begin;			// Start of allocation.
			T*					_last;			// End of vector elements, start of space allocated for possible expansion.
			T*					_end;			// End of allocated space.

			vector_base(typename std::allocator<T>::size_type n)
				: _allocator(), _begin(), _last(), _end()
			{
				if (n > 0)
					_begin = _allocator.allocate(n);
				_last = _begin + n;
				_end = _begin + n;
			}

			~vector_base()
			{
				if (_begin)
					_allocator.deallocate(_begin, _end - _begin);
			}

		};

	// Overload of std::swap for vector_base.
		template <class T>
		void	swap(vector_base<T>& a, vector_base<T>& b)
		{
			std::swap(a._allocator, b._allocator);
			std::swap(a._begin, b._begin);
			std::swap(a._last, b._last);
			std::swap(a._end, b._end);
		}
}

#endif
