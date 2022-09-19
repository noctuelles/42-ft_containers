/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:42 by plouvel           #+#    #+#             */
/*   Updated: 2022/09/19 15:41:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# include "uchar.h"

namespace	ft
{
	template <bool B, class T = void>
		struct enable_if {};

	template <class T>
		struct enable_if<true, T>
		{
			typedef T	type;
		};

	template <class T, T v>
		struct integral_constant
		{
			static const T					value = v;
			typedef T						value_type;
			typedef integral_constant<T,v>	type;
			operator value_type(void)
			{
				return (v);
			}
		};

	/* Obtains the type T without any top-level const or volatile qualification.
	 * The transformed type is aliased as member type remove_cv::type. */

	template <class T>
		struct remove_cv
		{ typedef T	type; };

	template <class T>
		struct remove_cv<const T>
		{ typedef T	type; };

	template <class T>
		struct remove_cv<volatile T>
		{ typedef T	type; };

	template <class T>
		struct remove_cv<const volatile T>
		{ typedef T	type; };


	typedef ft::integral_constant<bool, true>	true_type;
	typedef ft::integral_constant<bool, false>	false_type;

	template<typename T> struct is_integral_base		:	ft::false_type {};

	template<> struct is_integral_base<bool>		:	ft::true_type {};
	template<> struct is_integral_base<char>		:	ft::true_type {};
	template<> struct is_integral_base<char16_t>	:	ft::true_type {};
	template<> struct is_integral_base<char32_t>	:	ft::true_type {};
	template<> struct is_integral_base<wchar_t>		:	ft::true_type {};
	template<> struct is_integral_base<short>		:	ft::true_type {};
	template<> struct is_integral_base<int>			:	ft::true_type {};
	template<> struct is_integral_base<long>		:	ft::true_type {};
	template<> struct is_integral_base<long long>	:	ft::true_type {};

	template<> struct is_integral_base<unsigned char>		:	ft::true_type {};
	template<> struct is_integral_base<unsigned long>		:	ft::true_type {};
	template<> struct is_integral_base<unsigned long long>	:	ft::true_type {};


	template <class T>
		struct is_integral: is_integral_base<typename ft::remove_cv<T>::type> {};
}

#endif
