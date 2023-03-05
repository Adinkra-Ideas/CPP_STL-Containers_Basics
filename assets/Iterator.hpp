/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:02:27 by euyi              #+#    #+#             */
/*   Updated: 2023/03/05 18:07:27 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

# include <iostream>

# define CONST_CAST_rIT_THIS (const_cast<reverse_iterator *>(this))
# define CONST_CAST_IT_THIS (const_cast<RandomAccessIterator *>(this))

namespace ft {

template <typename T>
class reverse_iterator;

// Random Access Iterator
// Use to instantiate an object that 
// is an iterator for T (pointer of typename T)
template <typename T>
class	RandomAccessIterator {
public:
	typedef typename std::random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;

	template <typename T1>
	friend class reverse_iterator;

	RandomAccessIterator() : _iterT(NULL){}
	~RandomAccessIterator() {}

	RandomAccessIterator(const_pointer ptr) : _iterT(const_cast<pointer>(ptr)){}
	RandomAccessIterator(const_reference ptr) : _iterT(&ptr){}

	RandomAccessIterator(const RandomAccessIterator& obj) : _iterT(obj._iterT) {}
	RandomAccessIterator(const reverse_iterator<T>& other) : _iterT(other._ptr) {}

	RandomAccessIterator& operator=(const RandomAccessIterator& obj) const { 
		CONST_CAST_IT_THIS->_iterT = obj._iterT;
		return *CONST_CAST_IT_THIS;
		
  	}
	RandomAccessIterator& operator=(const reverse_iterator<T>& obj) const {
		CONST_CAST_IT_THIS->_iterT = obj._ptr;
		return *CONST_CAST_IT_THIS;
	}
	RandomAccessIterator& operator=(const_pointer ptr) const { 
		CONST_CAST_IT_THIS->_iterT = const_cast<pointer>(ptr);
		return *CONST_CAST_IT_THIS;	
  	}

	reference operator* () { return *_iterT; }
	const_reference operator*() const { return *_iterT; }//here

  	pointer operator-> () { return _iterT; }
	const_pointer operator->() const { return _iterT; }

	reference operator[](const std::size_t &pos) { return _iterT[pos]; }
  	const_reference operator[](const std::size_t &pos) const { return _iterT[pos]; }

	RandomAccessIterator& operator++() const {
		++CONST_CAST_IT_THIS->_iterT;
		return *CONST_CAST_IT_THIS;
	}
	RandomAccessIterator operator++(int) const {
		RandomAccessIterator tmp = *CONST_CAST_IT_THIS;
		++CONST_CAST_IT_THIS->_iterT;
		return tmp;
  	}

	RandomAccessIterator& operator--() const {
		--CONST_CAST_IT_THIS->_iterT;
		return *CONST_CAST_IT_THIS;
 	}
	RandomAccessIterator operator--(int) const {
		RandomAccessIterator tmp = *CONST_CAST_IT_THIS;
		--CONST_CAST_IT_THIS->_iterT;
		return tmp;
	}

	RandomAccessIterator& operator+=(difference_type n) const {
		CONST_CAST_IT_THIS->_iterT += n;
		return *CONST_CAST_IT_THIS;
	}
	RandomAccessIterator& operator-=(difference_type n) const {
		CONST_CAST_IT_THIS->_iterT -= n;
		return *CONST_CAST_IT_THIS;
	}

	RandomAccessIterator operator+(difference_type n) const {
		RandomAccessIterator copy = *CONST_CAST_IT_THIS;
		copy += n;
		return copy;
	}
	RandomAccessIterator operator-(difference_type n) const {
		RandomAccessIterator copy = *CONST_CAST_IT_THIS;
		copy -= n;
		return copy;
	}
	difference_type operator-(const RandomAccessIterator& other) const {
		return std::distance(other._iterT, _iterT);
	}
	
	bool operator==(const RandomAccessIterator& other) const {
		return (_iterT == other._iterT);
	}
	bool operator!=(const RandomAccessIterator& other) const {
		return (_iterT != other._iterT);
	}

	bool operator>(const RandomAccessIterator& other) const {
		return (_iterT > other._iterT);
	}
	bool operator<(const RandomAccessIterator& other) const {
		return (_iterT < other._iterT);
	}

	bool operator>=(const RandomAccessIterator& other) const {
		return (_iterT >= other._iterT);
	}
	bool operator<=(const RandomAccessIterator& other) const {
		return (_iterT <= other._iterT);
	}

	friend pointer operator+(const std::size_t& lhs,
                                   const RandomAccessIterator& rhs) {
		return rhs._iterT + lhs;
	}

private:
  pointer _iterT;
	
};


// *************************************************************************
//     Reverse Iterator
// *************************************************************************
template <typename T>
class reverse_iterator {
public:
	typedef typename std::random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;

	template <typename T1>
	friend class RandomAccessIterator;

	reverse_iterator() : _ptr(NULL){}
	~reverse_iterator() {}

	reverse_iterator(const_pointer ptr) : _ptr(const_cast<pointer>(ptr)){}
	reverse_iterator(const_reference ptr) : _ptr(&ptr){}

	reverse_iterator(const reverse_iterator& other) : _ptr(other._ptr) {}
	reverse_iterator(const RandomAccessIterator<T>& other) : _ptr(other._iterT) {}

	pointer base() const { return _ptr; }

	reverse_iterator& operator=(const reverse_iterator& other) const { 
		CONST_CAST_rIT_THIS->_ptr = other._ptr;
		return *CONST_CAST_rIT_THIS;
	}
	reverse_iterator& operator=(const RandomAccessIterator<T>& other) const {
		CONST_CAST_rIT_THIS->_ptr = other._iterT;
		return *CONST_CAST_rIT_THIS;
	}
	reverse_iterator& operator=(const_pointer ptr) const { 
		CONST_CAST_rIT_THIS->_ptr = const_cast<pointer>(ptr) + 1; // here
		return *CONST_CAST_rIT_THIS;	
  	}

	reference operator*() { return *(_ptr - 1); }
	const_reference operator*() const { return *(_ptr - 1); }

	pointer operator->() { return _ptr - 1; }
	const_pointer operator->() const { return _ptr - 1; }

	reference operator[](const std::size_t &pos) {
		long long int	tmp = -1;
		
		if (pos > 0)
			tmp -= pos;
		return _ptr[tmp];
	}
  	const_reference operator[](const std::size_t &pos) const {
		long long int	tmp = -1;
		
		if (pos > 0)
			tmp -= pos;
		return _ptr[tmp];
	}

	reverse_iterator& operator++() const {
		--CONST_CAST_rIT_THIS->_ptr;
		return *CONST_CAST_rIT_THIS;
	}
	reverse_iterator operator++(int) const {
		reverse_iterator tmp = *CONST_CAST_rIT_THIS;
		--CONST_CAST_rIT_THIS->_ptr;
		return tmp;
	}

	reverse_iterator& operator--() const {
		++CONST_CAST_rIT_THIS->_ptr;
		return *CONST_CAST_rIT_THIS;
	}
	reverse_iterator operator--(int) const {
		reverse_iterator tmp = *CONST_CAST_rIT_THIS;
		++CONST_CAST_rIT_THIS->_ptr;
		return tmp;
	}

	reverse_iterator& operator+=(difference_type n) const {
		CONST_CAST_rIT_THIS->_ptr -= n;
		return *CONST_CAST_rIT_THIS;
	}
	reverse_iterator& operator-=(difference_type n) const {
		CONST_CAST_rIT_THIS->_ptr += n;
		return *CONST_CAST_rIT_THIS;
	}

	reverse_iterator operator+(difference_type n) const {
		reverse_iterator copy = *CONST_CAST_rIT_THIS;
		copy += n;
		return copy;
	}
	reverse_iterator operator-(difference_type n) const {
		reverse_iterator copy = *CONST_CAST_rIT_THIS;
		copy -= n;
		return copy;
	}
	difference_type operator-(const reverse_iterator& other) const {
		return std::distance(_ptr, other._ptr);
	}

	bool operator==(const reverse_iterator& other) const {
		return (_ptr == other._ptr);
	}
	bool operator!=(const reverse_iterator& other) const {
		return (_ptr != other._ptr);
	}

	bool operator>(const reverse_iterator& other) const {
		return (_ptr < other._ptr);
	}
	bool operator<(const reverse_iterator& other) const {
		return (_ptr > other._ptr);
	}

	bool operator>=(const reverse_iterator& other) const {
		return (_ptr <= other._ptr);
	}
	bool operator<=(const reverse_iterator& other) const {
		return (_ptr >= other._ptr);
	}

	friend pointer operator+(const std::size_t& lhs,
                                   const reverse_iterator& rhs) {
		long long int	tmp = -1;
		tmp -= lhs;
		return rhs._ptr + tmp;
	}

private:
	pointer _ptr;
};

# define CONST_CAST_rRBT_THIS (const_cast<RBTreeReverseIterator *>(this))
# define CONST_CAST_RBT_THIS (const_cast<RBTreeIterator *>(this))

template <typename T, typename U>
class RBTreeReverseIterator;

// **********************************************************************************
// Red Black Tree Iterator
// **********************************************************************************
template <typename T, typename U>
class RBTreeIterator {
public:
	typedef typename std::bidirectional_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;

	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

	typedef U Node;

private:
	Node* _ptr;

public:
	template <typename T1, typename U1>
	friend class RBTreeReverseIterator;
	
	RBTreeIterator() : _ptr(NULL){}
	
	RBTreeIterator(const Node* ptr) : _ptr(const_cast<Node*>(ptr)){}
	RBTreeIterator(const Node& ptr) : _ptr(&ptr){}
	
	RBTreeIterator(const RBTreeIterator& other) : _ptr(other._ptr){}
	RBTreeIterator(const RBTreeReverseIterator<T, U>& other) : _ptr(other._ptr){}
	
	~RBTreeIterator(){}

	RBTreeIterator& operator=(const RBTreeIterator& other) const { 
		CONST_CAST_RBT_THIS->_ptr = other._ptr;
		return *CONST_CAST_RBT_THIS;
  	}
	RBTreeIterator& operator=(const RBTreeReverseIterator<T, U>& other) const {
		CONST_CAST_RBT_THIS->_ptr = other._ptr;
		return *CONST_CAST_RBT_THIS;
	}
	RBTreeIterator& operator=(const Node* ptr) const { 
		CONST_CAST_RBT_THIS->_ptr = const_cast<Node*>(ptr);
		return *CONST_CAST_RBT_THIS;	
  	}
	
	// template <typename T1, typename U1>
	// friend class RBTreeIterator;
	// template <typename T1, typename U1>
	// RBTreeIterator(const RBTreeIterator<T1, U1>& other) : _ptr(other._ptr){};

	
	reference operator*() { return _ptr->data; }
	reference operator*() const { return _ptr->data; }
	
	pointer operator->() { return &(_ptr->data); }
	pointer operator->() const { return &(_ptr->data); }

	RBTreeIterator& operator++() const {
		CONST_CAST_RBT_THIS->_ptr = successor(_ptr);
		return *CONST_CAST_RBT_THIS;
	}

	RBTreeIterator operator++(int) const {
		RBTreeIterator tmp = *CONST_CAST_RBT_THIS;
		operator++();
		return tmp;
	}

	RBTreeIterator& operator--() const {
		CONST_CAST_RBT_THIS->_ptr = predecessor(_ptr);
		return *CONST_CAST_RBT_THIS;
	}

	RBTreeIterator operator--(int) const {
		RBTreeIterator tmp = *CONST_CAST_RBT_THIS;
		operator--();
		return tmp;
	}

	friend bool operator==(const RBTreeIterator& lhs,
							const RBTreeIterator& rhs) {
		return lhs._ptr == rhs._ptr;
	}
	friend bool operator!=(const RBTreeIterator& lhs,
							const RBTreeIterator& rhs) {
		return lhs._ptr != rhs._ptr;
	}

private:
	Node* getMinElementOnThePath(Node* node) const {
		while (node && node->left) {
			node = node->left;
		}
		return node;
	}

	Node* getMaxElementOnThePath(Node* node) const {
		while (node && node->right) {
			node = node->right;
		}
		return node;
	}

	Node* predecessor(Node* node) const {
		if (node->left) {
			return getMaxElementOnThePath(node->left);
		} else {
			Node* parent = node->parent;
			while (parent && node == parent->left) {
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}
	}

	Node* successor(Node* node) const {
		if (node->right) {
			return getMinElementOnThePath(node->right);
		} else {
			Node* parent = node->parent;
			while (parent && node == parent->right) {
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}
	}
};

/*
 **=========================================================================
 **     Red Black Tree Reverse Iterator
 **=========================================================================
 */
template <typename T, typename U>
class RBTreeReverseIterator {
public:
	typedef typename std::bidirectional_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;

	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

	typedef U Node;

private:
	Node* _ptr;

public:
	template <typename T1, typename U1>
	friend class RBTreeIterator;
	
	RBTreeReverseIterator() : _ptr(NULL){}
	
	RBTreeReverseIterator(const Node* ptr) : _ptr(const_cast<Node*>(ptr)){}
	RBTreeReverseIterator(const Node& ptr) : _ptr(&ptr){}

	RBTreeReverseIterator(const RBTreeReverseIterator& other) : _ptr(other._ptr){}
	RBTreeReverseIterator(const RBTreeIterator<T, U>& other) : _ptr(other._ptr){}
	
	~RBTreeReverseIterator(){}

	RBTreeReverseIterator& operator=(const RBTreeReverseIterator& other) const { 
		CONST_CAST_rRBT_THIS->_ptr = other._ptr;
		return *CONST_CAST_rRBT_THIS;
		
  	}
	RBTreeReverseIterator& operator=(const RBTreeIterator<T, U>& other) const {
		CONST_CAST_rRBT_THIS->_ptr = other._ptr;
		return *CONST_CAST_rRBT_THIS;
	}
	RBTreeReverseIterator& operator=(const Node* ptr) const { 
		CONST_CAST_rRBT_THIS->_ptr = const_cast<Node *>(ptr);
		return *CONST_CAST_rRBT_THIS;	
  	}

	// template <typename T1, typename U1>
	// friend class RBTreeReverseIterator;
	// template <typename T1, typename U1>
	// RBTreeReverseIterator(const RBTreeReverseIterator<T1, U1>& other) : _ptr(other._ptr){}
	// template <typename T1, typename U1>
	// RBTreeReverseIterator(const RBTreeIterator<T1, U1>& other) : _ptr(other._ptr){}



	reference operator*() { return _ptr->data; }
	reference operator*() const { return _ptr->data; }
	
	pointer operator->() { return &(_ptr->data); }
	pointer operator->() const { return &(_ptr->data); }

	RBTreeReverseIterator& operator++() const {
		CONST_CAST_rRBT_THIS->_ptr = predecessor(_ptr);
		return *CONST_CAST_rRBT_THIS;
	}
	RBTreeReverseIterator operator++(int) {
		RBTreeReverseIterator tmp = *CONST_CAST_rRBT_THIS;
		operator++();
		return tmp;
	}

	RBTreeReverseIterator& operator--() {
		CONST_CAST_rRBT_THIS->_ptr = successor(_ptr);
		return *CONST_CAST_rRBT_THIS;
	}

	RBTreeReverseIterator operator--(int) {
		RBTreeReverseIterator tmp = *CONST_CAST_rRBT_THIS;
		operator--();
		return tmp;
	}

	friend bool operator==(const RBTreeReverseIterator& lhs,
							const RBTreeReverseIterator& rhs) {
		return lhs._ptr == rhs._ptr;
	}
	friend bool operator!=(const RBTreeReverseIterator& lhs,
							const RBTreeReverseIterator& rhs) {
		return lhs._ptr != rhs._ptr;
	}

private:
	Node* getMinElementOnThePath(Node* node) const {
		while (node && node->left) {
			node = node->left;
		}
		return node;
	}

	Node* getMaxElementOnThePath(Node* node) const {
		while (node && node->right) {
			node = node->right;
		}
		return node;
	}

	Node* predecessor(Node* node) const {
		if (node->left) {
			return getMaxElementOnThePath(node->left);
		} else {
			Node* parent = node->parent;
			while (parent && node == parent->left) {
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}
	}

	Node* successor(Node* node) const {
		if (node->right) {
			return getMinElementOnThePath(node->right);
		} else {
			Node* parent = node->parent;
			while (parent && node == parent->right) {
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}
	}
};

}

#endif
