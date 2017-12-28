/***************************
* Student name: Orsan Awwad
* Student: *
* Course Exercise Group: 01
* Exercise name: Exercise 5
***************************/

#include <stdio.h>
#include "ex5.h"
#include "string.h"

#define MAX_STUDENTS 50
#define MAX_NAME 20
#define MAX_COURSES 5

/**
 ** Note, In this program global variables were used to easily
 ** call and configure the students database, where instead of
 ** having to deal with pointers all I have to do is call the
 ** array name and its index, making the code a lot more readable
 ** and "flexible" for "future" changes, while yes it might be
 ** unsafe to do so, but again globals were used for convenience
 ** sake
 **/

//The first names array database
char firstNames[MAX_STUDENTS][MAX_NAME];
//The last names array database
char lastNames[MAX_STUDENTS][MAX_NAME];
//The courses for each student array
char courses[MAX_STUDENTS][MAX_COURSES][MAX_NAME];
//The grades for each course for each student
int grades[MAX_STUDENTS][MAX_COURSES];
//The sort array which contains indexes of students sorted by name then family name
int sortCache[MAX_STUDENTS];
//This is just to find out who we updated in the end for a print message
int lastUpdated = -1;


/**********************************************************************
 * Function name: PrintMenu
 * Input: No input
 * Output: No returns but it prints menu options
 * Function operation: Prints the main menu options
 **********************************************************************/
void PrintMenu() {
    printf("Please select the operation:\n");
    printf("\t0. Exit.\n");
    printf("\t1. Insert or update student grades.\n");
    printf("\t2. Delete student information.\n");
    printf("\t3. Print the student with maximal computed grade.\n");
    printf("\t4. Print all the students with their computed grades.\n");
    printf("\t5. Print the menu.\n");
}

/**********************************************************************
 * Function name: PrintAggregationMenu
 * Input: No input
 * Output: No returns but it prints menu options
 * Function operation: Prints the aggregation menu options
 **********************************************************************/
void PrintAggregationMenu() {
    printf("Please select the aggregation method:\n");
    printf("\ta. Average grade.\n");
    printf("\tb. Maximal grade.\n");
    printf("\tc. Minimal grade.\n");
    printf("\td. Sum.\n");
    printf("\te. Count.\n");
    printf("\t0. Return the main menu.\n");
}

/**********************************************************************
 * Function name: PrintNextOperationMessage
 * Input: No input
 * Output: No returns but it prints menu option
 * Function operation: Prints the Next Operation message
 **********************************************************************/
void PrintNextOperationMessage() {
    printf("Select the next operation (insert 5 for complete menu).\n");
}

/**********************************************************************
 * Function name: ArrayCopy
 * Input: Source Array to copy from, Source Begin Index for copying,
 *        Target Array to copy to, Target Begin Index for copying,
 *        Length of the string to copy
 * Output: No outputs
 * Function operation: This function mimics the Java System function
 *                     arraycopy where it takes the source and copy
 *                     each each character till a specific limit is
 *                     reached to the target array and uses the indexes
 *                     to point out where to begin from.
 **********************************************************************/
void ArrayCopy(char source[], int sourceBegin, char target[], int targetBegin, int length) {
    for(int i = sourceBegin, j = targetBegin; i < sourceBegin + length; i++, j++) {
        target[j] = '\0';
        target[j] = source[i];
        target[j + 1] = '\0';
    }
}

/**********************************************************************
 * Function name: ConvertStrToInt
 * Input: Input Array of numbers
 * Output: Returns an integer from the converted input
 * Function operation: It first checks if each of the chars in this
 *                     array is a number char, then it converts the
 *                     number to integer and adds to sum multiplied by
 *                     10 each time. (Its like atoi but manually
 *                     written)
 **********************************************************************/
int ConvertStrToInt(char inputToConvert[]) {
    int sum = 0;

    for (int i = 0; inputToConvert[i] != '\0'; ++i) {
        if (inputToConvert[i] >= '0' && inputToConvert[i] <= '9') {
            sum = (sum * 10) + (inputToConvert[i] - '0');
        }
    }

    return sum;
}

/**********************************************************************
 * Function name: CountCurrentAmountOfStudent
 * Input: No input
 * Output: returns the amount of students currently available in memory
 * Function operation: It loops each cell in the global firstNames
 *                     array and checks its first character if null or
 *                     not, \0 or null means this cell is empty and
 *                     hasn't been populated yet, if its not null then
 *                     it adds 1 to the count of students.
 **********************************************************************/
int CountCurrentAmountOfStudent() {
    int count = 0;
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if (firstNames[i][0] != '\0') {
            count = count + 1;
        }
    }
    return count;
}

/**********************************************************************
 * Function name: FetchEmptyStudentIndex
 * Input: No input
 * Output: returns an index position of an empty cell in firstNames
 *         array, if -1 it means no empty cell exists
 * Function operation: Loops through every cell in firstNames and
 *                     checks whether the first character is \0 aka
 *                     null or not, if it is, it returns the current
 *                     i from the loop which indicates to the index of
 *                     array, however if none were found it'll return -1
 *                     indicating that there is no empty position to
 *                     save new students
 **********************************************************************/
int FetchEmptyStudentIndex() {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if (firstNames[i][0] == '\0') {
            return i;
        }
    }
    return -1;
}

/**********************************************************************
 * Function name: FetchEmptyCourseIndexForStudent
 * Input: Student index
 * Output: Returns and empty cell's index number in courses array
 *         to save a course for a specific student, if -1 is returned it
 *         means no empty cells could be found.
 * Function operation: Like above, it loops each cell in courses array
 *                     for a specific student and checks whether the
 *                     first character is \0, if it is then this cell
 *                     is empty and we can save the name in it, else
 *                     return -1 if none where to be found.
 **********************************************************************/
int FetchEmptyCourseIndexForStudent(int studentIndex) {
    for (int i = 0; i < MAX_COURSES; ++i) {
        if (courses[studentIndex][i][0] == '\0') {
            return i;
        }
    }
    return -1;
}

/**********************************************************************
 * Function name: GetFirstNameIndexFromDB
 * Input: First name array
 * Output: Position of the first name if found, else returns -1
 * Function operation: It loops through each cell in firstNames and
 *                     uses strcmp to check whether the name exists or
 *                     not, it returns -1 if the name didn't exist
 **********************************************************************/
int GetFirstNameIndexFromDB(char firstName[]) {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if(strcmp(firstNames[i],firstName) == 0) {
            return i;
        }
    }
    return -1;
}

/**********************************************************************
 * Function name: SetFirstNameIntoIndex
 * Input: Index to save the first name to and the firstName array which
 *        contains the first name.
 * Output: No output
 * Function operation: Calls ArrayCopy and passes the global firstName
 *                     as index
 **********************************************************************/
void SetFirstNameIntoIndex(int index, char firstName[]) {
    ArrayCopy(firstName,0,firstNames[index],0,(int)strlen(firstName));
}

/**********************************************************************
 * Function name: DeleteFirstNameInIndex
 * Input: Index of student to delete it's first name
 * Output: No output
 * Function operation: Loops through each character in the firstName of
 *                     the given index and sets it to \0 (Null)
 **********************************************************************/
void DeleteFirstNameInIndex(int deletionIndex) {
    for (int i = 0; i < MAX_NAME; ++i) {
        firstNames[deletionIndex][i] = '\0';
    }
}

/**********************************************************************
 * Function name: GetLastNameIndexFromDB
 * Input: Last name array
 * Output: Returns the index of the lastName from the global lastNames
 *         array if found.
 * Function operation: Loops through lastNames and uses strcmp to check
 *                     if the last name exists or not then returns the
 *                     index of the lastName if exists, else returns -1
 **********************************************************************/
int GetLastNameIndexFromDB(char lastName[]) {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if(strcmp(lastNames[i],lastName) == 0) {
            return i;
        }
    }
    return -1;
}

/**********************************************************************
 * Function name: SetLastNameIntoIndex
 * Input: Index to save the last name to and the lastName array which
 *        contains the last name.
 * Output: No output
 * Function operation:
 **********************************************************************/
void SetLastNameIntoIndex(int index, char lastName[]) {
    ArrayCopy(lastName,0,lastNames[index],0,(int)strlen(lastName));
}

/**********************************************************************
 * Function name: DeleteLastNameInIndex
 * Input: Deletion index
 * Output: No output
 * Function operation: Sets each character of the lastNames cell of
 *                     a specific index to \0
 **********************************************************************/
void DeleteLastNameInIndex(int deletionIndex) {
    for (int i = 0; i < MAX_NAME; ++i) {
        lastNames[deletionIndex][i] = '\0';
    }
}

/**********************************************************************
 * Function name: GetCourseIndexFromStudentDB
 * Input: studentIndex, courseName array
 * Output: Index of the course name of a specific student
 * Function operation: Loops through each student's courses array
 *                     and runs strcmp to check if the course name
 *                     exists or not, if it does it returns i
 **********************************************************************/
int GetCourseIndexFromStudentDB(int studentIndex,char courseName[]) {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if(strcmp(courses[studentIndex][i],courseName) == 0) {
            return i;
        }
    }
    return -1;
}

/**********************************************************************
 * Function name: SetCourseIntoIndex
 * Input: Student index to change, course index to change, update
 *        course name
 * Output: No output
 * Function operation: Calls ArrayCopy and copies the updateCourse into
 *                     the target position in courses array
 **********************************************************************/
void SetCourseIntoIndex(int studentIndex,int courseIndex, char updatedCourse[]) {
    ArrayCopy(updatedCourse,0,courses[studentIndex][courseIndex],0,(int)strlen(updatedCourse));
}

/**********************************************************************
 * Function name: DeleteAllCoursesInIndex
 * Input: deletionIndex
 * Output: No output
 * Function operation: Resets the cell of all courses of a student to \0
 **********************************************************************/
void DeleteAllCoursesInIndex(int deletionIndex) {
    for (int i = 0; i < MAX_COURSES; ++i) {
        for (int j = 0; j < MAX_NAME; ++j) {
            courses[deletionIndex][i][j] = '\0';
        }
    }
}

/**********************************************************************
 * Function name: SetGradeIntoIndex
 * Input: studentIndex to update, courseIndex to set the grade for
 *        updateGrade to update the value
 * Output: No output
 * Function operation: Just sets the grade into the grades array of the
 *                     students index.
 **********************************************************************/
void SetGradeIntoIndex(int studentIndex,int courseIndex, int updatedGrade) {
    grades[studentIndex][courseIndex] = updatedGrade;
}

/**********************************************************************
 * Function name: ResetAllGradesInIndex
 * Input: Grade index to reset
 * Output: No output
 * Function operation: Loops through each grade of a specific student
 *                     index and resest it to -1, indicating this grade
 *                     does not exist
 **********************************************************************/
void ResetAllGradesInIndex(int deletionIndex) {
    for (int i = 0; i < MAX_COURSES; ++i) {
        grades[deletionIndex][i] = -1;
    }
}

/**********************************************************************
 * Function name: ResetSortCache
 * Input: No input
 * Output: No output
 * Function operation: Fills each cell in sortCache with its own index
 **********************************************************************/
void ResetSortCache() {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        sortCache[i] = i;
    }
}

/**********************************************************************
 * Function name: ResetEverything
 * Input: No input
 * Output: No output
 * Function operation: Loops through each student index and resets
 *                     all the details from using the functions called
 *                     below.
 **********************************************************************/
void ResetEverything() {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        DeleteFirstNameInIndex(i);
        DeleteLastNameInIndex(i);
        DeleteAllCoursesInIndex(i);
        ResetAllGradesInIndex(i);
        ResetSortCache();
    }
}

/**********************************************************************
 * Function name: CourseCountForStudent
 * Input: Student index
 * Output: Number of courses count
 * Function operation: Loops through each course of a student in
 *                     courses array and checks if its \0 or not, if
 *                     its not, it adds 1 to the count, after the loop
 *                     is over it returns the count
 **********************************************************************/
int CourseCountForStudent(int studentIndex) {
    int count = 0;
    for (int i = 0; i < MAX_COURSES; ++i) {
        if (courses[studentIndex][i][0] != '\0') {
            count++;
        }
    }
    return count;
}

/**********************************************************************
 * Function name: CourseSumForStudent
 * Input: studentIndex
 * Output: Sum of all grades of a student
 * Function operation: Counts each grade of the student from the grades
 *                     array and returns it, it checks each time if its
 *                     -1 to indicate that it didn't exist
 **********************************************************************/
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

/**********************************************************************
 * Function name: AverageForStudent
 * Input: studentIndex
 * Output: Average grade for a specific student
 * Function operation: Gets number of students, gets the sum of all
 *                     courses, checks that courses do exist using count
 *                     and returns sum divided by count. (The average)
 **********************************************************************/
int AverageForStudent(int studentIndex) {
    int count = CourseCountForStudent(studentIndex);
    int sum = CourseSumForStudent(studentIndex);
    if (count != 0) {
        return sum / count;
    } else {
        return -1;
    }
}

/**********************************************************************
 * Function name: MaxGradeForStudent
 * Input: studentIndex
 * Output: Returns the maximum grade of a student
 * Function operation: Loop through each grade of a specific student
 *                     in grades array, checks with the max number if
 *                     bigger than or less than, max variable
 *                     at first is set to the first index of the
 *                     grades of the specific student, if the number
 *                     in the loop is bigger than max, set it,
 *                     and returns the max when the loop ends.
 **********************************************************************/
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

/**********************************************************************
 * Function name: MinGradeForStudent
 * Input: studentIndex
 * Output: Returns the minimum grade of a student
 * Function operation: Same as above only checks with the minimum
 **********************************************************************/
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

/***********************************************************************************************
 * Function name: ValidateLineInput
 * Input: inputLine
 * Output: ParseStatus
 * Function operation: This function takes input line and validates it by going through each
 *                     character and checks with specific rules on how the validation is
 *                     supposed to be, the validation is split into 4 parts, first name, last
 *                     name, course name, and grade, each part has its own flags and indexes
 *                     count and temp arrays for storing names and everything else in order to
 *                     populate them later on if the checks passed right
 ***********************************************************************************************/
ParseStatus ValidateLineInput(char inputLine[]) {

    //First Name Part variables
    boolean BeganFirstNameCheck = false;
    boolean PassedFirstNameCheck = false;
    int firstNameBeginIndex = -1;
    int firstNameEndIndex = -1;
    char firstName[MAX_NAME+1];

    //Last Name Part variables
    boolean BeganLastNameCheck = false;
    boolean PassedLastNameCheck = false;
    int lastNameBeginIndex = -1;
    int lastNameEndIndex = -1;
    char lastName[MAX_NAME+1];

    //Any Course Name Part Variables
    boolean BeganCourseNameCheck = false;
    boolean PassedCourseNameCheck = false;
    int courseNameBeginIndex = -1;
    int courseNameEndIndex = -1;
    int courseNames[66][2];
    int courseNameIndex = 0;

    //Any Course Grade Part Variables
    boolean BeganCourseGradeCheck = false;
    boolean PassedCourseGradeCheck = false;
    int courseGradeBeginIndex = -1;
    int courseGradeEndIndex = -1;
    int courseGrades[66][2];
    int courseGradeIndex = 0;

    //Counters to keep the limit to 5 courses
    int inputCourseNameCount = 0;
    int inputCourseGradeCount = 0;

    //Loop through each character
    for (int i = 0; i < strlen(inputLine); ++i) {
        //These flags are for specific case character, they are self explanatory
        boolean IsSmallLetter = (boolean) (inputLine[i] >= 'a' && inputLine[i] <= 'z');
        boolean IsCapitalLetter = (boolean) (inputLine[i] >= 'A' && inputLine[i] <= 'Z');
        boolean IsLetter = (boolean) (IsCapitalLetter || IsSmallLetter);
        boolean IsDigitCharacter = (boolean) (inputLine[i] >= '0' && inputLine[i] <= '9');
        boolean IsNumberZeroCharacter = (boolean) (inputLine[i] == '0');
        boolean IsSpaceCharacter = (boolean) (inputLine[i] == ' ');
        boolean IsColonCharacter = (boolean) (inputLine[i] == ':');
        boolean IsCommaCharacter = (boolean) (inputLine[i] == ',');
        boolean IsSemiColonCharacter = (boolean) (inputLine[i] == ';');
        boolean IsNullOrNewLineCharacter = (boolean) (inputLine[i] == '\n' || inputLine[i] == '\0');

        //If we haven't started checking the first name
        if (!PassedFirstNameCheck) {
            //Then check if its space character and that we didn't start checking the first name, if so, continue
            if (IsSpaceCharacter && !BeganFirstNameCheck) {
                continue;
            } else if (IsLetter) {
                //When we get to the first letter we mark the BeganFirstNameCheck to true to indicate that we began
                //checking
                BeganFirstNameCheck = true;
                //And we set the index for where the first name begins in the input line
                if (firstNameBeginIndex == -1) {
                    firstNameBeginIndex = i;
                }
                continue;
            } else if (IsSpaceCharacter && BeganFirstNameCheck) {
                //Once we hit the space, we mark PassedFirstNameCheck to indicate that we successfully validated
                //first name, then we set the end index of the last name
                PassedFirstNameCheck = true;
                if (firstNameEndIndex == -1) {
                    firstNameEndIndex = i;
                }
                continue;
            } else {
                //If the validation fails (means that an illegal character was found or didn't meet the rules)
                //return INVALID_STUDENT_INPUT to indicate that something is wrong with the input
                return INVALID_STUDENT_INPUT;
            }
        } else if (!PassedLastNameCheck) {
            //The rest of the code is basicaly the same thing only for different parts of the validation
            //with different validation ending flags
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
                //Here in courses we save the index into a 2d array of index because there can be more than one
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
            //But after we're done checking the grade, and there was a space after the semi colon, we reset
            //the flags so we can start over course validation until we hit the new line character or null character
            //indicating that the input line is over
            BeganCourseNameCheck = false;
            PassedCourseNameCheck = false;
            BeganCourseGradeCheck = false;
            PassedCourseGradeCheck = false;
            //This is just to go back one character in the loop
            i--;
        }
    }

    //If all checks passes
    if (PassedFirstNameCheck && PassedLastNameCheck && PassedCourseNameCheck && PassedCourseGradeCheck) {

        char tempFirstName[MAX_NAME];
        char tempLastName[MAX_NAME];
        char tempCourses[courseNameIndex][MAX_NAME];
        char tempGradesChars[courseNameIndex][4];
        int tempGradesInt[courseNameIndex];
        ArrayCopy(inputLine,firstNameBeginIndex,tempFirstName,0,firstNameEndIndex-firstNameBeginIndex);
        ArrayCopy(inputLine,lastNameBeginIndex,tempLastName,0,lastNameEndIndex-lastNameBeginIndex);

        //Parse the line and extract the info into the temporarily defined variables
        for (int i = 0; i < courseNameIndex; ++i) {
            ArrayCopy(inputLine,courseNames[i][0],tempCourses[i],0,courseNames[i][1]-courseNames[i][0]);
            char tempGrade[4] = {'\0'};
            ArrayCopy(inputLine,courseGrades[i][0],tempGradesChars[i],0,courseGrades[i][1]-courseGrades[i][0]);
            int actualGradeTemp = ConvertStrToInt(tempGradesChars[i]);
            tempGradesInt[i] = actualGradeTemp;
        }

        //Check if the name exists
        int firstNameIndex = GetFirstNameIndexFromDB(tempFirstName);
        int lastNameIndex = GetLastNameIndexFromDB(tempLastName);
        //If it does, check the if the courses exists too, if they do, update the grade,
        //if they don't check if there's space for a new course, if so add it, else, check if we ever updated
        //any course, if we didn't return error.
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
                        if (!UpdatedAnyCourse) {
                            return INVALID_STUDENT_INPUT;
                        }
                    }
                }
            }
            lastUpdated = firstNameIndex;
            return UPDATED_STUDENT;
        } else {
            //If the user doesn't exist check if there's space, if so, add it and add the courses, else
            //return that there are no spaces, then return a status that we added a new student, so we can
            //update the sort array
            int insertQueueIndex = FetchEmptyStudentIndex();
            if (insertQueueIndex != -1) {
                SetFirstNameIntoIndex(insertQueueIndex,tempFirstName);
                SetLastNameIntoIndex(insertQueueIndex,tempLastName);
                for (int i = 0; i < courseNameIndex; ++i) {
                    int indexToInsertCourse = FetchEmptyCourseIndexForStudent(insertQueueIndex);
                    if (indexToInsertCourse != -1) {
                        SetCourseIntoIndex(insertQueueIndex,indexToInsertCourse,tempCourses[i]);
                        SetGradeIntoIndex(insertQueueIndex,indexToInsertCourse,tempGradesInt[i]);
                    }
                }
                lastUpdated = insertQueueIndex;
                return ADDED_STUDENT;
            } else {
                return INSUFFICIENT_SPACE;
            }
        }
    } else {
        return INVALID_STUDENT_INPUT;
    }
    return UNKNOWN_PARSE_ERROR;
}

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
boolean DeleteStudent() {
    boolean BeganFirstNameCheck = false;
    boolean PassedFirstNameCheck = false;
    int firstNameBeginIndex = -1;
    int firstNameEndIndex = -1;
    int firstNameIndex = 0;
    char firstName[MAX_NAME+1];

    boolean BeganLastNameCheck = false;
    boolean PassedLastNameCheck = false;
    int lastNameBeginIndex = -1;
    int lastNameEndIndex = -1;
    int lastNameIndex = 0;
    char lastName[MAX_NAME+1];
    char inputLine[200];
    fgets(inputLine,200,stdin);

    for (int i = 0; i < strlen(inputLine); ++i) {

        //The following 5 lines are simple flags indicating if the current char in the loop is one of the following

        //If its [a-z]
        boolean IsSmallLetter = (boolean) (inputLine[i] >= 'a' && inputLine[i] <= 'z');
        //If its [A-Z]
        boolean IsCapitalLetter = (boolean) (inputLine[i] >= 'A' && inputLine[i] <= 'Z');
        //If its [a-z][A-Z]
        boolean IsLetter = (boolean) (IsCapitalLetter || IsSmallLetter);
        //If its a space character
        boolean IsSpaceCharacter = (boolean) (inputLine[i] == ' ');
        //If its a new line or null
        boolean IsNullOrNewLineCharacter = (boolean) (inputLine[i] == '\n' || inputLine[i] == '\0');

        //Checks if we passed the firstName check
        if (!PassedFirstNameCheck) {
            //Check if the current character is a space and we didn't begin checking the first name
            //BeganFirstNameCheck means we started validating the first name
            if (IsSpaceCharacter && !BeganFirstNameCheck) {
                continue;
            } else if (IsLetter) {
                //If its a letter, set BeganFirstNameCheck to true, then copy the current character into firstName
                BeganFirstNameCheck = true;
                firstName[firstNameIndex] = inputLine[i];
                firstName[firstNameIndex + 1] = '\0';
                //This index is used to insert the characters into first name.
                firstNameIndex++;
                if (firstNameBeginIndex == -1) {
                    firstNameBeginIndex = i;
                }
                continue;
            } else if (IsSpaceCharacter && BeganFirstNameCheck) {
                //If its space and we were already checking the first name set PassedFirstNameCheck to true
                //to indicate that we successfully validated first name and copied the value
                PassedFirstNameCheck = true;
                if (firstNameEndIndex == -1) {
                    firstNameEndIndex = i;
                }
                continue;
            } else {
                //If the validation fails print error and return false
                printf("Error: invalid name.\n");
                return false;
            }
        } else if (!PassedLastNameCheck) {
            //Same checks as above but this time it checks whenever we hit \0 or \n to indicate that we successfully
            //checked last name and copied its value
            if (IsSpaceCharacter && !BeganLastNameCheck) {
                continue;
            } else if (IsLetter || IsSpaceCharacter) {
                BeganLastNameCheck = true;
                lastName[lastNameIndex] = inputLine[i];
                lastName[lastNameIndex + 1] = '\0';
                lastNameIndex++;
                if (lastNameBeginIndex == -1) {
                    lastNameBeginIndex = i;
                }
                continue;
            } else if (IsNullOrNewLineCharacter) {
                break;
            } else {
                //If the validation fails print error and return false
                printf("Error: invalid name.\n");
                return false;
            }
        }
    }

    //Get the indexes of the firstName and lastName from the global array (DB)
    int firstNameIndexDB = GetFirstNameIndexFromDB(firstName);
    int lastNameIndexDB = GetLastNameIndexFromDB(lastName);
    //If the indexes are the same and they're not -1 it means that it exists then proceed deleting the info
    if ((firstNameIndexDB == lastNameIndexDB) && (firstNameIndexDB != -1 && lastNameIndexDB != -1)) {
        DeleteFirstNameInIndex(firstNameIndexDB);
        DeleteLastNameInIndex(firstNameIndexDB);
        DeleteAllCoursesInIndex(firstNameIndexDB);
        ResetAllGradesInIndex(firstNameIndexDB);
        printf("Student \"%s %s\" deleted.\n",firstName,lastName);
    } else {
        printf("Error: invalid name.\n");
    }
    return false;
}

/**********************************************************************
 * Function name: UpdateSortCache
 * Input: No input
 * Output: No output
 * Function operation: Uses bubble sort algorithm and each time it
 *                     compares firstName using strcmp then checks the
 *                     value, if its bigger than zero that means
 *                     the second name we're comparing is bigger,
 *                     so we swap it and continue, if its zero,
 *                     it means that the first names are equal, then
 *                     proceed into checking last name, but most
 *                     importantly it checks if the value is not \0
 *                     because some of the cells can be empty.
 **********************************************************************/
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
}

/**********************************************************************
 * Function name: ProcessFirstOperation
 * Input: The input line from main
 * Output: No output
 * Function operation: Runs ValidateLineInput and checks the status
 *                     it returned, then print the currect message,
 *                     if a student was added it calls UpdateSortCache
 *                     to update the sort cache array
 **********************************************************************/
void ProcessFirstOperation(char inputLine[]) {
    ParseStatus parseStatus = ValidateLineInput(inputLine);
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

/**********************************************************************
 * Function name: ProcessAggregation
 * Input: aggregation type
 * Output: No output
 * Function operation: Asks for which aggregation operation to invoke
 *                     then using the switch case it calls
 *                     ProcessAggregationAfterOption with the correct
 *                     function pointer for that aggregation operation
 *                     with aggregation type passed in in order to
 *                     tell the program if its maximal or not
 **********************************************************************/
void ProcessAggregation(AggregationType aggregationType) {
    /*
     * Seems like a unknown bug that I can't figure out the source, if this dummy didn't exist, the aggregType gets
     * reset to default
     */
    AggregationType dummyEnumType = aggregationType;
    if (CountCurrentAmountOfStudent() == 0) {
        printf("Error: there are no students.\n");
        return;
    }
    PrintAggregationMenu();
    char inputLine[3] = {'\0'};
    fgets(inputLine,3,stdin);
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
