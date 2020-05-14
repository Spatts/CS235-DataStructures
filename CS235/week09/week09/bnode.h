//
//  bnode.h
//  week09
//
//  Created by Steven Patterson on 3/10/19.
//  Copyright © 2019 Steven Patterson. All rights reserved.
//

#ifndef bnode_h
#define bnode_h

#include <iostream>
#include <cassert>

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode
{
private:
   
public:
   int size() const
   {
      return 1 +
      (pLeft== NULL? 0 : pLeft->size()) +
      (pRight == NULL ? 0 : pRight->size());
   }
   
   // add node
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);
   
   // create node
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);
   
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T data;
   
   BinaryNode() : pLeft(NULL), pRight(NULL), pParent(NULL), data() {}
   BinaryNode(T t) : pLeft(NULL), pRight(NULL), pParent(NULL), data(t) {}
   BinaryNode(const BinaryNode <T> &rhs);
};

/*****************************************************************
 * COPY CONSTRUCTOR : Copies data
 *****************************************************************/
template<class T>
BinaryNode<T> :: BinaryNode(const BinaryNode <T> & rhs)
{
   this->pRight = NULL;
   this->pLeft = NULL;
   this->pParent = NULL;
   *this = rhs;
}

/*****************************************************************
 * COPYBTREE : Copies the binary tree
 *****************************************************************/
template <class T>
BinaryNode <T> * copyBTree(const BinaryNode <T> * source) throw (const char *)
{
   if(source == NULL)
   {
      return NULL;
   }
   BinaryNode <T> * destination =  new BinaryNode <T>(source->data);
   
   destination->pRight = copyBTree(source->pRight);
   
   if(destination->pRight != NULL)
   {
      destination->pRight->pParent = destination;
   }
   
   destination->pLeft = copyBTree(source->pLeft);
   
   if(destination->pLeft != NULL)
   {
      destination->pLeft->pParent = destination;
   }
   
   return destination;
}

/*****************************************************************
 * ADDLEFT : Adds a binary node to the left
 *****************************************************************/
template <class T>
void BinaryNode <T>::addLeft(const T & t) throw (const char *)
{
   try
   {
      if(t)
      {
         BinaryNode <T> * pAdd = new BinaryNode <T>(t);
         pAdd->pParent = this;
         pLeft = pAdd;
      }
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/*****************************************************************
 * ADDLEFT : Adds a binary node to the left
 *****************************************************************/
template <class T>
void BinaryNode<T>::addLeft(BinaryNode<T> * pAdd)
{
   if(pAdd != NULL)
   {
      pAdd->pParent = this;
   }
   pLeft = pAdd;
}

/*****************************************************************
 * ADDRIGHT : Adds a binary node to the right
 *****************************************************************/
template <class T>
void BinaryNode <T>::addRight(const T & t) throw (const char *)
{
   try
   {
      if(t)
      {
         BinaryNode <T> * pAdd = new BinaryNode <T>(t);
         pAdd->pParent = this;
         pRight = pAdd;
      }
      else
         std::cerr << "did not go in\n";
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
}
         
/*****************************************************************
 * ADDRIGHT : Adds a binary node to the right
 *****************************************************************/
template <class T>
void BinaryNode<T>::addRight(BinaryNode<T> * pAdd)
{
   if (pAdd != NULL)
   {
      pAdd->pParent = this;
   }
   pRight = pAdd;
}
         
/*****************************************************************
* SIZEBTREE : Returns the size of the tree
*****************************************************************/
template <class T>
int sizeBTree(BinaryNode<T> * node)
{
   if(node == NULL)
   {
      return 0;
   }
   else
   {
      return (sizeBTree(node->pLeft) + 1 + sizeBTree(node->pRight));
   }
}
         
/*****************************************************************
* DELETEBINARYTREE : Deletes the binary tree
*****************************************************************/
template <class T>
void deleteBinaryTree(BinaryNode <T> * node)
{
   if(node == NULL)
   {
      return;
   }
   deleteBinaryTree(node->pRight);
   deleteBinaryTree(node->pLeft);
   delete node;
}
         
/*****************************************************************
* << : Prints the binary tree
*****************************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, BinaryNode<T> * pNode)
{
   if (pNode != NULL)
   {
      std::cout << pNode->pLeft;
      out << pNode->data << " ";
      std::cout << pNode->pRight;
   }
   
   return out;
}


#endif /* bnode_h */
