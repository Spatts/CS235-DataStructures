/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    <Mitch Patterson>
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here

   Deque<Student> studentDeq;
   Student setStudent;
   Student currentStudent;
   
   string input;
   
   string course;
   string name;
   int helpTime;
   bool em;
   
   int numMinutes = 0;
   do
   {
      cout << "<" << numMinutes << "> ";
      cin.ignore();
      cin.clear();
      cin >> input;
      
      if(input == "finished")
      {
         break;
      }
      
      if (input == "!!")
      {
         cin >> course >> name >> helpTime;
         em = true;
         setStudent.setCourse(course);
         setStudent.setName(name);
         setStudent.setMins(helpTime);
         setStudent.setEm(em);
         
         if(currentStudent.getMins() <= 0)
         {
            currentStudent = setStudent;
         }
         else
         {
            studentDeq.push_front(setStudent);
         }
      }
      
      else if(input == "none")
      {
         if(currentStudent.getMins() <= 0 && !studentDeq.empty())
         {
            currentStudent = setStudent;
         }
      }
      
      else
      {
         course = input;
         cin >> name >> helpTime;
         em = false;
         
         setStudent.setCourse(course);
         setStudent.setName(name);
         setStudent.setMins(helpTime);
         setStudent.setEm(em);
         
         if(currentStudent.getMins() <= 0)
         {
            if(studentDeq.empty())
            {
               currentStudent = setStudent;
               
            }
            else
            {
               studentDeq.pop_front();
            }
         }
         
         else
         {
            studentDeq.push_back(setStudent);
         }
         
      }
      
      if (currentStudent.getMins() <= 0 && !studentDeq.empty())
      {
         
         currentStudent = studentDeq.front();
         
      }
      if (currentStudent.getMins() > 0)
      {
         
         if(numMinutes < 10)
         {
            display(currentStudent);
         }
         
         int time = currentStudent.getMins() - 1;
         currentStudent.setMins(time);
         
         if (currentStudent.isEm() == true)
         {
            studentDeq.pop_front();
            currentStudent = studentDeq.front();
         }
      }
      
      numMinutes++;
   }
   while(input != "finished");
   
   cout << "End of simulation\n";
}

void display(Student student)
{
   if(student.isEm() == false)
   {
      cout << "\tCurrently serving ";
   }
   else
   {
      cout << "\tEmergency for ";
   }
   
   cout << student.getName()  << " for class "
   << student.getCourse() << ". Time left: "
   << student.getMins() << endl;
   
}

