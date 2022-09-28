/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:47:19 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/28 18:21:54 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBT.hpp"

namespace ft
{
	/*
	 * Usefull wikipedia gif for understanding rotations :
	 * https://upload.wikimedia.org/wikipedia/commons/3/31/Tree_rotation_animation_250x250.gif
	 */

	void	rbt_rotate_left(RBTNode_Base* x, RBTNode_Base*& root)
	{
		RBTNode_Base*	y = x->_M_right;

		x->_M_right = y->_M_left;
		if (y->_M_left != NULL)
			y->_M_left->_M_parent = x;
		y->_M_parent = x->_M_parent;
		if (x == root)
			root = y;
		else if (x == x->_M_parent->_M_left)
			x->_M_parent->_M_left = y;
		else
			x->_M_parent->_M_right = x;
		y->_M_left = x;
		x->_M_parent = y;
	}

	void	rbt_rotate_right(RBTNode_Base* y, RBTNode_Base*& root)
	{
		RBTNode_Base*	x = y->_M_left;

		y->_M_left = x->_M_right;
		if (x->_M_right != NULL)
			x->_M_right->_M_parent = y;
		x->_M_parent = y->_M_parent;
		if (y == root)
			root = x;
		else if (y == y->_M_parent->_M_left)
			y->_M_parent->_M_left = x;
		else
			y->_M_parent->_M_right = x;
		x->_M_right = y;
		y->_M_parent = x;
	}

	/* Because we don't use a sentinel as a global NIL node (T.nil from Cormen's book),
	 * , we've to check everytime if the node exist (!= NULL) */

	void	rbt_insert_balance(RBTNode_Base* z, RBTNode_Base*& root)
	{
		while (z->_M_parent->_M_color == red)
		{
			RBTNode_Base* const zpp = z->_M_parent->_M_parent;

			if (z->_M_parent == zpp->_M_left)
			{
				RBTNode_Base* y = zpp->_M_right;

				if (y && y->_M_color == red)
				{
					z->_M_parent->_M_color = black;
					y->_M_color = black;
					zpp->_M_color = red;
					z = zpp;
				}
				else if (z == z->_M_parent->_M_right)
				{
					z = z->_M_parent;
					rbt_rotate_left(z, root);
				}
				z->_M_parent->_M_color = black;
				zpp->_M_color = red;
				rbt_rotate_right(zpp, root);
			}
			else
			{
				RBTNode_Base* y = zpp->_M_left;

				if (y && y->_M_color == red)
				{
					z->_M_parent->_M_color = black;
					y->_M_color = black;
					zpp->_M_color = red;
					z = zpp;
				}
				else if (z == z->_M_parent->_M_left)
				{
					z = z->_M_parent;
					rbt_rotate_right(z, root);
				}
				z->_M_parent->_M_color = black;
				zpp->_M_color = red;
				rbt_rotate_left(zpp, root);
			}
		}
	}

	/*
	 * rbt_insert insert a node x, where p is the parent of x.
	 * A reference to header is used to update the leftmost and rightmost
	 * tree.
	 */
	void	rbt_insert_n_balance(const bool insert_left,
						RBTNode_Base* x,
						RBTNode_Base* p,
						RBTNode_Base& header)
	{
		RBTNode_Base*&	root = header._M_parent;

		x->_M_parent = p;
		x->_M_left = NULL;
		x->_M_right = NULL;
		x->_M_color = red;

		// the first node is always inserted left.
		if (insert_left)
		{
			p->_M_left = x;
			if (p == &header) // the tree is empty
			{
				root = x; // the root of the tree.
				header._M_right = x;
			}
			else if (p == header._M_left)
				header._M_left = x;
		}
		else
		{
			p->_M_right = x;
			if (p == header._M_right)
				header._M_right = x;
		}
		if (x != root)
			rbt_insert_balance(x, header._M_parent);
		root->_M_color = black;
	}
}
