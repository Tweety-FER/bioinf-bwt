/***************************************************************************
 *   DynSA - Dynamic Suffix Array                                          *
 *   Copyright (C) 2006  Wolfgang Gerlach                                  *
 *                 2008  Mikael Salson                                     *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/


using namespace std;

#ifndef CUSTOM_TREE_H
#define CUSTOM_TREE_H
 
#include <iostream>
#include <unistd.h>  
#include <stdlib.h>
#include "types.h"
#include "rbtree.h"

using namespace std;
using namespace rbtree;


// Defining null value for different types 
// (ie. for size_t, for  a pair and for a pointer)
template<class T> struct Null;
template<> struct Null<size_t> { static size_t null() { return 0;}};
template<class T> struct Null<pair<T, T> > {static pair<T,T> null() { return pair<T,T>(Null<T>::null(),Null<T>::null());}};
template<> struct Null<void *> {static void *null() { return NULL;}};


template<class T> class CustomTree;
template<class T> class CustomNode;

template<class T> void callCustomTreeUpdateCounters(RBNode *n, RBTree *tree) {
  ((CustomTree<T> *)tree)->updateCounters((CustomNode<T>*) n);
}

template<class T> void callCustomTreeUpdateCountersOnPathToRoot(RBNode *n, RBTree *tree) {
  ((CustomTree<T> *)tree)->updateCountersOnPathToRoot((CustomNode<T>*) n);
}

// Defines the class for a node in the tree
template<class T>
class CustomNode : public RBNode {
public:
  T element;
  size_t subtreeSize;

  CustomNode() 
    : RBNode(this), subtreeSize(0){
  }	

  CustomNode(CustomNode *n, T elem) 
    : RBNode(n), element(elem), subtreeSize(1){
  }

};

// Defines the class for a red-black tree
template<class T>
class CustomTree : public RBTree{
 private:
  CustomNode<T> *insertedNode;
public:

  //results:

  CustomTree() {
    setNil(new CustomNode<T>());
    setRoot(getNil());
    insertedNode = getNil();
  }

  void setRoot(CustomNode<T>* n){
    ((RBTree*) this)->root=(RBNode*)n;
  }
	
  CustomNode<T>* getRoot(){
    return ((CustomNode<T>*) ((RBTree*) this)->root);
  }

  void setNil(CustomNode<T>* n){
    ((RBTree*) this)->nil=(RBNode*)n;
  }

  CustomNode<T>* getInsertedNode() {
    return insertedNode;
  }

  CustomNode<T>* getNil(){
    return ((CustomNode<T>*) ((RBTree*) this)->nil);
  }


  size_t getSize(){
    return (getRoot()!=getNil())?getRoot()->subtreeSize:0;
  }
	

  CustomNode<T> *getIthNode(size_t i) {
    CustomNode<T> *n= getRoot();
    
    size_t rest=0;
    size_t left_subtreeSize;
    bool found = false;
    
    while (n != getNil() && ! found) {
      left_subtreeSize = ((CustomNode<T> *)n->getLeft())->subtreeSize;
      
      if (i <= left_subtreeSize + rest) {
	n=(CustomNode<T> *)n->getLeft();
      } else if (i > left_subtreeSize + rest + 1) {
	rest += left_subtreeSize + 1;
	n= (CustomNode<T> *)n->getRight();
      } else {
	// match
	found = true;
      }
    }
    
    return (found) ? n : NULL;
  }

  size_t getNumNode(CustomNode<T> *node) {
    size_t sum = 1;
    if (node->getLeft() != getNil())
      sum += ((CustomNode<T> *)node->getLeft())->subtreeSize;
    while (node->getParent() != getNil()) {
      if (node->getParent()->getRight() == node) {
	sum += ((CustomNode<T> *)node->getParent())->subtreeSize - node->subtreeSize;
      }
      node = (CustomNode<T> *)node->getParent();
    }
    return sum;
  }

  T getElement(size_t i) {
    CustomNode<T> *n= getIthNode(i);
    if (n != NULL) {
      return n->element;
    }
    return Null<T>::null();
  }

  void updateElement(size_t i, T elem) {
    CustomNode<T> *n = getIthNode(i);
    if (n != NULL) {
      n->element = elem;
    }
  }

  void insertElement(T elem, size_t i) {
    CustomNode<T> *n= getRoot();
	
	
    if (n == getNil()) {
      CustomNode<T> *newLeaf= new CustomNode<T>(getNil(), elem); // 1=smallest key, 0 = error
      setRoot(newLeaf);
      ((RBNode*)newLeaf)->color=BLACK;
      insertedNode = newLeaf;
      return;
    }

    if (i > n->subtreeSize ) {
      //append
      n= (CustomNode<T>*) treeMaximum(n);
      CustomNode<T> *newLeaf= new CustomNode<T>(getNil(), elem);
      n->setRight(newLeaf);
      insertedNode = newLeaf;
      newLeaf->setParent(n);
      updateCountersOnPathToRoot(newLeaf);
      rbInsertFixup(newLeaf, callCustomTreeUpdateCounters<T>);

      CustomNode<T> *oldnode = n;
      while (n != getNil()) {
	oldnode = n;
	n = (CustomNode<T> *)n->getParent();
      }
      setRoot(oldnode);
      return;
    }

    size_t rest=0;
    size_t left;


    while (true) {
#ifndef NDEBUG
      if (n == getNil()) {
	cout << "insertSample: nil!" << endl;
	exit(EXIT_FAILURE);
      }
#endif

      left = ((CustomNode<T> *)n->getLeft())->subtreeSize;
		
	
      if (i <= left + rest) {
	n=(CustomNode<T> *)n->getLeft();
      } else if (i == left + rest + 1) {
			
	// match
	CustomNode<T> *newLeaf= new CustomNode<T>(getNil(), elem);
	if (n->getLeft() == getNil()) {
	  n->setLeft(newLeaf);
	} else {
	  n=(CustomNode<T>*) treeMaximum(n->getLeft());
	  n->setRight(newLeaf);
	}
	newLeaf->setParent(n);
	insertedNode = newLeaf;
	updateCountersOnPathToRoot(newLeaf);
	rbInsertFixup(newLeaf, callCustomTreeUpdateCounters<T>);
	return;
      } else {
	rest+=left+1;
	n=(CustomNode<T> *)n->getRight();
      }
    }
  }
  
  void deleteElement(size_t i){
    CustomNode<T> *n = getIthNode(i);
    deleteNode(n);
  }
  
  void deleteNode(CustomNode<T> *n) {
    if (n != NULL) {
      // match
      rbDelete(n, callCustomTreeUpdateCountersOnPathToRoot<T>);
      delete n;
      insertedNode = NULL;
    }
  }

  void updateCountersOnPathToRoot(CustomNode<T> *n) {
    while (n != getNil()) {
      updateCounters(n);
      
      n = (CustomNode<T> *)n->getParent();
    }
  }

  void updateCounters(CustomNode<T> *n) {
    if (n == getNil()) {
      cerr << "prob" << endl;
/*       exit(1); */
#ifndef NDEBUG
      cerr << "error: CustomTree::updateCounters" << endl;
      exit(EXIT_FAILURE);
#endif	
      return;
      
    }
    n->subtreeSize=1;
    n->subtreeSize += ((CustomNode<T> *)n->getLeft())->subtreeSize; 	
    n->subtreeSize += ((CustomNode<T> *)n->getRight())->subtreeSize;
  }

  void printSubTree(CustomNode<T> *n) {
    cout << n->element << " [";
    if (n->getLeft()==getNil()) cout << "N";
    else printSubTree((CustomNode<T> *)n->getLeft());
    cout << ",";
    if (n->getRight()==getNil()) cout << "N";
    else printSubTree((CustomNode<T> *)n->getRight());
    cout << "]";
  }

  void printSubTreeNodes(CustomNode<T> *n) {
    cout << n << " [";
    if (n->getLeft()==getNil()) cout << "N";
    else printSubTreeNodes((CustomNode<T> *)n->getLeft());
    cout << ",";
    if (n->getRight()==getNil()) cout << "N";
    else printSubTreeNodes((CustomNode<T> *)n->getRight());
    cout << "]";
  }


  void displayElements() {
    size_t nb_values_sampled = getSize();
    for (size_t t=0; t < nb_values_sampled; t++) {
      cout << getElement(t+1) << " ";
    }
    cout << endl;
  }
	
};


#endif
