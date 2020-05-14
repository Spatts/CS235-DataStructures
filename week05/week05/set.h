//
//  set.h
//  week05
//
//  Created by Steven Patterson
//  Copyright © 2019 Steven Patterson. All rights reserved.
//

#ifndef set_h
#define set_h

#include <iostream>       // for IFSTREAM and OFSTREAM
#include <cassert>        // for ASSERT in the constructors

template <class T>
class SetIterator;

template <class T>
class Set
{
public:
   // default constructor : empty and kinda useless
   Set() : numItemss(0), cap(0), data(NULL) {}
   
   // non-default constructor : pre-allocate
   Set(int capacity) throw (const char *);
   
   // copy constructor : copy it
   Set(const Set & rhs) throw (const char *);
   
   // destructor : free everything
   ~Set()
   {
      if (cap)
      {
         delete [] data;
      }
   }
   
   // how many items
   int size () const
   {
      return numItemss;
   }
   
   // max number of the set
   int capacity () const
   {
      return cap;
   }
   
   // is the set empty
   bool empty() const
   {
      return numItemss == 0;
   }
   
   // remove everything from the set
   void clear()
   {
      numItemss = 0;
   }
   
   //begin
   SetIterator <T> begin()
   {
      return SetIterator <T> (data);
   }
   
   //end
   SetIterator <T> end()
   {
      return SetIterator <T> (data + numItemss);
   }
   
   //intersecetion
   Set <T> operator && (const Set <T> &rhs) throw (const char *);
   //assignment
   Set <T> & operator = (const Set <T> &rhs) throw (const char *);
   //insert
   void insert(const T & t) throw (const char *);
   //union
   Set <T> operator || (const Set <T> &rhs) throw (const char *);
   //find
   int find(const T & t);
   //erase
   void erase(int eraseIndex);
   //resize
   void resize(int cap) throw (const char *);
   
private:
   T * data;         // dynamically allocated array of T
   int numItemss;  // how many items are currently in the set
   int cap;  // how many items can I put on the set before full?
   
};

/**************************************************
 * SET ITERATOR
 * An iterator through set
 *************************************************/
template <class T> class SetIterator
{
private:
   T * p;
   
public:
   // default constructor
   SetIterator() : p(NULL) {}
   
   // initialize to direct p to some item
   SetIterator(T * p) : p(p) {}
   
   // rhs side equals this rhs
   SetIterator(const SetIterator &rhs) { *this = rhs; }
   
   // not equals operator
   bool operator != (const SetIterator &rhs) const
   {
      return rhs.p != this->p;
   }
   
   // dereference operator
   T & operator * ()
   {
      return *p;
   }
   
   // prefix increment
   SetIterator<T> & operator ++ ()
   {
      p++;
      return *this;
   }
   
   // postfix increment
   SetIterator <T> operator ++ (int postfix)
   {
      SetIterator tmp(*this);
      p++;
      return tmp;
   }
   
   // equals equals operator
   bool operator == (const SetIterator &lhs) const
   {
      return lhs.p == this->p;
   }
   
   // equals operator
   SetIterator & operator = (const SetIterator &rhs)
   {
      this->p = rhs.p;
      return *this;
   }
};

/*******************************************
 * SET :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Set<T> :: Set (const Set<T> & rhs) throw (const char *)
{
   
   if (rhs.cap == 0)
   {
      cap = numItemss = 0;
      data = NULL;
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
   numItemss = rhs.numItemss;
   
   for (int i = 0; i < numItemss; i++)
   {
      data[i] = rhs.data[i];
   }
   
   for (int i = numItemss; i < cap; i++)
   {
      data[i] = T();
   }
   
}

/**********************************************
 * SET : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Set<T> :: Set(int capacity) throw(const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      
      this->cap = this->numItemss = 0;
      this->data = NULL;
      return;
   }
   
   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: attempting to allocate buffer";
   }
   
   // copy over the stuff
   this->cap = capacity;
   this->numItemss = 0;
   
   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
   {
      data[i] = T();
   }
   
}

/*******************************************
 * SET :: ASSIGNMENT OPERATOR
 *******************************************/
template <class T>
Set<T> & Set <T> :: operator = (const Set <T> & rhs) throw (const char *)
{
   if (cap)
   {
      delete [] data;
   }
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = 0;
      numItemss = 0;
      data = NULL;
      return *this;
   }
   
   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Vector";
   }
   
   numItemss = rhs.numItemss;
   cap = rhs.cap;
   
   for(int i = 0; i < numItemss; i++)
   {
      data[i] = rhs.data[i];
   }
   return *this;
}

/*******************************************
 * SET :: UNION OPERATOR
 *******************************************/
template <class T>
Set <T> Set <T> :: operator || (const Set <T> & rhs) throw (const char *)
{
   Set <T> setReturn;
   int iLhs = 0;
   int iRhs = 0;
   
   while(iLhs < this->numItemss || iRhs < rhs.numItemss)
   {
      if(iLhs == this->numItemss)
      {
         setReturn.insert(rhs.data[iRhs++]);
      }
      else if(iRhs == rhs.numItemss)
      {
         setReturn.insert(this->data[iLhs++]);
      }
      else if(this->data[iLhs] == rhs.data[iRhs])
      {
         setReturn.insert(this->data[iLhs]);
         iLhs++;
         iRhs++;
      }
      else if(this->data[iLhs] < rhs.data[iRhs])
      {
         setReturn.insert(this->data[iLhs++]);
      }
      else
      {
         setReturn.insert(rhs.data[iRhs++]);
      }
   }
   return setReturn;
}

/*******************************************
 * SET :: INTERSECTION OPERATOR
 *******************************************/
template <class T>
Set <T> Set <T> :: operator && (const Set <T> &rhs) throw (const char *)
{
   Set <T> setReturn;
   
   int iLhs = 0;
   int iRhs = 0;
   while(iLhs < numItemss || iRhs < rhs.numItemss)
   {
      if(iLhs == numItemss)
      {
         return setReturn;
      }
      else if(iRhs == rhs.numItemss)
      {
         return setReturn;
      }
      else if(data[iLhs] == rhs.data[iRhs])
      {
         setReturn.insert(data[iLhs]);
         iLhs++;
         iRhs++;
      }
      else if(data[iLhs] < data[iRhs])
      {
         iLhs++;
      }
      else
      {
         iRhs++;
      }
   }
   
   return setReturn;
}

/*******************************************
 * SET :: FIND
 * Finds the item
 *******************************************/
template <class T>
int Set <T> :: find (const T & t)
{
   int iBegin = 0;
   int iMiddle = 0;
   int iEnd = numItemss - 1;
   
   while(iBegin <= iEnd)
   {
      iMiddle = ((iBegin + iEnd) / 2);
      
      if(t == data[iMiddle])
      {
         return iMiddle;
      }
      
      if(t < data[iMiddle])
      {
         iEnd = iMiddle - 1;
      }
      
      else
      {
         iBegin = iMiddle + 1;
      }
   }
   return -1;
}

/**********************************************
 * SET : RESIZE
 * Reallocate the container
 **********************************************/
template <class T>
void Set <T> :: resize (int cap) throw(const char*)
{
   try
   {
      T * temp;
      if (cap == 0)
      {
         cap = 1;
         data = new T[cap];
         return;
      }
      else
      {
         temp = new T[cap *= 2];
         
         for (int i = 0; i < numItemss; i++)
         {
            temp[i] = data[i];
         }
         delete [] data;
         data = temp;
      }
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: attempting to allocate a new buffer for deque";
   }
}

/*******************************************
 * SET :: INSERT
 * Inserts the item
 *******************************************/
template <class T>
void Set <T> :: insert (const T & t) throw (const char *)
{
   int iInsert = find(t);
   if(iInsert != -1)
   {
      return;
   }
   
   if (cap == numItemss)
   {
      resize(cap);
   }
   
   int i = 0;
   for(i = numItemss - 1; i >= 0 && data[i] > t; i--)
   {
      data[i + 1] = data[i];
   }
   data[i + 1] = t;
   numItemss++;
}

/*******************************************
 * SET :: ERASE
 *******************************************/
template <class T>
void Set <T> :: erase (int eraseIndex)
{
   for(int i = eraseIndex; i < numItemss -1; i++)
   {
      data[i] = data[i + 1];
   }
   numItemss--;
}

#endif /* set_h */
