#ifndef EX5_H
#define EX5_H

typedef enum { false, true } boolean;

void PrintMenu();

void PrintAggregationMenu();

void ArrayCopy(char source[], int sourceBegin, char target[], int targetBegin, int length);

void ProcessFirstOperation(char inputLine[]);

void PrintNextOperationMessage();

boolean ValidateLineInput(char inputLine[]);

#endif //EX5_H
