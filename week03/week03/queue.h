#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>

// forward declaration for ContainerIterator
template <class T>
class QueueIterator;

/************************************************
 * CONTAINER
 * A class that holds stuff
 ***********************************************/
template <class T>
class Queue
{
public:
   // default constructor : empty and kinda useless
   Queue() : numItems(0), cap(0), data(NULL) {}
   
   // copy constructor : copy it
   Queue(const Queue & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Queue(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Queue()        { if (cap) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }
   
   // remove all the items from the container
   void clear()        { numItems = 0;                 }
   
   // how many items are currently in the container?
   int size() const    { return numItems;              }
   
   //return the number of elements that can be held in the currently allocated storage.
   int capacity() {return cap;}
   
   //Adds an element to the end of the vector and returns nothing
   void push(const T & t) throw (const char *);
   
   //Removes element from top of stack
   void pop() throw (const char *);
   
   //returns the head of the queue
   int iTail() const
   {
      return (numPush - 1) % cap;
   }
   
   //returns the head of the queue
   int iHead() const
   {
      return numPop % cap;
   }
   
   // add an item to the container
   void insert(const T & t) throw (const char *);
   
   // return an iterator to the beginning of the list
   QueueIterator <T> begin() { return QueueIterator<T>(data); }
   
   // return an iterator to the end of the list
   QueueIterator <T> end() { return QueueIterator<T>(data + numItems);}
   
   // gets the value from the front
   T & front() const throw (const char*);
   
   // gets the value from the back
   T & back() const throw (const char*);
   
   //Resize the Capacity
   void resize() throw (const char *);
   
   //front of the queue
   T front() throw (const char*)
   {
      if (empty())
      {
         throw "ERROR: attempting to access an item in an empty queue";
      }
      
      else
      {
         return data[iHead()];
      }
   }
   
   //back of the queue
   T back() throw (const char*)
   {
      if (empty())
      {
         throw "ERROR: attempting to access an item in an empty queue";
      }
      
      else
      {
         return data[iTail()];
      }
   }
   
   //Copy data from one vector to another
   Queue& operator= (const Queue &rhs)
   {
      assert(rhs.cap >= 0);
      
      // do nothing if there is nothing to do
      if (rhs.cap == 0)
      {
         cap = 0;
         numItems = 0;
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
         throw "ERROR: Unable to allocate buffer";
      }
      
      // copy over the capacity and size
      assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
      cap = rhs.cap;
      numItems = rhs.numItems;
      
      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numItems; i++)
         data[i] = rhs.data[i];
      
      // the rest needs to be filled with the default value for T
      for (int i = numItems; i < cap; i++)
         data[i] = T();
      
      
      return *this;
   }
   
   
   
private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Container?
   int cap;           // how many items can I put on the Container before full?
   int numPush;
   int numPop;
   
};

/**************************************************
 * CONTAINER ITERATOR
 * An iterator through Container
 *************************************************/
template <class T>
class QueueIterator
{
public:
   // default constructor
   QueueIterator() : p(NULL) {}
   
   // initialize to direct p to some item
   QueueIterator(T * p) : p(p) {}
   
   
   // not equals operator
   bool operator != (const QueueIterator & rhs) const
   {
      return rhs.p != this->p;
   }
   
   // dereference operator
   T & operator * ()
   {
      return *p;
   }
   
   // prefix increment
   QueueIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }
   
   // postfix increment
   QueueIterator <T> operator++(int postfix)
   {
      QueueIterator tmp(*this);
      p++;
      return tmp;
   }
   
private:
   T * p;
};

/*******************************************
 * CONTAINER :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);
   
   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = 0;
      numItems = 0;
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
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;
   
   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];
      
      // the rest needs to be filled with the default value for T
      for (int i = numItems; i < cap; i++)
         data[i] = T();
         }

/********************************************
 * VECTOR :: Resize
 * reallocate the vector to capacity.
 ********************************************/
template <class T>
void Queue<T> :: resize() throw (const char *)
{
   
   if (numItems + 1 > capacity())
   {
      T *temp = NULL;
      
      
      if (capacity() > 0)
         cap *= 2;
         else
            cap = 1;
            
            try
         {
            temp = new T[cap];
         }
      catch(std::bad_alloc)
      {
         throw "Failure";
      }
      
      for (int i = 0; i < numItems; i++)
         temp[i] = data[i];
         
         delete[] this->data;
      this->data = temp;
      
   }
   return;
}

/********************************************
 * Stack :: PUSH
 * inserts an Item in the collection and double the
 * object`s capacity when necessary.
 ********************************************/
template <class T>
void Queue<T> :: push (const T & t) throw (const char*)
{
   if (cap == numItems)
      resize();
      data[numItems++] = t;
      }

/**********************************************
 * stack : POP
 * Remove top item
 **********************************************/
template <class T>
void Queue <T> :: pop () throw(const char *)
{
   if (!empty())
   {
      numPop++;
      numItems--;
      
   }
   else
   {
      throw "ERROR: attempting to pop from an empty queue";
   }
}

/****************************************************************
 * QUEUE :: FRONT
 * Will check what value is at the front of the queue
 ****************************************************************/
template <class T>
T & Queue <T> :: front() const throw (const char*)
{
   if (!empty())
      return (data[iHead()]);
   else
   {
      throw "ERROR: attempting to access an element in an empty queue";
   }
}

/****************************************************************
 * QUEUE :: BACK
 * Will check what value is at the back of the queue
 ****************************************************************/
template <class T>
T & Queue <T> :: back() const throw (const char*)
{
   if (!empty())
      return (data[iTail()]);
   else
   {
      throw "ERROR: attempting to access an element in an empty queue";
   }
}

/**********************************************
 * CONTAINER : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Queue<T> :: Queue(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
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
      throw "ERROR: Unable to allocate buffer";
   }
   
   
   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;
   
   // initialize the container by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
      }

/***************************************************
 * CONTAINER :: INSERT
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Queue<T> :: insert(const T & t) throw (const char *)
{
   // do we have space?
   if (cap == 0 || cap == numItems)
      throw "ERROR: Insufficient space";
   
   // add an item to the end
   data[numItems++] = t;
}


#endif // STACK_H
