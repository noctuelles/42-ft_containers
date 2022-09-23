/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:11:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/23 18:15:21 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_TEMPLATE_CLASS_HPP
# define RBT_TEMPLATE_CLASS_HPP

#include "pair.hpp"
#include "iterators.hpp"
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>

namespace ft
{
	// Pour le moment, 
	template <class T, class Compare = std::less<T> >
		class RBT
		{
			private:

				struct RBTNode;

			public:

				/* ################################ Typedefs ################################ */

				typedef T							value_type;
				typedef Compare						key_compare;
				typedef RBTNode						node_type;
				typedef node_type*					node_ptr;
				typedef std::allocator<RBTNode>		allocator_type;

				/* ####################### Constructors & Destructor ######################## */

				RBT()
					: _m_allocator(), _m_cmp() ,_m_root() {}

				~RBT()
				{
					clear();
				}

				/* ######################## Public members functions ######################## */

				/* Insert a key val into the current tree.
				 * Returns false if the key already exist; otherwise returns true. */
				ft::pair<node_ptr, bool>	insert(const value_type& val = value_type())
				{
					node_ptr	x, y;

					x = _m_root;
					y = NULL;
					while (x != NULL)
					{
						y = x;
						if (_m_cmp(val, x->value))
							x = x->left;
						else if (!_m_cmp(val, x->value))
							x = x->right;
						else
							return (ft::make_pair(x, false));
					}
					if (y == NULL)
						x = _m_root = _m_allocator.allocate(1);
					else if (_m_cmp(val, y->value))
						x = y->left = _m_allocator.allocate(1);
					else
						x = y->right = _m_allocator.allocate(1);
					_m_allocator.construct(x, node_type(val));
					x->parent = y;
					return (ft::make_pair(x, true));
				}

				void	erase(const value_type& val)
				{
					node_ptr	z;

					z = _m_search(val);
					if (z)
						_m_delete_node(z);
				}

				node_ptr	getRoot() const
				{
					return (_m_root);
				}

				node_ptr	minimum()	const
				{
					return (_m_minimum(_m_root));
				}

				node_ptr	maximum() const
				{
					return (_m_maximum(_m_root));
				}

				void	print()
				{
					_m_debug_print("", _m_root, false);
				}

				void	clear()
				{
					_m_clear(_m_root);
					_m_allocator.destroy(_m_root);
					_m_allocator.deallocate(_m_root, 1);
				}

			private:

				/* ########################### Private attributes ########################### */

				allocator_type	_m_allocator;
				key_compare		_m_cmp;
				node_ptr		_m_root;

				/* ########################### Private structure ############################ */

				struct RBTNode
				{
					RBTNode(const value_type& val)
						: value(val), parent(), left(), right() {}

					enum color {black, red};

					value_type	value;
					color		color;
					node_ptr	parent;
					node_ptr	left;
					node_ptr	right;

				};

				/* ########################### Private functions ############################ */

				node_ptr	_m_minimum(node_ptr x)
				{
					while (x->left != NULL)
						x = x->left;
					return (x);
				}

				node_ptr	_m_succesor(node_ptr x)
				{
					node_ptr	y;

					if (x->right != NULL)
						return (_m_minimum(x->right));
					y = x->parent;
					while (y != NULL && x == y->right)
					{
						x = y;
						y = y->parent;
					}
					return (y);
				}

				node_ptr	_m_predecessor(node_ptr x)
				{
					node_ptr	y;

					if (x->left != NULL)
						return (_m_maximum(x->left));
					y = x->parent;
					while (y != NULL && x == y->left)
					{
						x = y;
						y = x->parent;
					}
					return (y);
				}

				/* _m_transplant replaces the subtree rooted as u by the subtree rooted as v.
				 * Thus, u's parent becomes node v's parent, and u's parent ends up having
				 * v as it's appropriate child. */
				void	_m_transplant(node_ptr u, node_ptr v)
				{
					if (u->parent == NULL)
						_m_root = v;
					else if (u == u->parent->left)
						u->parent->left = v;
					else
						u->parent->right = v;
					if (v != NULL)
						v->parent = u->parent;
				}

				/* _m_delete_node delete a given node z.
				 * z cannot be NULL. */
				void	_m_delete_node(node_ptr z)
				{
					if (z->left == NULL)
						_m_transplant(z, z->right);
					else if (z->right == NULL)
						_m_transplant(z, z->left);
					else
					{
						node_ptr	y;				/* y is z succesor. */

						y = _m_minimum(z->right);
						if (y->parent != z)
						{
							_m_transplant(y, y->right);
							y->right = z->right;
							y->right->parent = y;
						}
						_m_transplant(z, y);
						y->left = z->left;
						y->left->parent = y;
					}
					_m_allocator.destroy(z);
					_m_allocator.deallocate(z, 1);
				}

				node_ptr	_m_search(const value_type& val)
				{
					node_ptr	x;

					x = _m_root;
					while (x != NULL && x->value != val)
					{
						if (_m_cmp(val, x->value))
							x = x->left;
						else
							x = x->right;
					}
					return (x);
				}

				void	_m_clear(node_ptr x)
				{
					if (x == NULL)
						return ;
					_m_clear(x->left);
					if (x->left)
					{
						_m_allocator.destroy(x->left);
						_m_allocator.deallocate(x->left, 1);
					}
					_m_clear(x->right);
					if (x->right)
					{
						_m_allocator.destroy(x->right);
						_m_allocator.deallocate(x->right, 1);
					}
				}

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
