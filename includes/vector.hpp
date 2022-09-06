/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:42:04 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/06 09:27:38 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "iterators.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <algorithm>

/*	TODO:
 * Modifiers ;
 * Iterators DONE;
 * Capacity  DONE;
 */

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			class iterator;
			class const_iterator;

			typedef T														value_type;
			typedef Alloc													allocator_type;

			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;

			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

			typedef std::size_t												size_type;
			typedef	std::ptrdiff_t											difference_type;

			// ############# Iterators implementation #############

			class iterator : public ft::iterator<ft::random_access_iterator_tag, T>
			{
				public:

					using typename ft::iterator<ft::random_access_iterator_tag, T>::reference;
					using typename ft::iterator<ft::random_access_iterator_tag, T>::pointer;
					using typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type;

					iterator() : _ptr(NULL) {};
					iterator(pointer ptr) : _ptr(ptr) {};
					iterator(const iterator &it) : _ptr(it._ptr) {};
					~iterator() {};

					pointer base(void)
					{
						return (_ptr);
					}

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

					iterator&	operator+=(difference_type n)
					{
						_ptr += n;
						return (*this);
					}

					iterator&	operator-=(const iterator& rhs)
					{
						_ptr -= rhs._ptr;
						return (*this);
					}

					iterator&	operator-=(difference_type n)
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
					pointer	_ptr;
			};

			class const_iterator : public ft::const_iterator<ft::random_access_iterator_tag, T>
			{
				public:

					using typename ft::const_iterator<ft::random_access_iterator_tag, T>::reference;
					using typename ft::const_iterator<ft::random_access_iterator_tag, T>::pointer;
					using typename ft::const_iterator<ft::random_access_iterator_tag, T>::difference_type;

					const_iterator() : _ptr(NULL) {};
					const_iterator(T* ptr) : _ptr(ptr) {};
					const_iterator(pointer ptr) : _ptr(ptr) {};
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

					const_iterator&	operator+=(const const_iterator& rhs)
					{
						_ptr += rhs._ptr;
						return (*this);
					}

					const_iterator&	operator-=(const const_iterator& rhs)
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

					reference	operator*(void) const
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

					const_reference	operator[](size_t i)
					{
						return (_ptr[i]);
					}

				private:
					pointer	_ptr;
			};

			// ############################ Constructors and destructor ############################

			// Default constructor. Constructs an empty container with a default-constructed allocator.
			vector(void) : _allocator(allocator_type()), _size(0), _capacity(0), _array(NULL) {};

			// Constructs an empty container with the given allocator alloc.
			explicit vector(const allocator_type &alloc)
				: _allocator(alloc), _size(0), _capacity(0), _array(NULL) {}


			// Constructs the container with count copies of elements with value val.
			explicit vector(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type())
				: _allocator(alloc), _size(n), _capacity(n), _array(NULL)
			{
				this->resize(n, val);
			}

			// Constructs the container with the contents of the range [first, last).
			template <class InputIt>
				vector(InputIt first, InputIt last, const allocator_type& alloc = allocator_type())
				: _allocator(alloc), _size(0), _capacity(0), _array(NULL)
				{
					this->_reAlloc(std::distance(first, last));
				}

			/* Copy-assignement constructor
			 * Because it's a constructor, no need to deallocate. */
			vector(const vector& other) : _allocator(other._allocator), _size(other._size), _capacity(other._capacity), _array(NULL)
			{
				_array = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(&_array[i], other._array[i]);
			}

			// Destructor
			~vector(void)
			{
				this->_destroyAll();
				_allocator.deallocate(_array, _capacity);
			}

			// Copy assignment operator. Replaces the contents with a copy of the contents of rhs.
			vector&	operator=(const vector& rhs)
			{
				if (rhs != *this)
				{
					if (_array)
					{
						this->_destroyAll();
						_allocator.deallocate(_array, _capacity);
					}
					_allocator = rhs._allocator;
					_capacity = rhs._capacity;
					_size = rhs._size;
					_array = _allocator.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_allocator.construct(&_array[i], rhs._array[i]);
				}
				return (*this);
			}

			// ############################ Iterators ############################

			// Return an iterator to the first element of the array.
			// If the containers is empty, begin() == end()
			iterator	begin(void)
			{
				return (iterator(_array));
			}

			// Return a const_iterator to the first element of the array.
			const_iterator	begin(void) const
			{
				return (const_iterator(_array));
			}

			// Return an iterator to past the end element of the array.
			// If the containers is empty, begin() == end()
			iterator	end(void)
			{
				if (!_size)
					return (begin());
				else
					return (iterator(&_array[_size]));
			}

			// Return a const_iterator to past the end element of the array.
			// If the containers is empty, begin() == end()
			const_iterator	end(void) const
			{
				if (!_size)
					return (begin());
				else
					return (const_iterator(&_array[_size]));
			}

			/* Returns a reverse_iterator to past the end element of the array. */
			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(end()));
			}

			/* Returns a const_reverse_iterator to past the end element of the array. */
			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(end()));
			}

			/* Returns a reverse_iterator to the first element of the array. */
			reverse_iterator	rend(void)
			{
				return (reverse_iterator(begin()));
			}

			/* Returns a reverse_iterator to the first element of the array. */
			const_reverse_iterator	rend(void) const
			{
				return (const_reverse_iterator(begin()));
			}

			// ############################ Element Access ############################

			// Returns a reference to the n-th element.
			reference		operator[](size_type n)
			{
				return (_array[n]);
			}

			// Returns a const_reference to the n-th element.
			const_reference	operator[](size_type n) const
			{
				return (_array[n]);
			}

			// Same as operator[], but throws an exception if n >= size.
			const_reference	at(size_type n)
			{
				if (n >= _size)
					throw (std::out_of_range("vector::at"));
				return (static_cast<const_reference>(_array[n]));
			}

			// Same as const operator[], but throws an exception if n >= size.
			reference	at(size_type n) const
			{
				return (const_cast<reference>(this->at(n)));
			}

			// Returns a const_reference to the first element of the array.
			const_reference	front(void) const
			{
				return (_array[0]);
			}

			// Returns a reference to the first element of the array.
			reference		front(void)	
			{
				return (_array[0]);
			}

			// Returns a reference to the last element in the container.
			reference	back(void)
			{
				return (_array[_size - 1]);
			}

			// Returns a const_reference to the last element in the container.
			const_reference	back(void) const
			{
				return (_array[_size - 1]);
			}

			// Returns pointer to the underlying array serving as element storage.
			pointer	data(void)
			{
				return (_array);
			}

			// Returns a const_pointer to the underlying array serving as element storage.
			const_pointer	data(void) const
			{
				return (reinterpret_cast<const_pointer>(_array));
			}

			// ############################ Capacity ############################

			// Returns the current size of the container.
			size_type	size(void) const
			{
				return (_size);
			}

			// Returns the maximum number of elements the container is able to hold.
			size_type	max_size(void) const
			{
				return (_allocator.max_size());
			}

			// Returns the number of elements that the container has currently allocated space for.
			size_type	capacity(void) const
			{
				return (_capacity);
			}

			// Check if the vector has no elemens, returns true if that's the case.
			bool	empty(void) const
			{
				return (!_size);
			}

			/* Increase the capacity of the vector if new_cap > _capacity.
			 * Does not change the size of the vector, only the capacity.
			 * If reallocation occurs, all iterators are invalidated. */
			void	reserve(size_type new_cap)
			{
				if (new_cap > max_size())
					throw (std::length_error("vector::reserve"));
				if (new_cap > _capacity)
					this->_reAlloc(new_cap);
			}

			// ############################ Modifiers ############################

			/* Resizes the container to contain count elements.
			 * If new_size < _size, the container is shrinked, invalidating all iterators past the new size.
			 * Else, the container may reallocate if new_size > _capacity, and copies of type are appended. */
			void	resize(size_type new_size, value_type type = value_type())
			{
				if (new_size > max_size())
					throw (std::length_error("vector::resize"));
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
