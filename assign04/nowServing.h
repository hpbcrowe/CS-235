/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Ladell Owens, Ben Crowe
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include "deque.h"     // for DEQUE
#include <string>
using namespace std;

using custom::deque;

struct storeTicket
{
	string courseName;
	string studentName;
	int minutes;
	bool isEmergency;
};

// the interactive nowServing program
void nowServing();

//Cycles through minutes left, checks for next ticket
storeTicket processTickets(storeTicket presentStudent, deque<storeTicket> ticketList);

//Creates an emergency ticket and pushes it to front of
//deque
void createEmergencyTicket(deque<storeTicket> &ticketList);

//Creates a regular ticket and adds it to the back of the 
//deque
void createRegularTicket(string courseName, deque<storeTicket> &ticketList);

//Displays the ticket being worked at the moment
void displayTicket(storeTicket presentClient);

#endif // NOW_SERVING_H

