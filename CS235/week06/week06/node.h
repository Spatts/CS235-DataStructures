//
//  node.h
//  week06
//
//  Created by Steven Patterson on 2/18/19.
//  Copyright © 2019 Steven Patterson. All rights reserved.
//

#ifndef node_h
#define node_h

#include <cassert>
#include <iostream>

/************************************************
 * NODE: A class that holds stuff
 ***********************************************/
template <class T>
class Node
{
private:
   
public:
   T data;
   Node <T> * pNext;
   
   // default constructor : empty and kinda useless
   Node() : data(NULL), pNext(NULL) {}
   // non-default constructor : pre-allocate
   Node(const T & t) : data(t), pNext(NULL) {}
};

/***********************************************
 * INSERT: Inserts a node into the linked list
 **********************************************/
template <class T>
void insert(const T & t, Node <T> * & pCurrent, bool head = false) throw (const char *)
{
   try
   {
      Node <T> * pNew = new Node <T> (t);
      if(pCurrent == NULL)
      {
         head = true;
      }
      
      if(head == false)
      {
         //insert it in the middle or end of list
         pNew->pNext = pCurrent->pNext;
         pCurrent->pNext = pNew;
      }
      else
      {
         //insert it at the head/beginning
         pNew->pNext = pCurrent;
         //update pCurrent as new head
         pCurrent = pNew;
      }
      
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Can't allocate memory for a Node!";
   }
}

/***********************************************
 * COPY: Copies the Node
 **********************************************/
template <class T>
Node <T> * copy(Node <T> * pSource) throw (const char *)
{
   try
   {
      if(pSource == NULL)
      {
         return pSource;
      }
      Node <T> * pDestination = new Node <T> (pSource->data);
      pDestination->pNext = copy(pSource->pNext);
      return pDestination;
      
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Can't allocate memory for a Node!";
   }
}

/***********************************************
 * FIND: Finds a Node in linked list
 **********************************************/
template <class T>
Node <T> * find(Node <T> * pHead, const T & t, bool head = false) throw (const char *)
{
   if(pHead == NULL || pHead->data == t)
   {
      return pHead;
   }
   return find(pHead->pNext, t, false);
}

/***********************************************
 * OPERATOR <<: Displays linked list
 **********************************************/
template <class T>
std::ostream & operator << (std::ostream & out, Node <T> * & pDisplay)
{
   for(Node <T> * p = pDisplay; p; p = p->pNext)
   {
      out << p->data;
      if(p->pNext)
      {
         out << ", ";
      }
   }
   return out;
}

/***********************************************
 * FREEDATA: Deletes nodes
 **********************************************/
template <class T>
void freeData(Node <T> * & pHead)
{
   //if statment if it is already NULL
   if(pHead == NULL)
   {
      return;
   }
   
   freeData(pHead->pNext);
   delete pHead;
   pHead = NULL;
   
}

#endif /* node_h */
