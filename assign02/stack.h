/***********************************************************************
 * Header:
 *    Stack
 * Summary:
 *    This class contains the notion of a stack: a bucket to hold
 *    data for the user. Which is last in first out
 *
 *    This will contain the class definition of:
 *       Stack           
 * Author
 *    Br. Helfrich, Ben Crowe, Ladell Owens
 ************************************************************************/

#ifndef STACK_H
#define STACK_H

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
 * STACK
 * A class that holds stuff
 ***********************************************/
template <class T>
class stack
{
public:
	// constructors and destructors
  stack() : data(NULL), numElements(0), numCapacity(0)
   { }
   stack(const int & numElements)                  throw (const char *);
   stack(const stack & rhs)        throw (const char *);
   ~stack()                         { if(data != NULL) delete [] data; }
   stack & operator = (const stack & rhs) throw (const char *);
   
   // standard container interfaces
   //size returns the number of items in stack
   int  size()     const { return numElements;                 }
	
	//capacity returns the allocated space in the stack
   int  capacity() const { return numCapacity;                 }
	
	//empty returns true if there are no elements 
   bool empty()  const { return numElements == 0; }
   
	//Clear changes the number of items to 0
	void clear() {numElements = 0;}

   //Adds an item to the end of the stack
   void push(const T & t);
   
	//Subtracts one item off the end of the stack
	void pop();

	//Accesses the last item on the stack
	//A read/write and a const read only 
	T & top() throw (const char *);

	//Constant read only 
	const T & top() const throw (const char *);   
   
private:
   T * data;              // dynamically allocated array of T
   int numElements;       // both the capacity and the number of elements
   int numCapacity;
 
   void resize(int newCapacity);
	
};

/*******************************************
 * STACK :: Assignment
 *******************************************/
template <class T>
stack <T> & stack <T> :: operator = (const stack <T> & rhs)
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
   if(data != NULL )
      delete[] data; 
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
 * STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
stack <T> :: stack(const stack <T> & rhs) throw (const char *)
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
 * STACK : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
stack <T> :: stack(const int & numCapacity) throw (const char *)
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
   this->numElements = 0;
}

/********************************************
 * STACK : PUSH
 * Adds an item to the end of the stack, 
 * doubles the capacity when the stack is 
 * full
 *******************************************/
template <class T>
void stack <T> ::push(const T & t)
{
   if (numCapacity == 0)
      resize(1);
   else if (numElements == numCapacity)
      resize(numCapacity * 2);
		
   data[numElements++] = t;
}

/********************************************
 * STACK : POP
 * Subtracts an item to the end of the stack,
 * doubles the capacity when the stack is
 * full
 *******************************************/
template <class T>
void stack <T> :: pop()
{
   if (!empty())
      --numElements;
}

/********************************************
 * STACK : TOP
 * Accesses the last element added to the stack.
 * Functions both as a getter and as a setter.
 *******************************************/
template <class T>
T &stack <T> ::top() throw (const char *)
{
   if (!empty())
      return data[size() - 1];
   else
      {
         throw	"ERROR: Unable to reference the element from an empty Stack";
      }
}

/********************************************
* STACK : TOP
* Accesses the last element added to the stack.
* Functions both as a getter and as a setter.
*******************************************/

template <class T>
const T &stack <T> ::top() const throw (const char *)
{
   if (!empty())
      return data[size() - 1];
	else
	{
           throw "ERROR: Unable to reference the element from an empty Stack";
	}
}

/********************************************
 * VECTOR : RESIZE
 * Allocates a new array and deletes the old
 * when the capacity has been met
 *******************************************/
template <class T>
void stack <T> :: resize(int newCapacity)
{
   T * newArray;
   try
   {
      newArray = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for stack";
   }
   for (int i = 0; i < numElements; i++)
      newArray[i] = data[i];
   if (data != NULL)
      delete[] data;
   data = newArray;
   this->numCapacity = newCapacity;
}
}; // namespace custom

#endif // STACK_H

