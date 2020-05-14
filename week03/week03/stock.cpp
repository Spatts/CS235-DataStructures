/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
using namespace std;

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   // your code here...
   
   struct Transaction {
      Dollars price;
      int shares;
      Dollars profit;
   };
   
   Queue<Transaction> buy;
   Queue<Transaction> sell;
   
   string choice;
   while (choice != "quit") {
      cout << "> ";
      cin >> choice;
      
      Transaction transaction;
      
      if (choice == "buy")
      {
         int shares;
         cin >> shares;
         Dollars price;
         cin >> price;
         transaction.shares = shares;
         transaction.price = price;
         transaction.profit = 0;
         buy.push(transaction);
      }
      
      else if (choice == "sell")
      {
         int shares;
         cin >> shares;
         Dollars price;
         cin >> price;
         Dollars profit = 0;
         transaction.shares = 0;
         transaction.price = 0;
         transaction.profit = 0;
         
         while (shares != 0) {
            if (buy.size() == 0) {
               cout <<  "No stocks to sell";
               return;
            }
            else
            {
               while (buy.front().shares != 0 && shares != 0) {
//                  buy.front().shares -= 1;
                  transaction.shares += 1;
                  shares -= 1;
                  transaction.price = price;
                  transaction.profit = transaction.profit + price - buy.front().price;
                  
               }
               sell.push(transaction);
               transaction.shares = 0;
               transaction.price = 0;
               transaction.profit = 0;
               
               if (buy.front().shares == 0)
               {
                  buy.pop();
               }
            }
         }
      }
      
   }
   
   
   
   
   
   
   
   
   
   
   
   
   
   
}


