/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:15:27 by euyi              #+#    #+#             */
/*   Updated: 2023/03/04 19:50:12 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PAIR_HPP__
# define __PAIR_HPP__

# include "TypeTraits.hpp"

namespace ft {

template <typename T1, typename T2>
struct pair {
	typedef T1 first_type;
	typedef T2 second_type;

	pair() : first(), second(){}
	pair(const T1& x, const T2& y) : first(x), second(y){}

	template <class U1, class U2>
	pair(const pair<U1, U2>& p) : first(p.first), second(p.second){}

	pair(const pair& p) : first(p.first), second(p.second){}
	~pair(){}

	pair& operator=(const pair& other) {
		first = other.first;
		second = other.second;
		return *this;
	}

	first_type	first;
	second_type	second;
};

template <typename T1, typename T2>
pair<T1, std::string> make_pair(const T1& t, const T2& u,
	typename ft::enable_if<is_custom_integral<const T2>::value, T2>::type* = NULL,
	typename ft::enable_if<!is_custom_integral<const T1>::value, T1>::type* = NULL )
{
	return pair<T1, std::string>(t, u);
}

template <typename T1, typename T2>
pair<std::string, std::string> make_pair(const T1& t, const T2& u,
	typename ft::enable_if<is_custom_integral<const T2>::value, T2>::type* = NULL,
	typename ft::enable_if<is_custom_integral<const T1>::value, T1>::type* = NULL )
{
	return pair<std::string, std::string>(t, u);
}

template <typename T1, typename T2>
pair<T1, T2> make_pair(const T1& t, const T2& u,
	typename ft::enable_if<!is_custom_integral<const T1>::value, T1>::type* = NULL,
	typename ft::enable_if<!is_custom_integral<const T2>::value, T2>::type* = NULL )
{
	return pair<T1, T2>(t, u);
}

template <typename T1, typename T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename T1, typename T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	return !(lhs == rhs);
}

template <typename T1, typename T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	return lhs.first < rhs.first ||
         (lhs.first <= rhs.first && lhs.second < rhs.second);
}

template <typename T1, typename T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	return !(rhs < lhs);
}

template <typename T1, typename T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	return rhs < lhs;
}

template <typename T1, typename T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	return !(lhs < rhs);
}

	
}

#endif
