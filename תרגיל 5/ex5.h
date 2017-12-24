#ifndef EX5_H
#define EX5_H

typedef enum { false, true } boolean;

typedef enum {
    UPDATED_STUDENT,ADDED_STUDENT,INVALID_STUDENT_INPUT,INSUFFICIENT_SPACE,UNKNOWN_PARSE_ERROR
} StatusParseStatus;

void ResetEverything();

void PrintMenu();

void ProcessAggregation();

void ArrayCopy(char source[], int sourceBegin, char target[], int targetBegin, int length);

void ProcessFirstOperation(char inputLine[]);

void PrintNextOperationMessage();

StatusParseStatus ValidateLineInput(char inputLine[]);

boolean DeleteStudent();

#endif //EX5_H
