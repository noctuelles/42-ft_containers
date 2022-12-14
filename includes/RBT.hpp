/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:11:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/10/06 16:26:25 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_TEMPLATE_CLASS_HPP
# define RBT_TEMPLATE_CLASS_HPP

#include "pair.hpp"
#include "iterators.hpp"
#include "algorithm.hpp"
#include "ftl_utils.hpp"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <string>

namespace ft
{
	/* Red Black Tree implementation, based on libstdc++ implementation, and Introduction to Algorithm
	 * Note that the code concerning the RBT implemtation is hugely commented : this is not a good practice,
	 * but this project being a pure exercice it holds a potentially big educational potential.
	 * Note that this RBT doesn't allow for any duplicate and doesn't offer an interface to insert duplicate key.*/

	void	rbt_insert_n_balance(const bool insert_left,
						RBTNode_Base* x,
						RBTNode_Base* p,
						RBTNode_Base& header);

	void	rbt_delete_node_n_balance(RBTNode_Base* z, RBTNode_Base& header);

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

				typedef std::allocator<value_type>											allocator_type;
				typedef typename allocator_type::template rebind<RBTNode<Value> >::other	node_allocator;

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

				allocator_type get_allocator() const
				{
					return (*static_cast<const node_allocator *>(&_M_base));
				}

			private:

				typedef RBTNode_Base::base_ptr			base_node_ptr;
				typedef RBTNode_Base::const_base_ptr	const_base_node_ptr;

				struct RBT_Base : public node_allocator
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

						key_compare		_M_key_cmp;
						RBTNode_Base	_M_header;
						size_type		_M_nbr_node;

						RBT_Base(const node_allocator& alloc = node_allocator(), const key_compare& comp = key_compare())
							: node_allocator(alloc), _M_key_cmp(comp), _M_header(red, NULL, &_M_header, &_M_header), _M_nbr_node()
						{}

				};

				static const Value&	_S_value(const_base_node_ptr x)
				{
					return (static_cast<const_node_ptr>(x)->_M_value);
				}

				static const key_type&	_S_key(const_base_node_ptr x)
				{
					return (KeyOfValue()(_S_value(x)));
				}

				static const Value&	_S_value(const_node_ptr x)
				{
					return (x->_M_value);
				}

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

					node = _M_base.node_allocator::allocate(1);
					try
					{
						get_allocator().construct(&node->_M_value, val);
					}
					catch(...)
					{
						_M_base.node_allocator::deallocate(node, 1);
						throw;
					}
					return (node);
				}

				void	_M_destroy_node(node_ptr x)
				{
					get_allocator().destroy(&x->_M_value);
					_M_base.node_allocator::deallocate(x, 1);
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

				base_node_ptr&	_M_root()
				{
					return (_M_base._M_header._M_parent);
				}

				const_base_node_ptr	_M_root() const
				{
					return (static_cast<const_base_node_ptr>(_M_base._M_header._M_parent));
				}

				const_base_node_ptr	_M_rightmost() const
				{
					return (static_cast<const_base_node_ptr>(_M_base._M_header._M_right));
				}

				base_node_ptr&	_M_rightmost()
				{
					return (_M_base._M_header._M_right);
				}

				const_base_node_ptr	_M_leftmost() const
				{
					return (static_cast<const_base_node_ptr>(_M_base._M_header._M_left));
				}

				base_node_ptr&	_M_leftmost()
				{
					return (_M_base._M_header._M_left);
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
					: _M_base(other.get_allocator(), other._M_base._M_key_cmp)
				{
					this->insert_unique(other.begin(), other.clear());
				}

				~RBT()
				{
					clear();
					/*std::cout << "Header Recap : " << &_M_base._M_header << "\n\n";
					std::cout << "Number of nodes : " << _M_base._M_nbr_node << '\n';
					std::cout << "_M_right address : " << _M_base._M_header._M_right << ", value : " << _S_value(_M_base._M_header._M_right).second << '\n';
					std::cout << "_M_left address : " << _M_base._M_header._M_left << ", value : " << _S_value(_M_base._M_header._M_left).second << '\n';

					if (_M_base._M_header._M_parent)
						std::cout << "root : " << _M_base._M_header._M_parent << ", value : " << _S_value(_M_base._M_header._M_parent).second << '\n';*/
				}

				RBT&	operator=(const RBT& other)
				{
					if (this != &other)
					{
						clear();
						this->insert_unique(other.begin(), other.end());
					}
					return (*this);
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

				/* ################################ Capacity ################################ */

				bool	empty() const
				{
					return (_M_base._M_nbr_node == 0);
				}

				size_type	size() const
				{
					return (_M_base._M_nbr_node);
				}

				size_type	max_size() const
				{
					return (_M_base.node_allocator::max_size());
				}

				/* ############################### Modifiers ################################ */

				void	clear()
				{
					_M_erase(_M_begin());
					_M_base._M_header._M_right = &_M_base._M_header;
					_M_base._M_header._M_left = &_M_base._M_header;
					_M_base._M_header._M_parent = NULL;
					_M_base._M_nbr_node = 0;
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
					return (_M_insert_unique_value(hint, v));
				}

				const_iterator	insert_unique(const_iterator hint, const value_type& v)
				{
					return (_M_insert_unique_value(hint, v));
				}

				void	erase_unique(iterator pos)
				{
					rbt_delete_node_n_balance(pos._M_node, _M_base._M_header);
					_M_destroy_node(static_cast<node_ptr>(pos._M_node));
					_M_base._M_nbr_node--;
				}

				void	erase_unique(const_iterator pos)
				{
					base_node_ptr	node = const_cast<base_node_ptr>(pos._M_node);

					rbt_delete_node_n_balance(node, _M_base._M_header);
					_M_destroy_node(static_cast<node_ptr>(node));
					_M_base._M_nbr_node--;
				}

				void	erase_unique(iterator first, iterator end)
				{
					if (first == begin() && end == this->end())
						return (clear());
					while (first != end)
						erase_unique(first++);
				}

				void	erase_unique(const_iterator first, const_iterator end)
				{
					if (first == begin() && end == this->end())
						return (clear());
					while (first != end)
						erase_unique(first++);
				}

				size_type	erase_unique(const key_type& key)
				{
					iterator	i = this->find(key);
					if (i != end())
					{
						this->erase_unique(i);
						return (1);
					}
					return (0);
				}

				/*void	print() const
				{
					_M_debug_print("", _M_root(), true);
				}*/

				/* ################################# Lookup ################################# */

				iterator	lower_bound(const key_type& k)
				{
					node_ptr	x = _M_begin();
					node_ptr	y = _M_end(); // y is guarantee to be greater than k

					while (x != NULL)
					{
						if (!_M_base._M_key_cmp(_S_key(x), k)) // >=
						{
							y = x;
							x = _S_left(x);
						}
						else
							x = _S_right(x);
					}
					return (iterator(y));
				}

				const_iterator	lower_bound(const key_type& k) const
				{
					const_node_ptr	x = _M_begin();
					const_node_ptr	y = _M_end();

					while (x != NULL)
					{
						if (!_M_base._M_key_cmp(_S_key(x), k)) // >=
						{
							y = x;
							x = _S_left(x);
						}
						else
							x = _S_right(x);
					}
					return (const_iterator(y));
				}

				iterator	upper_bound(const key_type& k)
				{
					node_ptr	x = _M_begin();
					node_ptr	y = _M_end();

					while (x != NULL)
					{
						if (_M_base._M_key_cmp(k, _S_key(x)))
						{
							y = x;
							x = _S_left(x);
						}
						else
							x = _S_right(x);
					}
					return (iterator(y));
				}

				const_iterator	upper_bound(const key_type& k) const
				{
					const_node_ptr	x = _M_begin();
					const_node_ptr	y = _M_end();

					while (x != NULL)
					{
						if (_M_base._M_key_cmp(k, _S_key(x)))
						{
							y = x;
							x = _S_left(x);
						}
						else
							x = _S_right(x);
					}
					return (const_iterator(y));
				}

				ft::pair<iterator, iterator>	equal_range(const key_type& k)
				{
					return (ft::make_pair(lower_bound(k), upper_bound(k)));
				}

				ft::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const
				{
					return (ft::make_pair(lower_bound(k), upper_bound(k)));
				}

				iterator	find(const key_type& k)
				{
					node_ptr	x = _M_begin();
					node_ptr	y = NULL;

					while (x != NULL)
					{
						y = x;
						if (!_M_base._M_key_cmp(k, _S_key(x)) && !_M_base._M_key_cmp(_S_key(x), k))
							return (iterator(y));
						if (_M_base._M_key_cmp(k, _S_key(x)))
							x = _S_left(x);
						else
							x = _S_right(x);
					}
					return (end());
				}

				const_iterator	find(const key_type& k) const
				{
					const_node_ptr	x = _M_begin();
					const_node_ptr	y = NULL;

					while (x != NULL)
					{
						y = x;
						if (!_M_base._M_key_cmp(k, _S_key(x)) && !_M_base._M_key_cmp(_S_key(x), k))
							return (const_iterator(y));
						if (_M_base._M_key_cmp(k, _S_key(x)))
							x = _S_left(x);
						else
							x = _S_right(x);
					}
					return (end());
				}

				key_compare	key_comp() const
				{
					return (_M_base._M_key_cmp);
				}

				void	swap(RBT& other)
				{
					if (_M_root() == NULL)
					{
						if (other._M_root() != NULL)
						{
							_M_root() = other._M_root();
							_M_leftmost() = other._M_leftmost();
							_M_rightmost() = other._M_rightmost();
							_M_root()->_M_parent = _M_end();

							other._M_root() = NULL;
							other._M_leftmost() = other._M_end();
							other._M_rightmost() = other._M_end();
						}
					}
					else if (other._M_root() == NULL)
					{
						other._M_root() = _M_root();
						other._M_leftmost() = _M_leftmost();
						other._M_rightmost() = _M_rightmost();
						other._M_root()->_M_parent = other._M_end();

						_M_root() = NULL;
						_M_leftmost() = _M_end();
						_M_rightmost() = _M_end();
					}
					else
					{
						std::swap(_M_root(), other._M_root());
						std::swap(_M_leftmost(), other._M_leftmost());
						std::swap(_M_rightmost(), other._M_rightmost());

						// update the header in respective tree.
						_M_root()->_M_parent = _M_end();
						other._M_root()->_M_parent = other._M_end();
					}

					std::swap(_M_base._M_nbr_node, other._M_base._M_nbr_node);
					std::swap(_M_base._M_key_cmp, other._M_base._M_key_cmp);
				}

				/* ######################## Public members functions ######################## */

			private:

				/* ########################### Private attributes ########################### */

				RBT_Base	_M_base;

				/* ########################### Private structure ############################ */

				// All the const_iterator variant are needed for set, since a const_iterator and an iterator is the same type.
				void	_M_erase(node_ptr x)
				{
					while (x != NULL)
					{
						_M_erase(_S_right(x));
						node_ptr y = _S_left(x);
						_M_destroy_node(x);
						x = y;
					}
				}

				iterator _M_insert(const bool insert_left, base_node_ptr p, const value_type& val)
				{
					node_ptr	z;

					z = _M_create_node(val);
					rbt_insert_n_balance(insert_left, z, p, _M_base._M_header);
					_M_base._M_nbr_node++;
					return (iterator(z));
				}

				const_iterator _M_insert(const bool insert_left, const_base_node_ptr p, const value_type& val)
				{
					node_ptr	z;

					z = _M_create_node(val);
					rbt_insert_n_balance(insert_left, z, const_cast<base_node_ptr>(p), _M_base._M_header);
					_M_base._M_nbr_node++;
					return (const_iterator(z));
				}

				// insert an unique value into the tree.
				// if a value exist, the function return the iterator
				ft::pair<iterator, bool>	_M_insert_unique_value(const value_type& v)
				{
					node_ptr	x = _M_begin(); // root
					node_ptr	y = _M_end();   // header
					bool		comp = true;

					while (x != NULL)
					{
						y = x;
						if (!_M_base._M_key_cmp(KeyOfValue()(v), _S_key(x)) && !_M_base._M_key_cmp(_S_key(x), KeyOfValue()(v)))
							return (ft::pair<iterator, bool>(iterator(x), false));
						comp = _M_base._M_key_cmp(KeyOfValue()(v), _S_key(x));
						(comp) ? x = _S_left(x) : x = _S_right(x);
					}
					if (comp)
						return (ft::pair<iterator, bool>(_M_insert(true, y, v), true));
					else
						return (ft::pair<iterator, bool>(_M_insert(false, y, v), true));
				}

				ft::pair<const_iterator, bool>	_M_insert_unique_value(const value_type& v) const
				{
					const_node_ptr	x = _M_begin(); // root
					const_node_ptr	y = _M_end();   // header
					bool		comp = true;

					while (x != NULL)
					{
						y = x;
						if (!_M_base._M_key_cmp(KeyOfValue()(v), _S_key(x)) && !_M_base._M_key_cmp(_S_key(x), KeyOfValue()(v)))
							return (ft::pair<const_iterator, bool>(iterator(x), false));
						comp = _M_base._M_key_cmp(KeyOfValue()(v), _S_key(x));
						(comp) ? x = _S_left(x) : x = _S_right(x);
					}
					if (comp)
						return (ft::pair<const_iterator, bool>(_M_insert(true, y, v), true));
					else
						return (ft::pair<const_iterator, bool>(_M_insert(false, y, v), true));
				}

				iterator	_M_insert_unique_value(iterator hint, const value_type& v)
				{
					if (hint._M_node == _M_end())
					{
						if (size() > 0 && _M_base._M_key_cmp(_S_key(_M_rightmost()), KeyOfValue()(v))) // if the rightmost node key is lower than v key.
							return (_M_insert(false, _M_rightmost(), v)); // the new node'll be inserted at the end.
						else
							return (insert_unique(v).first); // the user gave us a bad hint: go though normal insertion routine.
					}
					// if the value to insert as a key lower than the hint
					// v < key(hint)
					else if (_M_base._M_key_cmp(KeyOfValue()(v), _S_key(hint._M_node)))
					{
						iterator	before = --hint;

						// is the hint the leftmost node ? easy: simply insert the value at the left branch of the leftmost node,
						// becoming the new leftmost..
						if (hint._M_node == _M_leftmost())
							return (_M_insert(true, _M_leftmost(), v));
						// is the key of the predecessor node of hint lower than the key to insert ?
						else if (_M_base._M_key_cmp(_S_key(before._M_node), KeyOfValue()(v)))
						{
							if (_S_right(before._M_node) == NULL)
								return (_M_insert(false, before._M_node, v));
							else
								return (_M_insert(true, hint._M_node, v));
						}
						else
							return (insert_unique(v).first);
					}
					// if the value to insert as a key greater than the hint
					// v > key(hint) <=> key(hint) < v
					else if (_M_base._M_key_cmp(_S_key(hint._M_node), KeyOfValue()(v)))
					{
						iterator	after = ++hint;

						// same logic as above.
						if (hint._M_node == _M_rightmost())
							return (_M_insert(false, _M_rightmost(), v));
						else if (_M_base._M_key_cmp(KeyOfValue()(v), _S_key(after._M_node)))
						{
							if (_S_right(hint._M_node) == NULL)
								return (_M_insert(false, hint._M_node, v));
							else
								return (_M_insert(true, after._M_node, v));
						}
						else
							return (insert_unique(v).first);
					}
					// the value to insert as q key equal that the hint : simply return the iterator.
					else
						return (hint);
				}

				const_iterator	_M_insert_unique_value(const_iterator hint, const value_type& v)
				{
					if (hint._M_node == _M_end())
					{
						if (size() > 0 && _M_base._M_key_cmp(_S_key(_M_rightmost()), KeyOfValue()(v)))
							return (_M_insert(false, _M_rightmost(), v));
						else
							return (const_iterator(insert_unique(v).first));
					}
					else if (_M_base._M_key_cmp(KeyOfValue()(v), _S_key(hint._M_node)))
					{
						const_iterator	before = --hint;

						if (hint._M_node == _M_leftmost())
							return (_M_insert(true, _M_leftmost(), v));
						else if (_M_base._M_key_cmp(_S_key(before._M_node), KeyOfValue()(v)))
						{
							if (_S_right(before._M_node) == NULL)
								return (_M_insert(false, before._M_node, v));
							else
								return (_M_insert(true, hint._M_node, v));
						}
						else
							return (const_iterator(insert_unique(v).first));
					}
					else if (_M_base._M_key_cmp(_S_key(hint._M_node), KeyOfValue()(v)))
					{
						const_iterator	after = ++hint;

						if (hint._M_node == _M_rightmost())
							return (_M_insert(false, _M_rightmost(), v));
						else if (_M_base._M_key_cmp(KeyOfValue()(v), _S_key(after._M_node)))
						{
							if (_S_right(hint._M_node) == NULL)
								return (_M_insert(false, hint._M_node, v));
							else
								return (_M_insert(true, after._M_node, v));
						}
						else
							return (const_iterator(insert_unique(v).first));
					}
					else
						return (hint);
				}

				void	_M_debug_print(const std::string& prefix, const_base_node_ptr x, bool isLeft) const
				{
					if (x)
					{
						std::cout << prefix;
						std::cout << (isLeft ? "?????????" : "?????????");
						std::cout << _S_key(x) << std::endl;
						x = _S_left(x);
						_M_debug_print(prefix + (isLeft ? "???   " : "    "), x, true);
						x = _S_right(x);
						_M_debug_print(prefix + (isLeft ? "???   " : "    "), x, false);
					}
				}
		};

	template <class Key, class Value, class KeyOfValue, class Compare>
		inline bool	operator==(const RBT<Key, Value, KeyOfValue, Compare>& x, const RBT<Key, Value, KeyOfValue, Compare>& y)
		{
			return (x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin()));
		}

	template <class Key, class Value, class KeyOfValue, class Compare>
		inline bool	operator!=(const RBT<Key, Value, KeyOfValue, Compare>& x, const RBT<Key, Value, KeyOfValue, Compare>& y)
		{
			return !(x == y);
		}

	template <class Key, class Value, class KeyOfValue, class Compare>
		inline bool	operator<(const RBT<Key, Value, KeyOfValue, Compare>& x, const RBT<Key, Value, KeyOfValue, Compare>& y)
		{
			return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
		}

	template <class Key, class Value, class KeyOfValue, class Compare>
		inline bool	operator<=(const RBT<Key, Value, KeyOfValue, Compare>& x, const RBT<Key, Value, KeyOfValue, Compare>& y)
		{
		 return !(y < x);
		}

	template <class Key, class Value, class KeyOfValue, class Compare>
		inline bool	operator>(const RBT<Key, Value, KeyOfValue, Compare>& x, const RBT<Key, Value, KeyOfValue, Compare>& y)
		{
			return (y < x);
		}

	template <class Key, class Value, class KeyOfValue, class Compare>
		inline bool	operator>=(const RBT<Key, Value, KeyOfValue, Compare>& x, const RBT<Key, Value, KeyOfValue, Compare>& y)
		{
			return !(x < y);
		}
}

#endif
