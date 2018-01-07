#ifndef UTILS_H
#define UTILS_H

#include "person.h"

void PrintCircle(Person* head);

char* ReadInputString();

int ReadNumber();

Person* FindPerson(Person* head, int ID);

Person* FindPreviousPerson(Person* head, Person* person);

Person* ConnectLeftAndRightOfPerson(Person* head, Person* personToRemove);

void BuildAndPrintKillStatement(Person* killer, Person* victim);

int CountNodes(Person* head);

#endif
