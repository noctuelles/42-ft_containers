/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_base.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:14:52 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/16 20:08:53 by plouvel          ###   ########.fr       */
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
			T*					_end;			// End of vector elements, start of space allocated for possible expansion.
			T*					_last;			// End of allocated space.

			vector_base(typename std::allocator<T>::size_type n)
				: _allocator(), _begin(_allocator.allocate(n)), _end(_begin + n), _last(_begin + n)
			{}

			~vector_base()
			{
				_allocator.deallocate(_begin, _last - _begin);
			}

		};

	template <class T>
		void	swap(vector_base<T>& a, vector_base<T>& b)
		{
			std::swap(a._allocator, b._allocator);
			std::swap(a._begin, b._begin);
			std::swap(a._end, b._end);
			std::swap(a._last, b._last);
		}
}

namespace ft
{
template <class T>
	class vector : private vector_base<T>
	{
		public:

			typedef std::allocator<T>							allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef std::size_t									size_type;
			typedef	std::ptrdiff_t								difference_type;

			~vector()
			{
				_destroy_elements();
			}

			explicit vector(size_type n, const T& val)
				: vector_base<T>(n)
			{
				std::uninitialized_fill(this->_begin, this->_begin + n, val);
			}

			vector(const vector& x)
				: vector_base<T>(x.size())
			{
				std::uninitialized_copy(x.begin(), x.end(), this->_begin);
			}

			vector&	operator=(const vector& rhs)
			{
				// Perform a deep copy of rhs by using to copy-constructor
				if (this->capacity() < rhs.size())
				{
					vector	tmp(rhs);
					this->swap(tmp);
					return (*this);
				}
			}

			size_type	size()
			{
				return (this->_end - this->_begin);
			}

			size_type	capacity() const
			{
				return (this->_last - this->_begin);
			}

			void	swap(vector& other)
			{
				ft::swap(*this, other);
			}

		private:

		void _destroy_elements()
		{
			for (pointer p = this->_begin; p != this->_last; p++)
				this->_allocator.destroy(p);
		}
	};
}

#endif
