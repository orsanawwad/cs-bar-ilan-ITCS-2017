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
#include "utils.h"
#include "string.h"

void SwapPersonNodes(Person* head, Person* firstCompare, Person* secondCompare) {
    Person* previousToFirst = FindPreviousPerson(head, firstCompare);
    Person* nextToSecond = secondCompare->next;
    previousToFirst->next = secondCompare;
    secondCompare->next = firstCompare;
    firstCompare->next = nextToSecond;
}

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