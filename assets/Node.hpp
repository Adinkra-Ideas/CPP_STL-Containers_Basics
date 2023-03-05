/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nod.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:26:32 by euyi              #+#    #+#             */
/*   Updated: 2023/02/14 17:29:32 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NODE_HPP__
# define __NODE_HPP__

# define RED 1
# define BLACK 0

namespace ft {
	
template <typename T>
struct Nod {
	Nod(T _data) : data(_data), parent(NULL), left(NULL), right(NULL), color(RED){};

	T data;
	Nod<T> *parent;
	Nod<T> *left;
	Nod<T> *right;
	int color;
};

}

#endif
