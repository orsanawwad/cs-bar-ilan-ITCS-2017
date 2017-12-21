#include <stdio.h>
#include "ex5.h"
#include "string.h"

#define MAX_STUDENTS 50
#define MAX_NAME 20
#define MAX_COURSES 20

char firstNames[MAX_STUDENTS][MAX_NAME + 1];
char lastNames[MAX_STUDENTS][MAX_NAME + 1];
char courses[MAX_STUDENTS][MAX_COURSES][MAX_NAME + 1];
int grades[MAX_STUDENTS][MAX_COURSES];
//char grades[MAX_STUDENTS][MAX_COURSES][4];

//Define boolean "data type" to easily express the code
//typedef enum { false, true } boolean;

enum Errors {
    INVALID_INPUT,INVALID_OPERATION,STUDENT_DOESNT_EXIST
};

enum Student {
    FIRST_NAME, LAST_NAME
};

typedef enum {
    UPDATED_STUDENT,DELETED_STUDENT,ADDED_STUDENT
} StudentUpdate;

typedef enum {
    StudentFirstName,StudentLastName,StudentCourse,StudentGrade
} ParseSymbols;


boolean DEBUG_ENABLED = 0;
void DebugLog(char debug_message[]) {
    if (DEBUG_ENABLED) {
        printf("DEBUG LOG: %s\n",debug_message);
    }
}

// ✅
void PrintMenu() {
    printf("Please select the operation:\n");
    printf("\t0. Exit.\n");
    printf("\t1. Insert or update student grades.\n");
    printf("\t2. Delete student information.\n");
    printf("\t3. Print the student with maximal computed grade.\n");
    printf("\t4. Print all the students with their computed grades.\n");
    printf("\t5. Print the menu.\n");
}

// ✅
void PrintAggregationMenu() {
    printf("Please select the aggregation method:\n");
    printf("\ta. Average grade.\n");
    printf("\tb. Maximal grade.\n");
    printf("\tc. Minimal grade.\n");
    printf("\td. Sum.\n");
    printf("\te. Count.\n");
    printf("\t0. Return the main menu.\n");
}

// ✅
void PrintNextOperationMessage() {
    printf("Select the next operation (insert 5 for complete menu).\n");
}

// ✅
void PrintAggregation(char firstName[], char lastName[], int grade) {
    printf("%s %s, %d", firstName, lastName, grade);
}

char StopMarker(ParseSymbols parseSymbols) {
    switch (parseSymbols) {
        case StudentFirstName:
            return ' ';
            break;
        case StudentLastName:
            return ':';
            break;
        case StudentCourse:
            return ',';
            break;
        case StudentGrade:
            return ';';
            break;
    }
}

// ✅
//// NOTE TO SELF: DONT FORGET TO ADD LIMITATION CHECKS HERE
//// Limitations checks aka if length is longer than array and what not
void ArrayCopy(char source[], int sourceBegin, char target[], int targetBegin, int length) {
    printf("INSIDE ARRAYCOPY\n");
    printf("\tValue of source: %s",source);
    printf("\tValue of sourceBegin: %d\n",sourceBegin);
    printf("\tValue of target: %s\n",target);
    printf("\tValue of targetBegin: %d\n",targetBegin);
    printf("\tValue of length: %d\n",length);
    for(int i = sourceBegin, j = targetBegin; i < sourceBegin + length; i++, j++) {
        DebugLog("Inside ArrayCopy Loop");
        target[j] = '\0';
        target[j] = source[i];
        target[j + 1] = '\0';
    }
}

void PrintStatusUpdate() {

}

void OperationPicker() {

}

void PrintErrors() {

}

int ConvertStrToInt(char str[])
{
    int sum = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            sum = (sum * 10) + (str[i] - '0');
        }
    }

    // return result.
    return sum;
}

int FetchEmptyQueue() {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        char DEBUGEMPTY = firstNames[i][0];
        DebugLog("Inside FetchEmptyQueue Loop");
        if (firstNames[i][0] == '\0') {
            return i;
        }
    }
    return -1;
}

int GetFirstNameIndexFromDB(char firstName[]) {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if(strcmp(firstNames[i],firstName) == 0) {
            return i;
        }
    }
    return -1;
}

int GetLastNameIndexFromDB(char lastName[]) {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if(strcmp(lastNames[i],lastName) == 0) {
            return i;
        }
    }
    return -1;
}

int GetCourseIndexFromDB(char studentCourses[],char courseName[]) {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if(strcmp((char*)studentCourses[i],courseName) == 0) {
            return i;
        }
    }
    return -1;
}

int GetGradeFromIndex(int studentIndex,int courseIndex) {
    return grades[studentIndex][courseIndex];
}

int SetGradeIntoIndex(int studentIndex,int courseIndex) {
    return grades[studentIndex][courseIndex];
}

// ✅
boolean ValidateLineInput(char inputLine[]) {

//    char firstNames[MAX_STUDENTS][MAX_NAME + 1];
//    char lastNames[MAX_STUDENTS][MAX_NAME + 1];
//    char courses[MAX_STUDENTS][MAX_COURSES][MAX_NAME + 1];
////int grades[MAX_STUDENTS][MAX_COURSES];
//    char grades[MAX_STUDENTS][MAX_COURSES][4];

    boolean BeganFirstNameCheck = false;
    boolean PassedFirstNameCheck = false;
    int firstNameBeginIndex = -1;
    int firstNameEndIndex = -1;
    char firstName[MAX_NAME+1];

    boolean BeganLastNameCheck = false;
    boolean PassedLastNameCheck = false;
    int lastNameBeginIndex = -1;
    int lastNameEndIndex = -1;
    char lastName[MAX_NAME+1];

    boolean BeganCourseNameCheck = false;
    boolean PassedCourseNameCheck = false;
    int courseNameBeginIndex = -1;
    int courseNameEndIndex = -1;
    int courseNames[66][2];
    int courseNameIndex = 0;

    boolean BeganCourseGradeCheck = false;
    boolean PassedCourseGradeCheck = false;
    int courseGradeBeginIndex = -1;
    int courseGradeEndIndex = -1;
    int courseGrades[66][2];
    int courseGradeIndex = 0;

    for (int i = 0; i < strlen(inputLine); ++i) {
        char DEBUG = inputLine[i];
        DebugLog("Inside ValidateLineInput Loop");
        boolean IsSmallLetter = (boolean) (inputLine[i] >= 'a' && inputLine[i] <= 'z');
        boolean IsCapitalLetter = (boolean) (inputLine[i] >= 'A' && inputLine[i] <= 'Z');
        boolean IsLetter = (boolean) (IsCapitalLetter || IsSmallLetter);
        boolean IsDigitCharacter = (boolean) (inputLine[i] >= '0' && inputLine[i] <= '9');
        boolean IsSpaceCharacter = (boolean) (inputLine[i] == ' ');
        boolean IsColonCharacter = (boolean) (inputLine[i] == ':');
        boolean IsCommaCharacter = (boolean) (inputLine[i] == ',');
        boolean IsSemiColonCharacter = (boolean) (inputLine[i] == ';');
        boolean IsNullOrNewLineCharacter = (boolean) (inputLine[i] == '\n' || inputLine[i] == '\0');

        if (!PassedFirstNameCheck) {
            if (IsSpaceCharacter && !BeganFirstNameCheck) {
                continue;
            } else if (IsLetter) {
                BeganFirstNameCheck = true;
                if (firstNameBeginIndex == -1) {
                    firstNameBeginIndex = i;
                }
                continue;
            } else if (IsSpaceCharacter) {
                PassedFirstNameCheck = true;
                if (firstNameEndIndex == -1) {
                    firstNameEndIndex = i;
                }
                continue;
            } else {
                return false;
            }
        } else if (!PassedLastNameCheck) {
            if (IsSpaceCharacter && !BeganLastNameCheck) {
                continue;
            } else if (IsLetter || IsSpaceCharacter) {
                BeganLastNameCheck = true;
                if (lastNameBeginIndex == -1) {
                    lastNameBeginIndex = i;
                }
                continue;
            } else if (IsColonCharacter) {
                PassedLastNameCheck = true;
                if (lastNameEndIndex == -1) {
                    lastNameEndIndex = i;
                }
                continue;
            } else {
                return false;
            }
        } else if (!PassedCourseNameCheck) {
            if (IsSpaceCharacter && !BeganCourseNameCheck) {
                continue;
            } else if (IsLetter || IsSpaceCharacter) {
                BeganCourseNameCheck = true;
                if (courseNameBeginIndex == -1) {
                    courseNameBeginIndex = i;
                }
                continue;
            } else if (IsCommaCharacter) {
                PassedCourseNameCheck = true;
                courseNameEndIndex = i;
                courseNames[courseNameIndex][0] = courseNameBeginIndex;
                courseNames[courseNameIndex][1] = courseNameEndIndex;
                courseNameIndex++;
                courseNameBeginIndex = -1;
                courseNameEndIndex = -1;
                continue;
            } else {
                return false;
            }
        } else if (!PassedCourseGradeCheck) {
            if (IsSpaceCharacter && !BeganCourseGradeCheck) {
                continue;
            } else if (IsDigitCharacter || IsSpaceCharacter) {
                BeganCourseGradeCheck = true;
                if (courseGradeBeginIndex == -1) {
                    courseGradeBeginIndex = i;
                }
                continue;
            } else if (IsSemiColonCharacter) {
                PassedCourseGradeCheck = true;
                if (courseGradeEndIndex == -1) {
                    courseGradeEndIndex = i;
                }
                courseGrades[courseGradeIndex][0] = courseGradeBeginIndex;
                courseGrades[courseGradeIndex][1] = courseGradeEndIndex;
                courseGradeIndex++;
                courseGradeBeginIndex = -1;
                courseGradeEndIndex = -1;
                continue;
            } else {
                return false;
            }
        } else if (!IsSpaceCharacter && !IsNullOrNewLineCharacter) {
            BeganCourseNameCheck = false;
            PassedCourseNameCheck = false;
            BeganCourseGradeCheck = false;
            PassedCourseGradeCheck = false;
            i--;
        }

    }

    //TODO: Add checks if name exists and if course exists etc...
    if (PassedFirstNameCheck && PassedLastNameCheck && PassedCourseNameCheck && PassedCourseGradeCheck) {
//        DebugLog("Inside ValidateLineInput INSERTION");

//        char tempFirstName[MAX_NAME];
//        char tempLastName[MAX_NAME];
//
//
//        if (GetFirstNameIndexFromDB() )
//
        printf("VALIDATION PASSED\n");
        printf("\tValue of firstNameBeginIndex: %d\n",firstNameBeginIndex);
        printf("\tValue of firstNameEndIndex: %d\n",firstNameEndIndex);
        printf("\tValue of firstNameLength: %d\n",firstNameEndIndex-firstNameBeginIndex);
        printf("\tValue of lastNameBeginIndex: %d\n",lastNameBeginIndex);
        printf("\tValue of lastNameEndIndex: %d\n",lastNameEndIndex);
        printf("\tValue of lastNameLength: %d\n",lastNameEndIndex-lastNameBeginIndex);

        int insertQueueIndex = FetchEmptyQueue();
        ArrayCopy(inputLine,firstNameBeginIndex,firstNames[insertQueueIndex],0,firstNameEndIndex-firstNameBeginIndex);
        ArrayCopy(inputLine,lastNameBeginIndex,lastNames[insertQueueIndex],0,lastNameEndIndex-lastNameBeginIndex);
        for (int i = 0; i < courseNameIndex; ++i) {
            printf("Inside ValidateLineInput INSERTION course loop\n");
            printf("\tValue of inputLine: %s",inputLine);
            printf("\tValue of courseNames[%d][0]: %d\n",i,courseNames[i][0]);
            printf("\tValue of courseNames[%d][1]: %d\n",i,courseNames[i][1]);
            printf("\tValue of courseNameLength: %d\n",courseNames[i][1]-courseNames[i][0]);
            printf("\tValue of courseGrades[%d][0]: %d\n",i,courseGrades[i][0]);
            printf("\tValue of courseGrades[%d][1]: %d\n",i,courseGrades[i][1]);
            printf("\tValue of courseGradeLength: %d\n",courseGrades[i][1]-courseGrades[i][0]);

            ArrayCopy(inputLine,courseNames[i][0],courses[insertQueueIndex][i],0,courseNames[i][1]-courseNames[i][0]);
            char tempGrade[4] = {'\0'};
            ArrayCopy(inputLine,courseGrades[i][0],tempGrade,0,courseGrades[i][1]-courseGrades[i][0]);
            int actualGradeTemp = ConvertStrToInt(tempGrade);
            grades[insertQueueIndex][i] = actualGradeTemp;
        }
        return true;
    } else {
        return false;
    }
}

void GetName(char inputLine[]) {
    for (int i = 0; inputLine[i] == ':'; ++i) {
        boolean IsSmallLetter = (boolean) (inputLine[i] >= 'a' && inputLine[i] <= 'z');
        boolean IsCapitalLetter = (boolean) (inputLine[i] >= 'A' && inputLine[i] <= 'Z');
        boolean IsLetter = (boolean) (IsCapitalLetter || IsSmallLetter);
        boolean IsSpaceCharacter = (boolean) (inputLine[i] == ' ');

    }
}

void ProcessFirstOperation(char inputLine[]) {
    boolean IsValidInput = ValidateLineInput(inputLine);
    printf("%s\n",firstNames[0]);
    printf("%s\n",lastNames[0]);
    printf("%s\n",courses[0][0]);
    printf("%d\n",grades[0][0]);
    printf("%s\n",courses[0][1]);
    printf("%d\n",grades[0][1]);
    printf("%s\n",courses[0][2]);
    printf("%d\n",grades[0][2]);
    printf("%s\n",firstNames[1]);
    printf("%s\n",lastNames[1]);
    printf("%s\n",courses[1][0]);
    printf("%d\n",grades[1][0]);
    printf("%s\n",courses[1][1]);
    printf("%d\n",grades[1][1]);
    printf("%s\n",courses[1][2]);
    printf("%d\n",grades[1][2]);
//    printf("%s\n",courses[0][3]);
//    printf("%s\n",grades[0][3]);
    if (IsValidInput) {

    }
}


/*
 *
 * Parse
 *
 * Check for valid input
 *
 * Cleanup
 *
 * Add to database
 *
 */

//a a:a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;a,0;

// Yossi Cohen: OOP,100; LA, 100; LAAAAA, 88;
// Yossi    Sham    : QQQQ, 10; LA,100; LAAAAA, 88;


//// Yossi Cohen: OOP,100;LAA,