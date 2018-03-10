/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 6
******************************************/

#include "stdio.h"
#include "person.h"
#include "string.h"
#include "stdlib.h"

/**
 * Constants
 */

#define BUFFER_SIZE 80

#define PRINT_CIRCLE_LINES "----------"

#define ERROR_CONNECTING_GOT_NULL "Error connecting left and right of person, received NULL as input."

#define PERSON_SCOREBOARD_ACTION " kills "

#define PERSON_SCOREBOARD_SUB_ACTION " and "

#define PERSON_SCOREBOARD_ERROR_NULL "Error, received null"

/**************************************************************************
 * Function name: PrintCircle
 * Input: Person pointer (The head of circle)
 * Output: No output
 * The function operation: The function loops through each node (using
 *                         next) and print their values using Print
 *                         function of that person.
 *************************************************************************/
void PrintCircle(Person* head) {
    Person* ptrHead = head;
    if (head != NULL) {
        puts(PRINT_CIRCLE_LINES);
        do {
            ptrHead->Print(ptrHead);
            puts(PRINT_CIRCLE_LINES);
            ptrHead = ptrHead->next;
        } while (head != ptrHead);
    }
}

/**************************************************************************
 * Function name: ReadInputString
 * Input: No input
 * Output: Returns pointer to a dynamically allocated text
 * The function operation: It sets a buffer of size 81, takes input from
 *                         user, allocates memory according to text size
 *                         then copies the text to the dynamically
 *                         allocated memory pointer, then returned.
 *************************************************************************/
char* ReadInputString() {
    char buffer[BUFFER_SIZE] = {'\0'};
    scanf("%s",&buffer);
    char* ptrText = NULL;
    ptrText = (char *)malloc((strlen(buffer) + 1));
    if (ptrText != NULL) {
        strcpy(ptrText, buffer);
        return ptrText;
    } else {
        return NULL;
    }
}

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
int ReadNumber() {
    char* number = ReadInputString();
    if (number != NULL) {
        int convertedNumber = 0;
        int sign = 1;
        int i = 0;
        if (number[0] == '-')
        {
            sign = -1;
            i++;
        }
        for (; i < strlen(number); ++i) {
            if (number[i] >= '0' && number[i] <= '9') {
                convertedNumber = convertedNumber * 10 + (number[i] - '0');
            } else {
                return -1;
            }
        }
        free(number);
        return sign*convertedNumber;
    } else {
        return -1;
    }
}

/**************************************************************************
 * Function name: FindPreviousPerson
 * Input: Person pointer (The head of circle), the person to find its
 *        previous node.
 * Output: Person pointer to that previous node.
 * The function operation: It loops through each node until it finds the
 *                         previous node of the input person using next
 *                         pointer of that person.
 *************************************************************************/
Person* FindPreviousPerson(Person* head, Person* person) {
    Person* ptrHead = head;
    Person* targetPerson = NULL;
    do {
        if (ptrHead->next == person) {
            targetPerson = ptrHead;
            return targetPerson;
        } else {
            ptrHead = ptrHead->next;
        }
    } while (ptrHead != head);
    return targetPerson;
}

/**************************************************************************
 * Function name: FindPerson
 * Input: Person pointer (The head of circle), id number of person to find
 * Output: Person pointer of the found person
 * The function operation: Loops through each node in the circle and
 *                         checks for id equality, if true, it returns
 *                         that person pointer.
 *************************************************************************/
Person* FindPerson(Person* head, int id) {
    Person* ptrHead = head;
    do {
        if (ptrHead != NULL) {
            if (ptrHead->id == id) {
                return ptrHead;
            } else {
                ptrHead = ptrHead->next;
            }
        } else {
            return NULL;
        }
    } while (ptrHead != head);
    return NULL;
}

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
Person* ConnectLeftAndRightOfPerson(Person* head, Person* personToRemove) {
    if (head != NULL) {
        if (head != personToRemove) {
            Person* previousToThePersonToRemove = FindPreviousPerson(head, personToRemove);
            Person* nextToPersonToRemove = personToRemove->next;
            personToRemove->SelfDestruct(personToRemove);
            previousToThePersonToRemove->next = nextToPersonToRemove;
            return head;
        } else {
            if (personToRemove->next != head) {
                Person* newHead = personToRemove->next;
                Person* previousToThePersonToRemove = FindPreviousPerson(head, personToRemove);
                Person* nextToPersonToRemove = personToRemove->next;
                personToRemove->SelfDestruct(personToRemove);
                previousToThePersonToRemove->next = nextToPersonToRemove;
                return newHead;
            } else {
                personToRemove->SelfDestruct(personToRemove);
                return NULL;
            }
        }
    } else {
        puts(ERROR_CONNECTING_GOT_NULL);
    }
    return NULL;
}

/**************************************************************************
 * Function name: ScoreBoardPrint
 * Input: Person pointer killer, Person pointer victim
 * Output: No output
 * The function operation: Prints the who kills who by printing the name
 *                         of the killer, then " kills " then the killer name
 *                         then their children names, with " and " before
 *                         each one.
 *************************************************************************/
void ScoreBoardPrint(Person *killer, Person *victim) {
    if (killer != NULL && victim != NULL) {
        printf(killer->name);
        printf(PERSON_SCOREBOARD_ACTION);
        printf(victim->name);

        for (int j = 0; j < victim->numOfKids; ++j) {
            printf(PERSON_SCOREBOARD_SUB_ACTION);
            printf(victim->kids[j]);
        }
        printf("\n");
    } else {
        puts(PERSON_SCOREBOARD_ERROR_NULL);
    }
}

/**************************************************************************
 * Function name: CountNodes
 * Input: Person pointer (The head of circle)
 * Output: Number of nodes in the circle
 * The function operation: Loop through each node and count them, then
 *                         return the count.
 *************************************************************************/
int CountNodes(Person* head) {
    int count = 0;
    Person* ptrHead = head;
    do {
        count++;
        ptrHead = ptrHead->next;
    } while (ptrHead != head);
    return count;
}
