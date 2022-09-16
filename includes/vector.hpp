/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:42:04 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/16 15:08:44 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "iterators.hpp"
#include <cstddef>
#include <cwchar>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <new>
#include <stdexcept>
#include <cstring>
#include <typeinfo>
#include <cstdlib>
#include <algorithm>
#include "Dummy.hpp"
#include "type_traits.hpp"

/*	TODO:
 * Modifiers ;
 * Iterators DONE;
 * Capacity  DONE;
 */

namespace ft
{
	template <class T>
		class vector
		{
			public:

				class iterator;
				class const_iterator;

				// ############# Typedefs ###########

				typedef T												value_type;
				typedef std::allocator<T>								allocator_type;

				typedef typename allocator_type::reference				reference;
				typedef typename allocator_type::const_reference		const_reference;
				typedef typename allocator_type::pointer				pointer;
				typedef typename allocator_type::const_pointer			const_pointer;

				typedef ft::reverse_iterator<iterator>					reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

				typedef std::size_t										size_type;
				typedef	std::ptrdiff_t									difference_type;

				// ############# Iterators implementation #############

				class iterator : public ft::iterator<std::random_access_iterator_tag, T>
				{
					public:

						using typename ft::iterator<std::random_access_iterator_tag, T>::reference;
						using typename ft::iterator<std::random_access_iterator_tag, T>::pointer;
						using typename ft::iterator<std::random_access_iterator_tag, T>::difference_type;

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

				class const_iterator : public ft::const_iterator<std::random_access_iterator_tag, T>
				{
					public:

						using typename ft::const_iterator<std::random_access_iterator_tag, T>::reference;
						using typename ft::const_iterator<std::random_access_iterator_tag, T>::pointer;
						using typename ft::const_iterator<std::random_access_iterator_tag, T>::difference_type;

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
				vector() :  _allocator(), _size(), _capacity(), _array() {}


				/* Constructs the container with count copies of elements with value val.
				 * The container is calling assign() behind the scene. */
				explicit vector(size_type n, const value_type &val = value_type())
					: _allocator(), _size(), _capacity(), _array()
				{
					this->assign(n, val);
				}

				/* Constructs the container with the contents of the range [first, last).
				 * The container is calling assign() behind the scene. */
				template <class InputIt>
					vector(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
					: _allocator(), _size(), _capacity(), _array()
					{
						this->assign(first, last);
					}

				/* Copy constructor
				 * Because it's a constructor, no need to deallocate. */
				vector(const vector& other) : _allocator(other._allocator), _size(other._size), _capacity(_size), _array()
				{
					_array = _allocator.allocate(_size);
					for (size_type i = 0; i < _size; i++)
						_allocator.construct(_array + i, other._array[i]);
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
					T*	pTmpArray;

					/* Allocating memory before deallocating the current array ; if _allocator.allocate throws an exception,
					 * the current instance is left untouched so it can be destroyed without any incident (double free, etc...). */
					if (this != &rhs)
					{
						pTmpArray = _allocator.allocate(rhs._size);
						if (_array)
						{
							this->_destroyAll();
							_allocator.deallocate(_array, _capacity);
						}
						_size = rhs._size;
						_capacity = _size;
						_allocator = rhs._allocator;
						_array = pTmpArray;
						for (size_type i = 0; i < _size; i++)
							_allocator.construct(_array + i, rhs._array[i]);
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
						return (iterator(_array + _size));
				}

				// Return a const_iterator to past the end element of the array.
				// If the containers is empty, begin() == end()
				const_iterator	end(void) const
				{
					if (!_size)
						return (begin());
					else
						return (const_iterator(_array + _size));
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

				/* Erases all elements from the container. After this call, size() returns zero.
				* Invalidates any references, pointers, or iterators referring to contained elements.
				* Any past-the-end iterators are also invalidated.
				* Capacity of the vector is unchanged. */
				void	clear(void)
				{
					this->_destructAll();
					_size = 0;
				}

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
							_allocator.destroy(_array + i);
					}
					else
					{
						if (new_size > _capacity)
							this->reserve(new_size);
						for (size_type i = _size; i < new_size; i++)
							_allocator.construct(_array + i, type);
					}
					_size = new_size;
				}

				/* Add an element at the end of the container.
				 * Might realloc if the size exceed the capacity. */
				void	push_back(const value_type& i)
				{
					if (_size + 1 > _capacity)
						this->reserve(_size + 1);
					_allocator.construct(_array + _size++, i);
				}

				// Removes the last element of the container.
				void	pop_back(void)
				{
					_allocator.destroy(_array + --_size);
				}

				// Replaces the contents with copies of those in the range [first, last).
				template <class InputIterator>
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
					assign(InputIterator first, InputIterator last)
					{
						difference_type	n;

						n = std::distance(first, last);
						if (n <= 0)
							return ;
						if (static_cast<size_t>(n) > _capacity)
						{
							this->_reAllocNoCopy(n);
							for (size_type i = 0; first != last; first++, i++)
								_allocator.construct(_array + i, *first);
						}
						else
						{
							std::copy(first, last, _array);
							for (size_type i = n; i < _size; i++)
								_allocator.destroy(_array + i);
						}
						_size = n;
					}

				// Replaces the contents with n copies of value val.
				void	assign(size_type n, const value_type& val)
				{
					if (n > _capacity)
					{
						this->_reAllocNoCopy(n);
						for (size_type i = 0; i < n; i++, _size++)
							_allocator.construct(_array + i, val);
					}
					else
					{
						std::fill_n(_array, n, val);
						for (size_type i = n; i < _size; i++)
							_allocator.destroy(_array + i);
					}
				}

				// Remove the element at position.
				// Invalidates all iterators at or past the point of erase.
				// Return an iterator following the last element removed.
				iterator	erase(iterator position)
				{
					return (erase(position, position + 1));
				}

				// Removes the elements in the range [first, last).
				// Invalidates all iterators at or past the point of erase.
				// Return an iterator following the last element removed.
				iterator	erase(iterator first, iterator last)
				{
					difference_type	iteratorDistance;

					iteratorDistance = std::distance(first, last);
					if (iteratorDistance <= 0)
						return (last);
					for (iterator it = std::copy(first + iteratorDistance, this->end(), first); it != this->end(); it++)
						_allocator.destroy(it.base());
					_size -= iteratorDistance;
					return (first);
				}

				void	insert(iterator pos, size_type count, const T& value)
				{
					this->_insert(pos, count, value);
				}

				// Insert value before pos
				iterator insert(iterator pos, const T& value)
				{
					return (this->_insert(pos, 1, value));
				}

				template <class RandomAccessIterator>
					void _insert(iterator pos, RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
					{
						bool	isRangeInCurrentVector;
						difference_type	firstDistance,
										lastDistance,
										count;

						isRangeInCurrentVector = false;
						count = std::distance(first, last);
						if (first.base() >= this->begin().base())
						{
							firstDistance = std::distance(this->begin(), first);
							lastDistance = std::distance(this->begin(), last);
							isRangeInCurrentVector = true;
						}
						if (count)
						{
							if (_size + count > _capacity)
							{
								this->_reAlloc(_size + count);
								if (isRangeInCurrentVector)
								{
									first = iterator(_array + firstDistance);
									last = iterator(_array + lastDistance);
								}
							}
							for (iterator it = this->end(); it != this->end() + count; it++)
							{
								(void) pos;
							}
						}
					}

				template <class InputIterator>
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
					insert(iterator pos, InputIterator first, InputIterator last)
					{
						this->_insert(pos, first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
					}

				// Exchanges the contents of the container with those of x.
				// There's no move, copy operation on individual elements.
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

				std::allocator<T>	_allocator;
				size_type			_size;
				size_type			_capacity;

				T*					_array;

				void	_insert_construct(size_type count)
				{
					pointer		p, pEndElem;
					size_type	i;
					size_type	toCopy;

					i = 0;
					toCopy = std::min(count, _size);
					pEndElem = _array + _size - 1;
					for (p = this->end().base(); i < toCopy; i++, p++, _size++)
						_allocator.construct(p, *(p - toCopy));
					for (; i < count; i++, p++, _size++)
						_allocator.construct(p, *pEndElem);
				}

				 // Insert count value before pos.
				iterator	_insert(iterator pos, size_type count, const T& value)
				{
					difference_type	iteratorDistance;
					iterator		oldItEnd;

					if (count == 0)
						return (pos);
					if (_size + count > _capacity)
					{
						iteratorDistance = std::distance(this->begin(), pos);
						this->_reAlloc(_size + count);
						pos = iterator(_array + iteratorDistance);
					}
					oldItEnd = this->end();
					this->_insert_construct(count);
					std::copy_backward(pos, oldItEnd, this->end());
					std::fill_n(pos, count, value);
					return (pos);
				}

				// Private functions
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

					/* Allocating the new array in a temporary pointer.
					 * Note that we allocate before destroying the old array to be exception-safe.
					 * Indeed, if allocating fails for some reason and throw an exception, the current instance
					 * should left untouched. */

					pTemp = _allocator.allocate(reAllocSize);
					for (size_type i = 0; i < _size; i++)
					{
						/* Catching every exception that a copy constructor can throw.
						 * To avoir memory leaks in such case, each object constructed before the throw is destroyed
						 * and the memory is deallocated.
						 * The exception is then re-throw higher in the call stack. */

						try { _allocator.construct(pTemp + i, *(_array + i)); }
						catch (...)
						{
							for (size_type j = 0; j < i; j++)
								_allocator.destroy(pTemp + j);
							_allocator.deallocate(pTemp, reAllocSize);
							throw;
						}
					}
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_array + i);
					if (_array)
						_allocator.deallocate(_array, _capacity);
					_capacity = reAllocSize;
					_array = pTemp;
				}

				void	_reAllocCustom(iterator pos, size_type n, size_type count, const T& val)
				{
					T*			pTemp;
					size_type	reAllocSize;
					iterator	it;
					size_type	i;

					reAllocSize = this->_getReAllocSize(n);
					pTemp = _allocator.allocate(reAllocSize);
					for (it = this->begin(), i = 0; it != pos; it++, i++)
					{
						_allocator.construct(pTemp + i, *it.base());
					}
					for (; count; count--, i++)
						_allocator.construct(pTemp + i, val);
					for (++it; it != this->end(); it++, i++)
						_allocator.construct(pTemp + i, *it.base());

					// The array is destructed after construction of the new array if a constructor throws an exception.
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_array + i);
					if (_array)
						_allocator.deallocate(_array, _capacity);
					_capacity = reAllocSize;
					_array = pTemp;
				}

				void	_reAllocNoCopy(size_type n)
				{
					T*			pTemp;
					size_type	reAllocSize;

					reAllocSize = this->_getReAllocSize(n);
					pTemp = _allocator.allocate(reAllocSize);
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_array + i);
					if (_array)
						_allocator.deallocate(_array, _capacity);
					_capacity = reAllocSize;
					_array = pTemp;
				}

				void	_destroyAll(void)
				{
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_array + i);
					_size = 0;
				}

		};
}

#endif
