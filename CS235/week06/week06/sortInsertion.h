/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   try
   {
      Node <T> * pInsert = NULL;
      Node <T> * pNew = NULL;
      
      for(int i = 0; i < num; i++)
      {
         if(!pInsert || array[i] < pInsert->data)
         {
            insert(array[i], pInsert, true);
         }
         else
         {
            pNew = pInsert;
            while(pNew->pNext != NULL && array[i] > pNew->pNext->data)
            {
               pNew = pNew->pNext;
            }
            
            if(pNew->pNext == NULL || array[i] <= pNew->pNext->data)
            {
               insert(array[i], pNew, false);
            }
         }
      }
      
      for(int i = 0; i < num; i++)
      {
         array[i] = pInsert->data;
         pInsert = pInsert->pNext;
      }
      
      freeData(pInsert);
      
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Can't allocate memory for a Node!";
   }

}

#endif // INSERTION_SORT_H

