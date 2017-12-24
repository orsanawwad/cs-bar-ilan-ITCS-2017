#include <stdio.h>
#include <string.h>
#include "ex5.h"

//#define MAX_STUDENTS 50
//#define MAX_NAME 20
//#define MAX_COURSES 20
//
//char firstNames[MAX_STUDENTS][MAX_NAME] = {
//        "Moshi","Sushi","Toti","Avi","Eli","Avinatan"
//};
//char lastNames[MAX_STUDENTS][MAX_NAME] = {
//        "Cohen","Shetrit","Flava","Fredes","Sabana","Hasedem"
//};
//
//char courses[MAX_STUDENTS][MAX_COURSES][MAX_NAME] = {
//    {"OOP","Linear Algebra","Intro To C"},
//    {"JAVA","Android","Criminology","Singing"},
//    {"Pilot","Car","Psechometry"},
//    {"Driving","New Course","Intro To C"},
//    {"OOP","Linear Algebra","CPP"},
//    {"Poetry","Slideshows","Intro To C"}
//};
//int grades[MAX_STUDENTS][MAX_COURSES] = {
//        {100,90,80},
//        {70,10,20,70},
//        {77,13,29},
//        {100,20,30},
//        {10,70,45},
//        {54,68,34}
//};

/*
int main1() {

    // Name length + space + name length to define the max length a name can hold
//    char firstNames[MAX_STUDENTS][MAX_NAME + 1];
//    char lastNames[MAX_STUDENTS][MAX_NAME + 1];
//    char courses[MAX_STUDENTS][MAX_COURSES][MAX_NAME + 1];
//    int grades[MAX_STUDENTS][MAX_COURSES];

    char example[] = "Yossi Cohen: Linear Algebra,85; OOP,90; Intro C,100;";
    int nameEnd = 0;
    int nextInsertPosition = 0;
    int ShouldChangeInsertNumber = 1;
    int countCourses = 0;

    for (int i = 0; i < strlen(example); ++i) {
        //Make this shorter
        if ((example[i] >= 'a' && example[i] <= 'z') ||
                (example[i] >= 'A' && example[i] <= 'Z')) {
            if (ShouldChangeInsertNumber) {
                nextInsertPosition = i;
                ShouldChangeInsertNumber = 0;
            }
        }
        if (example[i] == ':') {
            for (int j = nextInsertPosition, insertCount = 0; example[j] != ':'; ++j, insertCount++) {
                firstNames[0][insertCount] = example[j];
                firstNames[0][insertCount + 1] = '\0';
            }
            ShouldChangeInsertNumber = 1;
        }
        if (example[i] == ';') {
            for (int j = nextInsertPosition, insertCount = 0; example[j] != ';'; ++j,insertCount++) {
                int AddToGrades = 0;
                if (example[j] == ',') {
                    AddToGrades = 1;
                    j++;
                }
                if (!AddToGrades) {
                    courses[0][countCourses][insertCount] = example[j];
                    courses[0][countCourses][insertCount+1] = '\0';
                }
            }
            ShouldChangeInsertNumber = 1;
            countCourses++;
        }
    }

    printf("%s\n",firstNames[0]);
    printf("%s\n",courses[0][0]);
    printf("%s\n",courses[0][1]);
    printf("%s\n",courses[0][2]);

    return 0;
}

int mainoo() {

    char firstNames[MAX_STUDENTS][MAX_NAME + 1];
    char lastNames[MAX_STUDENTS][MAX_NAME + 1];
    char courses[MAX_STUDENTS][MAX_COURSES][MAX_NAME + 1];
    int grades[MAX_STUDENTS][MAX_COURSES];

    //Legal
    char example0[] = "     Yossi        Cohen: Linear Algebra,85; OOP,90; Intro C,100;";
    //Illegal Because there is a space between "," and "Algebra"
    char example1[] = "     Yossi        Cohen:     Linear     Algebra   ,   85; OOP  ,  90;   Intro   C , 100;     ";
    //Illegal Because there is a space between ":" and "Cohen"
    char example2[] = "     Yossi        Cohen   :  Linear  Algebra, 85 ;  OOP , 90 ;  Intro C , 100 ;  ";
    //Legal
    char example3[] = "     Yossi   Cohen: Linear Algebra,85; OOP,90; Intro C,100; Commentary,100; IT,100; CC,80; ASDASD,77;";
    //Illegal because there is additional data after the last semi colon ";" with incorrect format
    char example4[] = "     Yossi   Cohen: Linear Algebra,85; OOP,90; Intro C,100; Commentary,100; IT,100; CC,80; ASDASD,77;  qweqwe";

    //Legal
    char example5[] = "     Yossi        Cohen: Linear Algebra,85; OOP,90; Intro C  ,    100;    ";
    //Legal
    char example6[] = "     Yossi    4    Cohen  4: Linear Algebra,85; OOP,90; Intro C,100;";
    //Legal
    char example7[] = "     Yossi    234    Cohen  : Linear Algebra,85; OOP,90; Intro C,100;";
    //Illegal
    char example8[] = "  123123   Yossi   123123     Cohen: Linear Algebra,85; OOP,90; Intro C,100;";

    printf("%d\n",(int)ValidateLineInput(example0));
    printf("%d\n",(int)ValidateLineInput(example1));
    printf("%d\n",(int)ValidateLineInput(example2));
    printf("%d\n",(int)ValidateLineInput(example3));
    printf("%d\n\n\n\n\n\n",(int)ValidateLineInput(example4));
    printf("%d\n",(int)ValidateLineInput(example5));
    printf("%d\n",(int)ValidateLineInput(example6));
    printf("%d\n",(int)ValidateLineInput(example7));
    printf("%d\n",(int)ValidateLineInput(example8));


//    PrintMenu();
//    while (1) {
//        int inputNumber;
//        scanf("%d\n",&inputNumber);
//        char inputLine[201];
//        switch (inputNumber) {
//            case 1:
//                fgets(inputLine,201,stdin);
//                ProcessFirstOperation(inputLine);
//                break;
//            case 2:
//                break;
//            case 3:
//                break;
//            case 4:
//                break;
//            case 5:
//                break;
//            default:
//                return 0;
//        }
//    }


}

char firstNames[MAX_STUDENTS][MAX_NAME + 1];
char lastNames[MAX_STUDENTS][MAX_NAME + 1];
char courses[MAX_STUDENTS][MAX_COURSES][MAX_NAME + 1];
int grades[MAX_STUDENTS][MAX_COURSES];
*/
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


int mainasda() {
    char str1[15];
    char str2[15];
    int ret;


    strcpy(str1, "A");
    strcpy(str2, "B");

    ret = strcmp(str1, str2);

    if(ret < 0) {
        printf("str1 is less than str2");
    } else if(ret > 0) {
        printf("str2 is less than str1");
    } else {
        printf("str1 is equal to str2");
    }
    return 0;
}