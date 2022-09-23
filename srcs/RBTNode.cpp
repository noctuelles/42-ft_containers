/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTNode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:38:27 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/23 20:21:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBTNode.hpp"

/* ####################### RBTNode related functions ######################## */

// Cormen, Leiserson, Rivest, Stein : Introduction to Algorithms, 3rd Edition - page 286.

namespace ft
{
	// "Incrementing a node" does not have any sense outside the iterator semantic.
	// It can be seen as "finding the succesor of x".
	// A succesor is of x is the node with the smallest key greater than x.
	RBTNode_Base::base_ptr	rbt_node_increment(RBTNode_Base::base_ptr x) throw()
	{
		RBTNode_Base::base_ptr	y;

		if (x->_M_right != NULL)
			return (RBTNode_Base::minimum(x->_M_right));
		y = x->_M_parent;
		while (y != NULL && x == y->_M_right)
		{
			x = y;
			y = y->_M_parent; // or x->_M_parent
		}
		return (y);
	}

	RBTNode_Base::const_base_ptr	rbt_node_increment(RBTNode_Base::const_base_ptr x) throw()
	{
		// const_cast is never a good idea but in this case it's safe : x is safe from modification.
		// The sole purpose of const_cast here is to avoid code duplication.
		return (rbt_node_increment(const_cast<RBTNode_Base::base_ptr>(x)));
	}

	// A predecessor of x is the node with the biggest key smaller than x.
	RBTNode_Base::base_ptr	rbt_node_decrement(RBTNode_Base::base_ptr x) throw()
	{
		RBTNode_Base::base_ptr	y;

		if (x->_M_left != NULL)
			return (RBTNode_Base::maximum(x->_M_right));
		y = x->_M_parent;
		while (y != NULL && x == y->_M_left)
		{
			x = y;
			y = y->_M_parent;
		}
		return (y);
	}

	RBTNode_Base::const_base_ptr	rbt_node_decrement(RBTNode_Base::const_base_ptr x) throw()
	{
		return (rbt_node_decrement(const_cast<RBTNode_Base::base_ptr>(x)));
	}
}
