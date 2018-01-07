/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 6
******************************************/

#ifndef PERSON_H
#define PERSON_H

struct Person {
    char* name;
    int id;
    int numOfKids;
    char** kids;
    struct Person* next;
    void (*Print)(struct Person* this);
    void (*KillNext)(struct Person* this);
    struct Person* (*SelfDestruct)(struct Person* this);
    void (*CreateNext)(struct Person* this, int isNextNext, ...);
};

typedef struct Person Person;

/**************************************************************************
 * Function name: CreatePerson
 * Input: No input
 * Output: Returns pointer to a newly allocated person object
 * The function operation: Allocates new person object and calls
 *                         InitPersonValues to initialize all of it's
 *                         values like name, id, and kids names if there's
 *                         any, then returns the pointer to that object.
 *************************************************************************/
Person* CreatePerson();

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
void InitPersonValues(Person* person);

#endif
