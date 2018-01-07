//
// Created by Orsan Awwad on 31/12/2017.
//

/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: !(!(!(!(!(!(!(!(!(!(!(!(ENTER YOUR EXERCISE NAME HERE)!)!)!)!)!)!)!)!)!)!
******************************************/

#include "stdlib.h"
#include "person.h"
#include "utils.h"
#include "stdio.h"
#include "stdarg.h"

void PrintPerson(Person* person) {
    printf("Name: %s\n",person->name);
    printf("ID: %d\n",person->id);
    for (int i = 0; i < person->numOfKids; ++i) {
        printf("Kid #%d: %s\n",i+1,person->kids[i]);
    }
}

Person* CreatePerson() {
    Person* pPerson = malloc(sizeof(Person));
    if (pPerson != NULL) {
        InitPersonValues(pPerson);
        return pPerson;
    } else {
        //TODO: Add error handling
        return NULL;
    }
}

void CreateNext(Person* person, int isNextNext, ...) {
    if (isNextNext == 0) {
        if (person != NULL) {
            //TODO: Find last one and connect... what?
            person->next = CreatePerson();
        } else {
            //TODO: Find last one in the circle and connect the new one to it
            //TODO: Rethink what this else is supposed to do (error handling probably?)
            //EDIT: We might not need it because the previous function InitHungerGames will close the loop
        }
    } else {
        va_list ap;
        va_start(ap,isNextNext);
        Person* theLatter = va_arg(ap, Person*);
        va_end(ap);
        person->next = CreatePerson();
        (person->next)->next = theLatter;
    }
}

Person* SelfDestruct(Person* person) {
    free(person->name);
    for (int i = 0; i < person->numOfKids; ++i) {
        free(person->kids[i]);
    }
    free(person->kids);
    person->next = NULL;
    person->Print = NULL;
    person->KillNext = NULL;
    person->CreateNext = NULL;
    person->SelfDestruct = NULL;
    free(person);
    return NULL;
}

void KillNext(Person* person) {
    //TODO: Add checks like null issues and if the next/previous person is the same person (AKA only one in the circle)
//    Person* previousToThePersonToRemove = FindPreviousPerson(person, person);
//    Person* nextToPersonToRemove = person->next;
//    person->SelfDestruct(person);
//    previousToThePersonToRemove->next = nextToPersonToRemove;

    ConnectLeftAndRightOfPerson(person,person->next);
}

void InitPersonValues(Person* person) {
    if (person != NULL) {
        //TODO: Add NULL Check
        puts("Name:");
        person->name = ReadInputString();
        //TODO: Add negative number check
        puts("ID:");
        person->id = ReadNumber();
        //TODO: Add negative number check and if zero check
        puts("Num of kids:");
        person->numOfKids = ReadNumber();
        //TODO: Add NULL check for out of memory issue
        person->kids = (char **)calloc(person->numOfKids, sizeof(char *));
        for (int i = 0; i < person->numOfKids; ++i) {
            //TODO: Add printf with numbered message
            printf("Kid #%d name:\n",i+1);
            person->kids[i] = ReadInputString();
        }
        person->Print = PrintPerson;
        person->CreateNext = CreateNext;
        person->KillNext = KillNext;
        person->SelfDestruct = SelfDestruct;
        //TODO: Point the functions
    } else {
        //TODO: Add null pointer error
    }
}