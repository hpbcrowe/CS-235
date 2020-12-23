###############################################################
# Program:
#     Assignment 02, STACK
#     Brother Kirby, CS235
# Author:
#     Ladell Owens, Ben Crowe
# Summary:
#     Program will implement the Stack data structure and use it
# to change an infix equation input to a postfix equation.
#
# Time:
# Paired Programming:
# 3 1/2 hours
#
# Ben:
# 3 hours
#
# Ladell:
# 3 1/2 hours
#
# Most Difficult Part:
# Ben:
# Getting the order of operations to work properly with the
# equation. I had a hard time getting the throw to work in the
# top function in stack.h
#
# Ladell:
# I had the same difficulties that Ben had, it was just mind
# boggling trying to get the order of operations to work with
# the infix to postfix function.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h assignment02.o infix.o 
	g++ -o a.out assignment02.o infix.o  -std=c++11
	tar -cf assignment02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment02.o : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
assignment02.o: stack.h infix.h assignment02.cpp
	g++ -c assignment02.cpp  -std=c++11

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp -std=c++11

