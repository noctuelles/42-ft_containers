/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:47:19 by plouvel           #+#    #+#             */
/*   Updated: 2022/10/03 11:47:57 by plouvel          ###   ########.fr       */
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
				root = x; // x is now the root of the tree.
				header._M_right = x;
			}
			else if (p == header._M_left) // if the parent is the leftmost node
				header._M_left = x;
		}
		else
		{
			p->_M_right = x;
			if (p == header._M_right) // if the parent is the rightmost node
				header._M_right = x;
		}
		//if (x != root)
		//	rbt_insert_balance(x, header._M_parent);
		root->_M_color = black;
	}

	static void	rbt_transplant(RBTNode_Base* u, RBTNode_Base* v, RBTNode_Base& header)
	{
		RBTNode_Base*&	root = header._M_parent;

		if (u->_M_parent == &header)
			root = v;
		else if (u == u->_M_parent->_M_left)
			u->_M_parent->_M_left = v;
		else
			u->_M_parent->_M_right = v;
		if (v != NULL)
			v->_M_parent = u->_M_parent;
	}

	void	rbt_delete_node(RBTNode_Base* z, RBTNode_Base& header)
	{
		if (z->_M_left == NULL)
		{
			rbt_transplant(z, z->_M_right, header);
			if (z == header._M_left)
			{
				if (z->_M_right)
				{
					if (z->_M_right->_M_left)
						header._M_left = RBTNode_Base::minimum(z->_M_right->_M_left);
					else
						header._M_left = z->_M_right;
				}
				else
					header._M_left = z->_M_parent;
			}
		}
		else if (z->_M_right == NULL) // rightmost node..
		{
			rbt_transplant(z, z->_M_left, header);
			if (z == header._M_right)
			{
				if (z->_M_left)
				{
					if (z->_M_left->_M_right)
						header._M_right = RBTNode_Base::maximum(z->_M_left->_M_right);
					else
						header._M_right = z->_M_left;
				}
				else
					header._M_right = z->_M_parent;
			}
		}
		else // rightmost or leftmost node cannot have
		{
			RBTNode_Base*	y = RBTNode_Base::minimum(z->_M_right);

			if (y->_M_parent != z)
			{
				rbt_transplant(y, y->_M_right, header);
				y->_M_right = z->_M_right;
				y->_M_right->_M_parent = y;
			}
			rbt_transplant(z, y, header);
			y->_M_left = z->_M_left;
			y->_M_left->_M_parent = y;
		}
		if (header._M_parent == NULL)
			header._M_left = &header, header._M_right = &header;
	}
}
