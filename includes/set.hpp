/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:59:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/30 18:07:09 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functional>
#include "RBT.hpp"
#include "ftl_utils.hpp"

namespace ft
{

	template <class Key,
			 class Compare = std::less<Key>>
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

				typedef typename tree_type::iterator				iterator;
				typedef typename tree_type::const_iterator			const_iterator;
				typedef typename tree_type::reverse_iterator		reverse_iterator;
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

			private:

		};
}
