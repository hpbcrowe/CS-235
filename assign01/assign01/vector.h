/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of an vector: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::array
 *       vector :: iterator : an iterator through the array
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * VECTOR
 * A class that holds stuff
 ***********************************************/
template <class T>
class vector
{
public:
	// constructors and destructors
  vector() : data(NULL), numElements(0), numCapacity(0)
   { this->numElements = numElements,this->numCapacity = numCapacity;}
   vector(const int & numElements)                  throw (const char *);
   vector(const vector & rhs)        throw (const char *);
   ~vector()                         { if(data != NULL) delete [] data; }
   vector & operator = (const vector & rhs) throw (const char *);
   
   // standard container interfaces
   // vector treats size and max_size the same
   int  size()     const { return numElements;                 }
   int  capacity() const { return numCapacity;                 }

   bool empty()  const { return numElements == 0; }
   
		  

   void clear() {numElements = 0;}

   
   void push_back(const T & t);
   
   
   // vector-specific interfaces
   // what would happen if I passed -1 or something greater than num?
   T & operator [] (int index)       throw (const char *)
   {
      if(index < 0 || index >= numElements)
         throw "ERROR: Invalid index";
      return data[index];
   }

   const T & operator [] (int index) const throw (const char *)
   {
      if(index < 0 || index >= numElements)
         throw "ERROR: Invalid index";
      return data[index];
   }
      
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();

   class const_iterator;
   const_iterator cbegin() const { return const_iterator(data); }
   const_iterator cend()  const ;
   
private:
   T * data;              // dynamically allocated array of T
   int numElements;       // both the capacity and the number of elements
   int numCapacity;

   
   void resize(int newCapacity);
	
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through array
 *************************************************/
template <class T>
class vector <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
   // prefix decrement
   iterator & operator -- ()
   {
      p--;
      return *this;
   }
   
   //postfix decrement
   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      p--;
      return tmp;
   }
private:
   T * p;
};

/**************************************************
 * VECTOR CONSTANT ITERATOR
 * An iterator through array that is read only,
 * it won't change anything
 *************************************************/
template <class T>
class vector <T> ::const_iterator
{
public:
   // constructors, destructors, and assignment operator
  const_iterator() : p(NULL) {              }
  const_iterator(T * p) : p(p) {              }
   const_iterator(const const_iterator & rhs) { *this = rhs; }
   const_iterator & operator = (const const_iterator & rhs)
      {
         this->p = rhs.p;
         return *this;
      }

   // equals, not equals operator
   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }
   
   // dereference operator
   T & operator * () { return *p; }
   const T & operator * () const { return *p; }
   
   // prefix increment
   const_iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   const_iterator operator ++ (int postfix)
   {
      const_iterator tmp(*this);
      p++;
      return tmp;
   }
   
   // prefix decrement
   const_iterator & operator -- ()
   {
      p--;
      return *this;
   }

   //postfix decrement
   const_iterator operator -- (int postfix)
   {
      const_iterator tmp(*this);
      p--;
      return tmp;
   }

private:
	T * p;
};

/********************************************
 * VECTOR :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: iterator vector <T> :: end ()
{
   return iterator (data + numElements);
}

/********************************************
 * VECTOR :: CONSTANT END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> ::const_iterator vector <T> ::cend() const
{
   return const_iterator(data + numElements);
}

/*******************************************
 * VECTOR :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
          throw (const char *)
{

   // do nothing if there is nothing to do
   if (rhs.numCapacity == 0)
   {
      numCapacity = 0;
      numElements = 0;
      data = NULL;
      return *this;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for vector";
   }

   // copy over the capacity
   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;
   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];

   return *this;
}

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) throw (const char *)
{
   
   // do nothing if there is nothing to do
   if (rhs.numCapacity == 0)
   {
      numCapacity = 0;
      numElements = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for vector";
   }
   
   // copy over the capacity
   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;
   
   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(const int & numCapacity) throw (const char *)
{
   assert(numCapacity >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (numCapacity == 0)
   {
      this->numCapacity = 0;
      this->numElements = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for vector";
   }

      
   this->numCapacity = numCapacity;
   this->numElements = numElements;
   numElements = 10;
   
}

/********************************************
 * VECTOR : PUSHBACK
 * Adds an item to the end of the vector, 
 * doubles the capacity when the vector is 
 * full
 *******************************************/
template <class T>
void vector <T> ::push_back(const T & t)
{
   if (numCapacity == 0)
      resize(1);
   else if (numElements == numCapacity)
      resize(numCapacity * 2);
		
   data[numElements++] = t;

}


/********************************************
 * VECTOR : RESIZE
 * Allocates a new array and deletes the old
 * when the capacity has been met
 *******************************************/
template <class T>
void vector <T> :: resize(int newCapacity)
{
   T * newArray;
   try
   {
      newArray = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for vector";
   }
   for (int i = 0; i < numElements; i++)
      newArray[i] = data[i];
   if (data != NULL)
      delete[] data;
   data = newArray;
   this->numCapacity = newCapacity;
}
}; // namespace custom

#endif // VECTOR_H

