/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:10:13 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/24 18:28:16 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftl_utils.hpp"
#include "iterators.hpp"
#include "pair.hpp"
#include "RBT.hpp"
#include <cstddef>
#include <functional>
#include <memory>

#ifndef MAP_TEMPLATE_CLASS_HPP
# define MAP_TEMPLATE_CLASS_HPP

namespace ft
{
	template <class Key,
			 	class T,
				class Compare = std::less<Key>>
		class map
		{
			public :

				/* ################################ Typedefs ################################ */


				typedef Key							key_type;
				typedef Compare						key_compare;

				typedef T							mapped_type;
				typedef ft::pair<const Key, T>		value_type;
				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;
				typedef std::allocator<value_type>	allocator_type;

				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;

				typedef rbt_iterator<T>							iterator;
				typedef const_rbt_iterator<T>					const_iterator;

				typedef ft::reverse_iterator<iterator>			reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

				typedef RBT<Key, T, SelectFirst<value_type>, Compare>	tree_type;

				/* ####################### Constructors & Destructor ######################## */

				explicit	map(const key_compare& comp = key_compare())
					: _m_tree(), _m_key_compare(comp)
				{}

				template <class InputIt>
					map(InputIt first, InputIt last, const key_compare& comp = key_compare())
					: _m_tree(), _m_key_compare(comp)
				{
					(void) first;
					(void) last;
				}

				map(const map& other)
				{
					(void) other;
				}

				~map()
				{}

				iterator	begin()
				{
					return (_M_tree.begin());
				}

				reverse_iterator	rbegin()
				{
				}

			private:

				tree_type	_M_tree;

		};
}

#endif
