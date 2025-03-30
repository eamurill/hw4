#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;
		
		
protected:
    int8_t balance_;    // effectively a signed char // this is the balance to use
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		void insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
		void removeFix(AVLNode<Key, Value>* n, int diff);
		virtual void rotateLeft(AVLNode<Key, Value>* g);
    virtual void rotateRight(AVLNode<Key, Value>* g);
		


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO

    // First I need to call BST insert
    // set balance to 0 and create balance data member, look at parent
    // You can reuse your BST insert function
    
    // Have a helper function for insert-fix!!

		// tree empty

		// check duplicates

		// find an empty spot

		// call insert fix, based on balance if 

		// go line by line

		// for rotation, every variable is exactly like the slides, know which 6 pointers to update, 6 separate lines in every rotation
		
		// left rotation and right rotation function 

		AVLNode<Key, Value>* root = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::root_);

    // Case 1: Tree is empty
    if(root == nullptr) {
    	AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
      BinarySearchTree<Key, Value>::root_ = newNode;
      newNode->setBalance(0);
      return;
    }

    // Case 2: Check for duplicate
    AVLNode<Key, Value>* duplicate = static_cast<AVLNode<Key, Value>*>(this->internalFind(new_item.first));
    if(duplicate != nullptr) {
      duplicate->setValue(new_item.second);
      return;
    }

    // Case 3: Find insertion point
    AVLNode<Key, Value>* current = root;
    AVLNode<Key, Value>* parent = nullptr;

    while(current != nullptr) {
			parent = current;
			if(new_item.first < current->getKey()) {
				current = current->getLeft();
			} 
			else {
				current = current->getRight();
			}
    }

    // Create and link new node
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);

    if (new_item.first < parent->getKey()) {
      parent->setLeft(newNode);
    } 
		else {
      parent->setRight(newNode);
    }

    newNode->setBalance(0);

    // Update balance and call insertFix if needed
    int8_t parentBal = parent->getBalance();

    if(parentBal == -1 || parentBal == 1) {
        parent->setBalance(0);
        return;
    } 
		else if(parentBal == 0) {
      if(newNode == parent->getLeft()) {
          parent->setBalance(-1);
      } 
			else {
        parent->setBalance(1);
      }
      insertFix(parent, newNode);
  	}
	
}

// rotate left and rotate right

// rotate function that takes in top where p will become top, g will become right child
// check if g is a right child, 

// if g is a right child, then p is going to become a right child-->rotate right
// else

// if we rotate left zig-zag 

// rotate right and left takes in teh top node, pass in g

// do zig zag if balance of two nodes are opposite signs

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n)
{
    if(p == nullptr || p->getParent() == nullptr) {
    	return;
    }

    AVLNode<Key, Value>* g = p->getParent();

    if(p == g->getLeft()) {
    	g->updateBalance(-1);
			if(g->getBalance() == 0) {
				return;
			} 
			else if(g->getBalance() == -1) {
				insertFix(g, p);
			} 
			else if(g->getBalance() == -2) {
				if(n == p->getLeft()) {
					rotateRight(g);
					p->setBalance(0);
					g->setBalance(0);
			} 
			else {
				rotateLeft(p);
				rotateRight(g);

				if(n->getBalance() == -1) {
					p->setBalance(0);
					g->setBalance(1);
				} 
				else if(n->getBalance() == 0) {
					p->setBalance(0);
					g->setBalance(0);
				} 
				else {
					p->setBalance(-1);
					g->setBalance(0);
				}

				n->setBalance(0);
				}
    	}
    } 
		else { // Right child
    	g->updateBalance(1);

    	if(g->getBalance() == 0) {
            return;
    	} 
			else if (g->getBalance() == 1) {
        insertFix(g, p);
    	} 
			else if(g->getBalance() == 2) {
        if(n == p->getRight()) {
					rotateLeft(g);
					p->setBalance(0);
					g->setBalance(0);
    	} 
			else {
				rotateRight(p);
				rotateLeft(g);

				if (n->getBalance() == 1) {
						p->setBalance(0);
						g->setBalance(-1);
				} else if (n->getBalance() == 0) {
						p->setBalance(0);
						g->setBalance(0);
				} else {
						p->setBalance(1);
						g->setBalance(0);
				}

				n->setBalance(0);
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* g) {
    AVLNode<Key, Value>* p = g->getRight();
    if (p == nullptr) return;

    g->setRight(p->getLeft());
    if(p->getLeft()) {
    	p->getLeft()->setParent(g);
    }

    p->setParent(g->getParent());
    if(g->getParent() == nullptr) {
    	this->root_ = p;
    } 
		else if(g == g->getParent()->getLeft()) {
    	g->getParent()->setLeft(p);
    } 
		else {
    	g->getParent()->setRight(p);
    }

    p->setLeft(g);
    g->setParent(p);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* g) {
    AVLNode<Key, Value>* p = g->getLeft();
    if (p == nullptr) return;

    g->setLeft(p->getRight());
    if (p->getRight()) {
        p->getRight()->setParent(g);
    }

    p->setParent(g->getParent());
    if (g->getParent() == nullptr) {
        this->root_ = p;
    } else if (g == g->getParent()->getLeft()) {
        g->getParent()->setLeft(p);
    } else {
        g->getParent()->setRight(p);
    }

    p->setRight(g);
    g->setParent(p);
}




/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
	
	// Identify children, make boolean variables for hasleft and hasright

	// identify hasleft parent and hasright parent, if you're at a node, getParent, getLeft, that equals node then it is left child

	AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if(node == nullptr) return;

    // Step 1: If node has two children, swap with predecessor
    if(node->getLeft() != nullptr && node->getRight() != nullptr) {
			AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(node));
			this->nodeSwap(node, pred);
    }

    // Step 2: Now node has at most one child
    AVLNode<Key, Value>* child = nullptr;
    if(node->getLeft() != nullptr) {
      child = node->getLeft();
    } 
		else if(node->getRight() != nullptr) {
      child = node->getRight();
    }

    AVLNode<Key, Value>* parent = node->getParent();
    int diff = 0;

    // Step 3: Determine which side of parent node is being removed
    if(parent != nullptr) {
      if(parent->getLeft() == node) {
        diff = 1;
      } 
			else {
        diff = -1;
      }
    }

    // Step 4: Patch tree: reassign parent pointers
    if (child != nullptr) {
        child->setParent(parent);
    }

    if (parent == nullptr) {
        // Deleting the root
        this->root_ = child;
    } else {
        if (parent->getLeft() == node) {
            parent->setLeft(child);
        } else {
            parent->setRight(child);
        }
    }

    delete node;

    // Step 5: Rebalance
    removeFix(parent, diff);
	
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int diff)
{
    if (n == nullptr) return;

    AVLNode<Key, Value>* parent = n->getParent();
    int balanceChange = 0;

    if (parent != nullptr) {
        AVLNode<Key, Value>* leftChild = static_cast<AVLNode<Key, Value>*>(parent->getLeft());
        if (leftChild == n) {
            balanceChange = 1;
        } else {
            balanceChange = -1;
        }
    }

    int newBalance = n->getBalance() + diff;

    // Case 1: Left heavy
    if (newBalance == -2) {
        AVLNode<Key, Value>* child = n->getLeft();
        int childBalance = child->getBalance();

        if (childBalance == -1) {
            rotateRight(n);
            n->setBalance(0);
            child->setBalance(0);
            removeFix(parent, balanceChange);
        }
        else if (childBalance == 0) {
            rotateRight(n);
            n->setBalance(-1);
            child->setBalance(1);
            return;
        }
        else if (childBalance == 1) {
            AVLNode<Key, Value>* grandchild = child->getRight();
            int grandchildBalance = grandchild->getBalance();

            rotateLeft(child);
            rotateRight(n);

            if (grandchildBalance == 1) {
                n->setBalance(0);
                child->setBalance(-1);
            }
            else if (grandchildBalance == 0) {
                n->setBalance(0);
                child->setBalance(0);
            }
            else {
                n->setBalance(1);
                child->setBalance(0);
            }

            grandchild->setBalance(0);
            removeFix(parent, balanceChange);
        }
    }

    // Case 2: Right heavy
    else if (newBalance == 2) {
        AVLNode<Key, Value>* child = n->getRight();
        int childBalance = child->getBalance();

        if (childBalance == 1) {
            rotateLeft(n);
            n->setBalance(0);
            child->setBalance(0);
            removeFix(parent, balanceChange);
        }
        else if (childBalance == 0) {
            rotateLeft(n);
            n->setBalance(1);
            child->setBalance(-1);
            return;
        }
        else if (childBalance == -1) {
            AVLNode<Key, Value>* grandchild = child->getLeft();
            int grandchildBalance = grandchild->getBalance();

            rotateRight(child);
            rotateLeft(n);

            if (grandchildBalance == -1) {
                n->setBalance(0);
                child->setBalance(1);
            }
            else if (grandchildBalance == 0) {
                n->setBalance(0);
                child->setBalance(0);
            }
            else {
                n->setBalance(-1);
                child->setBalance(0);
            }

            grandchild->setBalance(0);
            removeFix(parent, balanceChange);
        }
    }

    // Tree still unbalanced: just update balance and return
    else if (newBalance == -1 || newBalance == 1) {
        n->setBalance(newBalance);
        return;
    }

    // Balanced case: continue up
    else {
        n->setBalance(0);
        removeFix(parent, balanceChange);
    }
}



template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
