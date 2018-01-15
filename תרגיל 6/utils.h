/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 6
******************************************/

#ifndef UTILS_H
#define UTILS_H

#include "person.h"

/**************************************************************************
 * Function name: PrintCircle
 * Input: Person pointer (The head of circle)
 * Output: No output
 * The function operation: The function loops through each node (using
 *                         next) and print their values using Print
 *                         function of that person.
 *************************************************************************/
void PrintCircle(Person* head);

/**************************************************************************
 * Function name: ReadInputString
 * Input: No input
 * Output: Returns pointer to a dynamically allocated text
 * The function operation: It sets a buffer of size 81, takes input from
 *                         user, allocates memory according to text size
 *                         then copies the text to the dynamically
 *                         allocated memory pointer, then returned.
 *************************************************************************/
char* ReadInputString();

/**************************************************************************
 * Function name: ReadNumber
 * Input: No input
 * Output: Integer number
 * The function operation: Calls ReadInputString function and then it takes
 *                         the string and convert it to numbers similar
 *                         to atoi function (which is not allowed to use
 *                         in this case), then the memory of
 *                         ReadInputString return pointer is freed.
 *************************************************************************/
int ReadNumber();

/**************************************************************************
 * Function name: FindPerson
 * Input: Person pointer (The head of circle), id number of person to find
 * Output: Person pointer of the found person
 * The function operation: Loops through each node in the circle and
 *                         checks for id equality, if true, it returns
 *                         that person pointer.
 *************************************************************************/
Person* FindPerson(Person* head, int ID);

/**************************************************************************
 * Function name: FindPreviousPerson
 * Input: Person pointer (The head of circle), the person to find its
 *        previous node.
 * Output: Person pointer to that previous node.
 * The function operation: It loops through each node until it finds the
 *                         previous node of the input person using next
 *                         pointer of that person.
 *************************************************************************/
Person* FindPreviousPerson(Person* head, Person* person);

/**************************************************************************
 * Function name: ConnectLeftAndRightOfPerson
 * Input: Person pointer (The head of circle), Person pointer to remove
 * Output: Person pointer of the head
 * The function operation: Takes the previous person of the one to remove
 *                         and the person after it, then we call
 *                         SelfDestruct of that person to remove, then
 *                         connect next of the previous person to the
 *                         person that was after it, but if the person
 *                         we're removing is actually the first node, we
 *                         then update the head with a new pointer,
 *                         but if the next person was actually equal to
 *                         the person that we need to remove, it means
 *                         there is only one person left in the circle
 *                         which we then need to remove only him and
 *                         return NULL.
 *************************************************************************/
Person* ConnectLeftAndRightOfPerson(Person* head, Person* personToRemove);

/**************************************************************************
 * Function name: ScoreBoardPrint
 * Input: Person pointer killer, Person pointer victim
 * Output: No output
 * The function operation: Prints the who kills who by printing the name
 *                         of the killer, then " kills " then the killer name
 *                         then their children names, with " and " before
 *                         each one.
 *************************************************************************/
void ScoreBoardPrint(Person *killer, Person *victim);

/**************************************************************************
 * Function name: CountNodes
 * Input: Person pointer (The head of circle)
 * Output: Number of nodes in the circle
 * The function operation: Loop through each node and count them, then
 *                         return the count.
 *************************************************************************/
int CountNodes(Person* head);

#endif
