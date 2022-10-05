/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:59:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/10/05 14:57:38 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functional>
#include "RBT.hpp"
#include "ftl_utils.hpp"

namespace ft
{

	/* set is different than map because :
	 *
	 *      -> it contains unique object of type Key instead of key-value pairs.
	 *      -> set's element are immutable : you cannot change the value of a key.
	 *      the following properties make set's iterator and const_iterator practically the same. */

	template <class Key,
			 class Compare = std::less<Key> >
		class set
		{
			public:

				typedef Key							key_type;
				typedef Compare						key_compare;
				typedef Key							value_type;

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;
				typedef std::allocator<value_type>	allocator_type;

				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;

				typedef RBT<value_type, value_type, Identity<value_type>, key_compare>	tree_type;

				typedef typename tree_type::const_iterator			iterator;
				typedef typename tree_type::const_iterator			const_iterator;
				typedef typename tree_type::const_reverse_iterator	reverse_iterator;
				typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

				class value_compare : public ft::binary_function<value_type, value_type, bool>
				{
					friend class set;

					public:

						typedef typename binary_function<value_type, value_type, bool>::result_type				result_type;
						typedef typename binary_function<value_type, value_type, bool>::first_argument_type		first_argument_type;
						typedef typename binary_function<value_type, value_type, bool>::second_argument_type	second_argument_type;

						bool	operator()(const value_type& x, const value_type& y)
						{
							return (comp(x, y));
						}
					protected:

						value_compare(key_compare comp) : comp(comp) {}

						key_compare	comp;
				};

				explicit	set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: _M_tree(comp, alloc)
				{}

				template <class InputIt>
					set(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: _M_tree(comp, alloc)
				{
					this->insert(first, last);
				}

				set(const set& other)
				{
					insert(other.begin(), other.end());
				}

				~set()
				{}

				set&	operator=(set& other)
				{
					_M_tree.operator=(other._M_tree);
					return (*this);
				}

				/* ############################# Element Access ############################# */

				key_type&	at(const key_type& k)
				{
					iterator	i = this->find(k);

					if (i == end())
						throw (std::out_of_range("set::at"));
					return ((*i).second);
				}

				key_type&	operator[](const key_type& k)
				{
					iterator	i = this->insert(value_type(k, key_type())).first;
					return ((*i).second);
				}

				allocator_type	get_allocator() const
				{
					return (_M_tree.get_allocator());
				}

				/* ############################### Iterators ################################ */

				iterator	begin()
				{
					return (_M_tree.begin());
				}

				const_iterator	begin() const
				{
					return (_M_tree.begin());
				}

				iterator	end()
				{
					return (_M_tree.end());
				}

				const_iterator	end() const
				{
					return (_M_tree.end());
				}

				reverse_iterator	rbegin()
				{
					return (_M_tree.rbegin());
				}

				const_reverse_iterator	rbegin() const
				{
					return (_M_tree.rbegin());
				}

				reverse_iterator	rend()
				{
					return (_M_tree.rend());
				}

				const_reverse_iterator	rend() const
				{
					return (_M_tree.rend());
				}

				/* ################################ Capacity ################################ */

				bool	empty() const
				{
					return (_M_tree.empty());
				}

				size_t	size() const
				{
					return (_M_tree.size());
				}

				size_type	max_size() const
				{
					return (_M_tree.max_size());
				}

				/* ############################### Modifiers ################################ */

				void	clear()
				{
					_M_tree.clear();
				}

				ft::pair<iterator, bool>	insert(const value_type& value)
				{
					return (_M_tree.insert_unique(value));
				}

				template <class InputIt>
					void	insert(InputIt first, InputIt last)
					{
						_M_tree.insert_unique(first, last);
					}

				iterator	insert(iterator hint, const value_type& v)
				{
					return (_M_tree.insert_unique(hint, v));
				}

				void	erase(iterator pos)
				{
					_M_tree.erase_unique(pos);
				}

				void	erase(iterator first, iterator last)
				{
					_M_tree.erase_unique(first, last);
				}

				size_type	erase(const key_type& key)
				{
					return (_M_tree.erase_unique(key));
				}

				// Returns an iterator pointing to the first element that is not less than key.
				iterator	lower_bound(const key_type& k)
				{
					return (_M_tree.lower_bound(k));
				}

				// Returns an iterator pointing to the first element that is not less than key.
				const_iterator	lower_bound(const key_type& k) const
				{
					return (_M_tree.lower_bound(k));
				}

				// Returns an iterator pointing to the first element that is greater than key.
				iterator	upper_bound(const key_type& k)
				{
					return (_M_tree.upper_bound(k));
				}

				// Returns an iterator pointing to the first element that is greater than key.
				const_iterator	upper_bound(const key_type& k) const
				{
					return (_M_tree.upper_bound(k));
				}

				ft::pair<iterator, iterator>	equal_range(const key_type& k)
				{
					return (_M_tree.equal_range(k));
				}

				ft::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const
				{
					return (_M_tree.equal_range(k));
				}

				iterator	find(const key_type& k)
				{
					return (_M_tree.find(k));
				}

				const_iterator	find(const key_type& k) const
				{
					return (_M_tree.find(k));
				}

				size_type	count(const key_type& k) const
				{
					return ((find(k) != end()) ? 1 : 0);
				}

				key_compare	key_comp() const
				{
					return (_M_tree.key_comp());
				}

				value_compare	value_comp() const
				{
					return (value_compare(_M_tree.key_comp()));
				}

				void	swap(set& other)
				{
					_M_tree.swap(other._M_tree);
				}

				void	print() const
				{
					_M_tree.print();
				}

				template <class _Key, class _Compare>
					friend inline bool	operator==(const set<_Key, _Compare>& x, const set<_Key, _Compare>& y);

				template <class _Key, class _Compare>
					friend inline bool	operator<(const set<_Key, _Compare>& x, const set<_Key, _Compare>& y);

			private:

				tree_type	_M_tree;
		};

	template <class Key, class Compare>
		inline bool	operator==(const set<Key, Compare>& x, const set<Key, Compare>& y)
		{
			return (x._M_tree == y._M_tree);
		}

	template <class Key, class Compare>
		inline bool	operator!=(const set<Key, Compare>& x, const set<Key, Compare>& y)
		{
			return !(x == y);
		}

	template <class Key,  class Compare>
		inline bool	operator<(const set<Key, Compare>& x, const set<Key, Compare>& y)
		{
			return (x._M_tree < y._M_tree);
		}

	template <class Key, class Compare>
		inline bool	operator<=(const set<Key, Compare>& x, const set<Key, Compare>& y)
		{
			return !(y < x);
		}

	template <class Key, class Compare>
		inline bool	operator>(const set<Key, Compare>& x, const set<Key, Compare>& y)
		{
			return (y < x);
		}

	template <class Key, class Compare>
		inline bool	operator>=(const set<Key, Compare>& x, const set<Key, Compare>& y)
		{
			return !(x < y);
		}
}
