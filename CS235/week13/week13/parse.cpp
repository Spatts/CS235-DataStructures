//
//  parse.cpp
//  week13
//
//  Created by Steven Patterson on 4/11/19.
//  Copyright © 2019 Steven Patterson. All rights reserved.
//

#include "parse.h"

List parse(ifstream & inputFile)
{
   List tree;

   string line;
   
   while (getline(inputFile, line))
   {
      if (line.find("0 @F") == 0)
         break;
      if (line.find("0 @I") == 0)
      {
         NodeP * record = new(nothrow) NodeP();
         
         int iD = 0;
         unsigned long start = 0;
         start = line.find("@ INDI");
         
         string stringID = line.substr(4, (start - 4));
         istringstream(stringID) >> iD;
         
         record->setId(iD);
         
         string last;
         string first;
         string birth;
         string previous;
         
         getline(inputFile, line);
         
         while (line.find("0 @I") != 0)
         {
            if (line.find("2 GIVN") == 0)
            {
               first = line.substr(7);
               record->setFirst(first);
            }
            else if (line.find("2 SURN") == 0)
            {
               last = line.substr(7);
               record->setLast(last);
            }
            else if (line.find("2 DATE") == 0 &&
                     previous.find("1 BIRT") == 0)
            {
               birth = line.substr(7);
               record->setBirth(birth);
            }
            else if (line.find("3 TIME") == 0)
               break;
            
            previous = line;
            getline(inputFile, line);
            
         }
         tree.push_alpha(record);
      }
   }
   
   while (line.find("0 @S1@ SOUR") != 0)
   {
      if (line.find("0 @F") == 0)
      {
         int husbandId = 0;
         int wifeId = 0;
         int childId = 0;
         
         getline(inputFile, line);
         
         while (line.find("0 @F") != 0)
         {
            if (line.find("0 @S1@ SOUR") == 0)
               break;
            if (line.find("1 HUSB") == 0)
            {
               string husband;
               husband = line.substr(9);
               husband = husband.substr(0, husband.length() - 1);
               istringstream(husband) >> husbandId;
            }
            else if (line.find("1 WIFE") == 0)
            {
               string wife;
               wife = line.substr(9);
               wife = wife.substr(0, wife.length() - 1);
               istringstream(wife) >> wifeId;
            }
            else if (line.find("1 CHIL") == 0)
            {
               string child;
               child = line.substr(9);
               child = child.substr(0, child.length() - 1);
               istringstream(child) >> childId;
            }
            getline(inputFile, line);
         }
         
         NodeP * husbandNode = NULL;
         NodeP * wifeNode = NULL;
         NodeP * childNode = NULL;
         
         husbandNode = tree.getNode(tree.search(husbandId));
         wifeNode = tree.getNode(tree.search(wifeId));
         childNode = tree.getNode(tree.search(childId));
         
         if (childNode != NULL)
         {
            childNode->setFather(husbandNode);
            childNode->setMother(wifeNode);
         }
      }
   }

   return tree;
}
