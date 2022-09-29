/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:10:13 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/29 18:40:30 by plouvel          ###   ########.fr       */
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
			 	class Value,
				class Compare = std::less<Key>>
		class map
		{
			public :

				/* ################################ Typedefs ################################ */


				typedef Key							key_type;
				typedef Compare						key_compare;

				typedef Value						mapped_type;
				typedef ft::pair<const Key, Value>	value_type;
				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;
				typedef std::allocator<value_type>	allocator_type;

				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;

				typedef RBT<key_type, value_type, SelectFirst<value_type>, key_compare>	tree_type;

				typedef typename tree_type::iterator				iterator;
				typedef typename tree_type::const_iterator			const_iterator;
				typedef typename tree_type::reverse_iterator		reverse_iterator;
				typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

				/* ####################### Constructors & Destructor ######################## */

				explicit	map(const key_compare& comp = key_compare())
					: _M_tree(comp)
				{}

				template <class InputIt>
					map(InputIt first, InputIt last, const key_compare& comp = key_compare())
					: _M_tree(comp)
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

				const_iterator	begin() const
				{
					return (_M_tree.begin());
				}

				iterator	end()
				{
					return (_M_tree.end());
				}

				const_iterator	end() const
				{
					return (_M_tree.end());
				}

				reverse_iterator	rbegin()
				{
					return (_M_tree.rbegin());
				}

				const_reverse_iterator	rbegin() const
				{
					return (_M_tree.rbegin());
				}

				reverse_iterator	rend()
				{
					return (_M_tree.rend());
				}

				const_reverse_iterator	rend() const
				{
					return (_M_tree.rend());
				}

				ft::pair<iterator, bool>	insert(const value_type& value)
				{
					return (_M_tree.insert_unique(value));
				}

				template <class InputIt>
					void	insert(InputIt first, InputIt last)
					{
						_M_tree.insert_unique(first, last);
					}

			private:

				tree_type	_M_tree;

		};
}

#endif
