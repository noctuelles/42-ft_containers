/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 17:47:19 by plouvel           #+#    #+#             */
/*   Updated: 2022/10/06 16:26:00 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RBT.hpp"

namespace ft
{
	/*
	 * Usefull wikipedia gif for understanding rotations :
	 * https://upload.wikimedia.org/wikipedia/commons/3/31/Tree_rotation_animation_250x250.gif
	 */

	RBTNode_Base::base_ptr	rbt_node_increment(RBTNode_Base::base_ptr x) throw()
	{
		RBTNode_Base::base_ptr	y;

		if (x->_M_right != NULL)
			return (RBTNode_Base::minimum(x->_M_right));
		y = x->_M_parent;
		while (x == y->_M_right)
		{
			x = y;
			y = y->_M_parent;
		}
		/* Consider the following case :
		 *      H --> y
		 *      |
		 *      8 --> x
		 *     /
		 *    1
		 * Note that H is the 'header' node.
		 * x is the right child of y, because y
		 */
		if (x->_M_right == y) // in case of the root is also the rightmost node of the tree
			y = x;
		return (y);
	}

	RBTNode_Base::const_base_ptr	rbt_node_increment(RBTNode_Base::const_base_ptr x) throw()
	{
		// const_cast is never a good idea but in this case it's safe : x is safe from modification.
		// The sole purpose of using const_cast here is to avoid code duplication.
		return (rbt_node_increment(const_cast<RBTNode_Base::base_ptr>(x)));
	}

	// A predecessor of x is the node with the biggest key smaller than x.
	RBTNode_Base::base_ptr	rbt_node_decrement(RBTNode_Base::base_ptr x) throw()
	{
		RBTNode_Base::base_ptr	y;

		/* If the current node is the 'header' node and is being decremented :
		 *
		 *    -> return the rightmost node, i.e the maximum key of the tree.
		 *
		 * The 'header' node is also red : to be distinguish from the root that
		 * shares the same mutual parent relationship.
		 * The 'header' node is used as an end() iterator. */

		if (x->_M_color == red && x->_M_parent->_M_parent == x)
			return (x->_M_right);
		if (x->_M_left != NULL)
			return (RBTNode_Base::maximum(x->_M_left));
		y = x->_M_parent;
		while (x == y->_M_left)
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
			x->_M_parent->_M_right = y;
		y->_M_left = x;
		x->_M_parent = y;
	}

	void	rbt_rotate_right(RBTNode_Base* x, RBTNode_Base*& root)
	{
		RBTNode_Base*	y = x->_M_left;

		x->_M_left = y->_M_right;
		if (y->_M_right != NULL)
			y->_M_right->_M_parent = x;
		y->_M_parent = x->_M_parent;
		if (x == root)
			root = y;
		else if (x == x->_M_parent->_M_right)
			x->_M_parent->_M_right = y;
		else
			x->_M_parent->_M_left = y;
		y->_M_right = x;
		x->_M_parent = y;
	}

	/* Because we don't use a sentinel as a global NIL node (T.nil from Cormen's book),
	 * , we've to check everytime if the node exist (!= NULL) */

	static void	rbt_insert_balance(RBTNode_Base* z, RBTNode_Base*& root)
	{
		while (z != root && z->_M_parent->_M_color == red)
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
				else
				{
					if (z == z->_M_parent->_M_right)
					{
						z = z->_M_parent;
						rbt_rotate_left(z, root);
					}
					z->_M_parent->_M_color = black;
					zpp->_M_color = red;
					rbt_rotate_right(zpp, root);
				}
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
				else
				{
					if (z == z->_M_parent->_M_left)
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
				header._M_parent = x; // x is now the root of the tree.
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
		rbt_insert_balance(x, header._M_parent);
		root->_M_color = black;
	}

	/*static void	rbt_transplant(RBTNode_Base* u, RBTNode_Base* v, RBTNode_Base& header)
	{
		RBTNode_Base*&	root = header._M_parent;

		if (u->_M_parent == &header)
		{
			root = v;
			root->_M_parent = &header;
		}
		else if (u == u->_M_parent->_M_left)
			u->_M_parent->_M_left = v;
		else
			u->_M_parent->_M_right = v;
		if (v != NULL)
			v->_M_parent = u->_M_parent;
	}*/

	void	rbt_delete_node_n_balance(RBTNode_Base* z, RBTNode_Base& header)
	{
		RBTNode_Base*&	root = header._M_parent;
		RBTNode_Base*&	leftmost = header._M_left;
		RBTNode_Base*&	rightmost = header._M_right;

		RBTNode_Base*	y = z;
		RBTNode_Base*	x = NULL; // the non-null children of y
		RBTNode_Base*	x_parent = NULL;

		// y is the node to delete here
		if (y->_M_left == NULL)
			x = y->_M_right;
		else
		{
			if (y->_M_right == NULL)
				x = y->_M_left;
			else
			{
				// z has two non null children ! find the succesor
				y = RBTNode_Base::minimum(y->_M_right);
				x = y->_M_right;
			}
		}
		if (y != z) // y is different than z here : z has two non null children.
		{
			// transplant z and y
			z->_M_left->_M_parent = y;
			y->_M_left = z->_M_left;
			if (y != z->_M_right)
			{
				x_parent = y->_M_parent;
				if (x)
					x->_M_parent = y->_M_parent;
				y->_M_parent->_M_left = x;
				y->_M_right = z->_M_right;
				z->_M_right->_M_parent = y;
			}
			else
				x_parent = y;
			if (root == z)
				root = y;
			else if (z->_M_parent->_M_left == z)
				z->_M_parent->_M_left = y;
			else
				z->_M_parent->_M_right = y;
			y->_M_parent = z->_M_parent;
			std::swap(y->_M_color, z->_M_color);
			y = z;
		}
		else // if z has one or zero children. rightmost and leftmost node cannot have two children.
			 // so we update them here.
		{
			x_parent = y->_M_parent;
			if (x)
				x->_M_parent = y->_M_parent;
			if (root == z)
				root = x;
			else
			{
				if (z->_M_parent->_M_left == z)
					z->_M_parent->_M_left = x;
				else
					z->_M_parent->_M_right = x;
			}
			if (leftmost == z)
			{
				if (z->_M_right == NULL) // both left and right children NULL ! So the new leftmost is my parent.
					leftmost = z->_M_parent;
				else
					leftmost = RBTNode_Base::minimum(x); // else : find the minimum node.
			}
			if (rightmost == z)
			{
				if (z->_M_left == NULL) // same reflexion above
					rightmost = z->_M_parent;
				else
					rightmost = RBTNode_Base::maximum(x); // else, find the maximum node.
			}
		}
		// Rebalance !
		if (y->_M_color != red)
		{
			while (x != root && (x == NULL || x->_M_color == black))
			{
				if (x == x_parent->_M_left)
				{
					RBTNode_Base*	w = x_parent->_M_right;

					if (w->_M_color == red)
					{
						w->_M_color = black;
						x_parent->_M_color = red;
						rbt_rotate_left(x_parent, root);
						w = x_parent->_M_right;
					}
					if ((w->_M_left == NULL || w->_M_left->_M_color == black) && (w->_M_right == NULL || w->_M_right->_M_color == black))
					{
						w->_M_color = red;
						x = x_parent;
						x_parent = x_parent->_M_parent;
					}
					else
					{
						if (w->_M_right == NULL || w->_M_right->_M_color == black)
						{
							w->_M_left->_M_color = black;
							w->_M_color = red;
							rbt_rotate_right(w, root);
							w = x_parent->_M_right;
						}
						w->_M_color = x_parent->_M_color;
						x_parent->_M_color = black;
						if (w->_M_right)
							w->_M_right->_M_color = black;
						rbt_rotate_left(x_parent, root);
						break ; // eq x = root;
					}
				}
				else // same as above but right -> left;
				{
					RBTNode_Base*	w = x_parent->_M_left;

					if (w->_M_color == red)
					{
						w->_M_color = black;
						x_parent->_M_color = red;
						rbt_rotate_right(x_parent, root);
						w = x_parent->_M_left;
					}
					if ((w->_M_right == NULL || w->_M_right->_M_color == black) && (w->_M_left == NULL || w->_M_left->_M_color == black))
					{
						w->_M_color = red;
						x = x_parent;
						x_parent = x_parent->_M_parent;
					}
					else
					{
						if (w->_M_left == NULL || w->_M_left->_M_color == black)
						{
							w->_M_right->_M_color = black;
							w->_M_color = red;
							rbt_rotate_left(w, root);
							w = x_parent->_M_left;
						}
						w->_M_color = x_parent->_M_color;
						x_parent->_M_color = black;
						if (w->_M_left)
							w->_M_left->_M_color = black;
						rbt_rotate_right(x_parent, root);
						break ;
					}
				}
			}
			if (x)
				x->_M_color = black;
		}

		// that was my attempt : leftmost and rightmost node updating was working fine !
		/*
		if (z->_M_left == NULL) // case 1.
		{
			x = z->_M_right;

			if (z == leftmost)
			{
				if (z->_M_right != NULL)
					leftmost = z->_M_right;
				else
					leftmost = z->_M_parent;
			}
			else if (z == rightmost) // the right node had to be NULL if z is the rightmost node so...
				rightmost = z->_M_parent;

			rbt_transplant(z, z->_M_right, header);
		}
		else if (z->_M_right == NULL) // rightmost node.., left is non NULL !
		{
			x = z->_M_left;
			if (z == rightmost)
			{
				if (z->_M_left != NULL)
					rightmost = z->_M_left;
				else
					rightmost = z->_M_parent;
			}
			// cannot be the leftmost node, because it would be trigger in case 1

			rbt_transplant(z, z->_M_left, header);
		}
		else // rightmost or leftmost node cannot have
		{
			// to be continued.
			// here both are non null ! need to figure out
			RBTNode_Base*	y = RBTNode_Base::minimum(z->_M_right);
			y_org_color = y->_M_color;

			x = y->_M_right;
			if (y->_M_parent == z)
				x->_M_parent = y;
			else
			{
				rbt_transplant(y, y->_M_right, header);
				y->_M_right = z->_M_right;
				y->_M_right->_M_parent = y;
			}

			rbt_transplant(z, y, header);
			y->_M_left = z->_M_left;
			y->_M_left->_M_parent = y;
			y->_M_color = z->_M_color;
		}
		if (y_org_color == black)
			rbt_delete_balance(x, header);
			*/
	}

}
