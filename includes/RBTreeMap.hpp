#ifndef __RBTREEMAP_HPP__
# define __RBTREEMAP_HPP__

#include "Node.hpp"
#include "Iterator.hpp"

namespace ft {

template <typename T, typename U>
class RBTreeIterator;
template <typename T, typename U>
class RBTreeReverseIterator;

template <typename T, typename Compare, typename Allocator>
class RBTreeMap {
public:
	typedef Nod<T> Node;
	typedef T value_type;
	typedef typename value_type::first_type key_type;
	typedef ft::RBTreeIterator<T, Node> iterator;
	typedef ft::RBTreeIterator<const T, const Node> const_iterator;
	typedef ft::RBTreeReverseIterator<T, Node> reverse_iterator;
	typedef ft::RBTreeReverseIterator<const T, const Node> const_reverse_iterator;

	typedef Allocator allocator_type;
	typedef typename allocator_type::template rebind<Node>::other node_allocator;
	typedef Compare key_compare;

private:
	Node *_superRoot;
	Node *_dummyRoot;
	Node *_root;
	allocator_type _alloc;
	node_allocator _nodeAlloc;
	key_compare _comp;

public:
	RBTreeMap() : _superRoot(NULL), _dummyRoot(NULL), _root(NULL), _alloc(allocator_type()),
				_nodeAlloc(node_allocator()), _comp(key_compare()) {
		_superRoot = _nodeAlloc.allocate(1);
		_nodeAlloc.construct(_superRoot, Node(value_type()));	
		_dummyRoot = _nodeAlloc.allocate(1);
		_nodeAlloc.construct(_dummyRoot, value_type());
		
		_superRoot->flag = SUP_ROOT;
		_dummyRoot->flag = DUM_ROOT;
	}

	RBTreeMap(const RBTreeMap& other) : _superRoot(NULL), _dummyRoot(NULL), _root(NULL), 
		_alloc(allocator_type()), _nodeAlloc(node_allocator()), _comp(key_compare()) {
		_superRoot = _nodeAlloc.allocate(1);
		_nodeAlloc.construct(_superRoot, Node(value_type()));
		_dummyRoot = _nodeAlloc.allocate(1);
		_nodeAlloc.construct(_dummyRoot, value_type());
		_root = clone(other._root, NULL, other._dummyRoot);
		_alloc = other._alloc;
		_nodeAlloc = other._nodeAlloc;
		_comp = other._comp;

		_superRoot->flag = SUP_ROOT;
		_dummyRoot->flag = DUM_ROOT;

		if (_root) {
			_root->parent = _superRoot;
			_superRoot->left = _root;
			Node *minNode = getMinimum(_root);
			_dummyRoot->parent = minNode;
			minNode->left = _dummyRoot;
		}
	}

	~RBTreeMap() {
		clear();
		cleanHelperRoots();
	}

	RBTreeMap &operator=(const RBTreeMap& other) {
		if (this != &other) {
			clear();
			cleanHelperRoots();

			_alloc = other._alloc;
			_nodeAlloc = other._nodeAlloc;
			_comp = other._comp;

			_superRoot = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(_superRoot, Node(value_type()));
			_dummyRoot = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(_dummyRoot, Node(value_type()));
			_root = clone(other._root, NULL, other._dummyRoot);

			if (_root) {
				_root->parent = _superRoot;
				_superRoot->left = _root;
				Node *minNode = getMinimum(_root);
				_dummyRoot->parent = minNode;
				minNode->left = _dummyRoot;
			}
		}
		return *this;
	}


// **********************************
// Clear
// **********************************
public:
	void clear() {
		clearHelper(_root);
		_root = NULL;
	}

private:
	void clearHelper(Node *curr) {
		if (curr == NULL || curr == _dummyRoot) {
			return;
		} else {
			clearHelper(curr->left);
			clearHelper(curr->right);
			_nodeAlloc.destroy(curr);
			_nodeAlloc.deallocate(curr, 1);
		}
	}
	
	void cleanHelperRoots() {
		if (_superRoot) {
			_nodeAlloc.destroy(_superRoot);
			_nodeAlloc.deallocate(_superRoot, 1);
		}
		if (_dummyRoot) {
			_nodeAlloc.destroy(_dummyRoot);
			_nodeAlloc.deallocate(_dummyRoot, 1);
		}
	}

// **********************************
// Clone() creates a new node with
// param1 being the current node from
// where 
// **********************************
public:
	Node *clone(Node *curr, Node *parent, Node *otherDummy) {
		if (curr != NULL && curr != otherDummy) {
			Node *node = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(node, Node(curr->data));
			node->parent = parent;
			node->left = clone(curr->left, node, otherDummy);
			node->right = clone(curr->right, node, otherDummy);
			return node;
		} else {
			return NULL;
		}
	}

// ******************************
// Search
// ******************************
public:
	iterator search(const key_type &key) {
		Node *res = searchHelp(key, _root);
		return res ? iterator(res) : end();
	}

  const_iterator search(const key_type &key) const {
    Node *res = searchHelp(key, _root);
    return res ? const_iterator(res) : end();
  }

private:
	Node *searchHelp(const key_type &key, Node *root) const {
		if (root == NULL || root == _dummyRoot) {
			return NULL;
		} else {
			bool cmpRes = _comp(key, root->data.first);
			if (root->data.first == key) {
				return root;
			} else if (cmpRes) {
				return searchHelp(key, root->left);
			} else {
				return searchHelp(key, root->right);
			}
		}
	}

// ***************************************
// INSERT
// ***************************************
public:
	iterator insertNode(const value_type &data) {
		if (_root != NULL) {
			_root->parent = NULL;
			_dummyRoot->parent->left = NULL;
			_dummyRoot->parent = NULL;
		}
		_superRoot->left = NULL;
		Node *inserted_node = _nodeAlloc.allocate(1);
		_nodeAlloc.construct(inserted_node, Node(data));
		if (_root == NULL) {
			_root = inserted_node;
		} else {
			Node *n = _root;
			while (1) {
				bool cmpRes = _comp(data.first, n->data.first);
				if (data.first == n->data.first) {
					n->data.second = data.second;
					return n;
				} else if (cmpRes) {
					if (n->left == NULL) {
						n->left = inserted_node;
						break;
					} else {
						n = n->left;
					}
				} else {
					if (n->right == NULL) {
						n->right = inserted_node;
						break;
					} else {
						n = n->right;
					}
				}
			}
			inserted_node->parent = n;
		}
		insert_case1(inserted_node);
		_root->parent = _superRoot;
		_superRoot->left = _root;
		Node *minNode = getMinimum(_root);
		minNode->left = _dummyRoot;
		_dummyRoot->parent = minNode;
		return search(data.first);
	}

private:
	void insert_case1(Node *n) {
		if (n->parent == NULL) {
			n->color = BLACK;
		} else {
			insert_case2(n);
		}
	}

	void insert_case2(Node *n) {
		if (n->parent->color == BLACK) {
			return;
		} else {
			insert_case3(n);
		}
	}

	void insert_case3(Node *n) {
		if (uncle(n) && uncle(n)->color == RED) {
			n->parent->color = 0;
			uncle(n)->color = 0;
			grandparent(n)->color = 1;
			insert_case1(grandparent(n));
		} else {
			insert_case4(n);
		}
	}

  	void insert_case4(Node *n) {
		if (n == n->parent->right &&
			(grandparent(n) && n->parent == grandparent(n)->left)) {
			rotate_left(n->parent);
			n = n->left;
		} else if (n == n->parent->left &&
				(grandparent(n) && n->parent == grandparent(n)->right)) {
			rotate_right(n->parent);
			n = n->right;
		}
		insert_case5(n);
	}

	void insert_case5(Node *n) {
		n->parent->color = 0;
		grandparent(n)->color = 1;
		if (n == n->parent->left &&
			(grandparent(n) && n->parent == grandparent(n)->left)) {
			rotate_right(grandparent(n));
		} else {
			rotate_left(grandparent(n));
		}
	}

// ***************************************
// Delete
// ***************************************
public:
	void deleteNode(const key_type &foreign_key) {
		typedef typename value_type::second_type val_type;

		bool 		deleting_root = false;		
		key_type	heir_key_copy;
		val_type	heir_val_copy;
		key_type	key = foreign_key;

		// Checking if the key we're about to delete is root
		if ( key == _root->data.first )
		{
			deleting_root = true;
			Node *replace;
			
			// Using inorder predecessor to search for Heir to Root
			replace = (_root->left && !_root->left->flag) ? getMaximum(_root->left) : NULL ;

			// if no Heir to Root found, use inorder successor to search instead
			if (!replace)
				replace = (_root->right) ? getMinimum(_root->right) : NULL ;

			// If replace is still NULL at this point, it means root is the only
			// Node in our RBBTS linked list. Therefore we delete root and return
			if ( !replace ) {
				_nodeAlloc.destroy(_root);
				_nodeAlloc.deallocate(_root, 1);
				_superRoot->left = NULL;
				_root = NULL;
				return ;				
			}
			
			// backing up Key=>Value pair of 
			heir_key_copy = replace->data.first;
			heir_val_copy = replace->data.second;
			key = heir_key_copy;
		}

		if (_root) {
			_root->parent = NULL;
			_superRoot->left = NULL;
			_dummyRoot->parent->left = NULL;
			_dummyRoot->parent = NULL;
		}
		Node *child;
		Node *n = searchHelp(key, _root);
		if (n == NULL) {
			return;
		}
		if (n->left != NULL && n->right != NULL) {
			Node *pred = getMaximum(n->left);
			bool isLeft = false;
			if (n->parent && n->parent->left == n) {
				isLeft = true;
			}
			Node *tmpParent = n->parent;
			Node *leftChild = n->left;
			Node *rightChild = n->right;
			int tmpColor = n->color;
			_nodeAlloc.destroy(n);
			_nodeAlloc.deallocate(n, 1);
			n = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(n, Node(pred->data));
			if (tmpParent) {
				n->parent = tmpParent;
				if (isLeft) {
				tmpParent->left = n;
				} else {
				tmpParent->right = n;
				}
			}
			if (leftChild) {
				leftChild->parent = n;
				n->left = leftChild;
			}
			if (rightChild) {
				rightChild->parent = n;
				n->right = rightChild;
			}
			n->color = tmpColor;
			n = pred;
		}
		child = n->right == NULL ? n->left : n->right;
		if (n->color == BLACK) {
			n->color = child != NULL ? child->color : 0;
			delete_case1(n);
		}
		replace_node(n, child);
		_nodeAlloc.destroy(n);
		_nodeAlloc.deallocate(n, 1);

		// If we were supposed to delete root node
		// we have deleted node holding root's heir instead
		// So, we now restore Key=>Value of Heir to root node
		if ( deleting_root ) {
			Node *find_old_root = searchHelp(foreign_key, _root);
			find_old_root->data.first = heir_key_copy;
			find_old_root->data.second = heir_val_copy;
		}

		if (_root) {
			_root->parent = _superRoot;
			_superRoot->left = _root;
			Node *minNode = getMinimum(_root);
			_dummyRoot->parent = minNode;
			minNode->left = _dummyRoot;
		}
	}

private:
	void delete_case1(Node *n) {
		if (n->parent == NULL) {
			return;
		} else {
			delete_case2(n);
		}
	}

	void delete_case2(Node *n) {
		if (sibling(n) && sibling(n)->color == RED) {
			n->parent->color = 1;
			sibling(n)->color = 0;
		if (n == n->parent->left)
			rotate_left(n->parent);
		else
			rotate_right(n->parent);
		}
		delete_case3(n);
	}

	void delete_case3(Node *n) {
		if (n->parent->color == BLACK && sibling(n) && sibling(n)->color == BLACK &&
			(sibling(n)->left == NULL || sibling(n)->left->color == BLACK) &&
			(sibling(n)->right == NULL || sibling(n)->right->color == BLACK)) {
			sibling(n)->color = RED;
			delete_case1(n->parent);
		} else {
			delete_case4(n);
		}
	}

	void delete_case4(Node *n) {
		if (n->parent->color == RED && sibling(n) && sibling(n)->color == BLACK &&
			(sibling(n)->left == NULL || sibling(n)->left->color == BLACK) &&
			(sibling(n)->right == NULL || sibling(n)->right->color == BLACK)) {
			sibling(n)->color = 1;
			n->parent->color = 0;
		} else {
			delete_case5(n);
		}
	}

	void delete_case5(Node *n) {
		if (n == n->parent->left && sibling(n) && sibling(n)->color == BLACK &&
			sibling(n)->left && sibling(n)->left->color == RED &&
			(sibling(n)->right == NULL || sibling(n)->right->color == BLACK)) {
			sibling(n)->color = 1;
			sibling(n)->left->color = 0;
			rotate_right(sibling(n));
		} else if (n == n->parent->right && sibling(n) &&
				sibling(n)->color == BLACK &&
				(sibling(n)->right && sibling(n)->right->color == RED) &&
				(sibling(n)->left == NULL || sibling(n)->left->color == BLACK)) {
			sibling(n)->color = 1;
			sibling(n)->right->color = 0;
			rotate_left(sibling(n));
		}
		delete_case6(n);
	}

	void delete_case6(Node *n) {
		if (sibling(n)) {
			sibling(n)->color = n->parent->color;
		}
		n->parent->color = 0;
		if (n == n->parent->left) {
			if (sibling(n) && sibling(n)->right->color == RED) {
				sibling(n)->right->color = 0;
			}
			rotate_left(n->parent);
		} else {
			if (sibling(n) && sibling(n)->left->color == RED) {
				sibling(n)->left->color = 0;
			}
			rotate_right(n->parent);
		}
	}

// *******************************************
// Min / Max Functions
// *******************************************

private:
	Node *getMinimum(Node *root) {
		while (root && root->left != NULL && root->left != _dummyRoot) {
			root = root->left;
		}
		return root;
	}

	Node *getMaximum(Node *root) {
		while (root && root->right != NULL) {
			root = root->right;
		}
		return root;
	}

	Node *getRoot() { return _root; }

	Node *getBegin() {
		if (_root == NULL) {
			return _superRoot;
		}
		Node *node = _root;
		while (node && node->left != NULL && node->left != _dummyRoot) {
			node = node->left;
		}
		return node;
	}

	Node *getBegin() const {
		if (_root == NULL) {
			return _superRoot;
		}
		Node *node = _root;
		while (node && node->left != NULL && node->left != _dummyRoot) {
			node = node->left;
		}
		return node;
	}

// ***************************
// Iterators
// ***************************

public:
	iterator begin() { return iterator(getBegin()); }
	const_iterator begin() const { return const_iterator(getBegin()); }
	iterator end() { return iterator(_superRoot); }
  	const_iterator end() const { return const_iterator(_superRoot); }

	reverse_iterator rbegin() {
		if (_root == NULL) {
			return reverse_iterator(_dummyRoot);
		}
		reverse_iterator rbegin = reverse_iterator(_superRoot);
		++rbegin;
		return rbegin;
	}

	const_reverse_iterator rbegin() const {
		if (_root == NULL) {
			return reverse_iterator(_dummyRoot);
		}
		const_reverse_iterator rbegin = const_reverse_iterator(_superRoot);
		rbegin++;
		return rbegin;
	}

	reverse_iterator rend() { return reverse_iterator(_dummyRoot); }
	const_reverse_iterator rend() const {
		return const_reverse_iterator(_dummyRoot);
	}

	iterator lower_bound(const key_type &key) {
		Node *curr = _root;
		Node *res = _superRoot;

		while (curr && curr != _dummyRoot) {
			bool cmpRes = _comp(key, curr->data.first);
			if (cmpRes || key == curr->data.first) {
				res = curr;
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}
		return iterator(res);
	}

	const_iterator lower_bound(const key_type &key) const {
		Node *curr = _root;
		Node *res = _superRoot;

		while (curr && curr != _dummyRoot) {
			bool cmpRes = _comp(key, curr->data.first);
			if (cmpRes || key == curr->data.first) {
				res = curr;
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}
		return const_iterator(res);
	}

	iterator upper_bound(const key_type &key) {
		Node *curr = _root;
		Node *res = _superRoot;

		while (curr && curr != _dummyRoot) {
			bool cmpRes = _comp(key, curr->data.first);
			if (cmpRes) {
				res = curr;
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}
		return iterator(res);
	}

	const_iterator upper_bound(const key_type &key) const {
		Node *curr = _root;
		Node *res = _superRoot;

		while (curr && curr != _dummyRoot) {
			bool cmpRes = _comp(key, curr->data.first);
			if (cmpRes) {
				res = curr;
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}
		return const_iterator(res);
	}

// *******************************************
// Get Relatives of current working node (*n)
// *******************************************
private:
	Node *grandparent(Node *n) {
		if (n && n->parent && n->parent->parent) {
		return n->parent->parent;
		} else {
		return NULL;
		}
	}
	Node *sibling(Node *n) {
		if (n == NULL || n->parent == NULL) {
		return NULL;
		} else {
		if (n == n->parent->left) {
			return n->parent->right;
		} else {
			return n->parent->left;
		}
		}
	}
	Node *uncle(Node *n) {
		if (n != NULL && n->parent != NULL && n->parent->parent != NULL) {
		return sibling(n->parent);
		} else {
		return NULL;
		}
	}

// **************************************
// Rotation
// **************************************
private:
	void rotate_left(Node *n) {
		if (n == NULL) {
			return;
		}
		Node *r = n->right;
		replace_node(n, r);
		if (n && r) {
			n->right = r->left;
		}
		if (r && r->left != NULL) {
			r->left->parent = n;
		}
		if (r) {
			r->left = n;
		}
		n->parent = r;
	}

	void rotate_right(Node *n) {
		if (n == NULL) {
			return;
		}
		Node *l = n->left;
		replace_node(n, l);
		if (n && l) {
			n->left = l->right;
		}
		if (l && l->right != NULL) {
			l->right->parent = n;
		}
		if (l) {
			l->right = n;
		}
		n->parent = l;
	}

// ************************************
// Replace
// ************************************
private:
	void replace_node(Node *oldn, Node *newn) {
		if (oldn->parent == NULL) {
			_root = newn;
		} else {
		if (oldn == oldn->parent->left) {
			oldn->parent->left = newn;
		} else
			oldn->parent->right = newn;
		}
		if (newn != NULL) {
			newn->parent = oldn->parent;
		}
	}

};

}

#endif
