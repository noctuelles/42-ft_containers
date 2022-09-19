/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_new.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 10:31:31 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/19 16:44:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "type_traits.hpp"
#include "vector_base.hpp"
#include "iterators.hpp"
#include "algorithm.hpp"
#include "print.hpp"
#include <algorithm>
#include <exception>
#include <iterator>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace ft
{
	template <class T>
		class vector : private vector_base<T>
		{
			public:

				class	iterator;
				class	const_iterator;

				/* ################################ Typedefs ################################ */

				typedef T											value_type;
				typedef std::allocator<value_type>					allocator_type;

				typedef value_type&									reference;
				typedef const value_type&							const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;

				typedef std::size_t									size_type;
				typedef	std::ptrdiff_t								difference_type;

				typedef ft::reverse_iterator<iterator>				reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

				/* ############################### Iterators ################################ */

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

						pointer base(void)
						{
							return (_ptr);
						}

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

				/* ####################### Constructors & Destructor ######################## */


				vector()
					: vector_base<T>(0)
				{
					std::cout << "Vector default constructor\n";
				}

				explicit vector(size_type n, const T& val = T())
					: vector_base<T>(n)
				{
					std::uninitialized_fill(this->_begin, this->_begin + n, val);
				}

				template <class InputIt>
					vector(InputIt first, InputIt last,
							typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
						: vector_base<T>(std::distance(first, last))
					{
						std::uninitialized_copy(first, last, this->_begin);
					}

				~vector()
				{
					clear();
				}

				vector(const vector& x)
					: vector_base<T>(x.size())
				{
					std::uninitialized_copy(x.begin(), x.end(), this->_begin);
				}

				/* ############################## Assignation ############################### */

				// Note that this copy-assignmenet operator offer basic exception guarantee.
				// If the copy assignment of T (T::operator=() ) throws an exception,
				// the current instance is already modified by previous assignment made.
				vector&	operator=(const vector& rhs)
				{
					size_type	mySize;
					size_type	rhsSize;

					if (this != &rhs)
					{
						// If the current capacity is lower than the size of the rhs vector,
						// We perform a deep copy and reallocation.
						if (capacity() < rhs.size())
						{
							vector	tmp(rhs);
							this->swap(tmp);
							return (*this);
						}

						mySize = size();
						rhsSize = rhs.size();

						// If the vector we want to copy have equals size of less.
						// We copy every elements of the rhs vector into ours, and then destruct
						// the unneccesary elements.
						if (rhsSize <= mySize)
						{
							std::copy(rhs.begin(), rhs.end(), this->_begin);
							for (pointer p = this->_begin + rhsSize; p != this->_last; p++)
								this->_allocator.destroy(p);
						}
						else
						{
							std::copy(rhs.begin(), rhs.begin() + mySize, this-> _begin);
							std::uninitialized_copy(rhs.begin() + mySize, rhs.end(), this->_last);
						}
						this->_last = this->_begin + rhsSize;
					}
					return (*this);
				}

				void	assign(size_type count, const T& value)
				{
					if (capacity() < count)
					{
						vector	tmp(count, value);
						this->swap(tmp);
					}
					else
					{
						if (count <= size())
						{
							std::fill_n(this->_begin, count, value);
							for (pointer p = this->_begin + count; p != this->_last; p++)
								this->_allocator.destroy(p);
						}
						else
						{
							std::fill(this->_begin, this->_last, value);
							std::uninitialized_fill(this->_last, this->_begin + count, value);
						}
						this->_last = this->_begin + count;
					}
				}

				template <class InputIt>
					typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
					assign(InputIt first, InputIt last)
					{
						_assign_range(first, last, typename ft::iterator_traits<InputIt>::iterator_category());
					}

				/* ############################# Element Access ############################# */

				reference	at(size_type pos)
				{
					return (const_cast<reference>(
								static_cast<const vector&>(*this).at(pos)
								));
				}

				const_reference	at(size_type pos) const
				{
					if (pos >= size())
						throw(std::out_of_range("vector::at"));
					return (this->_begin[pos]);
				}

				reference	operator[](size_type pos)
				{
					return (this->_begin[pos]);
				}

				const_reference	operator[](size_type pos) const
				{
					return (this->_begin[pos]);
				}

				reference	front()
				{
					return (*this->_begin);
				}

				const_reference	front() const
				{
					return (*this->_begin);
				}

				reference	back()
				{
					return (*(this->_last - 1));
				}

				const_reference	back() const
				{
					return (*(this->_last - 1));
				}

				pointer	data()
				{
					return (this->_begin);
				}

				const_pointer	data() const
				{
					return (this->_begin);
				}

				/* ########################## Iterators operations ########################## */

				iterator	begin()
				{
					return (iterator(this->_begin));
				}

				const_iterator	begin() const
				{
					return (const_iterator(this->_begin));
				}

				iterator	end()
				{
					return (iterator(this->_last));
				}

				const_iterator	end() const
				{
					return (const_iterator(this->_last));
				}

				reverse_iterator	rbegin()
				{
					return (reverse_iterator(this->_last));
				}

				const_reverse_iterator	rbegin() const
				{
					return (reverse_iterator(this->_last));
				}

				reverse_iterator	rend()
				{
					return (reverse_iterator(this->_begin));
				}

				const_reverse_iterator	rend() const
				{
					return (reverse_iterator(this->_begin));
				}

				/* ################################ Capacity ################################ */

				bool	empty() const
				{
					return (this->_begin == this->_last);
				}

				size_type	size() const
				{
					return (this->_last - this->_begin);
				}

				size_type	max_size() const
				{
					return (this->_allocator.max_size());
				}

				void	reserve(size_type n)
				{
					if (n > max_size())
						throw (std::length_error("vector::reserve"));
					if (n > capacity())
					{
						vector_base<T>	tmp(n);

						tmp._last = std::uninitialized_copy(this->_begin, this->_last, tmp._begin);
						this->_destroy_elements();
						ft::swap(*this, tmp);
					}
				}

				size_type	capacity() const
				{
					return (this->_end - this->_begin);
				}

				/* ############################### Modifiers ################################ */

				void	clear()
				{
					this->_destroy_elements();
					this->_last = this->_begin;
				}

				void	push_back(const T& value)
				{
					if (this->_last == this->_end)
						reserve(this->size() ? this->size() * 2 : 1);
					this->_allocator.construct(this->_last, value);
					this->_last++;
				}

				void	insert(iterator pos, const T& value)
				{
					return (insert(pos, 1, value));
				}

				void	insert(iterator pos, size_type count, const T& value)
				{
					if (size() + count > capacity())
					{
						vector	tmp;

						tmp.reserve(size() + count);
						tmp._last = std::uninitialized_copy(this->_begin, pos.base(), tmp._begin);
						tmp._last = std::uninitialized_fill_n(tmp._last, count, value);
						tmp._last = std::uninitialized_copy(pos.base(), this->_last, tmp._last);
						swap(tmp);
					}
					else
					{
						pointer	p = this->_last;

						// Because the vector capacity is big enough, resize just appends default-constructed T().
						resize(size() + count);
						std::copy_backward(pos.base(), p, this->_last);
						std::fill_n(pos.base(), count, value);
					}
				}

				template <class InputIt>
					typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
					insert(iterator pos, InputIt first, InputIt last)
					{
						_insert_range(pos, first, last,
								typename ft::iterator_traits<InputIt>::iterator_category());
					}

				iterator	erase(iterator pos)
				{
					return (erase(pos, pos + 1));
				}

				iterator	erase(iterator first, iterator last)
				{
					difference_type	iteratorDistance;

					iteratorDistance = std::distance(first, last);
					if (iteratorDistance <= 0)
						return (last);
					for (iterator it = std::copy(first + iteratorDistance, this->end(), first); it != this->end(); it++)
						this->_allocator.destroy(it.base());
					this->_last -= iteratorDistance;
					return (first);
				}

				void	pop_back()
				{
					this->_allocator.destroy(--this->_last);
				}

				void	resize(size_type count, T value = T())
				{
					if (count <= size())
					{
						for (pointer p = this->_begin + count; p != this->_last; p++)
							this->_allocator.destroy(p);
					}
					else
					{
						reserve(count);
						std::uninitialized_fill(this->_last, this->_begin + count, value);
					}
					this->_last = this->_begin + count;
				}

				void	swap(vector& other)
				{
					ft::swap(*this, other);
				}

				/* ################################## Misc ################################## */

				allocator_type	get_allocator() const
				{
					return (this->_allocator);
				}

			private:

				/* ######################### Insert tag dispatching ######################### */

				/* Because input iterator impose single-pass algorithm, we can't determine the distance
							vector	tmp;
				 * between first and last using std::distance for example. */
				template <class InputIt>
					void _insert_range(iterator pos, InputIt first, InputIt last, std::input_iterator_tag)
					{
						vector	tmp;

						tmp.reserve(this->_last - pos.base());
						tmp._last = std::uninitialized_copy(pos.base(), this->_last, tmp._begin);
						for (pointer p = pos.base(); p != this->_last; p++)
							this->_allocator.destroy(p);
						this->_last = pos.base();
						for ( ; first != last; first++)
							push_back(*first);
						reserve(size() + tmp.size());
						this->_last = std::uninitialized_copy(tmp.begin(), tmp.end(), this->_last);
					}

				template <class ForwardIt>
					void _insert_range(iterator pos, ForwardIt first, ForwardIt last, std::forward_iterator_tag)
					{
						size_type	count;

						count = std::distance(first, last);
						if (size() + count > capacity())
						{
							vector	tmp;

							tmp.reserve(size() + count);
							tmp._last = std::uninitialized_copy(this->_begin, pos.base(), tmp._begin);
							tmp._last = std::uninitialized_copy(first, last, tmp._last);
							tmp._last = std::uninitialized_copy(pos.base(), this->_last, tmp._last);
							swap(tmp);
						}
						else
						{
							pointer	p = this->_last;

							resize(size() + count);
							std::copy_backward(pos.base(), p, this->_last);
							std::copy(first, last, pos.base());
						}
					}

				/* ######################### Assign tag dispatching ######################### */

				template <class InputIt>
					void	_assign_range(InputIt first, InputIt last, std::input_iterator_tag)
					{
						vector	tmp;

						for ( ; first != last; first++)
							tmp.push_back(*first);
						swap(tmp);
					}

				template <class ForwardIt>
					void	_assign_range(ForwardIt first, ForwardIt last, std::forward_iterator_tag)
					{
						size_type	count;

						count = std::distance(first, last);
						if (count <= size())
						{
							for (pointer p = std::copy(first, last, this->_begin); p != this->_last; p++)
								this->_allocator.destroy(p);
						}
						else
						{
							resize(count);
							std::copy(first, last, this->_begin);
						}
						this->_last = this->_begin + count;
					}

				void _destroy_elements()
				{
					for (pointer p = this->_begin; p != this->_last; p++)
						this->_allocator.destroy(p);
				}
		};

	template <class T>
		bool	operator==(const ft::vector<T>& lhs, const ft::vector<T>& rhs)
		{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template <class T>
		bool	operator!=(const ft::vector<T>& lhs, const ft::vector<T>& rhs)
		{
			return (!(lhs == rhs));
		}
}
#endif