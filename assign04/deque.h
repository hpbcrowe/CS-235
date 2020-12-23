/***********************************************************************
 * Header:
 *    Deque
 * Summary:
 *    This class contains the notion of a stack: a bucket to hold
 *    data for the user. Which is first in first out
 *    The deque can be added to from the front or the back it also
 *    can remove items from the front or the back
 *
 *    This will contain the class definition of:
 *              Deque
 * Author
 *    Br. Helfrich, Ben Crowe, Ladell Owens
 ************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

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
* DEQUE
* A class that holds stuff
*************************************************/
   template <class T>
      class deque
   {
     public:
      // constructors and destructors
     deque() : data(NULL), iFront(0), iBack(-1), numCapacity(0)
      { }
      deque(const int & numCapacity) throw (const char *);

      // copy constructor
      deque(const deque & rhs) throw (const char *);

      // destructor
      ~deque()
      {
         if (data != NULL)
         {
            delete[] data;
         }
      }
      deque & operator = (const deque & rhs) throw (const char *);

      // standard container interfaces
      //size returns the number of items in stack
      int  size() const { return iBack - iFront + 1; }

      //empty returns true if there are no elements
      bool empty() const { return size() == 0; }

      //Clear changes the number of items to 0
      void clear() { iFront = 0; iBack = -1; }

      //Adds an item to the end of the stack
      void push_back(const T & t) throw (const char*);

      //Adds an item to the front of the stack
      void push_front(const T & t) throw (const char*);

      //Subtracts one item off the end of the stack
      void pop_back() throw (const char*);

      //Subtracts one item off the front of the stack
      void pop_front() throw (const char*);

      //Accesses the head item on the queue
      //A read/write and a const read only
      T & front() throw (const char *);

      //Constant read only 
      const T & front() const throw (const char *);

      //Accesses the last item on the queue
      //A read/write and a const read only
      T & back() throw (const char *);

      //Constant read only 
      const T & back() const throw (const char *);
      //
      void display() const;
     private:
      T * data;         // dynamically allocated array of T
      int iFront;      // index of the front
      int iBack;       // indes of the back
      int numCapacity;  // the amount of possible spaces in the the queue

      //Adjusts the deque (array) when the capacity needs to change
      void resize(int newCapacity);
      //Acts like a getter to return the capacity
      int capacity() const { return numCapacity; }
      //Adjusts or wraps the deque to fill empty spaces
      //in relation to the front
      int iFrontNormalize() const;
      //Adjusts or wraps the deque to fill empty spaces
      //in relation to the back
      int iBackNormalize() const;
      //This function needs to be filled in, ifrontnormalize
      //ibacknormalize, the assignment operator, all use this
      //function
      int iNormalize(int iposition) const;
   };

   /*******************************************
    * DEQUE :: Assignment
    *******************************************/
   template <class T>
      deque <T> & deque <T> :: operator = (const deque <T> & rhs)
      throw (const char *)
      {
         clear();
         if (this->capacity() < rhs.size())
         {
            resize(rhs.size());
         }
         for (int i = 0; i < rhs.size(); i++)
         {
            data[i] = rhs.data[rhs.iNormalize(rhs.iFront + i)];
         }
         this->iBack = rhs.size()-1;
         this->iFront = 0;
         

         return *this;
      }

   /*******************************************
    *	 DEQUE :: COPY CONSTRUCTOR
    *******************************************/
   template <class T>
      deque <T> ::deque(const deque <T> & rhs) throw (const char *)
   {
      if (rhs.numCapacity == 0)
      {
         this->iFront = 0;
         this->iBack = -1;
         this->numCapacity = 0;
         this->data = NULL;
         return;
      }
       try
       {
          data = new T[rhs.numCapacity];
       }
       catch (std::bad_alloc)
       {
          throw "ERROR: Unable to allocate a new buffer for deque";
       }
       
      
      this->numCapacity = rhs.numCapacity;
      //std::cerr << rhs.size();
      for (int i = 0; i < rhs.numCapacity; i++)
      {
         this->data[i] = rhs.data[rhs.iNormalize(rhs.iFront + i)];
         //	data[i] = rhs.data[i];
      }
      this->iBack = rhs.size()-1;
      this->iFront = 0;
      
   }

   /**********************************************
    * DEQUE : NON-DEFAULT CONSTRUCTOR
    * Preallocate the vector to "capacity"
    **********************************************/
   template <class T>
      deque <T> ::deque(const int & numCapacity) throw (const char *)
   {
      assert(numCapacity >= 0);

      this->iFront = 0;
      this->iBack = -1;
      // do nothing if there is nothing to do.
      // since we can't grow an array, this is kinda pointless
      if (capacity() <= 0)
      {
         this->numCapacity = 0;
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
         throw "ERROR: Unable to allocate a new buffer for deque";
      }
      this->numCapacity = numCapacity;
   }

   /********************************************
    * DEQUE : PUSH_BACK
    * Adds an item to the end of the DEQUE,
    * doubles the capacity when the DEQUE is
    * full
    *******************************************/
   template <class T>
      void deque <T> ::push_back(const T & t) throw(const char*)
   {
      if (empty())
      {
         resize(1);
      }
      if (size() == capacity())
      {
         resize(capacity() * 2);
      }
      iBack++;
      data[iBackNormalize()] = t;
   }

   /********************************************
    * DEQUE : PUSH_FRONT
    * Adds an item to the end of the DEQUE,
    * doubles the capacity when the DEQUE is
    * full
    *******************************************/
   template <class T>
      void deque <T> ::push_front(const T & t) throw(const char*)
   {
      if (empty())
      {
         resize(1);
      }
      if (size() == capacity())
      {
         resize(capacity() * 2);
      }
      iFront--;
      data[iFrontNormalize()] = t;
   }

   /********************************************
    * DEQUE : POP_BACK
    * Subtracts an item to the end of the DEQUE,
    * doubles the capacity when the DEQUE is
    * full
    *******************************************/
   template <class T>
      void deque <T> ::pop_back() throw (const char*)
   {
      if (!empty())
      {
         iBack--;
      }
   }

   /********************************************
    * DEQUE : POP_FRONT
    * Subtracts an item from the end of the DEQUE,
    ********************************************/
   template <class T>
      void deque <T> ::pop_front() throw (const char*)
   {
      if (!empty())
      {
         ++iFront;
      }
   }

   /********************************************
    * DEQUE :: FRONT
    * Accesses the last element added to the DEQUE.
    * Functions both as a getter and as a setter.
    *******************************************/
   template <class T>
      const T & deque <T> ::front() const throw (const char *)
   {
      if (!empty())
      {
         return data[iFrontNormalize()];
      }
      else
      {
         throw	"ERROR: unable to access data from an empty deque";
      }
   }

   /********************************************
    * DEQUE :: FRONT
    * Accesses the last element added to the DEQUE.
    * Functions both as a getter and as a setter.
    *******************************************/
   template <class T>
      T & deque <T> ::front()  throw (const char *)
   {
      if (!empty())
      {
         return data[iFrontNormalize()];

      }
      else
      {
         throw    "ERROR: unable to access data from an empty deque";
      }
   }


   /********************************************
   * DEQUE :: BACK
   * Accesses the last element added to the DEQUE.
   * Functions both as a getter and as a setter.
   *******************************************/
   template <class T>
      const T & deque <T> ::back() const throw (const char *)
   {
      if (!empty())
      {
         return data[iBackNormalize()];
      }
      else
      {
         throw	"ERROR: unable to access data from an empty deque";
      }
   }
   
   /********************************************
    * DEQUE :: BACK
    * Accesses the last element added to the DEQUE.
    * Functions both as a getter and as a setter.
    *******************************************/
   template <class T>
      T & deque <T> ::back() throw (const char *)
   {
      if (!empty())
      {
         return data[iBackNormalize()];
      }
      else
      {
         throw "ERROR: unable to access data from an empty deque";
      }
   }


   /********************************************
    * DEQUE : RESIZE
    * Allocates a new array and deletes the old
    * when the capacity has been met
    *******************************************/
   template <class T>
      void deque <T> ::resize(int newCapacity)
   {
      T * newArray;

      try
      {
         newArray = new T[newCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Deque";
      }

      //Loop through starting at head because array cb wrapped and not
      //in order, then copy over old array to new one, can't use data[i]
      //array won't be in order need to start at head % will advance
      //through after starting point ihead()
      for (int i = 0; i < size(); i++)
      {
         newArray[i] = data[iNormalize(iFront + i)];
      }

      if (data != NULL)
      {
         delete[] data;
      }

      data = newArray;
      this->numCapacity = newCapacity;
      this->iBack = size()-1;
      this->iFront = 0;
   }

   /********************************************
    * DEQUE : I FRONT NORMALIZE
    * Return valid index for the item in the front
    * of the deque
    *******************************************/
   template <class T>
      int deque<T> ::iFrontNormalize() const
   {
      return iNormalize(iFront);
   }

   /********************************************
    * DEQUE : I BACK NORMALIZE
    * Return valid index for the item in the back
    * of the deque
    *******************************************/
   template <class T>
      int deque<T> ::iBackNormalize() const
   {
      return iNormalize(iBack);
   }

   /********************************************
    * DEQUE : I  NORMALIZE
    * takes an index that may or may not be in
    * bounds and returns a valid index for index
    * given.
    *******************************************/
   template <class T>
      int deque<T> ::iNormalize(int iPosition) const 
   {
      while (iPosition < 0)
      {
         iPosition += capacity();
      }

      return iPosition % capacity();
   }

   /********************************************
    * DEQUE : DISPLAY
    * A debug utility to display the contents of the array
    *******************************************/
   template <class T>
      void deque <T> ::display() const
   {
      
#ifndef NDEBUG
      std::cerr << "queue<T>::display()\n";
      std::cerr << "\tiFront = " << iFront << "\n";
      std::cerr << "\tiBack = " << iBack << "\n";
      std::cerr << "\tnumCapacity = " << numCapacity << "\n";
      for (int i = 0; i < size(); i++)
         std::cerr << "\tdata[" << (iFront + i) % capacity()
                   << "] = " << data[(iFront + i) % capacity()]
                   << "\n";
#endif // NDEBUG
   }


}; // namespace custom

#endif // DEQUEUE_H

