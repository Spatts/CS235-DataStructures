//
//  nodeP.cpp
//  week13
//
//  Created by Steven Patterson on 4/6/19.
//  Copyright © 2019 Steven Patterson. All rights reserved.
//

#include "nodeP.h"

/*******************************************
 * Default constructor for the Node Class
 ******************************************/
NodeP :: NodeP()
{
   birth = first = last = "";
   id = 0;
   father = mother = next = NULL;
}

/*******************************************
 * Non-Default constructor.
 ******************************************/
NodeP :: NodeP(string birth, string first, string last, int id)
{
   this->birth = birth;
   this->first = first;
   this->last = last;
   this->id = id;
   
   father = mother = next = NULL;
}

/*******************************************
 * DISPLAY: Will print out the person's info.
 ******************************************/
void NodeP :: display()
{
   if(first != "" && last != "")
      cout << first << " ";
   
   if(first != "" && last == "")
      cout << first;
   
   if(last != "")
      cout << last;
   
   if(birth != "")
      cout << ", b. " << birth;
   
   cout << endl;
}
