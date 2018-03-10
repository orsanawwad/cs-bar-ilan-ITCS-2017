/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 6
******************************************/

#include "stdlib.h"
#include "person.h"
#include "utils.h"
#include "stdio.h"
#include "stdarg.h"

/**
 * Constants
 */

#define PRINT_PERSON_NAME "Name: %s\n"

#define PRINT_PERSON_ID "ID: %d\n"

#define PRINT_PERSON_KIDS "Kid #%d: %s\n"

#define PERSON_ERROR "Could not allocate memory for new person"

#define PERSON_ERROR_CREATE "Error creating next person."

#define PERSON_ERROR_CREATE_NULL "Error creating person, received null pointer."

#define PERSON_ERROR_CREATE_KIDS "Error Initializing values, error while allocating memory for kids"

#define PERSON_ERROR_RECEIVED_NULL "Error Initializing values, received pointer to NULL"

#define ASK_PERSON_NAME "Name:"

#define ASK_PERSON_ID "ID:"

#define ASK_PERSON_NUM_OF_KIDS "Num of kids:"

#define ASK_PERSON_KID_NUMBER_NAME "Kid #%d name:\n"

/**************************************************************************
 * Function name: PrintPerson
 * Input: Person pointer to print it's details
 * Output: No output
 * The function operation: Print the name, id and the children if any
 *                         exists.
 *************************************************************************/
void PrintPerson(Person* person) {
    printf(PRINT_PERSON_NAME,person->name);
    printf(PRINT_PERSON_ID,person->id);
    for (int i = 0; i < person->numOfKids; ++i) {
        printf(PRINT_PERSON_KIDS,i+1,person->kids[i]);
    }
}

/**************************************************************************
 * Function name: CreatePerson
 * Input: No input
 * Output: Returns pointer to a newly allocated person object
 * The function operation: Allocates new person object and calls
 *                         InitPersonValues to initialize all of it's
 *                         values like name, id, and kids names if there's
 *                         any, then returns the pointer to that object.
 *************************************************************************/
Person* CreatePerson() {
    Person* ptrPerson = (Person*)malloc(sizeof(Person));
    if (ptrPerson != NULL) {
        InitPersonValues(ptrPerson);
        return ptrPerson;
    } else {
        //If Initializing the value failed, return NULL
        puts(PERSON_ERROR);
        return NULL;
    }
}

/**************************************************************************
 * Function name: CreateNext
 * Input: Person pointerz, IsNextNext boolean, variadic that contains
 *        pointers to Person struct.
 * Output: No output.
 * The function operation: If IsNextNext is false, it takes the current
 *                         person and creates new person in its next
 *                         pointer, else, it takes the variadic list and
 *                         extracts the person object from there, then
 *                         it replaces the next pointer to of the
 *                         original person object to point to a new person
 *                         then in the new person next's pointer is then
 *                         pointed to the person that was extracted from
 *                         the variadic list.
 *************************************************************************/
void CreateNext(Person* person, int IsNextNext, ...) {
    if (IsNextNext == 0) {
        if (person != NULL) {
            person->next = CreatePerson();
            if (person->next == NULL) {
                puts(PERSON_ERROR_CREATE);
                return;
            }
        } else {
            puts(PERSON_ERROR_CREATE_NULL);
        }
    } else {
        va_list variadicNextList;
        va_start(variadicNextList,IsNextNext);
        Person* theLatter = va_arg(variadicNextList, Person*);
        va_end(variadicNextList);
        Person* newPerson = CreatePerson();
        if (newPerson == NULL) {
            //If Creating a new person failed, exit the function
            return;
        } else {
            person->next = newPerson;
        }
        (person->next)->next = theLatter;
    }
}

/**************************************************************************
 * Function name: SelfDestruct
 * Input: Person pointer
 * Output: NULL pointer
 * The function operation: Frees name, each kid, and the kids pointers,
 *                         set all the functions to null, and free the
 *                         person object pointer itself, then return
 *                         null.
 *************************************************************************/
Person* SelfDestruct(Person* person) {
    Person* nextToPerson = person->next;
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
    return nextToPerson;
}

/**************************************************************************
 * Function name: KillNext
 * Input: Person pointer
 * Output: No output
 * The function operation: This function connects the person and the
 *                         person after the victim and kills the victim.
 *************************************************************************/
void KillNext(Person* person) {
    if (person != NULL) {
        Person *victim = person->next;
        person->next = victim->next;
        victim->SelfDestruct(victim);
    }
}

/**************************************************************************
 * Function name: InitPersonValues
 * Input: Person pointer
 * Output: No output
 * The function operation: This function asks the user for information
 *                         about the person's name and id and number of
 *                         kids, if there were any number of kids it then
 *                         asks for their names and sets it.
 *************************************************************************/
void InitPersonValues(Person* person) {
    if (person != NULL) {
        puts(ASK_PERSON_NAME);
        person->name = ReadInputString();
        puts(ASK_PERSON_ID);
        person->id = ReadNumber();
        if (person->id < 0) {
            //Id number was negative
            person->id = -1*person->id;
        }
        puts(ASK_PERSON_NUM_OF_KIDS);
        person->numOfKids = ReadNumber();
        if (person->numOfKids < 0) {
            //Number of kids was negative
            person->numOfKids = -1*person->numOfKids;
        }
        person->kids = (char **)calloc(person->numOfKids, sizeof(char *));
        if (person->kids != NULL) {
            int i;
            for (i = 0; i < person->numOfKids; ++i) {
                printf(ASK_PERSON_KID_NUMBER_NAME, i + 1);
                person->kids[i] = ReadInputString();
                if (person->kids[i] == NULL) {
                    //If one of the children failed to get a name, free everything and exit function
                    for (int j = i; j != 0; j--) {
                        free(person->kids[j]);
                    }
                    free(person->kids);
                    free(person->name);
                    puts(PERSON_ERROR_RECEIVED_NULL);
                    return;
                }
            }
        } else {
            //If allocating kids failed, free the name, since it couldve passed
            free(person->name);
            puts(PERSON_ERROR_CREATE_KIDS);
            return;
        }
        person->Print = PrintPerson;
        person->CreateNext = CreateNext;
        person->KillNext = KillNext;
        person->SelfDestruct = SelfDestruct;

    } else {
        puts(PERSON_ERROR_RECEIVED_NULL);
        return;
    }
}
