/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   BST <T> sortBinaryTree;
   BSTIterator <T> it;
   
   for(int i = 0; i < num; i++)
   {
      sortBinaryTree.insert(array[i]);
   }
   
   int i = 0;
   for (it = sortBinaryTree.begin(); it != sortBinaryTree.end(); ++it)
   {
      array[i] = it.operator * ();
      i++;
   }

}

#endif // SORT_BINARY_H
