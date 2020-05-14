###############################################################
# Program:
#     Week 13, Geneaology
#     Brother Ercanbrack, CS235
# Author:
#     Steven Mitch Patterson
# Summary:
#     Final
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week13.o
	g++ -o a.out week13.o -g -std=c++11
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week13.o     : the driver program
##############################################################
week13.o: list.h personInfo.h merge.h bnode.h week13.cpp
	g++ -c week13.cpp -g -std=c++11

clean: 
	rm *.o *.tar a.out

