#include <stdio.h>
#include <string.h>
#include "ex5.h"

int main() {
    ResetEverything();
    PrintMenu();
    boolean PrintedMenu = false;
    while (1) {
        char inputNumber[1] = {'\0'};
        gets(inputNumber);
        char inputLine[201];
        switch (inputNumber[0]) {
            case '0':
                return 0;
            case '1':
                fgets(inputLine, 201, stdin);
                ProcessFirstOperation(inputLine);
                break;
            case '2':
                DeleteStudent();
                break;
            case '3':
                ProcessAggregation(MAXIMAL_STUDENT);
                break;
            case '4':
                ProcessAggregation(ALL_STUDENTS);
                break;
            case '5':
                PrintedMenu = true;
                PrintMenu();
                break;
            default:
                break;
        }
        if (!PrintedMenu) {
            PrintNextOperationMessage();
            PrintedMenu = false;
        }
    }
}