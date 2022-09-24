/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:11:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/24 18:28:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_TEMPLATE_CLASS_HPP
# define RBT_TEMPLATE_CLASS_HPP

#include "pair.hpp"
#include "iterators.hpp"
#include "RBTNode.hpp"
#include "ftl_utils.hpp"
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>

namespace ft
{
	// KeyOfValue is a functor that finds the key for a given Value.
	template <class Key, class Value, class KeyOfValue, class KeyCompare = std::less<Value> >
		class RBT
		{
			public:

				/* ################################ Typedefs ################################ */

				typedef Key							key_type;
				typedef Value						value_type;
				typedef KeyCompare					key_compare;

				typedef RBTNode<value_type>			node_type;
				typedef node_type*					node_ptr;
				typedef const node_type*			const_node_ptr;

				typedef std::allocator<node_type>	allocator_type;

				typedef rbt_iterator<value_type>				iterator;
				typedef const_rbt_iterator<value_type>			const_iterator;
				typedef ft::reverse_iterator<iterator>			reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

				typedef value_type*			pointer;
				typedef const value_type*	const_pointer;
				typedef value_type&			reference;
				typedef const value_type&	const_reference;

				typedef size_t			size_type;
				typedef ptrdiff_t		difference_type;

			private:

				typedef RBTNode_Base::base_ptr			base_node_ptr;
				typedef RBTNode_Base::const_base_ptr	const_base_node_ptr;

				struct RBT_Base
				{
					allocator_type	_M_node_allocator;
					key_compare		_M_key_cmp;
					base_node_ptr		_M_root;
					size_type		_M_nbr_node;

					RBT_Base(const allocator_type& alloc = allocator_type(), const key_compare& comp = key_compare())
						: _M_node_allocator(alloc), _M_key_cmp(comp), _M_root(NULL), _M_nbr_node(0)
					{

					}
				};

				// Return a const_reference to a value given a node x.
				static const_reference	_S_value(const_node_ptr x)
				{
					return (x->_M_value);
				}

				// Return the key of a given node x.
				static key_type&	_S_key(const_node_ptr x)
				{
					return (KeyOfValue()(_S_value(x)));
				}

				static base_node_ptr	_S_minimum(base_node_ptr x)
				{
					return (RBTNode_Base::minimum(x));
				}

				static const_base_node_ptr	_S_minimum(const_base_node_ptr x)
				{
					return (RBTNode_Base::minimum(x));
				}

				static base_node_ptr	_S_maximum(base_node_ptr x)
				{
					return (RBTNode_Base::maximum(x));
				}

				static const_base_node_ptr	_S_maximum(const_base_node_ptr x)
				{
					return (RBTNode_Base::maximum(x));
				}

			public:

				/* ####################### Constructors & Destructor ######################## */

				RBT()
					: _M_base() {}

				RBT(const key_compare& comp)
					: _M_base(allocator_type(), comp) {}

				RBT (const key_compare& comp, const allocator_type& alloc)
					: _M_base(alloc, comp) {}

				// Copy constructor, need deep copy of the tree!
				RBT(const RBT<Key, Value, KeyOfValue, KeyCompare>& other)
					: _M_base(other._M_base._M_node_allocator, other._M_base._M_key_cmp)
				{}

				~RBT()
				{
					// Free every tree node.
				}

				/* ################################ Accesors ################################ */

				iterator	begin()
				{

				}

				const_iterator	begin() const
				{

				}

				iterator	end()
				{

				}

				reverse_iterator	rbegin()
				{
					return (reverse_iterator(end()));
				}

				const_reverse_iterator	rend()
				{
					return (reverse_iterator(begin()));
				}

				bool	empty() const
				{
					return (_M_base._M_nbr_node == 0);
				}

				/* ######################## Public members functions ######################## */

			private:

				/* ########################### Private attributes ########################### */

				RBT_Base	_M_base;

				/* ########################### Private structure ############################ */

				void	_m_debug_print(const std::string& prefix, node_ptr x, bool isLeft)
				{
					if (x != NULL)
					{
						std::cout << prefix;
						std::cout << (isLeft ? "├──" : "└──");
						std::cout << x->value << std::endl;
						_m_debug_print(prefix + (isLeft ? "│   " : "    "), x->left, true);
						_m_debug_print(prefix + (isLeft ? "│   " : "    "), x->right, false);
					}
				}

		};
}

#endif
