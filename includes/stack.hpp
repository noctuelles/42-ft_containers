/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:46:09 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/19 19:49:34 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_CLASS_HPP
# define STACK_CLASS_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
		class	stack
		{
			public:

				typedef Container							container_type;
				typedef typename Container::value_type		value_type;
				typedef typename Container::size_type		size_type;
				typedef typename Container::reference		reference;
				typedef typename Container::const_reference	const_reference;

				explicit stack(const Container& cont = Container())
					: c(cont) {}

				~stack() {}

				stack&	operator=(const stack& other)
				{
					c = other.c;
				}

				/* ############################# Element Access ############################# */

				reference	top()
				{
					return (c.back());
				}

				const_reference	top() const
				{
					return (c.back());
				}

				/* ################################ Capacity ################################ */

				bool	empty() const
				{
					return (c.empty());
				}

				size_type	size() const
				{
					return (c.size());
				}

				/* ############################### Modifiers ################################ */

				void	push(const value_type& value)
				{
					c.push_back(value);
				}

				void	pop()
				{
					c.pop_back();
				}

			private:

				Container	c;
		};
}

#endif
