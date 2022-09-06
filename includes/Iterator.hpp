/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:20:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/06 07:29:48 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TEMPLATE_HPP
# define ITERATOR_TEMPLATE_HPP

// std::ptrdiff_t is a type that can hold any result of pointer arithmetic operation.

# include <cstddef>

namespace ft
{
	/* https://en.cppreference.com/w/cpp/iterator/iterator_tags
	 * Each iterator type must be define to be an alias to one of these tag types below.
	 * Iterator category tags carry information that can be used to select the most efficient algorithms for
	 * the specific requirement set that is implied by the category. */

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/* iterator is a pointer interface that is used to connect the STL containers
	 * with the STL algorithms library.
	 * Different types of iterator exists, such as :
	 *
	 *    - input iterator; is read-only and can only be incremented.
	 *    - output iterator; is write-only and can only be incremented.
	 *    - forward iterator; inherit from input iterator and output iterator properties (can be read and write, only incrementable).
	 *    - bidirectional iterator; inherit from forward_iterator properties, plus they can be decremented.
	 *    - random access iterator; inherit from bidirectional iterator, behave like base pointer type. */

	template <class Category,
			 class T,
			 class Distance = std::ptrdiff_t,
			 class Pointer = T*,
			 class Reference = T&>
		struct iterator
		{
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
		};

	/* const_iterators offer the same interface as iterator, but you can't modify
	 * the value of what they point to (they're read-only).
	 * The pointer is declared as const T*, allowing us to perform pointer arithmetic.
	 * Note that an iterator can be used to construct or assign a const_iterator but a const_iterator
	 * cannot be use to construct or assign an iterator. */

	template <class Category,
			 class T,
			 class Distance = std::ptrdiff_t,
			 class Pointer = const T*,
			 class Reference = const T&>
		struct const_iterator
		{
			typedef const T			value_type;
			typedef Distance		difference_type;
			typedef Pointer			pointer;
			typedef Reference		reference;
			typedef Category		iterator_category;
		};

	/* traits allow you to get information about a type during compilation.
	 * This is usefull when implementing algorithm for iterators such as std::advance,
	 * optimization can be done when manipulating different types of operator.
	 * traits are a C++ convention adopted by programmers, they're also always declared
	 * as struct. */

	template <class T>
		struct iterator_traits
		{
			typedef typename T::value_type			value_type;
			typedef typename T::pointer				pointer;
			typedef typename T::reference			reference;
			typedef typename T::difference_type		difference_type;
			typedef typename T::iterator_category	iterator_category;
		};

	/* Because a pointer isn't a user-define type and is a build-in types, partial template specialization for pointers is
	 * required to consider a pointer to be a random access iterator. */

	template <class T>
		struct iterator_traits<T*>
		{
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::ptrdiff_t					difference_type;
			typedef ft::random_access_iterator_tag	iterator_category;
		};

	template <class T>
		struct iterator_traits<const T*>
		{
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef std::ptrdiff_t					difference_type;
			typedef ft::random_access_iterator_tag	iterator_category;
		};

	/* reverse_iterator implementation. */

	template <class Iterator>
		class reverse_iterator
		{
			public:

				typedef Iterator													iterator_type;
				typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
				typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
				typedef typename ft::iterator_traits<Iterator>::reference			reference;

				// Constructors

				reverse_iterator(void) : _itr() {};
				~reverse_iterator(void) {};
				explicit reverse_iterator(iterator_type x) : _itr(x) {};
				template <class U>
					reverse_iterator(const reverse_iterator<U>& other) : _itr(other._itr) {};

				template <class U>
					reverse_iterator&	operator=(const reverse_iterator<U>& rhs)
					{
						_itr = rhs._itr;
						return (*this);
					}

				// Returns the underlying base iterator.
				iterator_type	base(void) const
				{
					return (_itr);
				}

				// Returns a reference previous to _itr.
				reference	operator*(void) const
				{
					return (*(_itr - 1));
				}

				// Returns a pointer previous to _itr.
				pointer	operator->(void) const
				{
					return (_itr - 1);
				}

				// Returns a reference to (_itr - n - 1).
				reference	operator[](difference_type n)
				{
					return (_itr[-n - 1]);
				}

				// Pre-increment by one.
				// For a reverse_iterator, it means decrementing by one the underlying iterator.
				reverse_iterator&	operator++(void)
				{
					_itr--;
					return (*this);
				}

				// Post-increment by one.
				// For a reverse_iterator, it means decrementing by one the underlying iterator.
				reverse_iterator	operator++(int)
				{
					iterator_type	it;

					it = _itr--;
					return (reverse_iterator(it));
				}

				// Pre-decrement by one.
				// For a reverse_iterator, it means incrementing by one the underlying iterator.
				reverse_iterator	operator--(void)
				{
					_itr++;
					return (*this);
				}

				// Post-decrement by one.
				// For a reverse_iterator, it means incrementing by one the underlying iterator.
				reverse_iterator	operator--(int)
				{
					iterator_type	it;

					it = _itr;
					_itr++;
					return (reverse_iterator(it));
				}

				// Returns a reverse_iterator which is advanced by n.
				reverse_iterator	operator+(difference_type n) const
				{
					return (reverse_iterator(_itr - n));
				}

				// Returns a reverse_iterator which is advanced by -n.
				reverse_iterator	operator-(difference_type n) const
				{
					return (reverse_iterator(_itr + n));
				}

				// Advance the current reverse_iterator by n.
				reverse_iterator&	operator+=(difference_type n) const
				{
					_itr -= n;
					return (*this);
				}

				// Advance the current reverse_iterator by n.
				reverse_iterator&	operator-=(difference_type n) const
				{
					_itr += n;
					return (*this);
				}

			private:
				iterator_type	_itr;
		};

	// Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.

	template <class It1, class It2>
		bool	operator==(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs)
		{
			return (lhs.base() == rhs.base);
		}

	template <class It1, class It2>
		bool	operator!=(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template <class It1, class It2>
		bool	operator<(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class It1, class It2>
		bool	operator<=(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class It1, class It2>
		bool	operator>(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class It1, class It2>
		bool	operator>=(const ft::reverse_iterator<It1>& lhs, const ft::reverse_iterator<It2>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class It>
		reverse_iterator<It>	operator+(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& it)
		{
			return (reverse_iterator<It>(it.base() - n));
		}

	template <class It>
		typename reverse_iterator<It>::difference_type	operator-(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{
			return (lhs.base() - rhs.base());
		}

	/* Iterator tags :
	 * They're empty types, used to distinguish different iterators. */

}

#endif
