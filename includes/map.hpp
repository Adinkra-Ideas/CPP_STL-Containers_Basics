/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:01:18 by euyi              #+#    #+#             */
/*   Updated: 2023/05/17 00:01:19 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <functional>
# include <algorithm> 
# include <iostream>
# include <memory>


# include "./Pair.hpp"
# include "./Algorithm.hpp"
# include "./RBTreeMap.hpp"
# include "./Iterator.hpp"
# include "./IteratorTraits.hpp"
# include "./TypeTraits.hpp"

namespace ft {

template <typename Key, typename T, class Compare = std::less< typename ft::rem_const<Key>::type >,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
public:
	typedef typename ft::rem_const<Key>::type key_type;
	// typedef Key key_type;
	typedef T mapped_type;
	typedef ft::pair<key_type, T> value_type;
	typedef Allocator allocator_type;
	typedef typename allocator_type::size_type size_type;
	typedef Compare key_compare;
	typedef typename ft::RBTreeMap<value_type, key_compare, allocator_type>::iterator iterator;
	typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename ft::RBTreeMap<value_type, key_compare, allocator_type>::const_iterator const_iterator;
	typedef typename ft::RBTreeMap<value_type, key_compare, allocator_type>::reverse_iterator reverse_iterator;
	typedef typename ft::RBTreeMap<value_type, key_compare, allocator_type>::const_reverse_iterator const_reverse_iterator;
	typedef typename allocator_type::template rebind< RBTreeMap<value_type, key_compare, allocator_type> >::other treeAllocator;

	struct value_compare {
  		bool operator() (const value_type& x, const value_type& y) {
			key_compare obj;
			return obj(x.first, y.first);
		}
	};

// **********************************************************************************
// MEMBER FUNCTIONS BEGIN
// **********************************************************************************
	map() : _size(0), _compare(key_compare()), _alloc(allocator_type()),
        	_treeAllocator(treeAllocator()), _rbtree(NULL) {
    	_rbtree = _treeAllocator.allocate(1);
    	_treeAllocator.construct(
        _rbtree, RBTreeMap<value_type, key_compare, allocator_type>());		
  }

private:
	size_type _size;
	key_compare _compare;
	allocator_type _alloc;
	treeAllocator _treeAllocator;
	RBTreeMap<value_type, key_compare, allocator_type>* _rbtree;

public:
	explicit map(const key_compare& comp,
               const allocator_type& alloc = allocator_type())
      : _size(0), _compare(comp), _alloc(alloc), _treeAllocator(treeAllocator()),
        _rbtree(NULL) {
    	_rbtree = _treeAllocator.allocate(1);
    	_treeAllocator.construct(
        	_rbtree, RBTreeMap<value_type, key_compare, allocator_type>());
  }

	template <class InputIt>
	map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
		: _size(0), _compare(comp), _alloc(alloc),
			_treeAllocator(treeAllocator()), _rbtree(NULL) {
		_rbtree = _treeAllocator.allocate(1);
		_treeAllocator.construct(_rbtree, RBTreeMap<value_type, key_compare, allocator_type>());
		insert(first, last);
	}

	map(const map& other)
		: _size(0), _compare(other._compare), _alloc(other._alloc),
			_treeAllocator(treeAllocator()), _rbtree(NULL) {
		*this = other;
	}

	~map() {
		_treeAllocator.destroy(_rbtree);
		_treeAllocator.deallocate(_rbtree, 1);
	}

	map& operator=(const map& other) {
		if (this != &other) {
			if (_rbtree) {
				_treeAllocator.destroy(_rbtree);
				_treeAllocator.deallocate(_rbtree, 1);
			}
			_rbtree = _treeAllocator.allocate(1);
			_treeAllocator.construct(
				_rbtree, RBTreeMap<value_type, key_compare, allocator_type>());
			_size = other._size;
			_compare = other._compare;
			_alloc = other._alloc;
			_treeAllocator = other._treeAllocator;
			*_rbtree = *(other._rbtree);
		}
		return *this;
	}

	allocator_type get_allocator() const { return _alloc; }

// *********************************************
// Element Access
// *********************************************

	mapped_type& at(const key_type& key) {
		iterator res = _rbtree->search(key);
		if (res == end()) {
			throw std::out_of_range("Error: key not found");
		} else {
			return (*res).second;
		}
	}
	const mapped_type& at(const key_type& key) const {
		iterator res = _rbtree->search(key);
		if (res == end()) {
			throw std::out_of_range("Error: key not found");
		} else {
			return (*res).second;
		}
	}

	mapped_type& operator[](const key_type& key) {
		iterator res = _rbtree->search(key);
		if (res == end()) {
			return (*insert(ft::make_pair(key, mapped_type())).first).second;
		} else {
			return (*res).second;
		}
	}

// ****************************************
//     Iterators
// ****************************************
	iterator begin() { return _rbtree->begin(); }
	const_iterator begin() const { return _rbtree->begin(); }

	iterator end() { return _rbtree->end(); } //here
	const_iterator end() const { return _rbtree->end(); }

	reverse_iterator rbegin() { return _rbtree->rbegin(); }
	const_reverse_iterator rbegin() const { return _rbtree->begin(); }

	reverse_iterator rend() { return _rbtree->rend(); }
	const_reverse_iterator rend() const { return _rbtree->rend(); }

// *************************************************
// Capacity
// *************************************************
	bool empty() const { return size() == 0; }
	size_type size() const { return _size; }
	size_type max_size() const { return allocator_type().max_size(); }

// *************************************************
//     Modifiers
// *************************************************
	void clear() {
		_rbtree->clear();
		_size = 0;
	}

	ft::pair<iterator, bool>	insert(const value_type& value) {
		iterator res = find(value.first);
		if (res == end()) {
			res = iterator(_rbtree->insertNode(value));
			_size++;
			return ft::make_pair<iterator, bool>(res, true);
		} else {
			return ft::make_pair<iterator, bool>(res, false);
		}
	}

	iterator insert(iterator, const value_type& value) {
		return (insert(value)).first;
	}

	template <class InputIt>
	void insert(InputIt first, InputIt last,
				typename ft::enable_if<!ft::is_integral<InputIt>::value,
										InputIt>::type* = NULL) {
		while (first != last) {
			insert(*first++);
		}
	}

	void erase(iterator pos,
				typename ft::enable_if<!ft::is_integral<iterator>::value,
										iterator>::type* = NULL) {
		_rbtree->deleteNode((*pos).first);
		_size--;
	}

	void erase(const iterator &firs, iterator last,
				typename ft::enable_if<!ft::is_integral<iterator>::value,
										iterator>::type* = NULL) {
		iterator &first = const_cast<iterator&>(firs);
		
		// backup "first" before while loop
		typedef Nod<value_type> Node;
		typedef typename allocator_type::template rebind<Node>::other node_allocator;
		node_allocator	_nodeAlloc;
		Node			*tmp_node = _nodeAlloc.allocate(1);
		_nodeAlloc.construct(tmp_node, Node(value_type(first->first, first->second)));
		
		// copy key of all nodes-to-be-erased linked from first to last
		// then erase the nodes using their keys
		std::size_t 	dist = std::distance(first, last) > 0 ? std::distance(first, last) : 0;
		typedef typename allocator_type::template rebind<key_type>::other KT_allocator;
		KT_allocator	_ktAlloc;
		key_type		*erase_keys = _ktAlloc.allocate(dist);
		for (std::size_t dist_i = 0; dist_i < dist; ++dist_i) {
			_ktAlloc.construct(erase_keys + dist_i, (*first).first);
			++first;
		}		
		for (std::size_t dist_i = 0; dist_i < dist; ++dist_i) {
			first = find(erase_keys[dist_i]);
			erase(first);
		}
		_ktAlloc.destroy(erase_keys);
		_ktAlloc.deallocate(erase_keys, dist);

		// restore "first"
		ft::RBTreeIterator<value_type, Nod<value_type> >	newIter(tmp_node);
		first = newIter;
		_nodeAlloc.deallocate(tmp_node, 1);
	}

	size_type erase(const key_type& key) {
		iterator pos = find(key);
		if (pos != end()) {
			erase(pos);
			return 1;
		} else {
			return 0;
		}
	}

	void swap(map& other) {
		size_type tmpSize = _size;
		key_compare tmpCompare = _compare;
		allocator_type tmpAlloc = _alloc;
		treeAllocator tmpTreeAllocator = _treeAllocator;
		RBTreeMap<value_type, key_compare, allocator_type>* tmpRbtree = _rbtree;

		_size = other._size;
		_compare = other._compare;
		_alloc = other._alloc;
		_treeAllocator = other._treeAllocator;
		_rbtree = other._rbtree;

		other._size = tmpSize;
		other._compare = tmpCompare;
		other._alloc = tmpAlloc;
		other._treeAllocator = tmpTreeAllocator;
		other._rbtree = tmpRbtree;
	}

// ***************************************
//    Lookup
// ***************************************

	size_type count(const key_type& key) const {
		return static_cast<size_type>(find(key) != end());
	}

  	iterator find(const key_type& key) { return _rbtree->search(key); }
  	const_iterator find(const key_type& key) const { return _rbtree->search(key); }

	ft::pair<iterator, iterator> equal_range(const key_type& key) {
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}
	const ft::pair<const_iterator, const_iterator> equal_range(
		const key_type& key) const {
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}

 	iterator lower_bound(const key_type& key) { return _rbtree->lower_bound(key); }
	const_iterator lower_bound(const key_type& key) const {
		return _rbtree->lower_bound(key);
	}

	iterator upper_bound(const key_type& key) { return _rbtree->upper_bound(key); }
	const_iterator upper_bound(const key_type& key) const {
		return _rbtree->upper_bound(key);
	}

// **************************************
//    Observers
// **************************************
	key_compare key_comp() const { return _compare; }
	value_compare value_comp() const {
		value_compare obj;
		return obj;
	}

// ***********************************
//     Comparison
// ***********************************
	friend bool operator==(const map<key_type, T, Compare, allocator_type>& lhs,
							const map<key_type, T, Compare, allocator_type>& rhs) {
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	friend bool operator!=(const map<key_type, T, Compare, allocator_type>& lhs,
							const map<key_type, T, Compare, allocator_type>& rhs) {
		return !operator==(lhs, rhs);
	}
	friend bool operator<(const map<key_type, T, Compare, allocator_type>& lhs,
							const map<key_type, T, Compare, allocator_type>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
										rhs.end());
	}
	friend bool operator<=(const map<key_type, T, Compare, allocator_type>& lhs,
							const map<key_type, T, Compare, allocator_type>& rhs) {
		return !(operator<(rhs, lhs));
	}
	friend bool operator>(const map<key_type, T, Compare, allocator_type>& lhs,
							const map<key_type, T, Compare, allocator_type>& rhs) {
		return operator<(rhs, lhs);
	}
	friend bool operator>=(const map<key_type, T, Compare, allocator_type>& lhs,
							const map<key_type, T, Compare, allocator_type>& rhs) {
		return !(operator<(lhs, rhs));
	}

};

	template <typename Key, typename T, class Compare, class Alloc>
	void swap( map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) {
			lhs.swap(rhs);
	}

}	// namespace ft

#endif
