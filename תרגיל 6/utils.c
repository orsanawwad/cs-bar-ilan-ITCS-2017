//
// Created by Orsan Awwad on 31/12/2017.
//

/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: !(!(!(!(!(!(!(!(!(!(!(!(ENTER YOUR EXERCISE NAME HERE)!)!)!)!)!)!)!)!)!)!
******************************************/

#include "stdio.h"
#include "person.h"
#include "string.h"
#include "stdlib.h"

#define BUFFER_SIZE 80

void PrintCircle(Person* head) {
    Person* pHead = head;
    if (head != NULL) {
        puts("----------");
        do {
            pHead->Print(pHead);
            pHead = pHead->next;
            puts("----------");
        } while (head != pHead);
    }
}

char* ReadInputString() {
    char buffer[BUFFER_SIZE+1] = {'\0'};
//    fgets(buffer,BUFFER_SIZE+1,stdin);
    scanf("\n%s",&buffer);
//    for (int i = 0; i < BUFFER_SIZE+1; ++i) {
//        if (buffer[i] == '\n'){
//            buffer[i] = '\0';
//        }
//    }
    char* pText = NULL;
    pText = (char *)malloc((strlen(buffer) + 1));
    if (pText != NULL) {
        strcpy(pText, buffer);
        return pText;
    } else {
        return NULL;
    }
}

//TODO: For each ReadNumber call make sure to check for less than zero values (because they're not supposed to be negatives)
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

Person* FindPreviousPerson(Person* head, Person* person) {
    Person* pHead = head;
    Person* targetPerson = NULL;
    do {
        if (pHead->next == person) {
            targetPerson = pHead;
            return targetPerson;
        } else {
            pHead = pHead->next;
        }
    } while (pHead != head);
    return targetPerson;
}

Person* FindPerson(Person* head, int id) {
    Person* pHead = head;
    do {
        if (pHead != NULL) {
            if (pHead->id == id) {
                return pHead;
            } else {
                pHead = pHead->next;
            }
        } else {
            return NULL;
        }
    } while (pHead != head);
    return NULL;
}


//TODO: Redo this function with better logic
Person* ConnectLeftAndRightOfPerson(Person* head, Person* personToRemove) {
    if (head != NULL) {
        if (head != personToRemove) {
            Person* previousToThePersonToRemove = FindPreviousPerson(head, personToRemove);
            Person* nextToPersonToRemove = personToRemove->next;
            personToRemove->SelfDestruct(personToRemove);
            previousToThePersonToRemove->next = nextToPersonToRemove;
            personToRemove = NULL;
            return head;
        } else {
            if (personToRemove->next != head) {
                Person* newHead = personToRemove->next;
                Person* previousToThePersonToRemove = FindPreviousPerson(head, personToRemove);
                Person* nextToPersonToRemove = personToRemove->next;
                personToRemove->SelfDestruct(personToRemove);
                previousToThePersonToRemove->next = nextToPersonToRemove;
                personToRemove = NULL;
                return newHead;
            } else {
                personToRemove->SelfDestruct(personToRemove);
                personToRemove = NULL;
                return NULL;
            }
        }
    } else {
        //TODO: print error
    }
    return NULL;
}

//TODO: Make sure this function works as intended and that char* is actually a stack memory placement
void BuildAndPrintKillStatement(Person* killer, Person* victim) {
    char* killsKeyword = " kills ";
    char* andKeyword = " and ";

    int totalChildrenNameCount = 0;
    for (int i = 0; i < victim->numOfKids; ++i) {
        totalChildrenNameCount = totalChildrenNameCount + (int)strlen(victim->kids[i]);
    }

    int stringCount = (int)(strlen(killer->name) + strlen(killsKeyword) + strlen(victim->name));
    stringCount += (int)(totalChildrenNameCount + strlen(andKeyword)*victim->numOfKids);

    char* statement = (char *)calloc(stringCount + 1, sizeof(char));

    strcat(statement,killer->name);
    strcat(statement,killsKeyword);
    strcat(statement,victim->name);
    for (int i = 0; i < victim->numOfKids; ++i) {
        strcat(statement,andKeyword);
        strcat(statement,victim->kids[i]);
    }
    puts(statement);
    strcpy(statement,"");
    free(statement);
}

int CountNodes(Person* head) {
    int count = 0;
    Person* pHead = head;
    do {
        count++;
        pHead = pHead->next;
    } while (pHead != head);
    return count;
}