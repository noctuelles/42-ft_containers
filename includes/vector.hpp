/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:42:04 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/05 17:20:07 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "Iterator.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <algorithm>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			class iterator;

			typedef T														value_type;
			typedef Alloc													allocator_type;

			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;

			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;

			typedef std::size_t												size_type;

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
					explicit iterator(T *ptr) : _ptr(ptr) {};
					explicit iterator(const iterator &it) : _ptr(it._ptr) {};
					~iterator() {};

					iterator& operator=(const iterator& rhs)
					{
						_ptr = rhs._ptr;
						return (*this);
					}

					iterator&	operator+=(const iterator& rhs)
					{
						_ptr += rhs._ptr;
						return (*this);
					}

					iterator&	operator+=(const difference_type& n)
					{
						_ptr += n;
						return (*this);
					}

					iterator&	operator-=(const iterator& rhs)
					{
						_ptr -= rhs._ptr;
						return (*this);
					}

					iterator&	operator-=(const difference_type& n)
					{
						_ptr -= n;
						return (*this);
					}

					/* Relational Operators */

					bool	operator==(const iterator& rhs)
					{
						return (_ptr == rhs._ptr);
					}

					bool	operator!=(const iterator& rhs)
					{
						return (_ptr != rhs._ptr);
					}

					bool	operator<(const iterator& rhs)
					{
						return (_ptr < rhs._ptr);
					}

					bool	operator<=(const iterator& rhs)
					{
						return (_ptr <= rhs._ptr);
					}

					bool	operator>(const iterator& rhs)
					{
						return (_ptr > rhs._ptr);
					}

					bool	operator>=(const iterator& rhs)
					{
						return (_ptr >= rhs._ptr);
					}

					reference	operator*(void) const
					{
						return (*_ptr);
					}

					pointer	operator->(void) const
					{
						return (_ptr);
					}

					/* Unary Operators */

					iterator&	operator++(void)
					{
						_ptr++;
						return (*this);
					}

					iterator	operator++(int)
					{
						pointer	pSave;

						pSave = _ptr;
						_ptr++;
						return (iterator(pSave));
					}

					iterator&	operator--(void)
					{
						_ptr--;
						return (*this);
					}

					iterator	operator--(int)
					{
						pointer	pSave;

						pSave = _ptr;
						_ptr--;
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
						return (_ptr[i]);
					}

				private:
					T*		_ptr;
			};

			class const_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
			{
				public:

					using typename ft::iterator<ft::random_access_iterator_tag, T>::reference;
					using typename ft::iterator<ft::random_access_iterator_tag, T>::pointer;
					using typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type;

					const_iterator() : _ptr(NULL) {};
					const_iterator(T *ptr) : _ptr(ptr) {};
					const_iterator(const iterator &it) : _ptr(it._ptr) {};
					const_iterator(const const_iterator &it) : _ptr(it._ptr) {};
					~const_iterator() {};

					const_iterator& operator=(const iterator& rhs)
					{
						_ptr = rhs._ptr;
						return (*this);
					}

					const_iterator& operator=(const const_iterator& rhs)
					{
						_ptr = rhs._ptr;
						return (*this);
					}

					const_iterator&	operator+=(const_iterator const& rhs)
					{
						_ptr += rhs._ptr;
						return (*this);
					}

					const_iterator&	operator-=(const_iterator const& rhs)
					{
						_ptr -= rhs._ptr;
						return (*this);
					}

					/* Relational Operators */

					bool	operator==(const const_iterator& rhs)
					{
						return (_ptr == rhs._ptr);
					}

					bool	operator!=(const const_iterator& rhs)
					{
						return (_ptr != rhs._ptr);
					}

					bool	operator<(const const_iterator& rhs)
					{
						return (_ptr < rhs._ptr);
					}

					bool	operator<=(const const_iterator& rhs)
					{
						return (_ptr <= rhs._ptr);
					}

					bool	operator>(const const_iterator& rhs)
					{
						return (_ptr > rhs._ptr);
					}

					bool	operator>=(const const_iterator& rhs)
					{
						return (_ptr >= rhs._ptr);
					}

					const reference	operator*(void) const
					{
						return (*_ptr);
					}

					pointer	operator->(void) const
					{
						return (_ptr);
					}

					/* Unary Operators */

					const_iterator&	operator++(void)
					{
						_ptr++;
						return (*this);
					}

					const_iterator	operator++(int)
					{
						pointer	pSave;

						pSave = _ptr;
						_ptr++;
						return (const_iterator(pSave));
					}

					const_iterator&	operator--(void)
					{
						_ptr--;
						return (*this);
					}

					const_iterator	operator--(int)
					{
						pointer	pSave;

						pSave = _ptr;
						_ptr--;
						return (const_iterator(pSave));
					}

					/* Binary Operators */

					const_iterator	operator+(const difference_type& rhs) const
					{
						return (const_iterator(_ptr + rhs));
					}

					const_iterator	operator+(const const_iterator& rhs) const
					{
						return (const_iterator(_ptr + rhs._ptr));
					}

					difference_type	operator+(const const_iterator &rhs)
					{
						return (_ptr + rhs._ptr);
					}

					const_iterator	operator-(const difference_type& rhs) const
					{
						return (const_iterator(_ptr - rhs));
					}
					const_iterator	operator-(const const_iterator& rhs) const
					{
						return (const_iterator(_ptr - rhs._ptr));
					}
					difference_type	operator-(const const_iterator &rhs)
					{
						return (_ptr - rhs._ptr);
					}

					/* Subscripting Operator */

					reference	operator[](size_t i)
					{
						return (_ptr[i]);
					}

				private:
					T*		_ptr;
			};



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

			vector&	operator=(const vector& rhs)
			{
				std::cout << "Vector assignement called.\n";
				_capacity = rhs._capacity;
				_size = rhs._size;
				_allocator = rhs._allocator;
				_array = rhs._array;
				return (*this);
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

			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(end()));
			}

			reverse_iterator	rend(void)
			{
				return (reverse_iterator(begin()));
			}

			// ## Element Access ##

			reference		operator[](size_type n)			{ return (this->_array[n]); }
			const reference	operator[](size_type n) const	{ return (this->_array[n]); }

			reference	at(size_type n)
			{
				if (n >= _size)
					throw (std::out_of_range("vector::at"));
				return (_array[n]);
			}

			const reference	at(size_type n) const
			{
				if (n >= _size)
					throw (std::out_of_range("vector::at"));
				return (_array[n]);
			}

			reference		front(void)			{ return (_array[0]); }
			const reference	front(void) const	{ return (_array[0]); }

			reference		back(void)			{ return (_array[_size - 1]); }
			const reference	back(void) const	{ return (_array[_size - 1]); }

			T*			data(void)			{ return (_array); }
			const T*	data(void) const	{ return (reinterpret_cast<const T*>(_array)); }

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

			// undefined behavior : when the container is empty (size == 0).
			void	pop_back(void)	{ _allocator.destroy(_array[--_size]); }

			void	clear(void)		{ this->_destructAll(); }

			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last)
			{
				difference_type	size;

				size = last - first;
			}

			void	assign(size_type n, const value_type& val)
			{
				if (n > _capacity)
					this->_reAlloc_noSave(n);
				_size = n;
				for (iterator it = this->begin(); it != this->end(); it++)
					*it = val;
			}

			// Find the address of the element to be erased.
			// Move the element past the

			iterator	erase(iterator position)
			{
				_allocator.destroy(&(*position));
				if (position != this->end())
				{
					std::copy(position + 1, this->end(), position);
					_size--;
				}
				return (position);
			}

			iterator	erase(iterator first, iterator last)
			{
				difference_type	spanDistance;

				spanDistance = last - first;
				for (iterator it = first; it != last; it++)
					_allocator.destroy(&*it);
				if (last != this->end())
					std::copy(last, this->end(), first);
				_size -= spanDistance;

				return (first);
			}

			iterator	insert(iterator pos, size_type count, const T& value)
			{
				difference_type	distanceFromBeg;
				iterator		fillStop;

				std::cout << "call to insert\n";
				distanceFromBeg = 0;
				if (_size + count > _capacity)
				{
					// If a re-allocation begins, update the iterator so it's referring to the same element.
					distanceFromBeg = &*pos - &(*this->begin()) ;
					this->_reAlloc(_size + count);
					pos = iterator(&_array[distanceFromBeg]);
				}
				if (pos != this->end())
					std::copy_backward(pos, this->end(), this->end() + count);
				fillStop = iterator(pos + count);
				for (iterator it = pos; it != fillStop; it++)
					_allocator.construct(&*it, value);
				_size += count;
				return (pos);
			}



			template< class InputIterator >
			void	insert(iterator pos, InputIterator first, InputIterator last)
			{
				difference_type	spanDistance;
				difference_type	distanceFromBeg;

				spanDistance = last - first;
				distanceFromBeg = 0;
				if (_size + spanDistance > _capacity)
				{
					// If a re-allocation begins, update the iterator so it's referring to the same element.
					distanceFromBeg = &*pos - &(*this->begin()) ;
					this->_reAlloc(_size + spanDistance);
					pos = iterator(&_array[distanceFromBeg]);
				}
			}

			void	swap(vector& x)
			{
				allocator_type	allocator  = _allocator;
				size_type		size       = _size;
				size_type		capacity   = _capacity;
				T*				array      = _array;

				_allocator = x._allocator;
				_size = x._size;
				_capacity = x._capacity;
				_array = x._array;

				x._allocator = allocator;
				x._size = size;
				x._capacity = capacity;
				x._array = array;
			}

			// ## Allocator ##

			allocator_type	get_allocator(void) const
			{
				return (_allocator);
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

			void	_reAlloc_noSave(size_type n)
			{
				T*			pTemp;
				size_type	reAllocSize;

				reAllocSize = this->_getReAllocSize(n);
				pTemp = _allocator.allocate(reAllocSize);
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(&_array[i]);
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
