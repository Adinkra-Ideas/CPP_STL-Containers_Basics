/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:47:45 by euyi              #+#    #+#             */
/*   Updated: 2023/03/05 18:04:45 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include <iostream>
# include <memory>
# include <stdexcept>

# include "assets/Iterator.hpp"
# include "assets/IteratorTraits.hpp"
# include "assets/TypeTraits.hpp"

namespace ft {

template <typename T, class Allocator = std::allocator<T> >
class	vector {
public:
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef ft::RandomAccessIterator<T> iterator;
	typedef const ft::RandomAccessIterator<value_type> const_iterator;
	
	typedef typename Allocator::size_type size_type;
	typedef typename Allocator::pointer pointer;
	
	typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

	typedef ft::reverse_iterator<value_type> reverse_iterator;
	typedef const ft::reverse_iterator<value_type> const_reverse_iterator;

	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::const_pointer const_pointer;

// **********************************************************************************
// MEMBER FUNCTIONS BEGIN
// **********************************************************************************
	vector( void ) : _capacity(0), _size(0), _arr(NULL), _alloc() {
	}

	// Parameterized Constructor
	explicit vector( const Allocator& alloc ) : _capacity(0), _size(0), _arr(NULL), _alloc(alloc) {	
	}

	// **************************************************************
	// Parameterized constructor									*
	// EXPLICIT MEANS, THIS CONSTRUCTOR ONLY						*
	// DOES IMPLICIT CONVERSION ONCE (DURING INSTANCE CONSTRUCTION)	*
	// **************************************************************
	explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) 
				: _capacity(0), _size(0), _arr(NULL), _alloc(alloc) {
		reserve(count);
		_size = count;
		
		for (size_type i = 0; i < count; i++)
			_alloc.construct(_arr + i, value);
  	}

	// **************************************************************
	// Parameterized constructor									*
	// Initialize obj from iterator range first...last				*
	// **************************************************************
	template <class InputIt>
  	vector(InputIt first, InputIt last,
         const  Allocator& alloc = Allocator(),
         typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                InputIt>::type* = NULL)
      : _capacity(0), _size(0), _arr(NULL), _alloc(alloc) {
		difference_type range = std::distance(first, last );
		reserve(range);
		_size = range;
		for (size_type i = 0; i < size(); i++) {
			_alloc.construct(_arr + i, *(first++));
		}
	}
	
	vector(const vector& other) : _capacity(0), _size(0), _arr(NULL)  {
    	// *this = other;
		reserve(other.capacity());
		_size = other.size();
		_alloc = other._alloc;
		for (size_type i = 0; i < size(); i++) {
			_alloc.construct(_arr + i, other._arr[i]);
		}
  	}
	
	~vector( void ) {
		clear();
		_alloc.deallocate(_arr, capacity());
	}

	vector& operator=(const vector& other) {
		clear();
		reserve(other.capacity());
		_size = other.size();
		_alloc = other._alloc;
		for (size_type i = 0; i < size(); i++) {
		_alloc.construct(_arr + i, other._arr[i]);
		}
		return *this;
	}
	
	void assign(size_type count, const value_type& value) {
		if (count > capacity())
			reserve(count);
		for (size_type i = 0; i < count; ++i)
			_alloc.construct(_arr + i, value);
		_size = count;
	}

	template <class InputIt>
  	void assign(InputIt first, InputIt last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = NULL) {
		size_type count = static_cast<size_type>(std::distance(first, last));
		if (count > capacity()) {
			reserve(count);
		}
		for (size_type i = 0; i < count; ++i) {
			_alloc.construct(_arr + i, *(first++));
		}
		_size = count;
	}

	allocator_type get_allocator() const {
		return _alloc;
	}

// **********************************************************************************
// MEMBER FUNCTIONS END	/	Element access BEGINS
// **********************************************************************************
	reference at(size_type pos) {
		if (!(pos < size())) {
			throw std::out_of_range("Error: pos is out of range");
		}
		return _arr[pos];
	}

	const_reference at(size_type pos) const {
		if (!(pos < size())) {
			throw std::out_of_range("Error: pos is out of range");
		}
		return _arr[pos];
	}

	reference operator[](size_type pos) { return _arr[pos]; };
  	const_reference operator[](size_type pos) const { return _arr[pos]; };

	reference front() { return *_arr; };
  	const_reference front() const { return *_arr; };

  	reference back() { return *(_arr + _size - 1); };
  	const_reference back() const { return *(_arr + _size - 1); };

  	value_type* data() { return _arr; }
  	const value_type* data() const { return _arr; };

// **********************************************************************************
// Element access ENDS	/	Iterators BEGINS  
// **********************************************************************************
	iterator begin() { return iterator(_arr); }
	const_iterator begin() const { return const_iterator(_arr); }

	iterator end() { return iterator(_arr + _size); }
	const_iterator end() const { return const_iterator(_arr + _size); }

	reverse_iterator rbegin() { return reverse_iterator(_arr + _size); }
	const_reverse_iterator rbegin() const {
    	return const_reverse_iterator(_arr + _size);
	}

	reverse_iterator rend() { return reverse_iterator(_arr); };
  	const_reverse_iterator rend() const {
		return const_reverse_iterator(_arr);
	}

// **********************************************************************************
// Iterators ENDS	/ Capacity BEGINS  
// **********************************************************************************	
	bool empty( void ) const
	{
		return (size() == 0);
	}

	size_type size( void ) const
	{
		return (_size);
	}

	// Returns the maximum number of elements
	// that is possible for Allocator::allocate()
	// to allocate from this environment 
	size_type max_size() const
	{ 
		return Allocator().max_size();
	}

	// **************************************************************
	// First backs up _arr data to tmp. then destroy _arr,			*
	// then resize _arr element capacity to the newCapacity			*
	// then restores the backup to _arr, then set _capacity			*
	// to newCapacity												*
	// if called from constructor, sets _arr to have a capacity of	*
	// newCapacity, but no value stored in it yet.					*********
	// but if called from function, we will have the previous values		*
	// of _arr intact, but the element capacity increased to newCapacity	*
	// **********************************************************************
	void reserve( size_type newCapacity ) 
	{
		// guards
		if ( newCapacity <= capacity() ) // newCapacity has to already be newNeededCapacity + _capacity
			return;
		if ( newCapacity > max_size() ) // greater than max possible on this environment
			throw std::length_error("Error: N in allocate(N, X) exceeds max alloc size");

		T* tmp = _alloc.allocate(newCapacity);					// allocates uninitialized storage of newCapacity element
		try {
			std::uninitialized_copy(_arr, _arr + _size, tmp);	// copies element from the range [_arr[0], _arr[_size]) to an uninitialized memory area beginning at tmp[0]
		} catch (const std::exception&) {
			_alloc.deallocate(tmp, newCapacity);
			throw std::length_error("reserve() Error: Failed to allocate new memory");
		}
		
		// destroy previous data in _arr
		for (size_type i = 0; i < size(); i++) {
			_alloc.destroy(_arr + i);
		}
	
		// free former memory held by _arr
		_alloc.deallocate(_arr, capacity());
		
		// setting _capacity to the new value
		_capacity = newCapacity;

		// pointing _arr to the new address of tmp
		_arr = tmp;
	}
	
	size_type capacity( void ) const
	{ 
		return (_capacity);
	}	
// **********************************************************************************
// Capacity ENDS	/ Modifiers BEGINS  
// **********************************************************************************
	void clear()
	{
		for (size_type i = 0; i < size(); i++) {
		_alloc.destroy(_arr + i);
		}
		_size = 0;
  	}

	iterator insert(const iterator pos, size_type count, const value_type& value)
	{
		size_type insertIdx = static_cast<size_type>(std::distance(begin(), pos));

		try {
			value_type tmp = value;
			(void) tmp;
		} catch (...) {
			return iterator(_arr + insertIdx);
		}

		// std::cout << "were you called? " <<  << std::endl;
		if ( count == 0 )
			return iterator(_arr + insertIdx);
				
		if ( (size() + count) > capacity() ) {
			int newCapacity =
				size() * 2 >= size() + count ? size() * 2 : size() + count;
			reserve(newCapacity);
		}
		if (empty()) {
			assign(count, value);
		} else {
			for (size_type i = size() - 1; i >= insertIdx; --i) {
				_alloc.construct(_arr + i + count, _arr[i]);
				if (i == 0) break;
			}
			for (size_type i = 0; i < count; ++i) {
				_alloc.construct(_arr + insertIdx++, value);
				_size++;
			}
		}
		return iterator(_arr + insertIdx);
  	}

	iterator insert(const iterator pos, const value_type& value) {
		size_type insertIdx = static_cast<size_type>(std::distance(begin(), pos));
		insert(pos, 1, value);
		return iterator(_arr + insertIdx);
	}

	template <class InputIt>
	iterator insert(const iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
	{
		size_type insertIdx = static_cast<size_type>(std::distance(begin(), pos)); // distance from .begin() to .begin() + pos
		size_type count = static_cast<size_type>(std::distance(first, last));
		if (count < 0)
			throw std::range_error("vector: invalid range");
		if ( count == 0 ) 
			return iterator(_arr + insertIdx);
		
		size_type	tmp_capacity = capacity(); // backup previous capacity before the if(empty()) in downline

		if (size() + count > capacity()) {
			int newCapacity =
			size() * 2 >= size() + count ? size() * 2 : size() + count;
			reserve(newCapacity);
		}

    	if (empty()) {
			T* tmp = _alloc.allocate(tmp_capacity);
			std::uninitialized_copy(_arr, _arr + _size, tmp);
			try{
				assign(first, last);
				_alloc.deallocate(tmp, tmp_capacity);
			} catch (...) {
				_alloc.deallocate(_arr, capacity());
				_capacity = tmp_capacity;
				_arr = tmp;
				throw ;
			}	
   	 	} else {
      		for (size_type i = size() - 1; i >= insertIdx; --i) {
       			_alloc.construct(_arr + i + count, _arr[i]);
        		if (i == 0)
					break;
      			}
			for (size_type i = 0; i < count; ++i) {
				_alloc.construct(_arr + insertIdx++, *first++);
				_size++;
			}
    	}
		return iterator(_arr + insertIdx);
  	}

	iterator erase(iterator pos) {
    	size_type deletedIndex = static_cast<size_type>(std::distance(begin(), pos));
    	for (size_type i = deletedIndex; i < size() - 1; ++i) {
     		_alloc.construct(_arr + i, _arr[i + 1]);
		}
		_alloc.destroy(_arr + size() - 1);
    	_size--;
    	return iterator(_arr + deletedIndex);
  	}
	  //   "     " 
	// |1|2|3|4|5|6|7|8|9|
	iterator erase(iterator first, iterator last) {
    	if (first == last)
      		return last;
    	size_type deletionStartIndex = static_cast<size_type>(std::distance(begin(), first)); //2
    	size_type valueToMoveIndex = static_cast<size_type>(std::distance(begin(), last)); //5
    	size_type count = valueToMoveIndex - deletionStartIndex; // 3

    	for (size_type i = deletionStartIndex; valueToMoveIndex < size(); i++) {
     		_alloc.construct(_arr + i, _arr[valueToMoveIndex++]);
    	}
		for (size_type i = size() - count; i < size(); i++) {
			_alloc.destroy(_arr + i);
		}
			_size -= count;
		return iterator(_arr + deletionStartIndex);
	}

	void push_back(const value_type& value) {
    	if (size() == capacity()) {
			int newCapacity = size() * 2 >= size() + 1 ? size() * 2 : size() + 1;
			reserve(newCapacity);
		}
		_alloc.construct(_arr + _size, value);
		_size++;
  	}

	void pop_back() {
		_alloc.destroy(_arr + size() - 1);
		_size--;
	}

	void resize(size_type count, value_type value = value_type()) {
		if (count > max_size() )
			throw std::length_error("Error: resize() count exceeds max alloc size");
    	if (count <= size()) {
      		for (size_type i = count; i < size(); ++i) {
				_alloc.destroy(_arr + i);
      		}
		} else {
			if ( count > capacity() ) {//here
				int newCapacity =
				size() * 2 >= count ? size() * 2 : count;
				reserve(newCapacity);
			}
			for (size_type i = size(); i < count; ++i) {
				push_back(value);
			}
		}
		_size = count;
	}

	void swap(vector& other) {
		size_type tmpCapacity = _capacity;
		size_type tmpSize = _size;
		pointer tmpArr = _arr;
		allocator_type tmpAlloc = _alloc;

		_capacity = other._capacity;
		_size = other._size;
    	_arr = other._arr;
    	_alloc = other._alloc;

		other._capacity = tmpCapacity;
		other._size = tmpSize;
		other._arr = tmpArr;
		other._alloc = tmpAlloc;
	}
// **********************************************************************************
// Modifiers ENDS	/ Non-member functions BEGINS
// **********************************************************************************
	friend bool operator==(const vector<value_type, allocator_type>& lhs,
                         const vector<value_type, allocator_type>& rhs) {
    	size_t i = 0, j = 0;
    	while (i < lhs.size() && j < rhs.size()) {
      		if (lhs._arr[i++] != rhs._arr[j++]) {
        		return false;
      		}
    	}
    	return i == lhs.size() && j == rhs.size();
	}

	friend bool operator!=(const vector<value_type, allocator_type>& lhs,
                         const vector<value_type, allocator_type>& rhs) {
    	return !operator==(lhs, rhs);
	}

	friend bool operator<(const vector<value_type, allocator_type>& lhs,
                        const vector<value_type, allocator_type>& rhs) {
		size_type i = 0;
    	while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i]) {
      		i++;
    	}
		return (i != rhs.size() && (i == lhs.size() || lhs._arr[i] < rhs._arr[i]));
	}

	friend bool operator<=(const vector<value_type, allocator_type>& lhs,
                         const vector<value_type, allocator_type>& rhs) {
		size_type i = 0;
		while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i]) {
			i++;
		}
		return (i == lhs.size() && i == rhs.size()) ||
			(i != rhs.size() && (i == lhs.size() || lhs._arr[i] < rhs._arr[i]));
	}

	friend bool operator>(const vector<value_type, allocator_type>& lhs,
							const vector<value_type, allocator_type>& rhs) {
		size_type i = 0;
    	while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i]) {
			i++;
		}
		return (i != lhs.size() && (i == rhs.size() || rhs._arr[i] < lhs._arr[i]));
	}

	friend bool operator>=(const vector<value_type, allocator_type>& lhs,
							const vector<value_type, allocator_type>& rhs) {
		size_type i = 0;
		while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i]) {
			i++;
		}
		return (i == rhs.size() && i == lhs.size()) ||
			(i != lhs.size() && (i == rhs.size() || rhs._arr[i] < lhs._arr[i]));
	}

private:
	size_type		_capacity;
	size_type		_size;
	pointer			_arr;
	allocator_type	_alloc;
};


template <typename value_type, class allocator_type >
void swap(vector<value_type, allocator_type>& lhs,
					vector<value_type, allocator_type>& rhs) {
		lhs.swap(rhs);
}

} //namespace ft

#endif
