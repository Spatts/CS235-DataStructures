//
//  list.h
//  week07
//
//  Created by Steven Patterson on 2/25/19.
//  Copyright © 2019 Steven Patterson. All rights reserved.
//

#ifndef list_h
#define list_h

#include <cassert>
#include <iostream>

template <class T>
class ListIterator;

/************************************************
 * NODE
 * A class that holds stuff
 ***********************************************/
template <class T>
class Node
{
private:
   
public:
   T data;
   Node <T> * pNext;
   Node <T> * pPrev;
   
   // default constructor : empty and kinda useless
   Node() : data(NULL), pNext(NULL), pPrev(NULL) {}
   // non-default constructor : pre-allocate
   Node(const T & t) : data(t), pNext(NULL), pPrev(NULL) {}
};

/***********************************************
 * FREEDATA
 * Deletes the nodes
 **********************************************/
template <class T>
void freeData(Node <T> * & pHead)
{
   if(pHead == NULL)
   {
      return;
   }
   
   while (pHead != NULL)
   {
      Node <T> *pDelete = pHead;
      pHead = pHead->pNext;
      delete pDelete;
   }
}

/***********************************************
 * COPY
 * Copy the nodes
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

/**************************************************
 * LIST
 * A list class
 *************************************************/
template <class T>
class List
{
private:
   
   Node <T> * pHead;
   Node <T> * pTail;
   int numElements;
   
public:
   
   //friend class ListIterator <T>;
   friend class Node <T>;
   List() : pHead(NULL), pTail(NULL), numElements(0) {}
   //List(const T & t) throw (const char *);
   List(List <T> & rhs) throw (const char *);
   
   ~List()
   {
      if(pHead == NULL)
      {
         return;
      }
      
      while(pHead != NULL)
      {
         Node <T> *pDelete = pHead;
         pHead = pHead->pNext;
         delete pDelete;
      }
   };
   
   List <T> & operator = (const List <T> & rhs) throw(const char *);
   
   int size()
   {
      return numElements;
   }
   
   bool empty()
   {
      if (size() == 0)
      {
         return true;
      }
      else
      {
         return false;
      }
   };
   
   void clear()
   {
      freeData(pHead);
      pTail = pHead;
      numElements = 0;
   };
   
   void push_back(const T & t)  throw (const char *);
   void push_front(const T & t) throw (const char *);
   T & back() throw (const char *);
   T & front() throw (const char *);
   
   ListIterator <T> insert(ListIterator <T> & it, const T & data) throw(const char *);
   ListIterator <T> remove(ListIterator <T> & it) throw(const char *);
   ListIterator <T> begin() { return ListIterator <T> (pHead); }
   ListIterator <T> rbegin() { return ListIterator <T> (pTail);}
   ListIterator <T> end() { return ListIterator <T> (NULL); }
   ListIterator <T> rend() { return ListIterator <T> (NULL); }
};

/************************************************
 * LISTITERATOR: A class that iterates through a list
 ***********************************************/
template <class T>
class ListIterator
{
   friend ListIterator<T> List<T> :: insert (ListIterator <T> & it, const T & data) throw(const char *);
   friend ListIterator<T> List<T> :: remove (ListIterator <T> & it) throw(const char *);
private:
   Node <T> * p;
   
public:
   
   //friend class List <T>;
   Node <T> * getP()
   {
      return p;
   }
   
   // default constructor
   ListIterator() : p(NULL) {}
   
   // initialize to direct p to some item
   ListIterator(Node <T> * p) : p(p) {}
   
   // rhs side equals this rhs
   ListIterator(const ListIterator &rhs) { *this = rhs; }
   
   // not equals operator
   bool operator != (const ListIterator &rhs) const
   {
      return rhs.p != this->p;
   }
   
   // dereference operator
   //Node <T> & operator * ()
   T & operator * ()
   {
      if(p != NULL)
      {
         return p->data;
      }
      else
      {
         throw "Error";
      }
   }
   
   // prefix increment
   ListIterator<T> & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }
   
   // postfix increment
   ListIterator <T> operator ++ (int postfix)
   {
      ListIterator tmp(*this);
      p = p->pNext;
      return tmp;
   }
   
   // postfix decrement
   ListIterator<T> & operator -- ()
   {
      p = p->pPrev;
      return *this;
   }
   
   // postfix decrement
   ListIterator <T> operator -- (int postfix)
   {
      ListIterator tmp(*this);
      p = p->pPrev;
      return tmp;
   }
   
   // equals equals operator
   bool operator == (const ListIterator &lhs) const
   {
      return lhs.p == this->p;
   }
   
   // equals operator
   ListIterator & operator = (const ListIterator &rhs)
   {
      this->p = rhs.p;
      return *this;
   }
   
};

/************************************************
 * OPERATOR =: Equals operator
 ***********************************************/
template <class T>
List <T> & List <T> :: operator = (const List <T> & rhs) throw (const char *)
{
   pHead = NULL;
   pTail = NULL;
   numElements = 0;
   try
   {
      pHead = copy(rhs.pHead);
      numElements = rhs.numElements;
      Node <T> * pLoop = pHead;
      
      for(int i = 0; i < rhs.numElements - 1; i++)
      {
         pLoop = pLoop->pNext;
      }
      pTail = pLoop;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   
   return *this;
}

/************************************************
 * COPY CONSTRUCTOR: Copies
 ***********************************************/
template <class T>
List <T> :: List (List <T> & rhs) throw (const char *)
{
   pHead = copy(rhs.pHead);
   numElements = rhs.numElements;
   Node <T> * pLoop = pHead;
   
   for(int i = 0; i < rhs.numElements - 1; i++)
   {
      pLoop = pLoop->pNext;
   }
   pTail = pLoop;
}

/************************************************
 * INSERT: Insert a node
 ***********************************************/
template <class T>
ListIterator<T> List<T> :: insert (ListIterator <T> & it, const T & data) throw(const char *)
{
   Node <T> * pNew = new Node <T> (data);
   
   if(empty())
   {
      pHead = pTail = pNew;
   }
   
   else if(it == end())
   {
      pTail->pNext = pNew;
      pNew->pPrev = pTail;
      pTail = pNew;
      
   }
   else
   {
      pNew->pNext = it.p;
      pNew->pPrev = it.p->pPrev;
      it.p->pPrev = pNew;
      
      if(it.p == pHead)
      {
         pHead = pNew;
      }
      else
      {
         pNew->pPrev->pNext = pNew;
      }
   }
   numElements++;
   return pNew;
   
}

/************************************************
 * REMOVE: Remove a node
 ***********************************************/
template <class T>
ListIterator<T> List<T> :: remove (ListIterator <T> & it) throw(const char *)
{
   ListIterator <T> itRemove = end();
   
   try
   {
      if(it.p->pPrev == NULL)
      {
         pHead = pHead->pNext;
      }
      if(it.p->pNext == NULL)
      {
         pTail = pTail->pPrev;
      }
      
      if(it.p->pPrev != NULL)
      {
         it.p->pPrev->pNext = it.p->pNext;
      }
      if(it.p->pNext != NULL)
      {
         it.p->pNext->pPrev = it.p->pPrev;
         itRemove = it.p->pNext;
      }
      
      numElements--;
      delete it.p;
      return itRemove;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to remove from an invalid location in a list";
   }
}

/************************************************
 * PUSH_FRONT: Push node to front
 ***********************************************/
template <class T>
void List <T> :: push_front(const T & t) throw (const char *)
{
   try
   {
      Node <T> * pInsert = new Node <T> (t);
      
      if (pHead != NULL)
      {
         pHead->pPrev = pInsert;
         pInsert->pNext = pHead;
         pHead = pInsert;
      }
      
      else
      {
         pHead = pTail = pInsert;
      }
      numElements++;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/************************************************
 * PUSH_BACK: Push a node back
 ***********************************************/
template <class T>
void List <T> :: push_back(const T & t) throw (const char *)
{
   try
   {
      Node <T> * pInsert = new Node <T> (t);
      
      if (pHead != NULL)
      {
         pTail->pNext = pInsert;
         pInsert->pPrev = pTail;
         pTail = pInsert;
      }
      else
      {
         pHead = pTail = pInsert;
      }
      numElements++;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/************************************************
 * FRONT: Returns the front node
 ***********************************************/
template <class T>
T & List <T> :: front() throw (const char *)
{
   try
   {
      return pHead->data;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Empty List";
   }
   
}

/************************************************
 * Back: Returns the back node
 ***********************************************/
template <class T>
T & List <T> :: back() throw (const char *)
{
   try
   {
      return pTail->data;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Empty List";
   }
}

#endif /* list_h */
