/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include "wholeNumbers.h"
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   WholeNumber prev1(1);
   WholeNumber prev2(1);
   WholeNumber temp;
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;
   
   for(int i = 0; i < number; i++)
   {
      cout << "\t" << prev1 << "\n";
      prev1 += prev2;
      temp = prev1;
      prev1 = prev2;
      prev2 = temp;
   }
   
   prev1 = 1;
   prev2 = 1;
   temp = 0;
   // Code to display a sequence of fibonacci numbers goes here.
   // loop until "number", calling your fibonacci number display function for each fibonacci # from 1 to "number".
   
   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;
   
   for(int i = 1; i < number; i++)
   {
      prev1 += prev2;
      temp = prev1;
      prev1 = prev2;
      prev2 = temp;
   }
   
   cout << "\t" << prev1 << "\n";
   // your code to display the <number>th Fibonacci number

}




