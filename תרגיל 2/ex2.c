/******************************************
* Student name: Orsan Awwad
* Student: *
* Course Exercise Group: 01
* Exercise name: Exercise 2
******************************************/


#include <stdio.h>

// Used for setting up how many bits the char can have for the first mission
#define MISSION_ONE_BIT_INPUT_LENGTH 6

//
// Function declarations
//

// Power function
int PowerOf(int number, int powerToNumber);

// Mission one function
void MissionOne();

// Mission two function
void MissionTwo();

// Mission three function
void MissionThree();

// Mission four function
void MissionFour();

// Mission five function
void MissionFive();

// Main function
int main() {

    // Straightforward, take a number of the mission, go over the cases and invoke the correct mission
    int action = 0;
    printf("Please enter the mission number:\n");
    scanf("%d",&action);
    switch (action) {
        case 1:
            MissionOne();
            break;
        case 2:
            MissionTwo();
            break;
        case 3:
            MissionThree();
            break;
        case 4:
            MissionFour();
            break;
        case 5:
            MissionFive();
            break;
        default:
            printf("Error");
            return 0;
            break;
    }

}

/**************************************************************************
 * Function name: PowerOf
 * Input: Takes two numbers
 * Output: number^powerToNumber
 * The function operation: First it chesk if powerToNumber is zero, if it
 * is then return zero, else set number as sum variable initial value,
 * then loop (powerToNumber - 1) times and multiple the sum with number
 * then set it back as sum, then return sum
 *************************************************************************/
int PowerOf(int number, int powerToNumber) {
    // If powerToNumber is zero, return 1, because anyThing^0 == 1
    if (powerToNumber == 0) {
        return 1;
    }
    // Set initial sum value as input number, then calculate the power through the for loop, then return it
    int sum = number;
    int i;
    for (i = 1; i < powerToNumber; ++i) {
        sum *= number;
    }
    return sum;
}

/**************************************************************************
 * Function name: MissionOne
 * Input: No input
 * Output: No output
 * The function operation: Asks for 6 digits of binary then calculate
 * the signed value of the number
 *************************************************************************/
void MissionOne() {

    const int inputBitsSize = MISSION_ONE_BIT_INPUT_LENGTH;

    char sixBitBinary[inputBitsSize];
    printf("Enter six digits binary number:\n");
    scanf("%s",sixBitBinary);
    int i;
    int j;
    int sum = 0;
    for(i = 0,j = inputBitsSize - 1; i < inputBitsSize; i++,j--) {
        if (sixBitBinary[0] - '0' && i == 0) {
            sum += (-1)*(sixBitBinary[i] - '0') * PowerOf(2, j);
        } else {
            sum += (sixBitBinary[i] - '0') * PowerOf(2, j);
        }
    }
    printf("%d",sum);
}

/**************************************************************************
 * Function name: MissionThree
 * Input: No Input
 * Output: No Output
 * The function operation: Asks for input number and prints it, then takes
 * the number and checks if its between 65-90 or 97-122, if its between
 * 65-90 then that means that its a capital character, then it adds 32 to
 * convert the character to its small form, because 'A' is 65 and 'a' is
 * 97, so 65 + 32 = 97, which is 'A', then print each one of the characters
 * on its own line, if it was between 97-122, then do the exact same but
 * instead of adding 32, we take away 32, then print each one on its own
 * line.
 *************************************************************************/
void MissionTwo() {
    // Input variable for the mission
    int inputNumberToCharacter = 0;
    printf("Enter ASCII code of some character:\n");
    // Print the number immediatly, because there is no need to check for range for it
    scanf("%d", &inputNumberToCharacter);
    printf("The number is: %d\n", inputNumberToCharacter);
    // Character variables to set the correct small and capital character of the letter
    char smallLetter;
    char capitalLetter;
    if (inputNumberToCharacter >= 97 && inputNumberToCharacter <= 122) {
        // If its between 97 and 122, then its small letter, take away 32 and save it in capitalLetter, then print them
        smallLetter = (char) inputNumberToCharacter;
        capitalLetter = (char) (inputNumberToCharacter - 32);
        printf("The letter is: %c\n", smallLetter);
        printf("The capital letter is: %c\n", capitalLetter);
    } else if (inputNumberToCharacter >= 65 && inputNumberToCharacter <= 90) {
        // If its between 97 and 122, then its small letter, add 32 and save it in smallLetter, then print them
        capitalLetter = (char) inputNumberToCharacter;
        smallLetter = (char) (inputNumberToCharacter + 32);
        printf("The letter is: %c\n", smallLetter);
        printf("The capital letter is: %c\n", capitalLetter);
    }
}

/**************************************************************************
 * Function name: MissionThree
 * Input: No input
 * Output: No output
 * The function operation: Asks for input of a real number, print integer
 * part and fractional part of it, then calculate sum of odd digits.
 *************************************************************************/
void MissionThree() {
    // Setup two variables for integer and fractional part
    int integerPart = 0;
    int fractionalPart = 0;
    // Take aaa.bbb as an input where aaa would go to integerPart and bbb would go to fractional part
    printf("Enter a real number:\n");
    scanf("%d.%d",&integerPart,&fractionalPart);
    // Print them, no need to do other operations for it
    printf("The integer part: %d\n", integerPart);
    printf("The fractional part: %d\n", fractionalPart);

    // Setup sum variable with zero, and i for the loop
    /*
     * This block of code can work not only with aaa.bbb format, but with any float formatted number (), it first counts
     * the number of digits of part of the number, starting with integerPart then fractionalPart, then check if the
     * count is even or odd, if its even then delete the last digit by replacing the same number using (a /= 10),
     * then inside the while loop it calculates the sum of odd numbers by taking the first far right digit using mod 10
     * then remove the far 2 digits using (a /= 100), because dividing int with int doesn't return float number,
     * and lastly print it.
     */
    int oddSum = 0;
    int i;
    for(i = 0; i < 2; i++) {
        // First use integerPart then fractionalPart
        int numberToCalculate = 0;
        if (i) {
            numberToCalculate = integerPart;
        } else {
            numberToCalculate = fractionalPart;
        }
        int numberToCountDigits = numberToCalculate;
        // Digits counter
        int digitCounter = 0;
        while(numberToCountDigits != 0) {
            numberToCountDigits /= 10;
            digitCounter++;
        }
        // If its even delete the last number
        if (digitCounter % 2 == 0) {
            numberToCalculate /= 10;
        }
        // Calculate odd number using modulo 10 and remove last two digits using /= 100 operator
        while (numberToCalculate > 0) {
            oddSum += (numberToCalculate % 10);
            numberToCalculate /= 100;
        }
    }
    // Print it...
    printf("The sum of odd digits: %d", oddSum);

}

/**************************************************************************
 * Function name: MissionFour
 * Input: No input
 * Output: No output
 * The function operation: Asks for 2 numbers, then an operator, and
 * performs a specific operation according to that input character operator
 *************************************************************************/
void MissionFour() {
    // Asks for input of a and b, then asks for operator input on its own
    printf("Welcome to the crazy calculator:\n");
    printf("Enter two numbers:\n");
    float a,b;
    char operator;
    scanf("%f %f",&a,&b);
    printf("Enter an action from: {! @ # \\ %%}:\n");
    scanf("\n%c",&operator);
    float sum = 0;
    // Self explanator, checks which of the specified cases the input character is and perform its own operation
    switch (operator) {
        case '!':
            sum = a + b;
            break;
        case '@':
            sum = a - b;
            break;
        case '#':
            sum = a * b;
            break;
        case '\\':
            sum = a / b;
            break;
        case '%':
            // Note we casted a and b to int so the fractional part becomes zero
            sum = (int)a / (int)b;
            break;
        default:
            //If none of the cases are met then print the following line and exit the function using (return;)
            printf("The action \'%c\' is not \"good\" for me!",operator);
            return;
    }
    if (sum - (int)sum > 0) {
        // If sum - sum is bigger than zero then that means we need to print the original float number
        printf("%d %c %d = %f",(int)a,operator,(int)b,sum);
    } else {
        // But if it is equal or less than zero, then we need to print only the integer part of the number using casting
        printf("%d %c %d = %d",(int)a,operator,(int)b,(int)sum);
    }
}

/**************************************************************************
 * Function name: MissionFive
 * Input: No input
 * Output: No output
 * The function operation: Asks for 3 coefficients numbers, then build
 * ax^2+bx+c = 0 formula which is printed using specific rules to meet the
 * criteria.
 *************************************************************************/
void MissionFive() {

    // Input three coefficient numbers to a b and c
    int a,b,c;
    // Flags used to indicate if we printed a specific part or not
    int printedFirstSegment = 0, printedSecondSegment = 0;
    printf("Enter three coefficients:\n");
    scanf("%d %d %d",&a,&b,&c);

    /*
     * The way the following lines of code work like
     * (ax^2+bx+c = 0)
     * Each part of a b and c has its own rules for formatting the formula, it prints each part on its own then finishes
     * with printing ' = 0', starting with part a, it checks if its not zero, if it is then it doesnt print as
     * the first part, then checks if it is minus 1, then it prints -x^2, because we don't want -1x^2
     * to print out, same if it was positive 1, anything else print the number with x^2 using %dx^2 format,
     * then set printedFirstSegment to 1, to indicate that we printed part a of the formula.
     *
     * Next we check if we printed the first part, and b or c are not zero, and b is bigger than 0, then print '+',
     * because if b was 0 or c was 0 and we already printed the first part, then that means they wont get formatted
     * and print them out, and if b was less than zero then that means we don't have to print '+' the negative symbol
     * minus '-' will take over '+'.
     *
     * Part b is exactly the same as part a, and sets printedSecondSegment to 1 if part b was checked and formatted
     * correctly and have been printed to console.
     *
     * Now to print the second '+' symbol between part b and part c is almost the same as the first '+', it checks if
     * the part a got printed out or part b got printed out, and b or c are not zero, and c is bigger than 0, then print
     * '+', explanation is the same as the first '+'.
     *
     * part c we check if its not 0 then print it out as usual, however if part a and part b were not printed to console
     * AND c was zero then print '0' for this specific input (0 0 0 -> '0 = 0').
     *
     * Lastly print ' = 0' to complete the formula formatting.
     *
     */

    // Part a
    // If its zero then that means 0x^2 == 0, there's no need to print it here
    if (a != 0) {
        // Other than that if its -1 or 1 then print x or -x without 1
        if (a == -1) {
            printf("-x^2");
        } else if (a == 1) {
            printf("x^2");
        } else {
            // Anything else print the number as it is
            printf("%dx^2",a);
        }
        // Set part a print flag to 1 (true)
        printedFirstSegment = 1;
    }

    // If the first was printed out and b or c were not zero and b is bigger than 0 then print '+'
    if (printedFirstSegment && (b != 0 || c != 0) && b > 0) {
        printf("+");
    }

    // Part b
    // Same as part a
    if (b != 0) {
        if (b == -1) {
            printf("-x");
        } else if (b == 1) {
            printf("x");
        } else {
            printf("%dx",b);
        }
        // Set part b print flag to 1 (true)
        printedSecondSegment = 1;
    }

    // If the second part and first part were printed out and b or c are not zero and c is bigger than zero, print '+'
    if ((printedSecondSegment || printedFirstSegment) && (b != 0 || c != 0) && c > 0) {
        printf("+");
    }

    // Part b
    // If c is not zero, print as is
    if (c != 0) {
        printf("%d",c);
    }

    // If part a and part b were not printed and c equals zero then that means the program should print '0 = 0'
    if (!printedFirstSegment && !printedSecondSegment && c == 0) {
        printf("0");
    }

    //Print
    printf(" = 0");

}
