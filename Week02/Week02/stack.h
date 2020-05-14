#ifndef STACK_H
#define STACK_H

#include <cassert>

// forward declaration for ContainerIterator
template <class T>
class StackIterator;

/************************************************
 * CONTAINER
 * A class that holds stuff
 ***********************************************/
template <class T>
class Stack
{
public:
   // default constructor : empty and kinda useless
   Stack() : numItems(0), cap(0), data(NULL) {}
   
   // copy constructor : copy it
   Stack(const Stack & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Stack(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Stack()        { if (cap) delete [] data; }
   
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
   
   //Returns value of element from top of stack
   T & top() throw (const char *);
   
   // add an item to the container
   void insert(const T & t) throw (const char *);
   
   // return an iterator to the beginning of the list
   StackIterator <T> begin() { return StackIterator<T>(data); }
   
   // return an iterator to the end of the list
   StackIterator <T> end() { return StackIterator<T>(data + numItems);}
   
   //Resize the Capacity
   void resize() throw (const char *);
   
   //Copy data from one vector to another
   Stack& operator= (const Stack &rhs)
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
   
};

/**************************************************
 * CONTAINER ITERATOR
 * An iterator through Container
 *************************************************/
template <class T>
class StackIterator
{
public:
   // default constructor
   StackIterator() : p(NULL) {}
   
   // initialize to direct p to some item
   StackIterator(T * p) : p(p) {}
   
   
   // not equals operator
   bool operator != (const StackIterator & rhs) const
   {
      return rhs.p != this->p;
   }
   
   // dereference operator
   T & operator * ()
   {
      return *p;
   }
   
   // prefix increment
   StackIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }
   
   // postfix increment
   StackIterator <T> operator++(int postfix)
   {
      StackIterator tmp(*this);
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
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
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
void Stack<T> :: resize() throw (const char *)
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
void Stack<T> :: push (const T & t) throw (const char*)
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
void Stack<T> :: pop() throw (const char *)
{
   if(numItems == 0 || cap <= 0)
      throw "ERROR: Unable to pop from an empty Stack";
   
   numItems -= 1;
   return;
}

/**********************************************
 * stack : TOP
 * return value of top item
 **********************************************/
template <class T>
T & Stack <T> :: top() throw (const char *)
{
   // if the stack is empty, throw an error.
   if(numItems == 0 || cap <= 0)
      throw "ERROR: Unable to reference the element from an empty Stack";
   
   return data[numItems-1];
}
/**********************************************
 * CONTAINER : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Stack<T> :: Stack(int capacity) throw (const char *)
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
void Stack<T> :: insert(const T & t) throw (const char *)
{
   // do we have space?
   if (cap == 0 || cap == numItems)
      throw "ERROR: Insufficient space";
   
   // add an item to the end
   data[numItems++] = t;
}


#endif // STACK_H
