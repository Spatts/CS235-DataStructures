/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <Mitch Patterson>
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include "deque.h"     // for DEQUE

// the interactive nowServing program
void nowServing();

#include <iostream>
#include <string>
using namespace std;

// the interactive nowServing program
void nowServing();

/************************************************
 * STUDENT
 * A class that holds information about Student
 ***********************************************/
class Student
{
private:
   string student;
   string course;
   int    studentMin;
   bool   studentEm;
   
public:
   Student(): course(""), student(""), studentMin(0), studentEm(0) {}
   
   string getName()
   {
      return student;
   }
   
   string getCourse()
   {
      return course;
   }
   
   bool isEm()
   {
      return studentEm;
   }
   
   int getMins()
   {
      return studentMin;
   }
   
   void setName(string studentName)
   {
      this->student = studentName;
   }

   void setCourse(string studentCourse)
   {
      this->course = studentCourse;
   }
   
   void setMins(int mins)
   {
      studentMin = mins;
   }
   
   void setEm(bool studentEm)
   {
      this->studentEm = studentEm;
   }
   
   
};

/************************************************
 * DEQUE: DISPLAY
 * Displays the current student
 ***********************************************/
void display(Student student);

#endif // NOW_SERVING_H

