#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

# include <iostream>


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

	RandomAccessIterator(pointer ptr) : _iterT(ptr){}
	RandomAccessIterator(const_reference ptr) : _iterT(&ptr){}

	RandomAccessIterator(const RandomAccessIterator& obj) : _iterT(obj._iterT) {}
	RandomAccessIterator(const reverse_iterator<T>& other) : _iterT(other._ptr) {}

	// for if this instance is RandomAccessIterator<const typename> 
	// and copied other is RandomAccessIterator<typename>
	template <typename U>
	friend class RandomAccessIterator;
	template <typename U>
	RandomAccessIterator(const RandomAccessIterator<U>& obj) : _iterT(obj._iterT) {}
	// template <typename U>
	// RandomAccessIterator(const reverse_iterator<U>& obj) : _iterT(obj._ptr) {}

	RandomAccessIterator& operator=(const RandomAccessIterator& obj) {
		_iterT = obj._iterT;
		return *this;
		
  	}
	RandomAccessIterator& operator=(const reverse_iterator<T>& obj) {
		_iterT = obj._ptr;
		return *this;
	}
	RandomAccessIterator& operator=(pointer ptr) { 
		_iterT = ptr;
		return *this;	
  	}

	reference operator* () { return *_iterT; }
	const_reference operator*() const { return *_iterT; }

  	pointer operator-> () { return _iterT; }
	const_pointer operator->() const { return _iterT; }

	reference operator[](const std::size_t &pos) { return _iterT[pos]; }
  	const_reference operator[](const std::size_t &pos) const { return _iterT[pos]; }

	RandomAccessIterator& operator++() {
		++_iterT;
		return *this;
	}
	RandomAccessIterator operator++(int) {
		RandomAccessIterator tmp = *this;
		++_iterT;
		return tmp;
  	}

	RandomAccessIterator& operator--() {
		--_iterT;
		return *this;
 	}
	RandomAccessIterator operator--(int) {
		RandomAccessIterator tmp = *this;
		--_iterT;
		return tmp;
	}

	RandomAccessIterator& operator+=(difference_type n) {
		_iterT += n;
		return *this;
	}
	RandomAccessIterator& operator-=(difference_type n) {
		_iterT -= n;
		return *this;
	}

	RandomAccessIterator operator+(difference_type n){
		RandomAccessIterator copy = *this;
		copy += n;
		return copy;
	}
	RandomAccessIterator operator-(difference_type n) {
		RandomAccessIterator copy = *this;
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

	template <typename U>
	bool operator==(const RandomAccessIterator<U>& other) const {
		return (_iterT == other._iterT);
	}
	template <typename U>
	bool operator!=(const RandomAccessIterator<U>& other) const {
		return (_iterT != other._iterT);
	}
	template <typename U>
	bool operator>(const RandomAccessIterator<U>& other) const {
		return (_iterT > other._iterT);
	}
	template <typename U>
	bool operator<(const RandomAccessIterator<U>& other) const {
		return (_iterT < other._iterT);
	}
	template <typename U>
	bool operator>=(const RandomAccessIterator<U>& other) const {
		return (_iterT >= other._iterT);
	}
	template <typename U>
	bool operator<=(const RandomAccessIterator<U>& other) const {
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

	reverse_iterator(pointer ptr) : _ptr(ptr){}
	reverse_iterator(const_reference ptr) : _ptr(&ptr){}

	reverse_iterator(const reverse_iterator& other) : _ptr(other._ptr) {}
	reverse_iterator(const RandomAccessIterator<T>& other) : _ptr(other._iterT) {}

	// for if this instance is reverse_iterator<const typename> 
	// and copied other is reverse_iterator<typename>
	template <typename U>
	friend class reverse_iterator;
	template <typename U>
	reverse_iterator(const reverse_iterator<U>& other) : _ptr(other._ptr) {}

	pointer base() const { return _ptr; }

	reverse_iterator& operator=(const reverse_iterator& other) {
		_ptr = other._ptr;
		return *this;
	}
	reverse_iterator& operator=(const RandomAccessIterator<T>& other){
		_ptr = other._iterT;
		return *this;
	}
	reverse_iterator& operator=(pointer ptr) { 
		_ptr = ptr + 1;
		return *this;	
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

	reverse_iterator& operator++() {
		--_ptr;
		return *this;
	}
	reverse_iterator operator++(int) {
		reverse_iterator tmp = *this;
		--_ptr;
		return tmp;
	}

	reverse_iterator& operator--(){
		++_ptr;
		return *this;
	}
	reverse_iterator operator--(int) {
		reverse_iterator tmp = *this;
		++_ptr;
		return tmp;
	}

	reverse_iterator& operator+=(difference_type n) {
		_ptr -= n;
		return *this;
	}
	reverse_iterator& operator-=(difference_type n) {
		_ptr += n;
		return *this;
	}

	reverse_iterator operator+(difference_type n) {
		reverse_iterator copy = *this;
		copy += n;
		return copy;
	}
	reverse_iterator operator-(difference_type n) {
		reverse_iterator copy = *this;
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

	template <typename U>
	bool operator==(const reverse_iterator<U>& other) const {
		return (_ptr == other._ptr);
	}
	template <typename U>
	bool operator!=(const reverse_iterator<U>& other) const {
		return (_ptr != other._ptr);
	}
	template <typename U>
	bool operator>(const reverse_iterator<U>& other) const {
		return (_ptr < other._ptr);
	}
	template <typename U>
	bool operator<(const reverse_iterator<U>& other) const {
		return (_ptr > other._ptr);
	}
	template <typename U>
	bool operator>=(const reverse_iterator<U>& other) const {
		return (_ptr <= other._ptr);
	}
	template <typename U>
	bool operator<=(const reverse_iterator<U>& other) const {
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

	// // We need a guarantee that the value type sent from
	// // RBTreeMap() through T is always non-constant
	// // Therefore, we have to recreate the value_type from T
	// typedef typename T::first_type key_type;
	// typedef typename T::second_type val_type;
	// typedef ft::pair<key_type, val_type> m_value_type;
	// //m_Node is always guaranteed to be a non-constant
	// // same as ft::map::erase<>::Node
	// typedef Nod<m_value_type> m_Node;
	// void destroyTmpNode( const m_Node* ptr ) {
	// 	// This empty overload is necessary to divert 
	// 	// the compiler's attention from thinking that
	// 	// the 'void deleteTmp( m_Node* ptr ){}' method
	// 	// will be called if m_Node AKA std::remove_const<T>::type
	// 	// were to be a const T.
	// }
	// void destroyTmpNode( m_Node* ptr ) {
	// 	if ( ptr != NULL && ptr->flag == true ) {
	// 		ptr->flag = false;
	// 		typedef class std::allocator<m_Node> node_allocator;
	// 		node_allocator	_nodeAlloc;
	// 		_nodeAlloc.destroy(ptr);
	// 		_nodeAlloc.deallocate(ptr, 1);
	// 	}
	// }

public:
	template <typename T1, typename U1>
	friend class RBTreeReverseIterator;
	
	RBTreeIterator() : _ptr(NULL){}
	
	RBTreeIterator(Node* ptr) : _ptr(ptr){}
	RBTreeIterator(const Node& ptr) : _ptr(&ptr){}
	
	RBTreeIterator(const RBTreeIterator& other) : _ptr(other._ptr){}
	RBTreeIterator(const RBTreeReverseIterator<T, U>& other) : _ptr(other._ptr){}
	
	~RBTreeIterator(){
		// destroyTmpNode(_ptr);
	}

	template <typename T1, typename U1>
	friend class RBTreeIterator ;
	template <typename T1, typename U1>
	RBTreeIterator(const RBTreeIterator<T1, U1>& obj) : _ptr(obj._ptr) {}

	RBTreeIterator& operator=(const RBTreeIterator& other) { 
		_ptr = other._ptr;
		return *this;
  	}
	RBTreeIterator& operator=(const RBTreeReverseIterator<T, U>& other) {
		_ptr = other._ptr;
		return *this;
	}
	RBTreeIterator& operator=(Node* ptr) { 
		_ptr = ptr;
		return *this;	
  	}
	
	reference operator*() { return _ptr->data; }
	reference operator*() const { return _ptr->data; }
	
	pointer operator->() { return &(_ptr->data); }
	pointer operator->() const { return &(_ptr->data); }

	RBTreeIterator& operator++() {
		_ptr = successor(_ptr);
		return *this;
	}
	RBTreeIterator operator++(int) {
		RBTreeIterator tmp = *this;
		operator++();
		return tmp;
	}

	RBTreeIterator& operator--() {
		_ptr = predecessor(_ptr);
		return *this;
	}
	RBTreeIterator operator--(int) {
		RBTreeIterator tmp = *this;
		operator--();
		return tmp;
	}

	bool operator==(const RBTreeIterator& other) const {
		return _ptr == other._ptr;
	}
	bool operator!=(const RBTreeIterator& other) const {
		return _ptr != other._ptr;
		// this idea of returning ptr might be looked into
	}

	template <typename T1, typename U1>
	bool operator==(const RBTreeIterator<T1, U1>& other) const {
		return _ptr == other._ptr;
	}
	template <typename T1, typename U1>
	bool operator!=(const RBTreeIterator<T1, U1>& other) const {
		return _ptr != other._ptr;
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
		if (node->flag == DUM_ROOT) {	//we're in dummy root. We need to restart from the Greatest Key
			Node* m_parent = node->parent;
			while (m_parent && node == m_parent->left)
			{
				node = m_parent;
				if ( node->flag == SUP_ROOT)		// We found Super root using its flag
					return getMaxElementOnThePath(node->left);
				else
					m_parent = m_parent->parent;
			}
		}
		
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
		if (node->flag == SUP_ROOT) {	// we're in Super root. We need to restart from the smallest Key
			return getMinElementOnThePath(node->left)->parent;
		}

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
	
	RBTreeReverseIterator(Node* ptr) : _ptr(ptr){}
	RBTreeReverseIterator(const Node& ptr) : _ptr(&ptr){}

	RBTreeReverseIterator(const RBTreeReverseIterator& other) : _ptr(other._ptr){}
	RBTreeReverseIterator(const RBTreeIterator<T, U>& other) : _ptr(other._ptr){
		--_ptr;
	}
	
	~RBTreeReverseIterator(){}

	RBTreeReverseIterator& operator=(const RBTreeReverseIterator& other) { 
		_ptr = other._ptr;
		return *this;
		
  	}
	RBTreeReverseIterator& operator=(const RBTreeIterator<T, U>& other) {
		_ptr = other._ptr;
		--_ptr;
		return *this;
	}
	RBTreeReverseIterator& operator=(Node* ptr) { 
		_ptr = ptr;
		return *this;	
  	}

	template <typename T1, typename U1>
	friend class RBTreeReverseIterator;
	template <typename T1, typename U1>
	RBTreeReverseIterator(const RBTreeReverseIterator<T1, U1>& other) : _ptr(other._ptr){}
	// template <typename T1, typename U1>
	// RBTreeReverseIterator(const RBTreeIterator<T1, U1>& other) : _ptr(other._ptr){}

	RBTreeIterator<T, U> base() { 
		RBTreeReverseIterator tmp = *this;
		--tmp;
		return tmp;	
	}

	reference operator*() { return _ptr->data; }
	reference operator*() const { return _ptr->data; }
	
	pointer operator->() { return &(_ptr->data); }
	pointer operator->() const { return &(_ptr->data); }

	RBTreeReverseIterator& operator++() {
		_ptr = predecessor(_ptr);
		return *this;
	}
	RBTreeReverseIterator operator++(int) {
		RBTreeReverseIterator tmp = *this;
		operator++();
		return tmp;
	}

	RBTreeReverseIterator& operator--() {
		_ptr = successor(_ptr);
		return *this;
	}

	RBTreeReverseIterator operator--(int) {
		RBTreeReverseIterator tmp = *this;
		operator--();
		return tmp;
	}

	bool operator==(const RBTreeReverseIterator& other) const {
		return _ptr == other._ptr;
	}
	bool operator!=(const RBTreeReverseIterator& other) const {
		return _ptr != other._ptr;
	}

	template <typename T1, typename U1>
	bool operator==(const RBTreeReverseIterator<T1, U1>& other) const {
		return _ptr == other._ptr;
	}
	template <typename T1, typename U1>
	bool operator!=(const RBTreeReverseIterator<T1, U1>& other) const {
		return _ptr != other._ptr;
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
