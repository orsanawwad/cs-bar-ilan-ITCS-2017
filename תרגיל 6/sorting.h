/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 6
******************************************/

#ifndef SORTING_H
#define SORTING_H

#include "person.h"

/**************************************************************************
 * Function name: SortCircleByID
 * Input: Person pointer (The head of circle)
 * Output: Person pointer that points to the head of circle if changed
 * The function operation: Calls BubbleSortPersonAlgo and with head and
 *                         SortIDIfCheck argument to sort the circle
 *                         using the ID
 *************************************************************************/
Person* SortCircleByID(Person* head);

/**************************************************************************
 * Function name: SortCircleByID
 * Input: Person pointer (The head of circle)
 * Output: Person pointer that points to the head of circle if changed
 * The function operation: Calls BubbleSortPersonAlgo and with head and
 *                         SortNameIfCheck argument to sort the circle
 *                         using the name
 *************************************************************************/
Person* SortCircleByName(Person* head);

#endif
