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

/************************************************
 * GET PRIORITY
 * Assigns a value to each operator to establish
 * order of operations.
 ************************************************/
int getPriority(const char & symbol)
{
   switch (symbol)
   {
      case '(':
         return 1;
         break;
      case '+':
      case '-':
         return 2;
         break;
      case '*':
      case '/':
      case '%':
         return 3;
         break;
      case '^':
         return 4;
         break;
      default:
         cout << "error symbol";
   }
   return 0;
}

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   string postfix = "";
   custom::stack <char> operators;
   string tempToken;
   
   for (int i = 0; i < infix.size();)
   {
      switch (infix[i])
         //	postfix[iPostfix++] = infix[iInfix]
      { 
         case '0' ... '9':
         case '.':   
            while (infix[i] == isdigit(infix[i]) && i < infix.length())
            {
               tempToken += infix[i];
               i++;
            }
            postfix += tempToken;
            
            break;
            
         case 'a' ... 'z':
         case 'A' ... 'Z':
         case '_':
            
            while(infix[i] == isalpha(infix[i]) && i < infix.length() )
            {
               tempToken += infix[i];
                  i++;
            }
            
            postfix += tempToken;
            
            break;
            
         case '(':
            
            operators.push(infix[i]);
            i++;
            break;
            
         case ')':
            //Keep copying from the stack
            //until we get to the open parenthesis
            while (operators.top() != '(')
            {
               postfix += " ";
               postfix += operators.top();
               operators.pop();
            }
            //don't forget to pop off the '('
            operators.pop();
            i++;
            break;
            
         //check for spaces
         case ' ':
            i++;
            break;
         //All we have left are operators
         default:
            //Go through the operators stack and take the operators off
            //the stack if they are less than or equal to current infix
            //value                     

//            int infixOp = getPriority(infix[i]);
//            int postfixOp = getPriority(operators.top());
                                                    
            while (! operators.empty()
                   && getPriority(infix[i])
                   <= getPriority(operators.top()))
            {
               postfix += " ";
               postfix += operators.top();
               operators.pop();
            }
            operators.push(infix[i]);
            i++;
      }
   }
   //copy the rest of elements from stack
   //to postfix
   while (! operators.empty())
   {
      postfix += " ";
      postfix += operators.top();
      operators.pop();
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
