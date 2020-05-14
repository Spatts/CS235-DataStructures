//
//  deque.h
//  week04
//
//  Created by Steven Patterson on 2/3/19.
//  Copyright © 2019 Steven Patterson. All rights reserved.
//

#ifndef deque_h
#define deque_h

#include <iostream>    // for ISTREAM and OSTREAM
#include <cassert>

/************************************************
 * DEQUE
 * A class that holds stuff
 ***********************************************/
template <class T>
class Deque
{
public:
   
   // default constructor : empty and kinda useless
   Deque() : numBack(0), numFront(0), cap(0), numItems(0), data(NULL) {}
   
   // non-default constructor : pre-allocate
   Deque(int capacity) throw (const char *);
   
   // copy constructor : copy it
   Deque(const Deque & rhs) throw (const char *);
   
   // destructor : free everything
   ~Deque()
   {
      if (cap > 0)
      {
         data = NULL;
         delete [] data;
      }
   };
   
   // how many items are currently in the deque?
   int size () const
   {
      return numItems;
   }
   
   // the capacity of the deque
   int capacity () const
   {
      return cap;
   }
   
   // is the deque currently empty
   bool empty() const
   {
      if (size() == 0)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   
   // remove all the items from the deque
   void clear()
   {
      while (!empty())
      {
         pop_front();
      }
   }
   
   //returns the tail of the deque
   int iTail() const
   {
      return (numBack - 1) % cap;
   }
   
   //returns the head of the deque
   int iHead() const
   {
      return numFront % cap;
   }
   
   //front of the deque
   T & front() throw (const char*)
   {
      if (empty())
      {
         throw "ERROR: unable to access data from an empty deque";
      }
      
      else
      {
         //return data[iHead()];
         return data[numFront];
      }
   }
   
   //back of the deque
   T & back() throw (const char*)
   {
      if (empty())
      {
         throw "ERROR: unable to access data from an empty deque";
      }
      
      else
      {
         //return data[iTail()];
         return data[(numBack - 1 + cap) % cap];
      }
   }
   
   // assignment operator
   Deque <T> & operator = (const Deque <T> & rhs) throw (const char *);
   
   // pushes an element onto the deque
   void push_back (T & t) throw (const char *);
   
   void push_front (T & t) throw (const char *);
   
   // takes an element off the deque
   void pop_front() throw (const char *);
   
   void pop_back() throw (const char *);
   
   //reallocates the deque
   void realloc () throw(const char*);
   
private:
   T * data; 			// dynamically allocated array of T
   int numItems;	// how many items are currently in the deque?
   int cap;	// how many items can I put on the deque before full?
   int numBack;      //back of Deque
   int numFront;     //font of Deque
   
};

/**********************************************
 * Deque : ASSIGNMENT OPERATOR
 * Assignment operator
 **********************************************/
template <class T>
Deque <T> & Deque <T> :: operator = (const Deque <T> & rhs) throw (const char *)
{
   if(data)
   {
      delete [] data;
   }
   if(rhs.cap == 0)
   {
      cap = 0;
      numItems = 0;
      numFront = 0;
      numBack = 0;
      data = NULL;
      return *this;
   }
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   cap = rhs.cap;
   numItems = rhs.numItems;
   numFront = rhs.numFront;
   numBack = rhs.numBack;
   int j = numFront;
   
   for (int i = 0; i < numItems; i++, j = ((j+1)% cap))
   {
      data[j] = rhs.data[j];
   }
   
   return *this;
}

/**********************************************
 * Deque : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Deque<T> :: Deque(int capacity) throw(const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      
      this->cap = 0;
      this->numItems = 0;
      this->numBack = 0;
      this->numFront = 0;
      this->data = NULL;
      return;
   }
   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;
   this->numBack = 0;
   this->numFront = 0;
   
   // attempt to allocate
   try
   {
      data = new T[cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: attempting to allocate buffer";
   }
   
   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
   {
      data[i] = T();
   }
}

/**********************************************
 * Deque : REALLOC
 * Reallocate the container
 **********************************************/
template <class T>
void Deque <T> :: realloc () throw(const char*)
{
   try
   {
      
      T * temp;
      if (cap == 0)
      {
         cap = 2;
         data = new T[cap];
      }
      else
      {
         temp = new T[cap * 2];
         int oldCapacity = cap;
         cap = cap * 2;
         
         int j = (numFront);
         
         for (int i = 0; i < numItems; i++, j = (j + 1) % oldCapacity)
         {
            temp[i] = data[j];
         }
         delete [] data;
         data = temp;
      }
      
      numFront = 0;
      numBack = numItems;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: attempting to allocate a new buffer for deque";
   }
}

/**********************************************
 * DEQUE : PUSH_BACK
 * Pushes elements onto the back of the deque
 **********************************************/
template <class T>
void Deque <T> :: push_back(T & t) throw(const char*)
{
   try
   {
      if (numItems == cap || cap == 0)
      {
         realloc();
      }
      
      data[numBack] = t;
      numBack = (numBack + 1) % cap;
      numItems++;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: attempting to allocate a new buffer for deque";
   }
}

/**********************************************
 * DEQUE : PUSH_FRONT
 * Pushes elements onto the front of the deque
 **********************************************/
template <class T>
void Deque <T> :: push_front(T & t) throw(const char*)
{
   try
   {
      
      if (numItems == cap || cap == 0)
      {
         realloc();
      }
      
      numFront = (numFront - 1 + cap) % cap;
      
      data[numFront] = t;
      numItems++;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: attempting to allocate a new buffer for deque";
   }
}

/**********************************************
 * DEQUE : POP_FRONT
 * Pops elements off the front of the deque
 **********************************************/
template <class T>
void Deque <T> :: pop_front () throw(const char *)
{
   if (!empty())
   {
      numFront = (numFront + 1) % cap;
      
      numItems--;
   }
   else
   {
      throw "ERROR: unable to pop from the front of empty deque";
   }
}

/**********************************************
 * DEQUE : POP_BACK
 * Pops elements off the back of the deque
 **********************************************/
template <class T>
void Deque <T> :: pop_back () throw(const char *)
{
   if (!empty())
   {
      numBack = (numBack - 1 + cap) % cap;
      
      numItems--;
   }
   else
   {
      throw "ERROR: unable to pop from the back of empty deque";
   }
}

/*******************************************
 * DEQUE :: COPY CONSTRUCTOR
 * Copies over the data
 *******************************************/
template <class T>
Deque<T> :: Deque (const Deque<T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
   
   if (rhs.cap == 0)
   {
      numFront = 0;
      numBack = 0;
      numItems = 0;
      cap = 0;
      data = NULL;
      return;
   }
   
   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: attempting to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;
   numBack = rhs.numBack;
   numFront = rhs.numFront;
   int j = numFront;
   
   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++, j = ((j+1)% cap))
   {
      data[j] = rhs.data[j];
   }
}

#endif /* deque_h */
