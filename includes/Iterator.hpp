/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:20:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/08/25 20:10:58 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TEMPLATE_HPP
# define ITERATOR_TEMPLATE_HPP

# include <cstddef>

namespace ft
{
	/*
	 *	value_type : type of elements pointed by the iterator.
	 */

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

	template <class T>
	struct iterator_traits
	{
		typedef typename T::value_type			value_type;
		typedef typename T::difference_type		difference_type;
		typedef typename T::pointer				pointer;
		typedef typename T::iterator_category	iterator_category;
	};

	/* Iterator tags :
	 * They're empty types, used to distinguish different iterators. */

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
}

#endif
