/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   string postfix;

   Stack <char> buffer;
   
   int _len = infix.length();
   
   for (int i = 0; i < _len; i++)
   {
      /************************************************
       * Check if the current character is an operand
       * or part of an operand and only add a space when
       * we get to the beginning
       ************************************************/
      if ((infix[i] >= '0' && infix[i] <= '9') || (infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z') || infix[i] == '.')
      {
         
         if ((infix[i - 1] >= '0' && infix[i - 1] <= '9') || (infix[i - 1] >= 'a' && infix[i - 1] <= 'z') || (infix[i - 1] >= 'A' && infix[i - 1] <= 'Z') || infix[i - 1] == '.')
            postfix += infix[i];
         
         else
         {
            postfix += " ";
            postfix += infix[i];
         }
      }
      
      //Open parenthesis push to buffer when found
      else if (infix[i] == '(')
         buffer.push('(');
      
      
      
      //Close parenthesis adds all operators in buffer until close parenthesis
      else if (infix[i] == ')')
      {
         while (!buffer.empty() && buffer.top() != '(')
         {
            postfix += " ";
            postfix += buffer.top();
            buffer.pop();
         }
         if (buffer.top() == '(')
         {
            buffer.pop();
         }
      }
      
      //When to add '+' and '-' vs when to push it to the buffer
      else if (infix[i] == '+' || infix[i] == '-')
      {
         while (!buffer.empty() && buffer.top() != '(')
         {
            postfix += " ";
            postfix += buffer.top();
            buffer.pop();
         }
         buffer.push(infix[i]);
      }
      
      //When to add '*' and '/' vs when to push it to the buffer
      else if (infix[i] == '*' || infix[i] == '/')
      {
         while (!buffer.empty() && buffer.top() != '(' && buffer.top() != '+' && buffer.top() != '-')
         {
            postfix += " ";
            postfix += buffer.top();
            buffer.pop();
         }
         buffer.push(infix[i]);
      }
      
      //When to push '^'
      else if (infix[i] == '^')
      {
         buffer.push(infix[i]);
      }
      
   }
   
   //Add all remaining items from buffer to the postfix string
   while (!buffer.empty())
   {
      postfix += " ";
      postfix += buffer.top();
      buffer.pop();
   }
   
   
   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
