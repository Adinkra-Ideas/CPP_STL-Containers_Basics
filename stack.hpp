/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:40:44 by euyi              #+#    #+#             */
/*   Updated: 2023/03/04 20:14:59 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_HPP__
# define __STACK_HPP__

# include <iostream>

# include "vector.hpp"

namespace ft {

template <typename T, class Container = ft::vector<T> >
class stack {
public:
	typedef Container container_type;
	typedef typename container_type::value_type value_type;
	typedef typename container_type::size_type size_type;
	typedef typename container_type::reference reference;
	typedef typename container_type::const_reference const_reference;

	stack(){}
	explicit stack(const container_type& cont) : c(cont){}
	stack(const stack& other) { c = other.c; }
	~stack(){}

	stack& operator=(const stack& other) {
		c = other.c;
		return *this;
  	}

// ***************************
//    Element Access
// ***************************
	reference top() { return c.back(); }
	const_reference top() const { return c.back(); }

// ***************************
//     Capacity
// ***************************
	bool empty() const { return c.empty(); }
	size_type size() const { return c.size(); }

// ***************************
//     Modifiers
// ***************************

	void push(const value_type& value) { c.push_back(value); }
  	void push(value_type& value) { c.push_back(value); }

	void pop() { c.pop_back(); }

// ***************************
//     Comparison
// ***************************

	friend bool operator==(const stack<value_type, container_type>& lhs,
                         const stack<value_type, container_type>& rhs) {
    	return lhs.c == rhs.c;
	}

	friend bool operator!=(const stack<value_type, container_type>& lhs,
                         const stack<value_type, container_type>& rhs) {
    	return lhs.c != rhs.c;
	}

	friend bool operator<(const stack<value_type, container_type>& lhs,
                        const stack<value_type, container_type>& rhs) {
		return lhs.c < rhs.c;
  	}

	friend bool operator<=(const stack<value_type, container_type>& lhs,
                         const stack<value_type, container_type>& rhs) {
		return lhs.c <= rhs.c;
  	}

	friend bool operator>(const stack<value_type, container_type>& lhs,
                        const stack<value_type, container_type>& rhs) {
    	return lhs.c > rhs.c;
  	}

	friend bool operator>=(const stack<value_type, container_type>& lhs,
                         const stack<value_type, container_type>& rhs) {
		return lhs.c >= rhs.c;
  	}

protected:
	container_type c;
};

}

#endif
