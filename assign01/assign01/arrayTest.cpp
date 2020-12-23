/***********************************************************************
 * Program
 *    Array Test
 * Summary:
 *    This program is designed to test the array class as defined
 *    in array.h.  It will illustrate how to include the array
 *    class, instantiate an array object, and iterate through an
 *    array using array :: iterator;
 * Author:
 *    Br. Helfrich
 *************************************************************************/

#include <iostream>     // for CIN and COUT
#include <iomanip>      // for SETW
#include "array.h"      // for ARRAY
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ostream;
using std::ios;
using std::setw;
using namespace custom;

/*************************************************
 * MAIN
 * Just a simple driver program
 *************************************************/
int main()
{
   // create two arrays, one of 10 values and one of 5.
   array <int> a1(10 /* numCapacity */);
   array <int> a2(5  /* numCapacity */);

   // fill the first with numbers
   for (int i = 0; i < a1.size(); i++)
      a1[i] = 100 + i;
   cout << "\ta1:";
   for (array <int> :: iterator it = a1.begin(); it != a1.end(); ++it)
      cout << setw(5) << *it;
   cout << endl;

   // fill the second with user input:
   cout << "Please enter " << a2.size() << " integers:\n";
   for (int i = 0; i < a2.size(); i++)
   {
      cout << "> ";
      cin  >> a2[i];
   }

   // make a copy of the second that is constant
   const array <int> a3(a2);
   cout << "\ta3:";
   for (int i = 0; i < a3.size(); i++)
      cout << setw(5) << a3[i];
   cout<< endl;
   

   // try to copy arrays of different sizes
   array <int> a4(9);
   cout << "Attempting to copy an array of size "
        << a1.size()
        << " onto an array of size "
        << a4.size()
        << endl;
   try
   {
      a4 = a1;
      cout << "\tWe were able to copy the array\n";
   }
   catch (const char * e)
   {
      cout << "\tCaught exception: \""
           << e
           << "\"\n";
   }

   // use the copy constructor
   array <int> a5(a1);
   cout << "The value of a5 before we destroy a1:\n";
   cout << "\ta5:";
   for (array <int> :: iterator it = a5.begin(); it != a5.end(); ++it)
      cout << setw(5) << *it;
   cout << endl;

   // use the iterator to set values
   for (array <int> :: iterator it = a1.begin(); it != a1.end(); ++it)
      *it = -1;

   // after we have changed the values, a4 should be unchanged
   cout << "After setting everything in a1 to -1, here is the results:\n";
   cout << "\ta1:";
   for (array <int> :: iterator it = a1.begin(); it != a1.end(); ++it)
      cout << setw(5) << *it;
   cout << endl;
   cout << "\ta5:";
   for (array <int> :: iterator it = a5.begin(); it != a5.end(); ++it)
      cout << setw(5) << *it;
   cout << endl;

   

}
