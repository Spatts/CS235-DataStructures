/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;
#include <fstream>
#include <string.h>

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   Set <Card> cardsInHand;
   Card playingCard;
   
   cardsInHand = readFile();
   int matches = 0;
   
   cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand" << endl;
   
   for(int i = 1; i < 6; i++)
   {
      cout << "round " << i << ": ";
      cin >> playingCard;
      
      if(cardsInHand.find(playingCard) >= 0)
      {
         cout <<"\tYou got a match!" << endl;
         cardsInHand.erase(cardsInHand.find(playingCard));
         matches++;
      }
      else
      {
         cout << "\tGo Fish!" << endl;
      }
      
   }
   cout << "You have " << matches << " matches!\nThe remaining cards: ";
   
   //printing the cards
   SetIterator <Card> it;
   int numCards = cardsInHand.size();
   for (it = cardsInHand.begin(); it != cardsInHand.end(); it++)
   {
      numCards--;
      cout << *it;
      if(numCards <= 0)
      {
         cout << "\n";
      }
      else
      {
         cout << ", ";
      }
   }
   
   return;
}

/**********************************************************************
 * READFILE
 * Reads the file and stores it as cards
 ***********************************************************************/
Set <Card> readFile()
{
   Card card;
   Set <Card> cardsInHand;
   string fileName = "/home/cs235e/week05/hand.txt";
   ifstream fin("/home/cs235e/week05/hand.txt");
   
   //file does not exist
   if (fin.fail())
   {
      cout << "Unable to open file " << fileName << endl;
      return -1;
   }
   
   while (fin >> card)
   {
      cardsInHand.insert(card);
   }
   
   fin.close();
   return cardsInHand;
}

