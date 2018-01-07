//
// Created by Orsan Awwad on 31/12/2017.
//

/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: !(!(!(!(!(!(!(!(!(!(!(!(ENTER YOUR EXERCISE NAME HERE)!)!)!)!)!)!)!)!)!)!
******************************************/

#include "person.h"
#include "stdlib.h"
#include "stdio.h"
#include "utils.h"

Person* InitTheHungerGame() {
    //TODO: Ask user questions
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
void InsertLaters(Person* head) {
    if (head != NULL) {
        while (1) {
            puts("Are you late? (0|1)");
            int option = ReadNumber();
            if (option == 1) {
                puts("Insert your best friend's ID:");
                //TODO: Write a function that finds the person pointer
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
Person* RemoveCowards(Person* head) {
    if (head != NULL) {
        Person *pHead = head;
        while (1) {
            if (pHead == NULL) {
                return NULL;
                break;
            }
            puts("Is there a coward in here? (0|1)");
            int option = ReadNumber();
            if (option == 1) {
                puts("Insert your ID, you, lame pudding-heart coward:");
                int idNumber = ReadNumber();
                Person *theCoward = FindPerson(pHead, idNumber);
                if (theCoward != NULL) {
//                    Person *behindTheCoward = FindPreviousPerson(pHead, theCoward);
                    printf("Let the world know that you are a coward, %s!\n", theCoward->name);
                    pHead = ConnectLeftAndRightOfPerson(pHead, theCoward);
                } else {
                    //TODO: rephrase the error message
                    printf("No Such ID: %d\n", idNumber);
                }
            } else {
                return pHead;
            }
        }
    }
}
void LetTheHungerGameBegin(Person* head) {
    if (head == NULL) {
        return;
    }
    Person* pHead = head;
    while (head != NULL && pHead->next != pHead) {
        //TODO: Print who kills who and their children
        BuildAndPrintKillStatement(pHead,pHead->next);
        pHead->KillNext(pHead);
        pHead = pHead->next;
    }
    printf("Ah, ha, ha, ha, stayin' alive, stayin' alive! Ah, ha, ha, ha, \"%s\" stayin' alive!\n", pHead->name);
    pHead->SelfDestruct(pHead);
}