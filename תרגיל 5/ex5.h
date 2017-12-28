/***************************
* Student name: Orsan Awwad
* Student: *
* Course Exercise Group: 01
* Exercise name: Exercise 5
***************************/
#ifndef EX5_H
#define EX5_H

//Typedef to define booleans, for better code readability
typedef enum { false, true } boolean;

//Parse status for understanding which of the following happened during the validation process, better than using
//numbers
typedef enum {
    UPDATED_STUDENT,ADDED_STUDENT,INVALID_STUDENT_INPUT,INSUFFICIENT_SPACE,UNKNOWN_PARSE_ERROR
} ParseStatus;

typedef enum {
    MAXIMAL_STUDENT, ALL_STUDENTS
} AggregationType;

/**********************************************************************
 * Function name: ResetEverything
 * Input: No input
 * Output: No output
 * Function operation: Loops through each student index and resets
 *                     all the details from using the functions called
 *                     below.
 **********************************************************************/
void ResetEverything();

/**********************************************************************
 * Function name: PrintMenu
 * Input: No input
 * Output: No returns but it prints menu options
 * Function operation: Prints the main menu options
 **********************************************************************/
void PrintMenu();

/**********************************************************************
 * Function name: ProcessAggregationAfterOption
 * Input: The function to call, and aggregation type (print maximal or
 *        everyone in order)
 * Output: No output
 * Function operation: The function checks which type of aggregation is
 *                     used then proceeds calling the generic
 *                     aggregation function with the index of the
 *                     student and prints the message as it should.
 **********************************************************************/
void ProcessAggregation(AggregationType type);

/**********************************************************************
 * Function name: ProcessFirstOperation
 * Input: The input line from main
 * Output: No output
 * Function operation: Runs ValidateLineInput and checks the status
 *                     it returned, then print the currect message,
 *                     if a student was added it calls UpdateSortCache
 *                     to update the sort cache array
 **********************************************************************/
void ProcessFirstOperation(char inputLine[]);

/**********************************************************************
 * Function name: PrintNextOperationMessage
 * Input: No input
 * Output: No returns but it prints menu option
 * Function operation: Prints the Next Operation message
 **********************************************************************/
void PrintNextOperationMessage();

/**********************************************************************
 * Function name: DeleteStudent
 * Input: No input
 * Output: No output
 * Function operation: This function asks for user input for first name
 *                     and last name then splits the name where if last
 *                     name included spaces it includes the spaces,
 *                     then checks if it exists using
 *                     GetFirstNameIndexFromDB and
 *                     GetLastNameIndexFromDB functions then proceed
 *                     into deleting every single information of that
 *                     student.
 **********************************************************************/
boolean DeleteStudent();

#endif //EX5_H
