/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftl_utils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:58:34 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/30 16:57:42 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTL_UTILS_HPP
# define FTL_UTILS_HPP

namespace ft
{
	// An unary function is a function that takes only one argument.
	template <class Arg, class Result>
		struct unary_function
		{
			typedef Arg		argument_type;

			typedef Result	result_type;
		};

	template <class FirstArg, class SecondArg, class Result>
		struct binary_function
		{
			typedef FirstArg		first_argument_type;
			typedef SecondArg		second_argument_type;

			typedef Result	result_type;
		};

	// SelectFirst is a functor (function object) that return the first of a given pair.
	// This is usefull in map implementation, where the "first" member of a pair is the key.
	// Therefore, i use this functor to retrieve the key of a pair value in a red-black tree implementation.
	template <class Pair>
		struct SelectFirst : public unary_function<Pair, typename Pair::first_type>
		{
			typedef typename unary_function<Pair, typename Pair::first_type>::result_type	result_type;

			result_type&	operator()(Pair& pair) const
			{
				return (pair.first);
			}

			const result_type&	operator()(const Pair& pair) const
			{
				return (pair.first);
			}
		};

	template <class T>
		struct Identity : public unary_function<T, T>
		{
			typedef typename unary_function<T, T>::result_type	result_type;

			result_type&	operator()(T& value) const
			{
				return (value);
			}

			const result_type&	operator()(const T& value) const
			{
				return (value);
			}
		};
}

#endif
