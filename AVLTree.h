#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

// Exceptions
class AVLTreeExcpetion : public std::exception {};
class DataNotFound : public std::exception {};

// class: AVL node															   
// Description: the base unit of an AVL Tree. it stores a key and data of a tree 
//				element.                                                  
//				(the type of key can be different from the type of the data)   
// Properties:                                                                 
//		K: type of key.                                                        
// 		T: type of data.                                                       
//		height: the height of the current node.                                
//		balance: the difference between the left and right child heights.      
//		parent: the parent node in the tree.                                   
template <class K, class T>
class AVLnode {
	K key;
	T data;
	int balance_;
	int height_;
public:
	AVLnode<K, T> *left_, *right_, *parent_;
	
	/* C-tor */
	AVLnode<K, T>(AVLnode<K, T> *p) : balance_(0), height_(0), left_(NULL), 
		right_(NULL), parent_(p) { }
	AVLnode<K, T>(K key, T data, AVLnode<K, T> *p) : key(key), data(data), 
		balance_(0), height_(0), left_(NULL), right_(NULL), parent_(p) {}

	/* D-tor */
	~AVLnode() { }

	/* Get functions */
	/* all this function Run time efficiency is O(1)*/
	K getKey() {
		return this->key;
	}
	const K getKey() const {
		return this->key;
	}
	T getData() {
		return this->data;
	}
	const T getData() const {
		return this->data;
	}
	int getHeight() const {
		return height_;
	}
	int getBalance() const {
		return balance_;
	}
	const AVLnode<K, T>* getLeft() const {
		return left_;
	}
	const AVLnode<K, T>* getRight() const {
		return right_;
	}
	const AVLnode<K, T>* getParent() const {
		return parent_;
	}

	/* Set functions */
	/* all this function Run time efficiency is O(1)*/
	void setKey(K key) {
		this->key = K(key);
	}
	void setData(T newData) {
		this->data = newData;
	}
	void setBalanc(int newBalacne) {
		balance_ = newBalacne;
	}
	void setHeight(int newHeight) {
		height_ = newHeight;
	}
};

/* AVL tree */
/*
K must implement -
	* copy c'tor
	* operator <
	* d'cot
	* operator =
T must implement -
	* copy c'tor
	* d'ctor
	* operator =
*/

/* AVLTree
Data structer that stores AVL tree.
K - the type of the keys in the tree.
T - the type of the values in the tree.
*/
template <class K, class T>
class AVLTree {
private:
	AVLnode<K, T> *root_;
	int size_;

	/*
	isTwoValuesEquals
	the function check if two given keys are equals
	*/
	bool isTwoValuesEquals(const K value1, const K value2) const {
		return ((! (value1 < value2) && !(value2 < value1)));
	}
	/*
	isFirstValueLessThan
	the function check if the first value is less than the second value
	*/
	bool isFirstValueLessThan(const K value1, const K value2) const {
		return (value1 < value2);
	}
	/*
	isFirstValuesLessOrEqaulThan
	the function check if the first value less or equals to the second value
	*/
	bool isFirstValuesLessOrEqaulThan(const K value1, const K value2) const {
		return isTwoValuesEquals(value1, value2) ||
			isFirstValueLessThan(value1, value2);
	}
	/*
	searchInTreeInternal
	the function search and return node of the tree by given key.
	if the key doesn't exists in the tree, the function return NULL.
	Run time efficiency is O(logn), when the n is the amount of the nodes in the tree.
	*/
	AVLnode<K, T>* searchInTreeInternal(const K key) const {
		AVLnode<K, T>* temp = root_;
		while (temp != NULL) {
			if (isTwoValuesEquals(temp->getKey(), key))
				return temp;

			temp = isFirstValuesLessOrEqaulThan(temp->getKey(), key) ? temp->right_ : temp->left_;
		}

		return NULL;
	}
	/*
	rotateLeft
	the function rotate left the given node.
	Run time efficiency is O(1).
	*/
	AVLnode<K, T>* rotateLeft(AVLnode<K, T> *b) {
		AVLnode<K, T> *a = b->left_;
		a->parent_ = b->parent_;
		b->left_ = a->right_;

		if (b->left_ != NULL)
			b->left_->parent_ = b;

		a->right_ = b;
		b->parent_ = a;

		if (a->parent_ != NULL) {
			if (a->parent_->right_ == b) {
				a->parent_->right_ = a;
			}
			else {
				a->parent_->left_ = a;
			}
		}

		a->setHeight(height(a));
		b->setHeight(height(b));

		setBalance(b);
		setBalance(a);

		return a;
	}
	/*
	rotateRight
	the function rotate rght the given node.
	Run time efficiency is O(1).
	*/
	AVLnode<K, T>* rotateRight(AVLnode<K, T> *b) {
		AVLnode<K, T> *a = b->right_;
		a->parent_ = b->parent_;
		b->right_ = a->left_;

		if (b->right_ != NULL)
			b->right_->parent_ = b;

		a->left_ = b;
		b->parent_ = a;


		if (a->parent_ != NULL) {
			if (a->parent_->right_ == b)
				a->parent_->right_ = a;
			else
				a->parent_->left_ = a;
		}

		b->setHeight(height(b));
		a->setHeight(height(a));

		setBalance(b);
		setBalance(a);


		return a;
	}
	/*
	rotateLeftThenRight
	the function rotate right the given node, and then rotate left.
	Run time efficiency is O(1).
	*/
	AVLnode<K, T>* rotateRightThanLeft(AVLnode<K, T> *n) {
		n->left_ = rotateRight(n->left_);
		return rotateLeft(n);
	}
	/*
	rotateRightThenLeft
	the function rotate left the given node, and then rotate right.
	Run time efficiency is O(1).
	*/
	AVLnode<K, T>* rotateLeftThanRight(AVLnode<K, T> *n) {
		n->right_ = rotateLeft(n->right_);
		return rotateRight(n);
	}
	/*
	getNextInOrderSearch
	the function get node and given key, and return the following node after
	the key in order search.
	Run time efficiency is O(logn), when n is the amount of the nodes in the trees.
	*/
	AVLnode<K, T>* getNextInOrderSearch(AVLnode<K, T>* n, K key) {
		if (n == NULL) {
			return NULL;
		}

		AVLnode<K, T>* leftRes = getNextInOrderSearch(n->left_, key);
		if (leftRes != NULL)
			return leftRes;
		if (isFirstValueLessThan(key, n->getKey()))
			return n;
		return getNextInOrderSearch(n->right_, key);
	}
	void rebalance(AVLnode<K, T> *n, bool calcHeight = false) {
		if (calcHeight) {
			if (n != NULL) {
				n->setHeight(height(n));
			}
		}

		setBalance(n);

		if (n->getBalance() >= 2) {
			// Left

			if (n->left_->getBalance() >= 0)
				n = rotateLeft(n);
			else
				n = rotateRightThanLeft(n);
		}
		else if (n->getBalance() <= -2) {
			// Right

			if (n->right_->getBalance() <= 0)
				n = rotateRight(n);
			else
				n = rotateLeftThanRight(n);
		}

		if (n->parent_ != NULL) {
			rebalance(n->parent_);
		}
		else {
			root_ = n;
		}
	}
	int height(AVLnode<K, T> *n) const {
		if (n == NULL)
			return -1;

		int left = height(n->left_);
		int right = height(n->right_);
		if (left > right)
			return 1 + left;
		return 1 + right;
	}
	void setBalance(AVLnode<K, T> *n) {
		if (n == NULL)
			return;

		int lHeight = n->left_ != NULL ? n->left_->getHeight() +1 : 0;
		int lRight = n->right_ != NULL ? n->right_->getHeight() +1 : 0;
		if (lHeight > lRight)
			n->setHeight(lHeight);
		else
			n->setHeight(lRight);

		n->setBalanc(lHeight - lRight);
	}
	/*
	swapNodeKeyAndData
	the function get two nodes and swap the keys and the data of them.
	Run time efficiency is O(1).
	*/
	void swapNodeKeyAndData(AVLnode<K, T>* w, AVLnode<K, T>* t) {
		T temp = w->getData();
		w->setData(t->getData());
		t->setData(temp);

		K tempKey = w->getKey();
		w->setKey(t->getKey());
		t->setKey(tempKey);
	}
	/*
	removeLeftOrMaxOneSon
	the function get node that has zero or one exactly children.
	the function remove the node from the tree.
	If the node has one child, it will be passed to the node parent.
	Run time efficiency is O(1).
	The function return true, if the remove succeed.
	*/
	bool removeLeftOrMaxOneSon(AVLnode<K, T>* t) {
		bool leftExists = t->left_ != NULL,
			rightExists = t->right_ != NULL;

		if (!leftExists && !rightExists) {
			removeLeaf(t);
			return true;
		}
		if ((leftExists && !rightExists) || (!leftExists && rightExists)) {
			removeNodeWithOnlyOneSon(t);
			return true;
		}

		return false;
	}
	/*
	removeLeaf
	the function remove leaf from the tree.
	Run time efficiency is O(1).
	*/
	void removeLeaf(AVLnode<K, T> *n) {
		AVLnode<K, T>* t = n->parent_;
		if (t == NULL) {
			// In case of the n is the root
			delete n;
			root_ = NULL;
			return;
		}
		if (t->left_ == n) {
			delete t->left_;
			t->left_ = NULL;
		}
		else {
			delete t->right_;
			t->right_ = NULL;
		}
	}
	/*
	removeNodeWithOnlyOneSon
	the function remove node with one children from the tree.
	Run time efficiency is O(1).
	*/
	void removeNodeWithOnlyOneSon(AVLnode<K, T> *n) {
		AVLnode<K, T>* t = n->parent_;
		if (t == NULL) {
			if (n->left_ != NULL)
				root_ = n->left_;
			else
				root_ = n->right_;

			root_->parent_ = NULL;
			delete n;
			return;
		}

		bool isTLeft = t->left_ == n;
		AVLnode<K, T>* son = (n->left_ == NULL && n->right_ != NULL) ? n->right_ : n->left_;
		if (son == NULL)
			return;

		if (isTLeft)
			t->left_ = son;
		else
			t->right_ = son;
		son->parent_ = t;

		n->left_ = NULL;
		n->right_ = NULL;
		n->parent_ = NULL;
		delete n;

		return;
	}
	/*
	removeRightLeafsInternal
	the function remove the given number of the leafs from the right of the tree.
	Run time efficiency is O(n), when n is number of nodes in the tree.
	*/
	void removeRightLeafsInternal(AVLnode<K, T>* n, int counter) {
		if (counter == 0)
			return;
		if (n->right_ != NULL)
			removeRightLeafsInternal(n->right_, counter);
		else {
			removeLeaf(n);
			size_--;
			return;
		}

		removeRightLeafsInternal(n->left_, counter - 1);
	}
	/*
	populateTreeInternal
	the function get array of keys and values and insert it to the tree in
	left order algoritam.
	The function doesn't free the previous data in the nodes.
	input:
	@n- current node of the tree.
	@keyArr - the array of sorted keys.
	@valueArr - the values array the synchronized with the keyArr order.
	@iPointer - the current place of the arrays to be placed in the node.
	@size - the amount of the nodes.
	Run time efficiency is O(n), when n is number of nodes in the tree.
	*/
	void populateTreeInternal(AVLnode<K, T>* n, K keyArr[], T valueArr[], int* iPointer, int size) {
		if (n == NULL || iPointer == NULL || *iPointer == size - 1)
			return;
		if (n->left_ != NULL)
			populateTreeInternal(n->left_, keyArr, valueArr, iPointer, size);

		n->setKey(keyArr[*iPointer]);
		n->setData(valueArr[*iPointer]);
		(*iPointer)++;

		if (n->right_ != NULL)
			populateTreeInternal(n->right_, keyArr, valueArr, iPointer, size);
	}
	/*
	getKeysInorder
	the function gets: node, key array and pointer to int that indicates
	the empty place in the array. With this data the function populate the array
	with keys from the tree in inorder search.
	Run time efficiency is O(n), when n is number of nodes in the tree(including the new nodes).
	*/
	void getKeysInorder(AVLnode<K, T>* n, K* keyArr, int* iPointer) const {
		if (n == NULL)
			return;

		getKeysInorder(n->left_, keyArr, iPointer);
		keyArr[(*iPointer)++] = K(n->getKey());
		getKeysInorder(n->right_, keyArr, iPointer);
	}
	/*
	getDataInOrderInternal
	the function gets: node, T array and pointer to int that indicates
	the empty place in the array. With this data the function populate the array
	with data from the tree in inorder search.
	Run time efficiency is O(n), when n is number of nodes in the tree(including the new nodes).
	*/
	void getDataInOrderInternal(AVLnode<K, T>* n, T* arr, int* iPointer) {
		if (n == NULL)
			return;

		getDataInOrderInternal(n->left_, arr, iPointer);
		arr[(*iPointer)++] = n->getData();
		getDataInOrderInternal(n->right_, arr, iPointer);
	}
	void releaseAllNodes(AVLnode<K, T>* n) {
		if (n == NULL)
			return;
		releaseAllNodes(n->left_);
		releaseAllNodes(n->right_);

		delete n;
	}
public:
	//  C'tor
	AVLTree() : root_(NULL), size_(0) { };
	AVLTree(AVLnode<K, T>* n) :root_(n), size_(0) { };

	// Dc'tor
	~AVLTree() {
		releaseAllNodes(root_);
	}

	void destroyTree() {
		releaseAllNodes(root_);
		root_ = NULL;
		size_= 0;
	}
	void setRoot(AVLnode<K, T>* n) {
		root_ = n;
	}

	bool insert(K key, T value) {
		if (root_ == NULL) {
			root_ = new AVLnode<K, T>(K(key), value, NULL);
			size_++;
			return true;
		}

		AVLnode<K, T> *n = root_, *parent;

		while (true) {
			if (isTwoValuesEquals(n->getKey(), key))
				return false;

			parent = n;

			bool goLeft = isFirstValueLessThan(key, n->getKey());
			n = goLeft ? n->left_ : n->right_;

			if (n == NULL) {
				if (goLeft) {
					parent->left_ = new AVLnode<K, T>(K(key), value, parent);
				}
				else {
					parent->right_ = new AVLnode<K, T>(K(key), value, parent);
				}

				parent->setHeight(1);

				rebalance(parent, true);
				break;
			}
		}

		size_++;
		return true;
	}
	void deleteKey(const K key) {
		if (root_ == NULL)
			return;

		AVLnode<K, T>* t = searchInTreeInternal(key);

		// Key wasn't found
		if (t == NULL)
			return;

		size_--;
		AVLnode<K, T>* parent = t->parent_;
		if (removeLeftOrMaxOneSon(t)) {
			if (parent != NULL) {
				parent->setHeight(height(parent));
				rebalance(parent, true);
			}
			else {
				// The node is the root
				if (root_ != NULL) {
					root_->setBalanc(0);
					root_->setHeight(0);
				}
			}
			return;
		}

		AVLnode<K, T>* w = getNextInOrderSearch(root_, key);

		// Swap data
		swapNodeKeyAndData(w, t);

		AVLnode<K, T>* wParent = w->parent_;
		removeLeftOrMaxOneSon(w);

		wParent->setHeight(height(wParent));
		rebalance(wParent, true);
	}

	/*
	getPreviousInOrderSearchOfMax
	the function return the previous node data, in InOrderSearch by the following assumption:
	1. the key is the maximum key in the tree.
	2. the key must exists in the tree.
	Run time efficiency is O(logn), when the n is the amount of the nodes in the tree.
	*/
	T getPreviousInOrderSearchOfMax(const K key) {
		AVLnode<K, T>* n = searchInTreeInternal(key);
		if (n->parent_ != NULL)
			return n->parent_->getData();
		if (n->left_ != NULL)
			return n->getLeft()->getData();
		throw DataNotFound();
	}
	/*
	searchInTree
	the function search node by given key in the tree, and return the
	data of it.
	If the node doesn't exists the function throw DataNotFound execption.
	@key - the given key, to search in the tree.
	Run time efficiency is O(logn), when n is number of nodes in the tree.
	*/
	T searchInTree(const K key) {
		AVLnode<K, T> * res = searchInTreeInternal(key);
		if (res == NULL)
			throw DataNotFound();
		return res->getData();
	}
	/*
	getSize
	the function return the amount of the nodes in the tree.
	Run time efficiency is O(1).
	*/
	int getSize() const {
		return size_;
	}

	/*
	removeRightLefts
	the function get amount of leafs to remove.
	in case the counter is zero to negative the function will do nothing.
	Otherwise the function remove leafs by the amount of the counter from the
	right to left leafs order.
	function assumption is the counter is less than the amount of the leafs
	in the tree.
	Run time efficiency is O(n), when n is number of nodes in the tree.
	*/
	void removeRightLeafs(int counter) {
		if (counter <= 0)
			return;
		removeRightLeafsInternal(root_, counter);
	}
	/*
	populateTree
	the function get key and value array and populate the tree with this data.
	@keyArr - the array of keys to insert.
	@valueArr - the array of values to insert. The array synchronized with the keyArr order.
	@iPointer - the pointer to start from the data from the arrays
	@size - the length of the arrays
	Run time efficiency is O(n), when n is number of nodes in the tree(including the new nodes).
	*/
	void populateTree(K* keyArr, T* valueArr, int* iPointer, int size) {
		populateTreeInternal(root_, keyArr, valueArr, iPointer, size);
		size_ = size;
	}
	/*
	getKeysInOrder
	the function get array of K and set into it the keys from the tree
	in inorder search.
	Run time efficiency is O(n), when n is number of nodes in the tree(including the new nodes).
	*/
	void getKeysInorder(K* keyArr) const {
		int i = 0;
		getKeysInorder(root_, keyArr, &i);
	}
	/*
	getDataInOrder
	the function get array of T and set into it the values from the tree
	in inorder search.
	Run time efficiency is O(n), when n is number of nodes in the tree(including the new nodes).
	*/
	void getDataInOrder(T* arr) {
		int i = 0;
		getDataInOrderInternal(root_, arr, &i);
	}

	/*
	 getRoot
	 the function return the root of the Tree.
	 */
	AVLnode<K, T>* getRoot() { return root_; }

};

/*
storeInOrder
the function fetch data and key from given node and store it in the given arrays.
Similary it fetch for the right and left nodes of the given node.
index_ptr - hold the current place in the arrays to place the values from the given node.
The store alghoritam is in order search in AVL tree.
Run time efficiency is O(n), when n is number of nodes in the tree.
*/
template <class K, class T>
void storeInOrder(const AVLnode<K, T>* node, K keyInorder[], T inorder[], int *index_ptr) {
	if (node == NULL)
		return;

	storeInOrder(node->getLeft(), keyInorder, inorder, index_ptr);

	inorder[(*index_ptr)] = T(node->getData());
	keyInorder[(*index_ptr)++] = K(node->getKey());

	storeInOrder(node->getRight(), keyInorder, inorder, index_ptr);
}
/*
merge
the function get two keys array and sort them in key array result in the right order of the keys.
In addition the function save the data that suitable for the keys in the merged Array.
Run time efficiency is O(max(m,n)), when m is the length of the first arrays(key/data)
and n is the second arrays length(key/data).
*/
template <class K, class T>
void merge(K keyArr1[], K keyArr2[], T arr1[], T arr2[], int m, int n, K keyRessArr[], T mergedArr[]) {
	int i = 0, j = 0, k = 0;

	while (i < m && j < n) {
		if (keyArr1[i] < keyArr2[j]) {
			keyRessArr[k] = K(keyArr1[i]);
			mergedArr[k] = arr1[i];
			i++;
		}
		else {
			keyRessArr[k] = K(keyArr2[j]);
			mergedArr[k] = arr1[j];
			j++;
		}
		k++;
	}

	while (i < m)
	{
		keyRessArr[k] = K(keyArr1[i]);
		mergedArr[k] = arr1[i];
		i++;
		k++;
	}

	while (j < n)
	{
		keyRessArr[k] = K(keyArr2[j]);
		mergedArr[k] = arr2[j];
		j++;
		k++;
	}
}
/*
mergeTrees
the function get two trees and their length, and return new tree that has the merge of the data and keys in each tree.
The return tree is AVLTree.
Run time efficiency is O(firstTreeSize + secondTreeSize)).
*/
template <class K, class T>
void mergeTrees(AVLTree<K, T>* tree, AVLTree<K, T>* tree1, AVLTree<K, T>* tree2, int firstTreeSize, int secondTreeSize) {
	T* mergeArr, *arr2;
	K* keyMergeArr, *keyArr2;
	int size = firstTreeSize + secondTreeSize;

	int i = 0;
	bool isFirstTreeEmpty = tree1 == NULL || tree1->getRoot() == NULL,
		isSecondTreeEmpty = tree2 == NULL || tree2->getRoot() == NULL;
	if (isFirstTreeEmpty && isSecondTreeEmpty)
		return;

	if (isFirstTreeEmpty || isSecondTreeEmpty || (tree1 == tree2)) {
		if (isFirstTreeEmpty)
			size = secondTreeSize;
		else
			size = firstTreeSize;

		mergeArr = new T[!isFirstTreeEmpty ? firstTreeSize : secondTreeSize];
		keyMergeArr = new K[!isFirstTreeEmpty ? firstTreeSize : secondTreeSize];
		storeInOrder(isFirstTreeEmpty ? tree2->getRoot() : tree1->getRoot(), keyMergeArr, mergeArr, &i);
	}
	else {
		T* arr1 = new T[firstTreeSize];
		K* keyArr1 = new K[firstTreeSize];
		storeInOrder<K, T>(tree1->getRoot(), keyArr1, arr1, &i);

		i = 0;
		arr2 = new T[secondTreeSize];
		keyArr2 = new K[secondTreeSize];
		storeInOrder(tree2->getRoot(), keyArr2, arr2, &i);

		mergeArr = new T[firstTreeSize + secondTreeSize];
		keyMergeArr = new K[firstTreeSize + secondTreeSize];

		merge<K, T>(keyArr1, keyArr2, arr1, arr2, firstTreeSize, secondTreeSize, keyMergeArr, mergeArr);

		delete[] arr1;
		delete[] keyArr1;
		delete[] arr2;
		delete[] keyArr2;
	}

	generateTreeFromArray(tree, keyMergeArr, mergeArr, size);

	delete[] mergeArr;
	delete[] keyMergeArr;
}
/*
generateEmptyTree
the function get the required hieght of the tree, and create empty tree in the given
hieght.
if height zero or negative the function will return NULL.
Run time efficiency is O(n), when n is number of nodes in the tree(including the new nodes).
*/
template <class K, class T>
AVLTree<K, T>* generateEmptyTree(AVLTree<K, T>* tree, int height) {
	if (height <= 0)
		return NULL;

	AVLnode<K, T>* n = new AVLnode<K, T>(NULL);
	buildTree(n, height - 1);
	n->setHeight(height);

	tree->setRoot(n);
	return tree;
}
/*
generateTreeFromArray
the function get key array and value array and create new Tree in the given
size of the arrays.
in case of zero or negative size the function will reutrn NULL.
Run time efficiency is O(n), when n is number of nodes in the tree.
*/
template <class K, class T>
AVLTree<K, T>* generateTreeFromArray(AVLTree<K, T>* tree, K* keyArr, T* arr, int size) {
	if (size <= 0)
		return NULL;

	int counter = 0, n = size;
	while (n > 0) {
		n /= 2;
		counter++;
	}

	generateEmptyTree<K, T>(tree, counter);
	int powOfTwo = 1;
	while (counter-- > 0) {
		powOfTwo *= 2;
	}

	// size of tree begin from 0
	tree->removeRightLeafs(powOfTwo - size -1);
	int i = 0;
	tree->populateTree(keyArr, arr, &i, size);

	return tree;
}
/*
buildTree
the function create empty children of the given node in the required height.
in case of zero or negative height the function will not create the tree.
The function doesn't free the old children from the tree.
Run time efficiency is O(n), when n is number of nodes in the tree(including the new nodes).
*/
template <class K, class T>
void buildTree(AVLnode<K, T>* n, int height) {
	if (height <= 0 || n == NULL)
		return;

	n->left_ = new AVLnode<K, T>(n);
	n->right_ = new AVLnode<K, T>(n);

	n->setHeight(height);

	buildTree(n->left_, height - 1);
	buildTree(n->right_, height - 1);
}



#endif // AVL_TREE_H
