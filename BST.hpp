/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:07:58 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/21 16:32:26 by plouvel          ###   ########.fr       */
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
					: pair(val), left(), right() {}

				~Node()
				{}

				value_type	pair;

				Node	*left;
				Node	*right;
			};

			typedef Node*	node_ptr;

			node_ptr	m_search(const Key& key, node_ptr root) 
			{
				if (root == NULL)
					return (NULL);
				if (root->pair.first == key)
					return (root);
				if (root->pair.first < key)
					return (m_search(key, root->left));
				if (root->pair.first > key)
					return (m_search(key, root->right));
			}

			void	m_insert(const value_type& val, node_ptr root)
			{
				if (root == NULL)
					return ;
				if (val.first < root->pair.first)
				{
					m_insert(val, root->left);
					root->left = new Node(val);
				}
				else if (val.first > root->pair.first)
				{
					m_insert(val, root->right);
					root->right = new Node(val);
				}
				else 
					throw (std::exception());
			}

			void	m_erase(node_ptr root)
			{
				if (!root)
					return ;
				if (root->left)
					m_erase(root->left);
				if (root->right)
					m_erase(root->right);
				delete root->left;
				root->left = NULL;
				delete root->right;
				root->right = NULL;
			}

			Node*	m_root;

		public:

			BST()
				: m_root() {}

			~BST()
			{
				std::cout << "Destructor called\n";
				m_erase(m_root);
			}

			node_ptr	search(const Key& key)
			{
				return (m_search(key, m_root));
			}

			const Value&	operator[](const Key& key)
			{
				node_ptr	ptr = search(key);
				if (!ptr)
					throw (std::exception());
				return (ptr->pair.second);
			}

			void		insert(const Key& key, const Value& val)
			{
				if (!m_root)
					m_root = new Node(std::make_pair(key, val));
				else
					m_insert(std::make_pair(key, val), m_root);
			}
	};

#endif
