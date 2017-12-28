#include <stdio.h>
#include "ex5.h"
#include "string.h"

#define MAX_STUDENTS 50
#define MAX_NAME 20
#define MAX_COURSES 5

char firstNames[MAX_STUDENTS][MAX_NAME];
char lastNames[MAX_STUDENTS][MAX_NAME];
char courses[MAX_STUDENTS][MAX_COURSES][MAX_NAME];
int grades[MAX_STUDENTS][MAX_COURSES];
int sortCache[MAX_STUDENTS];
int lastUpdated = -1;

void PrintMenu() {
    printf("Please select the operation:\n");
    printf("\t0. Exit.\n");
    printf("\t1. Insert or update student grades.\n");
    printf("\t2. Delete student information.\n");
    printf("\t3. Print the student with maximal computed grade.\n");
    printf("\t4. Print all the students with their computed grades.\n");
    printf("\t5. Print the menu.\n");
}

void PrintAggregationMenu() {
    printf("Please select the aggregation method:\n");
    printf("\ta. Average grade.\n");
    printf("\tb. Maximal grade.\n");
    printf("\tc. Minimal grade.\n");
    printf("\td. Sum.\n");
    printf("\te. Count.\n");
    printf("\t0. Return the main menu.\n");
}

void PrintNextOperationMessage() {
    printf("Select the next operation (insert 5 for complete menu).\n");
}

void ArrayCopy(char source[], int sourceBegin, char target[], int targetBegin, int length) {
    for(int i = sourceBegin, j = targetBegin; i < sourceBegin + length; i++, j++) {
        target[j] = '\0';
        target[j] = source[i];
        target[j + 1] = '\0';
    }
}

int ConvertStrToInt(char inputToConvert[]) {
    int sum = 0;

    for (int i = 0; inputToConvert[i] != '\0'; ++i) {
        if (inputToConvert[i] >= '0' && inputToConvert[i] <= '9') {
            sum = (sum * 10) + (inputToConvert[i] - '0');
        }
    }

    // return result.
    return sum;
}

int CountCurrentAmountOfStudent() {
    int count = 0;
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if (firstNames[i][0] != '\0') {
            count = count + 1;
        }
    }
    return count;
}

int FetchEmptyStudentIndex() {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if (firstNames[i][0] == '\0') {
            return i;
        }
    }
    return -1;
}

int FetchEmptyCourseIndexForStudent(int studentIndex) {
    for (int i = 0; i < MAX_COURSES; ++i) {
        if (courses[studentIndex][i][0] == '\0') {
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

void SetFirstNameIntoIndex(int index, char firstName[]) {
    ArrayCopy(firstName,0,firstNames[index],0,(int)strlen(firstName));
}

void DeleteFirstNameInIndex(int deletionIndex) {
    for (int i = 0; i < MAX_NAME; ++i) {
        firstNames[deletionIndex][i] = '\0';
    }
}

int GetLastNameIndexFromDB(char lastName[]) {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if(strcmp(lastNames[i],lastName) == 0) {
            return i;
        }
    }
    return -1;
}

void SetLastNameIntoIndex(int index, char lastName[]) {
    ArrayCopy(lastName,0,lastNames[index],0,(int)strlen(lastName));
}

void DeleteLastNameInIndex(int deletionIndex) {
    for (int i = 0; i < MAX_NAME; ++i) {
        lastNames[deletionIndex][i] = '\0';
    }
}

int GetCourseIndexFromStudentDB(int studentIndex,char courseName[]) {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if(strcmp(courses[studentIndex][i],courseName) == 0) {
            return i;
        }
    }
    return -1;
}

void SetCourseIntoIndex(int studentIndex,int courseIndex, char updatedCourse[]) {
    ArrayCopy(updatedCourse,0,courses[studentIndex][courseIndex],0,(int)strlen(updatedCourse));
}

void DeleteAllCoursesInIndex(int deletionIndex) {
    for (int i = 0; i < MAX_COURSES; ++i) {
        for (int j = 0; j < MAX_NAME; ++j) {
            courses[deletionIndex][i][j] = '\0';
        }
    }
}

void SetGradeIntoIndex(int studentIndex,int courseIndex, int updatedGrade) {
    grades[studentIndex][courseIndex] = updatedGrade;
}

void ResetAllGradesInIndex(int deletionIndex) {
    for (int i = 0; i < MAX_COURSES; ++i) {
        grades[deletionIndex][i] = -1;
    }
}

void ResetSortCache() {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        sortCache[i] = i;
    }
}

void ResetEverything() {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
//        for (int j = 0; j < MAX_NAME; ++j) {
//            firstNames[i][j] = '\0';
//            lastNames[i][j] = '\0';
//            for (int k = 0; k < MAX_COURSES; ++k) {
//                courses[i][k][j] = '\0';
//                grades[i][j] = 0;
//            }
//        }
        DeleteFirstNameInIndex(i);
        DeleteLastNameInIndex(i);
        DeleteAllCoursesInIndex(i);
        ResetAllGradesInIndex(i);
        ResetSortCache();
    }
}

int CourseCountForStudent(int studentIndex) {
    int count = 0;
    for (int i = 0; i < MAX_COURSES; ++i) {
        if (courses[studentIndex][i][0] != '\0') {
            count++;
        }
    }
    return count;
}

int CourseSumForStudent(int studentIndex) {
    int count = CourseCountForStudent(studentIndex);
    int sum = 0;
    for (int i = 0; i < count; ++i) {
        if (grades[studentIndex][i] != -1) {
            sum = sum + grades[studentIndex][i];
        }
    }
    return sum;
}

int AverageForStudent(int studentIndex) {
    int count = CourseCountForStudent(studentIndex);
    int sum = CourseSumForStudent(studentIndex);
    if (count != 0) {
        return sum / count;
    } else {
        return -1;
    }
}

int MaxGradeForStudent(int studentIndex) {
    int count = CourseCountForStudent(studentIndex);
    int max = grades[studentIndex][0];
    for (int i = 1; i < count; ++i) {
        if (max < grades[studentIndex][i]) {
            max = grades[studentIndex][i];
        }
    }
    return max;
}

int MinGradeForStudent(int studentIndex) {
    int count = CourseCountForStudent(studentIndex);
    int min = grades[studentIndex][0];
    for (int i = 1; i < count; ++i) {
        if (min > grades[studentIndex][i]) {
            min = grades[studentIndex][i];
        }
    }
    return min;
}

StatusParseStatus ValidateLineInput(char inputLine[]) {

    ////TODO: Split this function to multiple functions if possible
    ////TODO: Check with piazza, and other people for additional sneaky conditional inputs to prevent pitfalls
    ////TODO: Document the whole code
    ////TODO: Clean up

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

    int inputCourseNameCount = 0;
    int inputCourseGradeCount = 0;

    for (int i = 0; i < strlen(inputLine); ++i) {
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
            } else if (IsSpaceCharacter && BeganFirstNameCheck) {
                PassedFirstNameCheck = true;
                if (firstNameEndIndex == -1) {
                    firstNameEndIndex = i;
                }
                continue;
            } else {
                return INVALID_STUDENT_INPUT;
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
                return INVALID_STUDENT_INPUT;
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
            } else if (IsCommaCharacter && BeganCourseNameCheck) {
                PassedCourseNameCheck = true;
                courseNameEndIndex = i;
                courseNames[courseNameIndex][0] = courseNameBeginIndex;
                courseNames[courseNameIndex][1] = courseNameEndIndex;
                courseNameIndex++;
                inputCourseNameCount++;
                courseNameBeginIndex = -1;
                courseNameEndIndex = -1;
                continue;
            } else {
                return INVALID_STUDENT_INPUT;
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
            } else if (IsSemiColonCharacter && BeganCourseGradeCheck) {
                PassedCourseGradeCheck = true;
                if (courseGradeEndIndex == -1) {
                    courseGradeEndIndex = i;
                }
                courseGrades[courseGradeIndex][0] = courseGradeBeginIndex;
                courseGrades[courseGradeIndex][1] = courseGradeEndIndex;
                courseGradeIndex++;
                inputCourseGradeCount++;
                if (inputCourseGradeCount == 5 && inputCourseNameCount == 5) {
                    break;
                }
                courseGradeBeginIndex = -1;
                courseGradeEndIndex = -1;
                continue;
            } else {
                return INVALID_STUDENT_INPUT;
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

        char tempFirstName[MAX_NAME];
        char tempLastName[MAX_NAME];
        char tempCourses[courseNameIndex][MAX_NAME];
        char tempGradesChars[courseNameIndex][4];
        int tempGradesInt[courseNameIndex];
        ArrayCopy(inputLine,firstNameBeginIndex,tempFirstName,0,firstNameEndIndex-firstNameBeginIndex);
        ArrayCopy(inputLine,lastNameBeginIndex,tempLastName,0,lastNameEndIndex-lastNameBeginIndex);

        for (int i = 0; i < courseNameIndex; ++i) {
            ArrayCopy(inputLine,courseNames[i][0],tempCourses[i],0,courseNames[i][1]-courseNames[i][0]);
            char tempGrade[4] = {'\0'};
            ArrayCopy(inputLine,courseGrades[i][0],tempGradesChars[i],0,courseGrades[i][1]-courseGrades[i][0]);
            int actualGradeTemp = ConvertStrToInt(tempGradesChars[i]);
            tempGradesInt[i] = actualGradeTemp;
        }

        int firstNameIndex = GetFirstNameIndexFromDB(tempFirstName);
        int lastNameIndex = GetLastNameIndexFromDB(tempLastName);
        if ((firstNameIndex == lastNameIndex) && (firstNameIndex != -1 && lastNameIndex != -1)) {
            int studentIndex = firstNameIndex;
            boolean UpdatedAnyCourse = false;

            for (int i = 0; i < courseNameIndex; ++i) {
                int dbCourseIndex = GetCourseIndexFromStudentDB(studentIndex,tempCourses[i]);
                if (dbCourseIndex != -1) {
                    SetGradeIntoIndex(firstNameIndex,dbCourseIndex,tempGradesInt[i]);
                    UpdatedAnyCourse = true;
                } else {
                    int indexToInsertCourse = FetchEmptyCourseIndexForStudent(studentIndex);
                    if (indexToInsertCourse != -1) {
                        SetCourseIntoIndex(studentIndex,indexToInsertCourse,tempCourses[i]);
                        SetGradeIntoIndex(studentIndex,indexToInsertCourse,tempGradesInt[i]);
                        UpdatedAnyCourse = true;
                    } else {
                        ////TODO: PRINT NO SPACE ERROR ERROR
                        ////ACTUALLY YOU MIGHT JUST NEED TO PASS, NO ERRORS NEED TO BE THROWN
                        if (!UpdatedAnyCourse) {
                            return INVALID_STUDENT_INPUT;
                        }
                    }
                }
            }
            lastUpdated = firstNameIndex;
            return UPDATED_STUDENT;
        } else {
            int insertQueueIndex = FetchEmptyStudentIndex();
            if (insertQueueIndex != -1) {
                SetFirstNameIntoIndex(insertQueueIndex,tempFirstName);
                SetLastNameIntoIndex(insertQueueIndex,tempLastName);
                for (int i = 0; i < courseNameIndex; ++i) {
//                    int dbCourseIndex = GetCourseIndexFromStudentDB(firstNameIndex,tempCourses[i]);
//                    if (dbCourseIndex != -1) {
//                        SetGradeIntoIndex(firstNameIndex,dbCourseIndex,tempGradesInt[i]);
//                    } else {
//
//                    }
                    int indexToInsertCourse = FetchEmptyCourseIndexForStudent(insertQueueIndex);
                    if (indexToInsertCourse != -1) {
                        SetCourseIntoIndex(insertQueueIndex,indexToInsertCourse,tempCourses[i]);
                        SetGradeIntoIndex(insertQueueIndex,indexToInsertCourse,tempGradesInt[i]);
                    } else {
                        ////TODO: PRINT NO SPACE ERROR ERROR
                        ////ACTUALLY YOU MIGHT JUST NEED TO PASS, NO ERRORS NEED TO BE THROWN
                    }
                }
                lastUpdated = insertQueueIndex;
                return ADDED_STUDENT;
            } else {
                ////TODO: PRINT NO SPACE ERROR
                return INSUFFICIENT_SPACE;
            }
        }
    } else {
        return INVALID_STUDENT_INPUT;
    }
    return UNKNOWN_PARSE_ERROR;
}

boolean DeleteStudent() {
    ////TODO: CHANGE SCANF WITH FGETS AND PARSE NAME AND LASTNAME INDEPENDENTLY
    char firstName[MAX_NAME];
    char lastName[MAX_NAME];
    char DUMMY;
    scanf("%s %s",firstName,lastName);
    scanf("%c",&DUMMY);

    int firstNameIndex = GetFirstNameIndexFromDB(firstName);
    int lastNameIndex = GetLastNameIndexFromDB(lastName);
    if ((firstNameIndex == lastNameIndex) && (firstNameIndex != -1 && lastNameIndex != -1)) {
        DeleteFirstNameInIndex(firstNameIndex);
        DeleteLastNameInIndex(firstNameIndex);
        DeleteAllCoursesInIndex(firstNameIndex);
        ResetAllGradesInIndex(firstNameIndex);
        printf("Student \"%s %s\" deleted.\n",firstName,lastName);
    } else {
        return false;
    }
}

void UpdateSortCache() {
    for (int i = 0; i < MAX_STUDENTS - 1; ++i) {
        if (firstNames[sortCache[i]] == '\0') {
            continue;
        } else {
            for (int j = 0; j < MAX_STUDENTS - 1 - i; ++j) {
                if (firstNames[sortCache[j + 1]][0] != '\0') {
                    int wordCompare = strcmp(firstNames[sortCache[j]], firstNames[sortCache[j + 1]]);
                    if(wordCompare < 0) {
                        continue;
                    } else if (wordCompare > 0) {
                        int tmp = sortCache[j];
                        sortCache[j] = sortCache[j + 1];
                        sortCache[j + 1] = tmp;
                        continue;
                    } else {
                        wordCompare = strcmp(lastNames[sortCache[j]], lastNames[sortCache[j + 1]]);
                        if(wordCompare < 0) {
                            continue;
                        } else if (wordCompare > 0) {
                            int tmp = sortCache[j];
                            sortCache[j] = sortCache[j + 1];
                            sortCache[j + 1] = tmp;
                            continue;
                        } else {
                            continue;
                        }
                    }
                }
            }
        }
    }
//    for (int l = 0; l < 4; ++l) {
//        printf("%s",firstNames[sortCache[l]]);
//    }
}

void ProcessFirstOperation(char inputLine[]) {
    StatusParseStatus parseStatus = ValidateLineInput(inputLine);
    switch (parseStatus) {
        case ADDED_STUDENT:
            UpdateSortCache();
            printf("Student \"%s %s\" added.\n",firstNames[lastUpdated],lastNames[lastUpdated]);
            break;
        case UPDATED_STUDENT:
            printf("Student \"%s %s\" updated.\n",firstNames[lastUpdated],lastNames[lastUpdated]);
            break;
        case INVALID_STUDENT_INPUT:
            printf("Error: invalid name or grade.\n");
            break;
        case INSUFFICIENT_SPACE:
            printf("Error: there is no more space.\n");
            break;
        default:
            printf("UNKNOWN ERROR\n");
            break;
    }
}

void ProcessAggregationAfterOption(int (*aggregationFunction)(int), AggregationType aggregationType) {

    int max = -1;
    int maxIndex = -1;
    switch (aggregationType) {
        case MAXIMAL_STUDENT:
            for (int i = 0; i < MAX_STUDENTS; ++i) {
                if (max < aggregationFunction(i)) {
                    max = aggregationFunction(i);
                    maxIndex = i;
                }
            }
            printf("%s %s, %d\n",firstNames[maxIndex],lastNames[maxIndex],max);
            break;
        case ALL_STUDENTS:
            for (int i = 0; i < MAX_STUDENTS; ++i) {
                if (firstNames[sortCache[i]][0] != '\0') {
                    printf("%s %s, %d\n", firstNames[sortCache[i]], lastNames[sortCache[i]], aggregationFunction(i));
                }
            }
            break;
        default:
            printf("ERROR\n");
    }




}

void ProcessAggregation(AggregationType aggregationType) {
    AggregationType saveType = aggregationType;
    if (CountCurrentAmountOfStudent() == 0) {
        printf("Error: there are no students.\n");
        return;
    }
    PrintAggregationMenu();
    char inputLine[1] = {'\0'};
    gets(inputLine);
    switch (inputLine[0]) {
        case 'a':
            ProcessAggregationAfterOption(AverageForStudent,aggregationType);
            break;
        case 'b':
            ProcessAggregationAfterOption(MaxGradeForStudent,aggregationType);
            break;
        case 'c':
            ProcessAggregationAfterOption(MinGradeForStudent,aggregationType);
            break;
        case 'd':
            ProcessAggregationAfterOption(CourseSumForStudent,aggregationType);
            break;
        case 'e':
            ProcessAggregationAfterOption(CourseCountForStudent,aggregationType);
            break;
        case '0':
            break;
        default:
            printf("UNKNOWN COMMAND");
            break;
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
// Tal Hanan: OOP,100; LA, 100; LAAAAA, 88;
// Tal Ianan: OOP,100; LA, 100; LAAAAA, 88;
// Avi    Sham: QQQQ, 10; LA,100; LAAAAA, 88;


//// Yossi Cohen: OOP,100;LAA,