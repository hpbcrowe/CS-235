###############################################################
# Program:
#     Assignment 01, Vector
#     Brother Kirby, CS235
# Author:
#     Ben Crowe, Brother Helfrich
# Summary:
#     Builds a vector and then tests the functionality of the
#     vector by inserting different data types
# Time:
#     6 hours with help from Michael the tutor
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h assignment01.o
	g++ -o a.out assignment01.o -std=c++11
	tar -cf assignment01.tar vector.h assignment01.cpp makefile

##############################################################
# The individual components
#      assignment01.o     : the driver program
##############################################################
assignment01.o: vector.h assignment01.cpp
	g++ -c assignment01.cpp -std=c++11

