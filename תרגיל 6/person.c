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

/**************************************************************************
 * Function name: PrintPerson
 * Input: Person pointer to print it's details
 * Output: No output
 * The function operation: Print the name, id and the children if any
 *                         exists.
 *************************************************************************/
void PrintPerson(Person* person) {
    printf("Name: %s\n",person->name);
    printf("ID: %d\n",person->id);
    for (int i = 0; i < person->numOfKids; ++i) {
        printf("Kid #%d: %s\n",i+1,person->kids[i]);
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
    Person* pPerson = malloc(sizeof(Person));
    if (pPerson != NULL) {
        InitPersonValues(pPerson);
        return pPerson;
    } else {
        puts("Could not allocate memory for new person");
        return NULL;
    }
}

/**************************************************************************
 * Function name: CreateNext
 * Input: Person pointerz, IsNextNext boolean, variadic list of Person struct
 *        pointers.
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
                puts("Error creating next person.");
            }
        } else {
            puts("Error creating person, received null pointer.");
        }
    } else {
        va_list ap;
        va_start(ap,IsNextNext);
        Person* theLatter = va_arg(ap, Person*);
        va_end(ap);
        person->next = CreatePerson();
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

/**************************************************************************
 * Function name: KillNext
 * Input: Person pointer
 * Output: No output
 * The function operation: This function just calls
 *                         ConnectLeftAndRightOfPerson which takes two
 *                         pointers to person objects and deletes the
 *                         second one and connect the first and the one
 *                         that was after the second input person.
 *************************************************************************/
void KillNext(Person* person) {
    ConnectLeftAndRightOfPerson(person,person->next);
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
        puts("Name:");
        person->name = ReadInputString();
        puts("ID:");
        person->id = ReadNumber();
        if (person->id < 0) {
            //Id number was negative
            person->id = -1*person->id;
        }
        puts("Num of kids:");
        person->numOfKids = ReadNumber();
        if (person->numOfKids < 0) {
            //Number of kids was negative
            person->numOfKids = -1*person->numOfKids;
        }
        person->kids = (char **)calloc(person->numOfKids, sizeof(char *));
        if (person->kids != NULL) {
            for (int i = 0; i < person->numOfKids; ++i) {
                printf("Kid #%d name:\n", i + 1);
                person->kids[i] = ReadInputString();
            }
        } else {
            puts("Error Initializing values, error while allocating memory for kids");
            return;
        }
        person->Print = PrintPerson;
        person->CreateNext = CreateNext;
        person->KillNext = KillNext;
        person->SelfDestruct = SelfDestruct;
    } else {
        puts("Error Initializing values, received pointer to NULL");
    }
}