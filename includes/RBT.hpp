/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:11:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/22 17:31:54 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_TEMPLATE_CLASS_HPP
# define RBT_TEMPLATE_CLASS_HPP

#include <functional>
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

				class bst_iterator
				{
					public:

					private:
						node_ptr	_m_current;
				};

				/* ######################## Public members functions ######################## */

				void	insert(const value_type& val = value_type())
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
							return ;
					}
					if (y == NULL)
						x = _m_root = _m_allocator.allocate(1);
					else if (_m_cmp(val, y->value))
						x = y->left = _m_allocator.allocate(1);
					else
						x = y->right = _m_allocator.allocate(1);
					_m_allocator.construct(x, node_type(val));
					x->parent = y;
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

					value_type	value;
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
						y = x->parent;
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

		};
}

#endif
