###############################################################
# Program:
#     Assignment 04, DEQUE
#     Brother Kirby, CS235
# Author:
#     Ladell Owens, Ben Crowe
# Summary:
#     This program implements the deque data structure
#     and uses it to store student names, the minutes they are
#     requesting and if their need is an emergency or not.
#     It uses this information in a program to help them in 
#     order unless it is an emergency then it uses the push_front
#     method to put them at the front of the line.
# Coding Time:
#   Pair Programming: 2
#   Ladell:
#   Ben: 12.5 hrs
# The most difficult part:
#   Ben: I met with the tutor twice and he was helpful explaining
#        how the inormalize method works and wrapping in the deque
#        it is still kinda difficult to understand how to wrapping
#        not knowing where to start when you are at the front or 
#        the back. Besides that I would say that the hardest part 
#        was the nowServing.cpp since we couldn't get it to pass.
#   Ladell:
# 
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h assignment04.o nowServing.o
	g++ -o a.out assignment04.o nowServing.o -std=c++11
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment04.o : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
assignment04.o: deque.h assignment04.cpp
	g++ -c assignment04.cpp -std=c++11

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp -std=c++11
