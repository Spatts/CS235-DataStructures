//
//  week13.cpp
//  week13
//
//  Created by Steven Patterson on 4/6/19.
//  Copyright © 2019 Steven Patterson. All rights reserved.
//

#include "nodeP.h"
#include "list.h"
#include "parse.h"
#include <iostream>

using namespace std;

int main(int argc, const char * argv[])
{
   ifstream inputFile;
   if (argc > 1)
   {
      inputFile.open(argv[1]);
      
      if(inputFile.fail())
      {
         cout << "ERROR: Failed to open file." << endl;
         return -1;
      }
   }
   else
   {
      cout << "ERROR: Please specify file." << endl;
      return -1;
   }
   
   List tree = parse(inputFile);

   tree.printList();
   tree.printGen();
   
   return 0;
}
