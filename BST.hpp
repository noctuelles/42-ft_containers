/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:07:58 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/22 17:32:01 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_CLASS
# define BST_CLASS

#include <exception>
#include <utility>
#include <memory>
#include <string>
#include <iostream>

template <class Key, class Value>
	class BST
	{
			/* ########################## Node implementation ########################### */

			typedef std::pair<const Key, Value>	value_type;

			struct Node
			{
				Node(const value_type& val)
					: pair(val), left(), right(), parent() {}

				~Node()
				{
					delete left;
					delete right;
				}

				value_type	pair;

				Node	*parent;
				Node	*left;
				Node	*right;
			};

			typedef Node*	node_ptr;

			

			Node*	m_root;

		public:

			class EmptyTree {};
			class ExistingKey {};
			class KeyNotFound {};

			BST()
				: m_root() {}

			~BST()
			{
				delete m_root;
			}

			Value&	operator[](const Key& key)
			{
				try
				{
					search(key);
				}
				catch (KeyNotFound)
				{
					insert(key);
				}
				return (search(key));
			}

			Value&	search(const Key& key)
			{
				node_ptr	x;

				x = m_root;
				while (x != NULL && x->pair.first != key)
				{
					if (key < x->pair.first)
						x = x->left;
					else
						x = x->right;
				}
				if (!x)
					throw (KeyNotFound());
				return (x->pair.second);
			}

			void		insert(const Key& key, const Value& val = Value())
			{
				node_ptr	x, y;

				x = m_root;
				y = NULL;
				while (x != NULL)
				{
					y = x;
					if (key < x->pair.first)
						x = x->left;
					else if (key > x->pair.first)
						x = x->right;
					else
						return ;
				}
				if (y == NULL)
					x = m_root = new Node(std::make_pair(key, val));
				else if (key < y->pair.first)
					x = y->left = new Node(std::make_pair(key, val));
				else
					x = y->right = new Node(std::make_pair(key, val));
				x->parent = y;
			}

			const Value&	minimum()
			{
				node_ptr	x;

				x = _m_minimum(m_root);
				if (!x)
					throw (EmptyTree());
				return (x->pair.second);
			}

			const Value&	maximum()
			{
				node_ptr	x;

				x = _m_maximum(m_root);
				if (!x)
					throw (EmptyTree());
				return (x->pair.second);
			}

		private:
			
			node_ptr	_m_minimum(node_ptr x)
			{
				while (x->left != NULL)
					x = x->left;
				return (x);
			}

			node_ptr	_m_maximum(node_ptr x)
			{
				while (x->right != NULL)
					x = x->right;
				return (x);
			}

			// NULL -> No sucessor at a given node x
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
	};

#endif
