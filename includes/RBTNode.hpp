/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:11:38 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/23 20:21:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTNODE_HPP
# define RBTNODE_HPP

#include <cctype>
#include <memory>

namespace ft
{
	enum	RBTNode_Color {black, red};

	struct RBTNode_Base
	{
		typedef RBTNode_Base*		base_ptr;
		typedef const RBTNode_Base*	const_base_ptr;

		RBTNode_Color	_M_color;
		base_ptr		_M_parent;
		base_ptr		_M_left;
		base_ptr		_M_right;

		// These functions are static so that they're callable from anywhere
		// without declaring any RBTNode_Base type.
		static base_ptr	minimum(base_ptr x)
		{
			while (x->_M_left != NULL)
				x = x->_M_left;
			return (x);
		}

		static const_base_ptr	minimum(const_base_ptr x)
		{
			return (minimum(const_cast<base_ptr>(x)));
		}

		static base_ptr	maximum(base_ptr x)
		{
			while (x->_M_right != NULL)
				x = x->_M_right;
			return (x);
		}

		static const_base_ptr	maximum(const_base_ptr x)
		{
			return (maximum(const_cast<base_ptr>(x)));
		}
	};

	template <class Value>
		struct RBTNode : public RBTNode_Base
		{
			typedef RBTNode*	link_type;

			Value	_M_value;
		};

	/* ############################# Node functions ############################# */

	RBTNode_Base::base_ptr			rbt_node_increment(RBTNode_Base::base_ptr x) throw();

	RBTNode_Base::const_base_ptr	rbt_node_increment(RBTNode_Base::const_base_ptr x) throw();

	RBTNode_Base::base_ptr			rbt_node_decrement(RBTNode_Base::base_ptr x) throw();

	RBTNode_Base::const_base_ptr	rbt_node_decrement(RBTNode_Base::const_base_ptr x) throw();
}

#endif
