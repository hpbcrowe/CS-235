/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Ladell Owens, Ben Crowe
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE

using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   //use to enter course name, student
   string selection;
   custom::deque<storeTicket> ticketList;

   //initiate struct
   storeTicket presentClient;

   //to iterate
   int counter = 0;

   presentClient.minutes = 0;
   do
   {
      //This first part deals with building the ticket putting
      //the information the user gives into the ticket struct
      //Puts the line number on the screen
      cout << "<" << counter << "> ";
      counter++;
      cin >> selection;

      //This is the emergency selection
      if (selection == "!!")
      {
         createEmergencyTicket(ticketList);
         // presentClient = processTickets(presentClient,ticketList);
      }

      else if (selection == "none" || selection == "None" ||
               selection == "NONE")
      {
         // presentClient = processTickets(presentClient,ticketList);
      }

      //Trying to anticipate all possible course entries
      else if 
         
	 (selection == "cs124" || selection == "CS124"
          || selection == "cs165" || selection == "CS165"
          || selection == "cs235" || selection == "CS235")
      {
         createRegularTicket(selection,ticketList);
         // presentClient = processTickets(presentClient,ticketList);
      }

      else if (selection != "finished")
      {
         cout << "Invalid Entry. Please reenter your selection." << endl;
         cin.ignore(256, '\n');
      }
      if (presentClient.minutes == 0)
      {
         presentClient = ticketList.front();
         ticketList.pop_front();
      }
      //This part will work with client dealing with the person
      //at the front of the deque
      if (presentClient.minutes > 0)
      {
         displayTicket(presentClient);
         presentClient.minutes--;
      }
      else if (!ticketList.empty())
      {
         presentClient = ticketList.front();

         ticketList.pop_front();

         displayTicket(presentClient);

         presentClient.minutes--;
      }
      
   } while (selection != "finished");

   // end
   std::cout << "End of simulation\n";
}

/************************************************************************
* NOW SERVING  : PROCESS TICKETS
* NEED TO FILL THIS OUT CAN'T FIGURE A WAY TO PROCESS THE TICKETS THE OTHER
* TWO FUNCTIONS ADD TO THE FRONT OR TO THE BACK NEED AN ALGORITHM TO
* CYCLE THROUGH THE DEQUE AND POP OFF THE STRUCT WHEN THE TIME HAS RUN OUT
* AND EACH TIME THERE IS AN ENTRY IT DECREMENTS A MINUTE --
* I HAD THIS JUST PASSING IN THE STRUCT BUT MICHAEL SAID TO PASS IT THE
* DEQUE I DON'T KNOW IF I NEED BOTH.
*************************************************************************/
storeTicket processTickets(storeTicket presentClient,
                           deque<storeTicket> ticketList)
{
   // Do nothing if the deque is empty and current ticket has no time left.
   
   if (!ticketList.empty() || presentClient.minutes > 0)
   {
      // Take a minute away, if the presentClient has more time
      // and display the change
      
      if (presentClient.minutes > 0)
      {
         displayTicket(presentClient);
         
         presentClient.minutes--;
      }
      // If the ticketList is empty them help next client

      else if (!ticketList.empty())
      {
         presentClient = ticketList.front();
         
         ticketList.pop_front();
         
         displayTicket(presentClient);
         
         presentClient.minutes--;
      }
   }

   return presentClient;
}

/************************************************************************
* NOW SERVING  : CREATE EMERGENCY TICKET
* Adds an emergency appointment item to the front of the DEQUE,
*
*************************************************************************/
void createEmergencyTicket(deque<storeTicket> &ticketList)
{
   string courseName;
   string studentName;
   int minutes;
   cin >> courseName;
   cin >> studentName;
   cin >> minutes;

   storeTicket newTicket;

   newTicket.courseName = courseName;
   newTicket.studentName = studentName;
   newTicket.minutes = minutes;
   newTicket.isEmergency = true;

   ticketList.push_front(newTicket);
}

/************************************************************************
* NOW SERVING  : CREATE REGULAR TICKET
* Adds a REGULAR item to the end of the DEQUE,
* 
*************************************************************************/
void createRegularTicket(string courseName, deque<storeTicket> &ticketList)
{
   string studentName;
   int minutes;
   bool isEmergency;

   cin >> studentName;
   cin >> minutes;

   storeTicket newTicket;
   newTicket.courseName = courseName;
   newTicket.studentName = studentName;
   newTicket.minutes = minutes;
   newTicket.isEmergency = false;

   ticketList.push_back(newTicket);
}

/************************************************************************
* NOW SERVING  : DISPLAY
* DISPLAYS THE STRUCT OF STUDENT, COURSE AND MINUTES REQUESTED LEFT AFTER
* EACH TIME A PROMPT IS MADE
*************************************************************************/
void displayTicket(storeTicket client)
{
   if (client.isEmergency)
   {
      cout << "\tEmergency for ";
   }
   else
   {
      cout << "\tCurrently serving ";
   }
   cout << client.studentName
         << " for class "
         << client.courseName
         << ". Time left: "
         << client.minutes
         << endl;
   
}
