/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:11:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/29 18:47:58 by plouvel          ###   ########.fr       */
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
				void	rbt_insert_n_balance(const bool insert_left,
									RBTNode_Base* x,
									RBTNode_Base* p,
									RBTNode_Base& header);

	/* Red Black Tree implementation, based on libstdc++ implementation, and Introduction to Algorithm
	 * Note that the code concerning the RBT implemtation is hugely commented : this is not a good practice,
	 * but this project being a pure exercice it holds a potentially big educational potential.
	 */
	template <class Key, class Value, class KeyOfValue, class KeyCompare = std::less<Value> >
		class RBT
		{
			public:

				/* ################################ Typedefs ################################ */

				typedef Key							key_type;
				typedef Value						value_type;
				typedef KeyCompare					key_compare;

				typedef RBTNode<value_type>			node_type;
				typedef RBTNode<value_type>*		node_ptr;
				typedef const RBTNode<value_type>*	const_node_ptr;

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
					public:

						/*
						 * The header contains information about the current tree (like a header document that
						 * contains informations about the document...) :
						 *
						 *     -> the root node : _M_parent.
						 *     -> the leftmost node of the tree : _M_left.
						 *     -> the rightmost node of the tree : _M_right.
						 *
						 * Note that the root also has the header as a parent. Thus :
						 *
						 *     _M_header._M_parent == root && root->_M_parent == &header.
						 */

						allocator_type	_M_node_allocator;
						key_compare		_M_key_cmp;
						RBTNode_Base	_M_header;
						size_type		_M_nbr_node;

						RBT_Base(const allocator_type& alloc = allocator_type(), const key_compare& comp = key_compare())
							: _M_node_allocator(alloc), _M_key_cmp(comp), _M_header(), _M_nbr_node()
						{
							_M_header._M_color = red;
							_M_header._M_left = &_M_header;
							_M_header._M_right = &_M_header;
						}
				};

				// Return a const_reference to a value given a node x.
				static const Value&	_S_value(const_node_ptr x)
				{
					return (x->_M_value);
				}

				static const Value&	_S_value(const_base_node_ptr x)
				{
					return (static_cast<const_node_ptr>(x)->_M_value);
				}

				// Return the key of a given node x.
				static const key_type&	_S_key(const_node_ptr x)
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

				/* Why do we have node_ptr and const_node_ptr as return type ?
				 * We want to be able to create iterator and const_iterator by calling these function, so we need a const and non-const version.
				 * We use a static_cast to promote a node_base_ptr to a node_ptr, thus allowing us to have access to _M_value field. */

				node_ptr	_M_begin()
				{
					return (static_cast<node_ptr>(_M_base._M_header._M_parent));
				}

				const_node_ptr	_M_begin() const
				{
					return (static_cast<const_node_ptr>(_M_base._M_header._M_parent));
				}

				node_ptr	_M_end()
				{
					return (static_cast<node_ptr>(&_M_base._M_header));
				}

				const_node_ptr	_M_end() const
				{
					return (static_cast<const_node_ptr>(&_M_base._M_header));
				}

				node_ptr	_M_create_node(const value_type& val)
				{
					node_ptr	node;

					node = _M_base._M_node_allocator.allocate(1);
					try
					{
						_M_base._M_node_allocator.construct(&node->_M_value, val);
					}
					catch(...)
					{
						_M_base._M_node_allocator.deallocate(node, 1);
						throw;
					}
					return (node);
				}

				static node_ptr	_S_left(base_node_ptr x)
				{
					return (static_cast<node_ptr>(x->_M_left));
				}

				static const_node_ptr	_S_left(const_base_node_ptr x)
				{
					return (static_cast<const_node_ptr>(x->_M_left));
				}

				static node_ptr	_S_right(base_node_ptr x)
				{
					return (static_cast<node_ptr>(x->_M_right));
				}

				static const_node_ptr	_S_right(const_base_node_ptr x)
				{
					return (static_cast<const_node_ptr>(x->_M_right));
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
					std::cout << "Header Recap : " << &_M_base._M_header << "\n\n";
					std::cout << "Number of nodes : " << _M_base._M_nbr_node << '\n';
					std::cout << "_M_right address : " << _M_base._M_header._M_right << ", value : " << _S_value(_M_base._M_header._M_right).second << '\n';
					std::cout << "_M_left address : " << _M_base._M_header._M_left << ", value : " << _S_value(_M_base._M_header._M_left).second << '\n';
					std::cout << "root : " << _M_base._M_header._M_parent << ", value : " << _S_value(_M_base._M_header._M_parent).second << '\n';
					// Free every tree node.
				}

				/* ################################ Accesors ################################ */

				iterator	begin()
				{
					return (iterator(static_cast<node_ptr>(_M_base._M_header._M_left)));
				}

				const_iterator	begin() const
				{
					return (const_iterator(static_cast<const_node_ptr>(_M_base._M_header._M_left)));
				}

				iterator	end()
				{
					return (iterator(static_cast<node_ptr>(&_M_base._M_header)));
				}

				const_iterator	end() const
				{
					return (const_iterator(static_cast<const_node_ptr>(&_M_base._M_header)));
				}

				reverse_iterator	rbegin()
				{
					return (reverse_iterator(end()));
				}

				const_reverse_iterator	rbegin() const
				{
					return (const_reverse_iterator(end()));
				}

				reverse_iterator	rend()
				{
					return (reverse_iterator(begin()));
				}

				const_reverse_iterator	rend() const
				{
					return (const_reverse_iterator(begin()));
				}

				bool	empty() const
				{
					return (_M_base._M_nbr_node == 0);
				}

				ft::pair<iterator, bool>	insert_unique(const value_type& v)
				{
					return (_M_insert_unique_value(v));
				}

				template <class InputIt>
					void	insert_unique(InputIt first, InputIt last)
					{
						while (first != last)
						{
							_M_insert_unique_value(*first);
							first++;
						}
					}

				iterator	insert_unique(iterator hint, const value_type& v)
				{

				}


				/* ######################## Public members functions ######################## */

			private:

				/* ########################### Private attributes ########################### */

				RBT_Base	_M_base;

				/* ########################### Private structure ############################ */



				iterator _M_insert(const bool insert_left, base_node_ptr p, const value_type& val)
				{
					node_ptr	z;

					z = _M_create_node(val);
					rbt_insert_n_balance(insert_left, z, p, _M_base._M_header);
					_M_base._M_nbr_node++;
					return (iterator(z));
				}

				// insert an unique value into the tree.
				// if a value exist, the function return the iterator
				ft::pair<iterator, bool>	_M_insert_unique_value(const value_type& v)
				{
					node_ptr	x = _M_begin(); // root
					node_ptr	y = _M_end();   // header

					while (x != NULL)
					{
						y = x;
						if (KeyOfValue()(v) == _S_key(x))
							return (ft::pair<iterator, bool>(iterator(x), false));
						if (_M_base._M_key_cmp(KeyOfValue()(v), _S_key(x))) // if v < x.key
							x = _S_left(x);
						else
							x = _S_right(x);
					}
					if (y == _M_end() || _M_base._M_key_cmp(KeyOfValue()(v), _S_key(y)))
						return (ft::pair<iterator, bool>(_M_insert(true, y, v), true));
					else
						return (ft::pair<iterator, bool>(_M_insert(false, y, v), true));
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
