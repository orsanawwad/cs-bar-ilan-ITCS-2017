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
 * The function operation: It sorts the nodes by ID using bubble sort,
 *                         it first gets the amount of nodes inside the
 *                         circle, then compares 2 nodes each time and
 *                         if the first is bigger than the second, it swaps
 *                         them, however, we always have to keep track of
 *                         head pointer, as the current head we know might
 *                         get changed to something else, every time we
 *                         need to swap persons nodes, we first check if
 *                         the first person is actually head, if so, set
 *                         the new head to the second person we're swapping
 *                         with then swap, regularly, after than, we set
 *                         the next two nodes by replacing firstPerson
 *                         to firstCompare, because after swapping the
 *                         nodes the next two nodes are firstCompare,
 *                         which is the node we swapped in the first place,
 *                         then the second value the next pointer of the
 *                         firstCompare, but if no swapping happened we
 *                         just set the new compare nodes to second person
 *                         and the one after it
 *************************************************************************/
Person* SortCircleByID(Person* head);

/**************************************************************************
 * Function name: SortCircleByID
 * Input: Person pointer (The head of circle)
 * Output: Person pointer that points to the head of circle if changed
 * The function operation: It sorts the nodes by name using bubble sort,
 *                         it first gets the amount of nodes inside the
 *                         circle, then compares 2 nodes each time and
 *                         if the first is bigger than the second, it swaps
 *                         them, however, we always have to keep track of
 *                         head pointer, as the current head we know might
 *                         get changed to something else, every time we
 *                         need to swap persons nodes, we first check if
 *                         the first person is actually head, if so, set
 *                         the new head to the second person we're swapping
 *                         with then swap, regularly, after than, we set
 *                         the next two nodes by replacing firstPerson
 *                         to firstCompare, because after swapping the
 *                         nodes the next two nodes are firstCompare,
 *                         which is the node we swapped in the first place,
 *                         then the second value the next pointer of the
 *                         firstCompare, but if no swapping happened we
 *                         just set the new compare nodes to second person
 *                         and the one after it
 *************************************************************************/
Person* SortCircleByName(Person* head);

#endif
