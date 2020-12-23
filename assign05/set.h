
/***********************************************************************
 * Header:
 *    Set
 * Summary:
 *    This class contains the notion of an vector: a bucket to hold
 *    data for the user.
 *
 *    This will contain the class definition of:
 *       set
 *       set :: iterator : an iterator through the array
 * Author
 *    Br. Helfrich, Ben Crowe, Ladell Owens
 ************************************************************************/

#ifndef SET_H
#define SET_H

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
	 * SET
	 * A class that holds stuff
	 ***********************************************/
	template <class T>
	class set
	{
	public:
		// constructors and destructors
		set() : data(NULL), numElements(0), numCapacity(0) {}
		
		set(const int & numElements)                  throw (const char *);
		set(const set & rhs)        throw (const char *);
		~set() { if (data != NULL) delete[] data; }
		set & operator = (const set & rhs) throw (const char *);

		// standard container interfaces
		int  size()     const { return numElements; }	

		bool empty()  const { return numElements == 0; }
					  		
		void clear() { numElements = 0; }
			  
		void insert(const T &t);

		
		// set operator ||
	   set <T>  operator || (const set <T> & rhs) const throw (const char*);

		//set  &&
		set <T> operator && (const set <T> & rhs) const throw (const char*);

		// set operator -
		set  <T> operator - (const set <T> &rhs) const throw (const char*);


		// the various iterator interfaces
		class iterator;
		iterator begin() { return iterator(data); }
		iterator end() { return iterator(data + numElements); }
		iterator find(T t);
		iterator erase(iterator it);

		class const_iterator;
		const_iterator cbegin() const { return const_iterator(data); }
		const_iterator cend()  const { return const_iterator(data + numElements); }

	private:
		T * data;              // dynamically allocated array of T
		int numElements;       // both the capacity and the number of elements
		int numCapacity;


		void resize(int newCapacity);
		int findIndex(const T  &t) const;

	};

	/**************************************************
	 * SET ITERATOR
	 * An iterator through array
	 *************************************************/
	template <class T>
	class set <T> ::iterator
	{
	public:
		// constructors, destructors, and assignment operator
		iterator() : p(NULL) {              }
		iterator(T * p) : p(p) {              }
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
		T & operator * () { return *p; }
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
	 * SET CONSTANT ITERATOR
	 * An iterator through array that is read only,
	 * it won't change anything
	 *************************************************/
	template <class T>
	class set <T> ::const_iterator
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

	
		
	/*********************************************
	* SET :: FIND
	*
	*********************************************/
	template <class T>
	typename set <T> ::iterator set<T> ::find(T t)
	{
		int iBegin = 0;
		int iEnd = numElements - 1;
		//make iMiddle the beggining and end 
		//divided by two
		while (iBegin <= iEnd)
		{
			int iMiddle = (iBegin + iEnd) / 2;

			//if the item the entered is iMiddle
			//return the iterator address of the item in the middle
			if (t == data[iMiddle])
				return iterator(&data[iMiddle]); //return iterater(data + iMiddle)

			//shift the items if the item is found
			if (t < data[iMiddle])
				iEnd = iMiddle - 1;
			else
				iBegin = iMiddle + 1;
		}
		return iterator(data + numElements); //This is the same as the end() function


	}

	/*********************************************
	* SET :: ERASE
	*
	**********************************************/
	template <class T>
	typename set <T> ::iterator set<T> ::erase(iterator it)
	{
		/*iErase = find(t) this is the old code without iterators
			if (data[iErase] == t)
				for (int i = iErase; i < numElements; i++)
					data[i] = data[i + 1];
		numElements--;*/

		if (it != end())
		{
			iterator current = it;
			iterator next = ++it;
			while (next != end())
			{
				*current = *next;
				current++;
				next++;
			}
			numElements--;


		}
		return --it;
			
	}

	/*******************************************
	 * SET :: Assignment
	 *******************************************/
	template <class T>
	set <T> & set <T> :: operator = (const set <T> & rhs)
		throw (const char *)
           {
              clear();
              if (rhs.numElements > numCapacity)
                 resize(rhs.numElements);

		// copy over the capacity
              numElements = rhs.numElements;
		// copy the items over one at a time using the assignment operator
		for (int i = 0; i < numElements; i++)
			data[i] = rhs.data[i];

		return *this;
	}

	/*******************************************
	 * SET :: COPY CONSTRUCTOR
	 *******************************************/
	template <class T>
	set <T> ::set(const set <T> & rhs) throw (const char *)
	{
           numElements =0;
           numCapacity = 0;
           data = NULL;
           *this = rhs;
		
	}

	/**********************************************
	 * SET : NON-DEFAULT CONSTRUCTOR
	 * Preallocate the vector to "capacity"
	 **********************************************/
	template <class T>
	set <T> ::set(const int & numCapacity) throw (const char *)
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
			throw "ERROR: Unable to allocate a new buffer for set";
		}


		this->numCapacity = numCapacity;
		this->numElements = 0;
		

	}

	
	/********************************************
	 * SET : INSERT
	 * Adds an item to the  SET,
	 * doubles the capacity when the SET is
	 * full
	 *******************************************/
	template <class T>
	void set <T> ::insert(const T & t)
	{
           if (numCapacity == 0 )
              resize(1);
           else if (size() == numCapacity)
              resize(numCapacity * 2);
                 //find where the item belongs in the list
		int iInsert = findIndex(t);
		//put the item in the list if it's not found 
		if (data[iInsert] != t)
                {
                   //shifting the elements to make space for new
                   //item
                   for (int i = numElements; i > iInsert; i--)
                      data[i] = data[i - 1];
                   //inst  alling the new item in the list
                   
                   data[iInsert] = t;
                   
                   numElements++;
                }
	}

	/********************************************
	* SET : || UNION OPERATOR 
	*
	********************************************/
	template <class T>
	set <T> set <T> :: operator || (const set <T> & rhs) const throw (const char*)
	{
		set <T> newSet;
		int iLhs = 0;
		int iRhs = 0;
		while (iLhs < this->numElements || iRhs < rhs.numElements)
		//while (iLhs < this->numElements && iRhs < rhs.numElements)
		{
			if (iLhs == this->numElements)
                        {
				newSet.insert(rhs.data[iRhs++]);
			}

			else if (iRhs == rhs.numElements)
                        {
				newSet.insert(data[iLhs++]);
                        }

			else if (data[iLhs] == rhs.data[iRhs])
			{
				newSet.insert(data[iLhs]);
				iLhs++;
				iRhs++;
			}

			else if (data[iLhs] < rhs.data[iRhs])
                        {
				newSet.insert(data[iLhs++]);
                        }
			else
                        {
				newSet.insert(data[iRhs++]);
                        }
			
		}
		return newSet;
	}

	/********************************************
	* SET : && INTERSECTION OPERATOR
	*
	*********************************************/
	template <class T>
	set<T> set<T> ::operator && (const set <T> & rhs) const throw (const char*)
	{
		set <T> intersection;
		int iLhs = 0;
		int iRhs = 0;
		while (iLhs < this->numElements || iRhs < rhs.numElements)
		{
			if (iLhs == this->numElements)
				return intersection;
			else if (iRhs == rhs.numElements)
				return intersection;
			else if (data[iLhs] == rhs.data[iRhs])
			{
				intersection.insert(data[iLhs]);
				iLhs++;
				iRhs++;
			}
			else if (data[iLhs] < rhs.data[iRhs])
				iLhs++;
			else
				iRhs++;
		}
		return intersection;
	}

	/********************************************
	* SET : DIFFERENCE OPERATOR
	*
	*********************************************/
	template <class T>
	set<T> set<T> ::operator - (const set <T> &rhs) const throw (const char*)
	{
		set <T> difference;
		int iLhs = 0;
		int iRhs = 0;
		while (iLhs < this->numElements || iRhs < rhs.numElements)
		{
			if (iLhs == this->numElements)
				return difference;
			else if (iRhs == rhs.numElements)
				//return difference;
				difference.insert(data[iLhs++]);
			else if (data[iLhs] == rhs.data[iRhs])
			{
				//intersection.insert(data[iLhs]);
				iLhs++;
				iRhs++;
			}
			else if (data[iLhs] < rhs.data[iRhs])

				difference.insert(data[iLhs++]);


			else if (data[iLhs] > rhs.data[iRhs])


				//difference.insert(data[iRhs++]);
				iRhs++;
			
		}
		return difference;
	
	}

	/********************************************
	 * SET : RESIZE
	 * Allocates a new array and deletes the old
	 * when the capacity has been met
	 *******************************************/
	template <class T>
	void set <T> ::resize(int newCapacity)
	{
		T * newArray;
		try
		{
			newArray = new T[newCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for set";
		}
		for (int i = 0; i < numElements; i++)
			newArray[i] = data[i];
		if (data != NULL)
			delete[] data;
		data = newArray;
		this->numCapacity = newCapacity;
	}

	/******************************************
	* SET :: FIND INDEX
	*
	*******************************************/
	template <class T>
	int set <T> ::findIndex(const T &t) const
	{
		for (int i = 0; i < size(); i++)
	
			if (data[i] >= t)
				return i;
		return numElements;
	}

}; // namespace custom

#endif // SET_H
