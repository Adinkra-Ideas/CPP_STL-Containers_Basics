#ifndef __ITERATORTRAITS_HPP__
# define __ITERATORTRAITS_HPP__

# include <iostream>

namespace ft {

template <class T>
struct	iterator_traits {
public:
	typedef typename T::difference_type difference_type;
	typedef typename T::value_type value_type;
	typedef typename T::pointer pointer;
	typedef typename T::reference reference;
	typedef typename T::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*> {
public:
	typedef std::ptrdiff_t difference_type;
	typedef T value_type;
	typedef value_type& pointer;
	typedef value_type& reference;
	typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
public:
	typedef std::ptrdiff_t difference_type;
	typedef T value_type;
	typedef const value_type& const_pointer;
	typedef const value_type& const_reference;
	typedef std::random_access_iterator_tag iterator_category;
};

}

#endif
