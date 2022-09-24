/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:20:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/24 18:28:18 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TEMPLATE_HPP
# define ITERATOR_TEMPLATE_HPP

// std::ptrdiff_t is a type that can hold any result of pointer arithmetic operation.

#include "RBTNode.hpp"
# include <iterator>
# include <cstddef>
# include <iostream>

namespace ft
{
	/* https://en.cppreference.com/w/cpp/iterator/iterator_tags
	 * Each iterator type must be define to be an alias to one of these tag types below.
	 * Iterator category tags carry information that can be used to select the most efficient algorithms for
	 * the specific requirement set that is implied by the category.
	 * Notes that for ft_container, it is not mandatory to define them. */

	/*struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};*/

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

	template <class Category,
			 class T,
			 class Distance = std::ptrdiff_t,
			 class Pointer = const T*,
			 class Reference = const T&>
		struct const_iterator
		{
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
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
			typedef std::random_access_iterator_tag	iterator_category;
		};

	template <class T>
		struct iterator_traits<const T*>
		{
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef std::ptrdiff_t					difference_type;
			typedef std::random_access_iterator_tag	iterator_category;
		};

	template <class Iterator>
		class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
												typename iterator_traits<Iterator>::value_type,
												typename iterator_traits<Iterator>::difference_type,
												typename iterator_traits<Iterator>::pointer,
												typename iterator_traits<Iterator>::reference>
		{
			public:

				typedef Iterator												iterator_type;
				typedef typename iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename iterator_traits<Iterator>::pointer				pointer;
				typedef typename iterator_traits<Iterator>::reference			reference;

				// Constructors

				reverse_iterator(void) : _itr() {};
				explicit reverse_iterator(iterator_type x) : _itr(x) {};
				reverse_iterator(const reverse_iterator& other)
					: _itr(other._itr)
				{}
				~reverse_iterator(void) {};

				template <class U>
					reverse_iterator(const reverse_iterator<U>& other) : _itr(other.base()) {};

				template <class U>
					reverse_iterator&	operator=(const reverse_iterator<U>& rhs)
					{
						_itr = rhs.base();
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
					Iterator	tmp;

					tmp = _itr;
					return (*--tmp);
				}

				// Returns a pointer previous to _itr.
				pointer	operator->(void) const
				{
					return (&operator*());
				}

				// Returns a reference to (_itr - n - 1).
				reference	operator[](difference_type n) const
				{
					return (*(*this + n));
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
					return (reverse_iterator(_itr--));
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
					return (reverse_iterator(_itr++));
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
				reverse_iterator&	operator+=(difference_type n)
				{
					_itr -= n;
					return (*this);
				}

				// Advance the current reverse_iterator by n.
				reverse_iterator&	operator-=(difference_type n)
				{
					_itr += n;
					return (*this);
				}

			protected:

				iterator_type	_itr;
		};

	// Compares the underlying iterators. Inverse comparisons are applied in order to take into account that the iterator order is reversed.

	template <class It>
		inline bool	operator==(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class It>
		inline bool	operator!=(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{
			return !(lhs == rhs);
		}

	template <class It>
		inline bool	operator<(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class It>
		inline bool	operator<=(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class It>
		inline bool	operator>(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class It>
		inline bool	operator>=(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class It>
		inline typename reverse_iterator<It>::difference_type
		operator-(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
		{
			return (rhs.base() - lhs.base());
		}

	template <class It>
		inline reverse_iterator<It>
		operator+(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& rhs)
		{
			return (reverse_iterator<It>(rhs.base() - n));
		}

	/* Comparaison of reverse_iterator to const reverse_iterator */

	template <class ItLeft, class ItRight>
		bool	operator==(const ft::reverse_iterator<ItLeft>& lhs, const ft::reverse_iterator<ItRight>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class ItLeft, class ItRight>
		bool	operator!=(const ft::reverse_iterator<ItLeft>& lhs, const ft::reverse_iterator<ItRight>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template <class ItLeft, class ItRight>
		bool	operator<(const ft::reverse_iterator<ItLeft>& lhs, const ft::reverse_iterator<ItRight>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class ItLeft, class ItRight>
		bool	operator<=(const ft::reverse_iterator<ItLeft>& lhs, const ft::reverse_iterator<ItRight>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class ItLeft, class ItRight>
		bool	operator>(const ft::reverse_iterator<ItLeft>& lhs, const ft::reverse_iterator<ItRight>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class ItLeft, class ItRight>
		bool	operator>=(const ft::reverse_iterator<ItLeft>& lhs, const ft::reverse_iterator<ItRight>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class ItLeft, class ItRight>
		inline typename reverse_iterator<ItLeft>::difference_type
		operator-(const reverse_iterator<ItLeft>& lhs, const reverse_iterator<ItRight>& rhs)
		{
			return (rhs.base() - lhs.base());
		}

	template <class ItLeft, class ItRight>
		inline reverse_iterator<ItLeft>
		operator+(typename reverse_iterator<ItLeft>::difference_type n, const reverse_iterator<ItRight>& rhs)
		{
			return (reverse_iterator<ItLeft>(rhs.base() - n));
		}

	template <class It>
		class normal_iterator
		{
			public:

				typedef typename iterator_traits<It>::value_type		value_type;
				typedef typename iterator_traits<It>::pointer			pointer;
				typedef typename iterator_traits<It>::reference			reference;
				typedef typename iterator_traits<It>::difference_type	difference_type;
				typedef typename iterator_traits<It>::iterator_category	iterator_category;

				normal_iterator()
					: _curr(It()) {}
				normal_iterator(const It& it)
					: _curr(it) {}
				~normal_iterator() {}

				template <class Iter>
					normal_iterator(const normal_iterator<Iter>& other)
					:_curr(other.base()) {}

				reference	operator*() const
				{
					return (*_curr);
				}

				pointer	operator->() const
				{
					return (_curr);
				}

				normal_iterator&	operator++()
				{
					++_curr;
					return (*this);
				}

				normal_iterator	operator++(int)
				{
					return (normal_iterator(_curr++));
				}

				// Bidirectionnal iterator requirements

				normal_iterator&	operator--()
				{
					--_curr;
					return (*this);
				}

				normal_iterator	operator--(int)
				{
					return (normal_iterator(_curr--));
				}

				// Random access iterator requirements

				reference	operator[](difference_type n)
				{
					return (_curr[n]);
				}

				normal_iterator&	operator+=(difference_type n)
				{
					_curr += n;
					return (*this);
				}

				normal_iterator	operator+(difference_type n) const
				{
					return (normal_iterator(_curr + n));
				}

				normal_iterator&	operator-=(difference_type n)
				{
					_curr -= n;
					return (*this);
				}

				normal_iterator	operator-(difference_type n) const
				{
					return (normal_iterator(_curr - n));
				}

				const It&	base() const
				{
					return (_curr);
				}

			protected:

				It	_curr;
		};

	template <class ItLeft, class ItRight>
		inline bool	operator==(const normal_iterator<ItLeft>& lhs, const normal_iterator<ItRight>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class ItLeft, class ItRight>
		inline bool	operator!=(const normal_iterator<ItLeft>& lhs, const normal_iterator<ItRight>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template <class ItLeft, class ItRight>
		inline bool	operator<(const normal_iterator<ItLeft>& lhs, const normal_iterator<ItRight>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class ItLeft, class ItRight>
		inline bool	operator<=(const normal_iterator<ItLeft>& lhs, const normal_iterator<ItRight>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class ItLeft, class ItRight>
		inline bool	operator>(const normal_iterator<ItLeft>& lhs, const normal_iterator<ItRight>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class ItLeft, class ItRight>
		inline bool	operator>=(const normal_iterator<ItLeft>& lhs, const normal_iterator<ItRight>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class ItLeft, class ItRight>
		inline typename normal_iterator<ItLeft>::difference_type
		operator-(const normal_iterator<ItLeft>& lhs, const normal_iterator<ItRight>& rhs)
		{
			return (lhs.base() - rhs.base());
		}

	template <class It>
		inline bool	operator==(const normal_iterator<It>& lhs, const normal_iterator<It>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class It>
		inline bool	operator!=(const normal_iterator<It>& lhs, const normal_iterator<It>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template <class It>
		inline bool	operator<(const normal_iterator<It>& lhs, const normal_iterator<It>& rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class It>
		inline bool	operator<=(const normal_iterator<It>& lhs, const normal_iterator<It>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class It>
		inline bool	operator>(const normal_iterator<It>& lhs, const normal_iterator<It>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class It>
		inline bool	operator>=(const normal_iterator<It>& lhs, const normal_iterator<It>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class It>
		inline typename normal_iterator<It>::difference_type
		operator-(const normal_iterator<It>& lhs, const normal_iterator<It>& rhs)
		{
			return (lhs.base() - rhs.base());
		}

	template <class It>
		inline normal_iterator<It>
		operator+(typename normal_iterator<It>::difference_type lhs, const normal_iterator<It>& rhs)
		{
			return (normal_iterator<It>(rhs.base() + lhs));
		}

	/* reverse_iterator implementation. */

	// Unfortunatly, we can't avoid code duplication for non-const and const iterator.
	template <class T>
		class rbt_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
		{
			public:

				typedef typename iterator_traits<T>::value_type			value_type;
				typedef typename iterator_traits<T>::pointer			pointer;
				typedef typename iterator_traits<T>::reference			reference;

				typedef RBTNode_Base::base_ptr		base_ptr;
				typedef RBTNode<T>*					link_type;

				rbt_iterator()
					: _M_node() {}
				explicit rbt_iterator(link_type node)
					: _M_node(node) {}
				~rbt_iterator();

				reference	operator*()
				{
					return (static_cast<link_type>(_M_node)->_M_value);
				}

				pointer	operator->()
				{
					return(&operator*());
				}

				rbt_iterator&	operator++()
				{
					_M_node = rbt_node_increment(_M_node);
					return (*this);
				}

				rbt_iterator	operator++(int)
				{
					rbt_iterator	tmp;

					tmp = *this;
					_M_node = rbt_node_increment(_M_node);
					return (tmp);
				}

				rbt_iterator&	operator--()
				{
					_M_node = rbt_node_decrement(_M_node);
					return (*this);
				}

				rbt_iterator	operator--(int)
				{
					rbt_iterator	tmp;

					tmp = *this;
					_M_node = rbt_node_decrement(_M_node);
					return (tmp);
				}

				bool	operator==(const rbt_iterator& rhs) const
				{
					return (_M_node == rhs._M_node);
				}

				bool	operator!=(const rbt_iterator& rhs) const
				{
					return (_M_node != rhs._M_node);
				}

			private:

				base_ptr	_M_node;
		};

	template <class T>
		class const_rbt_iterator : public ft::const_iterator<std::bidirectional_iterator_tag, T>
		{
			public:

				typedef typename iterator_traits<T>::value_type			value_type;
				typedef typename iterator_traits<T>::pointer			pointer;
				typedef typename iterator_traits<T>::reference			reference;

				typedef RBTNode_Base::const_base_ptr	base_ptr;
				typedef const RBTNode<T>*				link_type;

				const_rbt_iterator()
					: _M_node() {}
				explicit const_rbt_iterator(link_type node)
					: _M_node(node) {}
				// non const_iterator is able to be "promoted" to a const_iterator
				const_rbt_iterator(const rbt_iterator<T>& it)
					: _M_node(it._M_node) {}
				~const_rbt_iterator();

				reference	operator*()
				{
					return (static_cast<link_type>(_M_node)->_M_value);
				}

				pointer	operator->()
				{
					return(&operator*());
				}

				const_rbt_iterator&	operator++()
				{
					_M_node = rbt_node_increment(_M_node);
					return (*this);
				}

				const_rbt_iterator	operator++(int)
				{
					const_rbt_iterator	tmp;

					tmp = *this;
					_M_node = rbt_node_increment(_M_node);
					return (tmp);
				}

				const_rbt_iterator&	operator--()
				{
					_M_node = rbt_node_decrement(_M_node);
					return (*this);
				}

				const_rbt_iterator	operator--(int)
				{
					const_rbt_iterator	tmp;

					tmp = *this;
					_M_node = rbt_node_decrement(_M_node);
					return (tmp);
				}

				bool	operator==(const const_rbt_iterator& rhs) const
				{
					return (_M_node == rhs._M_node);
				}

				bool	operator!=(const const_rbt_iterator& rhs) const
				{
					return (_M_node != rhs._M_node);
				}

			private:

				base_ptr	_M_node;
		};

	template <class U>
		inline bool	operator==(const rbt_iterator<U>& lhs, const const_rbt_iterator<U>& rhs)
		{
			return (lhs._M_node == rhs._M_node);
		}
	template <class U>
		inline bool	operator!=(const rbt_iterator<U>& lhs, const const_rbt_iterator<U>& rhs)
		{
			return (lhs._M_node != rhs._M_node);
		}
}

#endif
