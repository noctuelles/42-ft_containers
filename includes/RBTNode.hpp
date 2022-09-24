/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:11:38 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/24 18:28:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTNODE_HPP
# define RBTNODE_HPP

#include <cctype>
#include <memory>

/* This is an implementation of a Red Black Tree, which is one type of balanced
 * binary search tree, inspired by:
 *
 *      Cormen, Leiserson, Rivest, Stein : Introduction to Algorithms, 3rd Edition 
 *
 * and the gcc implementation:
 *
 *      https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.1/stl__tree_8h-source.html
 *
 * I made a lot of comments: mainly for myself. I learned a lot from reading gcc's implementation,
 * but because my C++ experience is three month long, i need to comments a lot to fix things
 * in my memory and to have a proper understanding of what i write.
 */

namespace ft
{
	enum	RBTNode_Color {black, red};

	// A node can have no value : for example the sentinel of the red-black-tree.
	struct RBTNode_Base
	{
		typedef RBTNode_Base*		base_ptr;
		typedef const RBTNode_Base*	const_base_ptr;

		RBTNode_Color	_M_color;
		base_ptr		_M_parent;
		base_ptr		_M_left;
		base_ptr		_M_right;

		// These functions are static so that they're callable from anywhere
		// without declaring any RBTNode_Base type.
		static base_ptr	minimum(base_ptr x)
		{
			while (x->_M_left != NULL)
				x = x->_M_left;
			return (x);
		}

		static const_base_ptr	minimum(const_base_ptr x)
		{
			return (minimum(const_cast<base_ptr>(x)));
		}

		static base_ptr	maximum(base_ptr x)
		{
			while (x->_M_right != NULL)
				x = x->_M_right;
			return (x);
		}

		static const_base_ptr	maximum(const_base_ptr x)
		{
			return (maximum(const_cast<base_ptr>(x)));
		}
	};

	template <class Value>
		struct RBTNode : public RBTNode_Base
		{
			typedef RBTNode*	link_type;

			Value	_M_value;
		};

	/* ############################# Node functions ############################# */

	RBTNode_Base::base_ptr			rbt_node_increment(RBTNode_Base::base_ptr x) throw();

	RBTNode_Base::const_base_ptr	rbt_node_increment(RBTNode_Base::const_base_ptr x) throw();

	RBTNode_Base::base_ptr			rbt_node_decrement(RBTNode_Base::base_ptr x) throw();

	RBTNode_Base::const_base_ptr	rbt_node_decrement(RBTNode_Base::const_base_ptr x) throw();
}

#endif
