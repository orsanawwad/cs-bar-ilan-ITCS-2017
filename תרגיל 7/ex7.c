/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 7 C Part
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

#define BUFFER_LIMIT 100
#define NUM_OF_FUNCS_IN_FUNCS_H 8

/** HOW TO ADD SUPPORT FOR ADDITIONAL FUNCTIONS
 *
 * Note: 1 and 4 are for adding functions that supports more than one param, The main points are 2 and 3
 *
 * To add support for additional bitwise functions
 * 1. If the number of args is more than 4, please define a generic pointer to it before GenericFunction pointer line
 * 2. Update NUM_OF_FUNCS_IN_FUNCS_H to the total number of functions
 * 3. Inside SetupFunctionHashMapTable add a new line with SetFuncNameFor function where the first param is the index
 *    of the array (you have to setup different index for each different array), then the name, then the function
 *    pointer, casted to GenericFunction so it can be passed around freely and easily
 * 4. Inside ExecuteFunctionWithName add a new case for whatever new number of arguements pointer you added and
 *    call it like this
 *
 *          return ((FuncWithNParams)(FunctionHashMapTable->function))(param[0],param[1],...,param[n-1]);
 *          Note 1: N is the number of args
 *          Note 2: The three dots written here has nothing to do with variadic list
 *
 * 5. That's it, this code should handle dynamic addition of additional functions for the future
 *
 */

/**
 * Generic Pointers for functions with multiple params, used to cast GenericFunction Pointer so it accepts multiple
 * arguements
 * */
typedef int (*FuncWith1Params)(int x);
typedef int (*FuncWith2Params)(int x, int y);
typedef int (*FuncWith3Params)(int x, int y, int z);
typedef int (*FuncWith4Params)(int x, int y, int z, int w);
typedef int (*GenericFunction)(void);

/**
 * Custom HashMap Implementation for HashMap<String,FunctionReference> in c, just the basic stuff
 * Explanation: This struct contains 2 params, a pointer string (char *) used to store the function name,
 *              and a pointer to the function itself, how this works is we compare a function string name with
 *              multiple structs, if we get a match then the function gets executed with the currect params
 */
typedef struct {
    char *funcName;
    GenericFunction function;
} FunctionHashMap;

// Array Of structs for FunctionHashMap
FunctionHashMap FunctionHashMapTable[NUM_OF_FUNCS_IN_FUNCS_H];

// Setup Function name and pointer for specific index in the table
/******************
 * Function Name: SetFuncNameFor
 * Input: Index, Function name, Generic function pointer
 * Output: No output
 * Function Operation: Sets the name and function pointer of a struct from the FunctionHashMapTable using the index
 *                     value.
 ******************/
void SetFuncNameFor(int i, char *funcName, GenericFunction function) {
    FunctionHashMapTable[i].funcName = (char *)malloc(strlen(funcName) + 1);
    strcpy(FunctionHashMapTable[i].funcName,funcName);
    FunctionHashMapTable[i].function = function;
}


/********************************************************************
 * Function Name: SetupFunctionHashMapTable
 * Input: No Input
 * Output: No Output
 * Function Operation: Setup all of the current available functions,
 *                     if a new functions needs to be added, just add
 *                     a new line in the same pattern.
 ********************************************************************/
void SetupFunctionHashMapTable() {
    SetFuncNameFor(0, "bitAnd", (GenericFunction) bitAnd);
    SetFuncNameFor(1, "bitCount", (GenericFunction) bitCount);
    SetFuncNameFor(2, "bang", (GenericFunction) bang);
    SetFuncNameFor(3, "fitsBits", (GenericFunction) fitsBits);
    SetFuncNameFor(4, "divpwr2", (GenericFunction) divpwr2);
    SetFuncNameFor(5, "negate", (GenericFunction) negate);
    SetFuncNameFor(6, "isPositive", (GenericFunction) isPositive);
    SetFuncNameFor(7, "isLessOrEqual", (GenericFunction) isLessOrEqual);
}

/******************
 * Function Name: ExecuteFunctionWithName
 * Input: Name, Number of arguemnts, Parameters array
 * Output: Result of the dyanmicly called function
 * Function Operation: It checks how many arguements the functions we're calling contains, finds that function
 *                     and calls it
 ******************/
int ExecuteFunctionWithName(char *name, int numberOfArgs, int *pars) {
    for (int i = 0; i < NUM_OF_FUNCS_IN_FUNCS_H; ++i) {
        if (strcmp(FunctionHashMapTable[i].funcName,name) == 0) {
            switch (numberOfArgs) {
                case 1:
                    return ((FuncWith1Params)(FunctionHashMapTable[i].function))(pars[0]);
                case 2:
                    return ((FuncWith2Params)(FunctionHashMapTable[i].function))(pars[0],pars[1]);
                case 3:
                    return ((FuncWith3Params)(FunctionHashMapTable[i].function))(pars[0],pars[1],pars[2]);
                case 4:
                    return ((FuncWith4Params)(FunctionHashMapTable[i].function))(pars[0],pars[1],pars[2],pars[3]);
                default:
                    printf("ERROR - Number of arguments not supported.");
                    break;
            }
        }
    }
    return -1;
}

/******************
 * Function Name: FreeAllHashMapTableNames
 * Input: No Input
 * Output: No Output
 * Function Operation: Frees all the dynamically allocated names in the structs
 ******************/
void FreeAllHashMapTableNames() {
    for (int i = 0; i < NUM_OF_FUNCS_IN_FUNCS_H; ++i) {
        free(FunctionHashMapTable[i].funcName);
    }
}

/******************
 * Function Name: ParseTill
 * Input: Stop mark character, FILE source
 * Output: Returns pointer to a dynamically allocated string
 * Function Operation: Takes the current FILE struct with its current pivot point, calls fgetc
 *                     and loops each character, adds them to a new dynamicly allocated array
 *                     and once it reaches the stop mark character it breaks the loop, adds \0 to the end
 *                     of the string, and return back the pointer.
 ******************/
char *ParseTill(char stopMark, FILE *src) {

    char c;
    int parseCounter = 1;

    char *parseText = (char*) malloc(parseCounter);

    while (stopMark != (c=fgetc(src))) {
        parseCounter++;
        parseText = (char*) realloc(parseText,parseCounter);
        parseText[parseCounter-2] = c;
    }
    parseText[parseCounter-1] = '\0';
    return parseText;
}

/******************
 * Function Name: GetNumberOfArguments
 * Input: FILE source
 * Output: Returns number of arguement parsed from the current file (and current line)
 * Function Operation: Calls ParseTill function which basically says take every character from your current
 *                     pivot character and add them to a new array till it gets to the stop mark, in other words
 *                     it parses it, the stop mark in this case is ':', then it converts the number using atoi
 ******************/
int GetNumberOfArguments(FILE *src) {
    char *number = ParseTill(':',src);
    int convertedNumber = atoi(number);
    free(number);
    return convertedNumber;
}

/******************
 * Function Name: ResetBuffer
 * Input: Buffer array
 * Output: No Output
 * Function Operation: Takes the buffer array and sets each cell to '\0'.
 ******************/
void ResetBuffer(char *buffer) {
    for (int i = 0; i < BUFFER_LIMIT; ++i) {
        buffer[i] = '\0';
    }
}

/******************
 * Function Name: GetFunctionParams
 * Input: FILE source, number of arguments
 * Output: Array of arguments
 * Function Operation: Parses the text from the current pivot point of the file till the end of the line
 *                     (using the '\n' mark), Then it goes through the string again, and splits it to multiple
 *                     numbers into a dynamic int array, then returns that array back.
 ******************/
int *GetFunctionParams(FILE *src, int numberOfArgs) {
    int count = 0;
    char *params = ParseTill('\n',src);
    int *paramsInt = (int *)malloc(numberOfArgs*(sizeof(int)));
    char buffer[BUFFER_LIMIT] = {'\0'};
    for (int i = 0, j = 0; numberOfArgs != 0; i++) {
        if (params[i] == ',' || params[i] == '\0') {
            paramsInt[count] = atoi(buffer);
            count++;
            numberOfArgs--;
            j = 0;
            ResetBuffer(buffer);
            continue;
        }
        buffer[j] = params[i];
        j++;
    }
    free(params);
    return paramsInt;
}

/******************
 * Function Name: GetFunctionName
 * Input: FILE source
 * Output: Returns function name string from the file
 * Function Operation: Parses the file's current line till ':' and returns a string pointer
 ******************/
char *GetFunctionName(FILE *src) {
    char *funcName = ParseTill(':',src);
    return funcName;
}

int main(int argc, char *argv[]) {
    // Source and Target FILE pointers
    FILE *src, *trg;
    // Character pivot for FILEs
    char c;
    // Setup the HashMapTable which will be used to call the functions using strings
    SetupFunctionHashMapTable();
    // If main arguemnts are different than 3 then the input is not right
    if (argc != 3) {
        printf("Bad params, please insert two file names.\n");
        return 1;
    }
    // Read the files using the main arguments where [0] is for input and [1] is for output
    // Open input file in read only mode
    src = fopen(argv[1], "r");
    // Open output file for writing (if it doesn't exist, creates new one)
    trg = fopen(argv[2], "w");
    // If one of the files is NULL then reading the files have been failed
    if(src == NULL || trg == NULL) {
        printf("Failed opening files");
        return 1;
    }
    /**
     * Loop through each character in the file till it gets to EOF, while parsing the file to 3 different
     * params, Function name, number of arguments, and the arguments themselves in an integer array, then
     * call the function using the function name provided by comparing it with the function name in a
     * list of structs where each struct holds its name and the pointer for that function, then calls that
     * function pointer with the correct arguments, then write that value inside the new file.
     */
    while (EOF != (c=fgetc(src))) {
        // If its a new line character, skip
        if (c == '\r' || c == '\n') continue;
        // Go back 1 character so the parsing process goes as it should
        fseek(src,-1,SEEK_CUR);
        // Get the funciton name
        char *funcName = GetFunctionName(src);
        // Get the number of argumnets
        int numberOfArgs = GetNumberOfArguments(src);
        // Get function params
        int *params = GetFunctionParams(src, numberOfArgs);
        // Write the function name into the new file
        fprintf(trg,"%s",funcName);
        // Write "(" after the function name
        fprintf(trg,"(");
        // Write the parameters with , between them
        for (int i = 0; i < numberOfArgs; ++i) {
            int param = params[i];
            fprintf(trg,"%d",params[i]);
            if (i < numberOfArgs-1) {
                fprintf(trg,",");
            }
        }
        // Finish off with ")" and call the correct function using its name and params, and write the value after "="
        fprintf(trg,") = %d\n",ExecuteFunctionWithName(funcName,numberOfArgs,params));
        // Free the params
        free(params);
        // Free the function name
        free(funcName);
        // Because these were dynamically allocated
    }
    // Frees the names inside the HashMapTable because they were dynamically allocated so we can prevent mem leaks
    FreeAllHashMapTableNames();
    // Close the source file
    fclose(src);
    // Close the target file
    fclose(trg);
}
