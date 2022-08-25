/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:42:04 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/25 20:21:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "Iterator.hpp"
#include <memory>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			/*	default-constructible, copy-constructible, copy-assignable,
			 *	destructible.
			 *
			 */

			class iterator : public ft::iterator<ft::random_access_iterator_tag, T>
			{
				public:

					iterator() : _ptr(NULL) {};
					iterator(T *ptr) : _ptr(ptr) {};
					iterator(const iterator &it) : _ptr(it._ptr) {};
					~iterator();

					iterator&	operator=(iterator const& rhs)
					{
						_ptr = rhs._ptr;
						return (*this);
					}

					iterator&	operator+=(iterator const& rhs)
					{
						this->_ptr += rhs._ptr;
						return (*this);
					}

					iterator&	operator-=(iterator const& rhs)
					{
						this->_ptr -= rhs._ptr;
						return (*this);
					}

					/* Relational Operators */

					bool	operator==(const iterator& rhs)
					{
						if (this->_ptr == rhs._ptr)
							return (true);
						else
							return (false);
					}

					bool	operator!=(const iterator& rhs)
					{
						if (this->_ptr != rhs._ptr)
							return (true);
						else
							return (false);
					}

					bool	operator>(const iterator& rhs)
					{
						if (this->_ptr > rhs._ptr)
							return (true);
						else
							return (false);
					}

					bool	operator<(const iterator& rhs)
					{
						if (this->_ptr < rhs._ptr)
							return (true);
						else
							return (false);
					}

					bool	operator>=(const iterator& rhs)
					{
						if (this->_ptr >= rhs._ptr)
							return (true);
						else
							return (false);
					}

					bool	operator<=(const iterator& rhs)
					{
						if (this->_ptr <= rhs._ptr)
							return (true);
						else
							return (false);
					}

					iterator&	operator*(void) const
					{
						return (*this->_ptr);
					}
					iterator*	operator->(void) const
					{
						return (this->_ptr);
					}

					/* Unary Operators */

					iterator	operator++(void) const
					{
						this->_ptr++;
						return (iterator(this->_ptr));
					}
					iterator	operator++(int) const
					{
						T*	pSave;

						pSave = this->_ptr;
						this->_ptr++;
						return (iterator(pSave));
					}

					/* Binary Operators */

					iterator	operator+(const iterator& rhs)
					{
						iterator	it;

						it._ptr = this->_ptr + rhs._ptr;
						return (it);
					}
					iterator	operator-(const iterator& rhs)
					{
						iterator	it;

						it._ptr = this->_ptr + rhs._ptr;
						return (it);
					}
					
					/* Subscripting Operator */

					iterator&	operator[](size_t i)
					{
						return (this->_ptr[i]);
					}


				private:

					T		*_ptr;
			};

			typedef T			value_type;
			typedef Alloc		allocator_type;

			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;

			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef std::size_t											size_type;

			// Default constructor
			explicit	vector(const allocator_type &alloc = allocator_type())
				: _allocator(alloc), _size(0)
			{

			}

			// Fill constructor
			// const value_type &val = value_type() : calls the default constructor if no argument is provided.
			explicit	vector(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type())
				: _allocator(alloc), _size(n)
			{
				(void) val;
			}

			size_type	max_size(void) const
			{
				return (_allocator.max_size());
			}

			size_type	size(void) const
			{
				return (_size);
			}

			void		reserve(size_type n);

			// ## Allocator ##

			allocator_type	get_allocator(void) const
			{
				return (_allocator);
			}

		private:
			allocator_type	_allocator;
			size_type		_capacity;
			size_type		_size;

			T				*_array;
	};
}

#endif
