/*
 * File:  merg-two-sorted-lists.c
 *
 * Demonstrate merging two ordered singly-linked lists into
 * one ordered singly-linked list.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void loadDataIntoList(List *pList, const char *listData[], int listDataLength);
void mergeSortedLists(const List *pList1, const List *pList2, List *pDestList);
void outputList(List *pList);

int main(void)
{
   /* Variables */
   const char *list1Data[] = {
      "aardvark",
      "badger",
      "horse",
      "zebra"
   };
   const char *list2Data[] = {
      "armadillo",
      "baboon",
      "cat",
      "kangaroo"
   };
   List list1;
   List list2;
   List mergedList;

   /* Initialize the lists */
   list_init(&list1, NULL);
   list_init(&list2, NULL);
   list_init(&mergedList, NULL);

   /* Load sorted data into lists */
   loadDataIntoList(&list1, list1Data, sizeof(list1Data) / sizeof(*list1Data));
   loadDataIntoList(&list2, list2Data, sizeof(list2Data) / sizeof(*list2Data));

   /* Merge sorted list into destination list */
   mergeSortedLists(&list1, &list2, &mergedList);

   /* Output contents of all three lists */
   outputList(&list1);
   outputList(&list2);
   outputList(&mergedList);

   /* Destroy the lists */
   list_destroy(&list1);
   list_destroy(&list2);
   list_destroy(&mergedList);

   return EXIT_SUCCESS;
}

void loadDataIntoList(List *pList, const char *listData[], int listDataLength)
{
   int i;

   for (i = 0; i < listDataLength; ++i)
   {
      list_ins_next(pList, list_tail(pList), listData[i]);
   }
}

void mergeSortedLists(const List *pList1, const List *pList2, List *pDestList)
{
   ListElmt *pList1Elmt;
   ListElmt *pList2Elmt;
   const char *pList1Data;
   const char *pList2Data;
   const char *pDataToInsert;

   /* Get head element from both source lists */
   pList1Elmt = list_head(pList1);
   pList2Elmt = list_head(pList2);

   /* Add all elements from both lists to the destination list while
      maintaining sorted order */
   while (pList1Elmt != NULL || pList2Elmt != NULL)
   {
      /* Determine which data should be added next */
      if (pList1Elmt == NULL)
      {
         /* Everything from list 1 has been added, select next from list 2 */
         pDataToInsert = (const char *)list_data(pList2Elmt);
         pList2Elmt = list_next(pList2Elmt);
      }
      else if (pList2Elmt == NULL)
      {
         /* Everything from list 2 has been added, select next from list 1 */
         pDataToInsert = (const char *)list_data(pList1Elmt);
         pList1Elmt = list_next(pList1Elmt);
      }
      else
      {
         /* List 1 and 2 contain more elements */
         pList1Data = (const char *)list_data(pList1Elmt);
         pList2Data = (const char *)list_data(pList2Elmt);

         /* Determine whether element from list 1 or 2 should be added next */
         if (strcmp(pList1Data, pList2Data) < 0)
         {
            /* List 1 contains smaller element, select next from list 1 */
            pDataToInsert = (const char *)list_data(pList1Elmt);
            pList1Elmt = list_next(pList1Elmt);
         }
         else
         {
            /* List 2 contains smaller element, select next from list 2 */
            pDataToInsert = (const char *)list_data(pList2Elmt);
            pList2Elmt = list_next(pList2Elmt);
         }
      }

      /* Add the data to the end of the destination list */
      list_ins_next(pDestList, list_tail(pDestList), pDataToInsert);
   }
}

void outputList(List *pList)
{
   ListElmt *pListElmt;

   printf("List\n");
   printf("----\n");

   /* Get head element of list */
   pListElmt = list_head(pList);

   /* Output each element */
   while (pListElmt != NULL)
   {
      printf("%s\n", (const char *)list_data(pListElmt));
      pListElmt = list_next(pListElmt);
   }

   printf("\n");
}

/*
 * Program output:
        List
        ----
        aardvark
        badger
        horse
        zebra

        List
        ----
        armadillo
        baboon
        cat
        kangaroo

        List
        ----
        aardvark
        armadillo
        baboon
        badger
        cat
        horse
        kangaroo
        zebra
 */
