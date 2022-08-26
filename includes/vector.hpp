/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:42:04 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/27 00:18:06 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "Iterator.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			/*	default-constructible, copy-constructible, copy-assignable,
			 *	destructible.
			 *	random access iterator are behaving like a normal pointer.
			 */

			class iterator : public ft::iterator<ft::random_access_iterator_tag, T>
			{
				public:

					using typename ft::iterator<ft::random_access_iterator_tag, T>::reference;
					using typename ft::iterator<ft::random_access_iterator_tag, T>::pointer;
					using typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type;

					iterator() : _ptr(NULL) {};
					iterator(T *ptr) : _ptr(ptr) {};
					iterator(const iterator &it) : _ptr(it._ptr) {};
					~iterator() {};

					iterator& operator=(iterator const& rhs)
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
						return (this->_ptr == rhs._ptr);
					}

					bool	operator!=(const iterator& rhs)
					{
						return (this->_ptr != rhs._ptr);
					}

					bool	operator>(const iterator& rhs)
					{
						return (this->_ptr > rhs._ptr);
					}

					bool	operator<(const iterator& rhs)
					{
						return (this->_ptr < rhs._ptr);
					}

					bool	operator>=(const iterator& rhs)
					{
						return (this->_ptr >= rhs._ptr);
					}

					bool	operator<=(const iterator& rhs)
					{
						return (this->_ptr <= rhs._ptr);
					}

					reference	operator*(void) const
					{
						return (*this->_ptr);
					}
					pointer	operator->(void) const
					{
						return (this->_ptr);
					}

					/* Unary Operators */

					iterator	operator++(void)
					{
						return (iterator(_ptr++));
					}

					iterator	operator++(int)
					{
						pointer	pSave;

						pSave = _ptr;
						_ptr++;
						return (iterator(pSave));
					}

					/* Binary Operators */

					iterator	operator+(const difference_type& rhs) const
					{
						return (iterator(_ptr + rhs));
					}
					iterator	operator+(const iterator& rhs) const
					{
						return (iterator(_ptr + rhs._ptr));
					}
					difference_type	operator+(const iterator &rhs)
					{
						return (_ptr + rhs._ptr);
					}

					iterator	operator-(const difference_type& rhs) const
					{
						return (iterator(_ptr - rhs));
					}
					iterator	operator-(const iterator& rhs) const
					{
						return (iterator(_ptr - rhs._ptr));
					}
					difference_type	operator-(const iterator &rhs)
					{
						return (_ptr - rhs._ptr);
					}
					
					/* Subscripting Operator */

					reference	operator[](size_t i)
					{
						return (this->_ptr[i]);
					}

				private:

					T		*_ptr;
			};

			typedef T														value_type;
			typedef Alloc													allocator_type;

			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;

			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef std::size_t												size_type;

			// Default constructor
			explicit	vector(const allocator_type &alloc = allocator_type())
				: _allocator(alloc), _size(0), _capacity(0), _array(NULL) {}

			// Fill constructor
			// const value_type &val = value_type() : calls the default constructor if no argument is provided.
			explicit	vector(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type())
				: _allocator(alloc), _size(n), _capacity(n)
			{
				(void) val;
			}

			~vector()
			{
				this->_destroyAll();
				_allocator.deallocate(_array, _capacity);
			}

			// ## Iterator ##

			iterator	begin(void)
			{
				return (iterator(_array));
			}

			iterator	end(void)
			{
				if (!_size)
					return (begin());
				else
					return (iterator(&_array[_size]));
			}

			// ## Capacity ##

			size_type	size(void) const		{ return (_size); }
			size_type	max_size(void) const	{ return (_allocator.max_size()); }
			size_type	capacity(void) const	{ return (_capacity); }
			bool		empty(void) const		{ return (!_size); }

			void		reserve(size_type n)
			{
				T*	pTemp;

				if (n > max_size())
					throw (std::length_error("vector::reserve"));
				if (n > _capacity)
					this->_reAlloc(n);
			}

			void	resize(size_type new_size, value_type type = value_type())
			{
				if (new_size < _size)
				{
					for (size_type i = new_size; i < _size; i++)
						_allocator.destroy(&_array[i]);
				}
				else
				{
					if (new_size > _capacity)
						this->_reAlloc(new_size);
					for (size_type i = _size; i < new_size; i++)
						_allocator.construct(&_array[i], type);
				}
				_size = new_size;
			}

			// ## Element modifier ##

			void	push_back(const value_type& i)
			{
				if (_size + 1 > _capacity)
					this->_reAlloc(_size + 1);
				_array[_size++] = i;
			}

			void	clear(void) { this->_destructAll(); }

			// ## Allocator ##

			allocator_type	get_allocator(void) const
			{
				return (_allocator);
			}

			reference	operator[](size_type n)
			{
				return (this->_array[n]);
			}

		private:
			allocator_type	_allocator;
			size_type		_size;
			size_type		_capacity;

			T*				_array;

			size_type	_getReAllocSize(size_type n)
			{
				if (_capacity * 2 >= n)
					return (_capacity * 2);
				else
					return (_capacity + n);
			}

			void	_reAlloc(size_type n)
			{
				T*			pTemp;
				size_type	reAllocSize;

				reAllocSize = this->_getReAllocSize(n);
				pTemp = _allocator.allocate(reAllocSize);
				for (size_type i = 0; i < _size; i++)
				{
					_allocator.construct(&pTemp[i], _array[i]);
					_allocator.destroy(&_array[i]);
				}
				if (_array)
					_allocator.deallocate(_array, _capacity);
				_capacity = reAllocSize;
				_array = pTemp;
			}

			void	_destroyAll(void)
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(&_array[i]);
				_size = 0;
			}
	};
}

#endif
