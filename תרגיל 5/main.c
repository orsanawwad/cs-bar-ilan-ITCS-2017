/***************************
* Student name: Orsan Awwad
* Student: *
* Course Exercise Group: 01
* Exercise name: Exercise 5
***************************/

#include <stdio.h>
#include "ex5.h"

//Main function
int main() {
    //Reset the database to nulls
    ResetEverything();
    //Print the menu
    PrintMenu();
    //Flag for keeping track if we built the menu or not
    boolean PrintedMenu = false;
    while (1) {
        //Asks for input
        char inputNumber[3] = {'\0'};
        fgets(inputNumber,3,stdin);
        char inputLine[201];
        switch (inputNumber[0]) {
            case '0':
                return 0;
            case '1':
                //Get the line to check
                fgets(inputLine, 201, stdin);
                ProcessFirstOperation(inputLine);
                break;
            case '2':
                //Start deleting student process
                DeleteStudent();
                break;
            case '3':
                //Start aggregation process that calculate the maximum value
                ProcessAggregation(MAXIMAL_STUDENT);
                break;
            case '4':
                //Start aggregation process that calculate the value for each student
                ProcessAggregation(ALL_STUDENTS);
                break;
            case '5':
                //Print the menu and set flag to true, because we dont want to print Next operation message after this
                PrintedMenu = true;
                PrintMenu();
                break;
            default:
                break;
        }
        if (PrintedMenu) {
            PrintedMenu = false;
        } else {
            PrintNextOperationMessage();
        }
    }
}
