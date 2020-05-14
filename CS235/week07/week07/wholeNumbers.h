//
//  wholeNumbers.h
//  week07
//
//  Created by Steven Patterson on 2/25/19.
//  Copyright © 2019 Steven Patterson. All rights reserved.
//

#ifndef wholeNumbers_h
#define wholeNumbers_h

#include "list.h"
#include "fibonacci.h"
#include <ostream>
#include <iomanip>
using namespace std;

/**************************************************
 * WHOLENUMBER: A whole number class
 *************************************************/
class WholeNumber
{
public:
   WholeNumber() {}
   WholeNumber(unsigned int number) { digits.push_front(number); }
   WholeNumber(const WholeNumber & rhs) { *this = rhs; }
   ~WholeNumber() {}
   
   WholeNumber & operator = (const WholeNumber & rhs)
   {
      this->digits = rhs.digits;
      return *this;
   }
   
   WholeNumber & operator += (WholeNumber rhs);
   
   friend std::ostream & operator << (std::ostream & out, WholeNumber rhs);
   
private:
   List <unsigned int> digits;

};

/**************************************************
 * += OPERATOR: Adds whole numbers
 *************************************************/
WholeNumber & WholeNumber :: operator += (WholeNumber  rhs)
{
   ListIterator <unsigned int> it1 = this->digits.rbegin();
   ListIterator <unsigned int> it2 = rhs.digits.rbegin();
   
   int sum = 0;
   int carryOver = 0;
   List <unsigned int> total;
   
   while (it1 != this->digits.rend() || it2 != rhs.digits.rend())
   {
      int prev1;
      int prev2;
      
      if(it1 == this->digits.rend())
      {
         prev1 = 0;
      }
      else
      {
         prev1 = *it1;
      }
      
      if(it2 == this->digits.rend())
      {
         prev2 = 0;
      }
      else
      {
         prev2 = *it2;
      }
      
      sum = (prev1 + prev2 + carryOver) % 1000;
      
      total.push_front(sum);
      
      carryOver = (prev1 + prev2 + carryOver) / 1000;
      
      if (it1 != this->digits.rend())
      {
         it1++;
      }
      if (it2 != rhs.digits.rend())
      {
         it2++;
      }
   }
   
   if (carryOver == 1)
   {
      total.push_front(carryOver);
   }
   
   this->digits = total;
   
   return *this;
}

/**************************************************
 * << OPERATOR: Displays whole numbers
 *************************************************/
ostream & operator << (ostream & out, WholeNumber rhs)
{
   ListIterator <unsigned int> it = rhs.digits.begin();
   for (it = rhs.digits.begin(); it != rhs.digits.end(); ++it)
   {
      if(*it < 10 && it != rhs.digits.begin())
      {
         out << "00" << *it <<",";
      }
      else if(*it < 99 && it != rhs.digits.begin())
      {
         out << "0" << *it << ",";
      }
      else if(*it > 99 && it != rhs.digits.begin())
      {
         out << *it << ",";
      }
      else
      {
         out << *it;
      }
   }
   return out;
}

#endif /* wholeNumbers_h */
