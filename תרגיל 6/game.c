/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 6
******************************************/

#include "person.h"
#include "stdlib.h"
#include "stdio.h"
#include "utils.h"

/**************************************************************************
 * Function name: InitTheHungerGame
 * Input: No input
 * Output: Returns a pointer to Person object which is the head of the
 *         circle.
 * The function operation: Asks the user if he wants to create Persons
 *                         objects and proceed into allocating memory for
 *                         each person object then asks the user for name,
 *                         id, number of kids, and each kid's name,
 *                         once the function is over it returns the "first"
 *                         object which is actually the first node in the
 *                         circle aka the head of circle.
 *************************************************************************/
Person* InitTheHungerGame() {
    char dummy;
    scanf("%c",&dummy);
    Person* pHead = NULL;
    Person* followUpPerson = NULL;
    while (1) {
        puts("Add a person to the game? (0|1)");
        int option = ReadNumber();
        if (option == 1) {
            if (pHead == NULL) {
                pHead = CreatePerson();
                followUpPerson = pHead;
            } else {
                followUpPerson->CreateNext(followUpPerson,0);
                followUpPerson = followUpPerson->next;
            }
        } else {
            if (followUpPerson != NULL) {
                followUpPerson->next = pHead;
                return pHead;
            } else {
                return NULL;
            }
        }
    }
}

/**************************************************************************
 * Function name: InsertLaters
 * Input: Person pointer (The head of circle)
 * Output: No output
 * The function operation: Asks the user if there are any other persons
 *                         that needs to be added and adds them just like
 *                         InitTheHungerGames but this time it asks for ID
 *                         of where to "append" the new person object
 *                         and finds the pointer of that person with the
 *                         input id, if found, it replaces the next
 *                         pointer of that person and with the new person's
 *                         next pointer is pointed at the what was
 *                         previously pointed by the input id person
 *************************************************************************/
void InsertLaters(Person* head) {
    if (head != NULL) {
        while (1) {
            puts("Are you late? (0|1)");
            int option = ReadNumber();
            if (option == 1) {
                puts("Insert your best friend's ID:");
                int idNumber = ReadNumber();
                Person *findHead = FindPerson(head, idNumber);
                if (findHead != NULL) {
                    Person *nextToFindHead = findHead->next;
                    findHead->CreateNext(findHead, 1, nextToFindHead);
                } else {
                    printf("No Such ID: %d\n", idNumber);
                }
            } else {
                break;
            }
        }
    }
}

/**************************************************************************
 * Function name: RemoveCowards
 * Input: Person pointer (The head of circle)
 * Output: Returns a pointer to Person object which is the head of the
 *         circle.
 * The function operation: Asks the user if there are any persons to remove
 *                         if there are, it asks for their ids, then looks
 *                         for them in the circle, if found, they're
 *                         removed and deallocated from memory, then the
 *                         previous node of the coward and the one after
 *                         it are connected (basicaly replacing the next
 *                         pointer of the previous node of the coward to
 *                         point to the one after it).
 *************************************************************************/
Person* RemoveCowards(Person* head) {
    if (head != NULL) {
        Person *pHead = head;
        while (1) {
            if (pHead == NULL) {
                return NULL;
            }
            puts("Is there a coward in here? (0|1)");
            int option = ReadNumber();
            if (option == 1) {
                puts("Insert your ID, you, lame pudding-heart coward:");
                int idNumber = ReadNumber();
                Person *theCoward = FindPerson(pHead, idNumber);
                if (theCoward != NULL) {
                    printf("Let the world know that you are a coward, %s!\n", theCoward->name);
                    pHead = ConnectLeftAndRightOfPerson(pHead, theCoward);
                } else {
                    printf("No Such ID: %d\n", idNumber);
                }
            } else {
                return pHead;
            }
        }
    } else {
        return NULL;
    }
}

/**************************************************************************
 * Function name: LetTheHungerGameBegin
 * Input: Person pointer (The head of circle)
 * Output: No output
 * The function operation: Starts the hunger games, it starts from head,
 *                         builds and prints the kill statement of who
 *                         kills who, then calls the function killNext
 *                         of the current person pHead pointer, which then
 *                         kills the person sits next to the pHead person
 *                         and deallocates him from memory, then it gets
 *                         connected to the one after it, once all the
 *                         nodes in the circle are down and there is only
 *                         one left, display stayin' alive lyrics with
 *                         the person's name who won the game, then kill
 *                         that last person and deallocate him... yep...
 *************************************************************************/
void LetTheHungerGameBegin(Person* head) {
    if (head == NULL) {
        return;
    }
    Person* pHead = head;
    while (pHead->next != pHead) {
        BuildAndPrintKillStatement(pHead,pHead->next);
        pHead->KillNext(pHead);
        pHead = pHead->next;
    }
    printf("Ah, ha, ha, ha, stayin' alive, stayin' alive! Ah, ha, ha, ha, \"%s\" stayin' alive!\n", pHead->name);
    pHead->SelfDestruct(pHead);
}