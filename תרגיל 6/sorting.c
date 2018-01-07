/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 6
******************************************/

#include "stdio.h"
#include "person.h"
#include "utils.h"
#include "string.h"

/**************************************************************************
 * Function name: SwapPersonNodes
 * Input: Person pointer (The head of circle)
 * Output: No output
 * The function operation: Swaps the nodes of first person and second
 *                         person and sets their next pointer correctly.
 *************************************************************************/
void SwapPersonNodes(Person* head, Person* firstCompare, Person* secondCompare) {
    Person* previousToFirst = FindPreviousPerson(head, firstCompare);
    Person* nextToSecond = secondCompare->next;
    previousToFirst->next = secondCompare;
    secondCompare->next = firstCompare;
    firstCompare->next = nextToSecond;
}

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
Person* SortCircleByID(Person* head) {
    if (head == NULL) {
        return NULL;
    }
    int amountOfNodes = CountNodes(head);
    Person* newHead = head;
    for (int i = 0; i < amountOfNodes - 1; ++i) {
        Person* firstPerson = newHead;
        Person* secondPerson = firstPerson->next;
        for (int j = 0; j < amountOfNodes - 1 - i; ++j) {
            if(firstPerson->id > secondPerson->id) {
                Person* firstCompare = firstPerson;
                Person* secondCompare = secondPerson;
                if (firstCompare == newHead) {
                    newHead = secondCompare;
                }
                SwapPersonNodes(head, firstCompare, secondCompare);
                firstPerson = firstCompare;
                secondPerson = firstPerson->next;
            } else {
                firstPerson = secondPerson;
                secondPerson = firstPerson->next;
            }
        }
    }
    return newHead;
}

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
Person* SortCircleByName(Person* head) {
    if (head == NULL) {
        return NULL;
    }
    int amountOfNodes = CountNodes(head);
    Person* newHead = head;
    for (int i = 0; i < amountOfNodes - 1; ++i) {
        Person* firstPerson = newHead;
        Person* secondPerson = firstPerson->next;
        for (int j = 0; j < amountOfNodes - 1 - i; ++j) {
            if(strcmp(firstPerson->name, secondPerson->name) > 0) {
                Person* firstCompare = firstPerson;
                Person* secondCompare = secondPerson;
                if (firstCompare == newHead) {
                    newHead = secondCompare;
                }
                SwapPersonNodes(head, firstCompare, secondCompare);
                firstPerson = firstCompare;
                secondPerson = firstPerson->next;
            } else {
                firstPerson = secondPerson;
                secondPerson = firstPerson->next;
            }
        }
    }
    return newHead;
}