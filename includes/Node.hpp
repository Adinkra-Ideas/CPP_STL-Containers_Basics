#ifndef __NODE_HPP__
# define __NODE_HPP__

# define RED 1
# define BLACK 0

# define SUP_ROOT -10
# define DUM_ROOT 10


namespace ft {
	
template <typename T>
struct Nod {


	Nod(T _data) : data(_data), parent(NULL), left(NULL), right(NULL), color(RED),flag(0) {}


	T data;
	Nod<T> *parent;
	Nod<T> *left;
	Nod<T> *right;
	int color;
	int flag;
};

}

#endif
