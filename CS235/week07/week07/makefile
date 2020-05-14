###############################################################
# Program:
#     Week 07, LIST
#     Brother XXXXX, CS235
# Author:
#     <your name here>
# Summary:
#     <put a description here>
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h week07.o fibonacci.o wholeNumbers.h
	g++ -o a.out week07.o fibonacci.o -std=c++11
	tar -cf week07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week07.o       : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
week07.o: list.h week07.cpp
	g++ -c week07.cpp -std=c++11

fibonacci.o: fibonacci.h fibonacci.cpp list.h wholeNumbers.h
	g++ -c fibonacci.cpp -std=c++11

