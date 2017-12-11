/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 4
******************************************/

#include "ex4.h"
#include <stdio.h>
#include "math.h"

/**************************************************************************
 * Function name: Collatz
 * Input: Number to use with collatz formula
 * Output: Prints the number during each iteration and then steps and
 * runtime-steps
 * Function Operation: Prints the number after being processed for each
 * iteration until it reaches 1 and prints the number of steps for the
 * number and total steps during the runtime of this function
 *************************************************************************/
void Collatz(long int numberForCollatz) {
    // Initialize the counter for collatz, both local and static counters
    long int stepCount = 0;
    static long int runtimeTotalStepCount = 0;
    // Print the first number whatever it is
    printf("%li", numberForCollatz);
    // Check if the input itself is not 1, if it is 1, print a new line, otherwise print the arrow
    if (numberForCollatz != 1) {
        printf("->");
    } else {
        printf("\n");
    }
    // Runs the loop while the number is not one
    while (numberForCollatz != 1) {
        // If its an odd number, multiply by 3 and add 1
        if (numberForCollatz % 2) {
            numberForCollatz = 3 * numberForCollatz + 1;
            printf("%li", numberForCollatz);
        } else {
            // Else divide it by 2
            numberForCollatz = numberForCollatz / 2;
            printf("%li", numberForCollatz);
        }
        // If the processed number is not 1, print the arrow, else print new line
        if (numberForCollatz != 1) {
            printf("->");
        } else {
            printf("\n");
        }
        // Add 1 to stepCount (local variable) and runtimeTotalStepCount (the static runtime variable)
        stepCount++;
        runtimeTotalStepCount++;
    }
    // Print the count of the steps
    printf("num of steps: %li\n",stepCount);
    printf("total num of steps: %d\n",runtimeTotalStepCount);
}

/**************************************************************************
 * Function name: CollatzNoPrint
 * Input: Number to use with collatz formula
 * Output: Returns the number of steps
 * Function Operation: Processes the number using collatz formula and
 * returns the number of steps for that number (which indicates how many
 * iterations)
 *************************************************************************/
unsigned long int CollatzNoPrint(long int n) {
    // The step counter for the number to use with collatz
    unsigned long int stepCount = 0;
    // Same Collatz functionality as above
    while (n != 1) {
        if (n % 2) {
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
        stepCount++;
        // But, when the unsigned long int variable is 0, it means that it reached the end of the of the variable
        // range, and then reverted back to 0, There is no need to define a name for 0xFFFFFFFF and use that to
        // compare
        if (stepCount == 0) {
            return 0;
        }
    }
    // The step count to return
    return stepCount;
}

/**************************************************************************
 * Function name: ProofCollatzUntill
 * Input: Takes number input and loop from 1 to n
 * Output: Runs the function and prints the returned result
 * Function Operation: Loops from 1 to n and prints the passed: number of
 * steps message, also works with 1
 *************************************************************************/
void ProofCollatzUntill(long int n) {
    for (long int i = 1; (i < n) || (i == 1); ++i) {
        unsigned long int steps = CollatzNoPrint(i);
        if (steps == 0 && n != 1) {
            printf("you might want to check")
        }
        printf("passed: %li (num of steps: %lu)\n",i,CollatzNoPrint(i));
    }
}

/**************************************************************************
 * Function name: Fermat
 * Input: Power of number and the stop limit
 * Output: Prints all of phythagoros equations of Fermat last theorem
 * Function Operation: It loops through all the possible numbers and check
 * which one of them applies to the theorem, then prints it, if nothing
 * prints, it prints "meh :(" instead
 *************************************************************************/
void Fermat(int n, int stop) {
    int count = 0;
    for (int i = 1; i < stop; ++i) {
        // Note that we start this loop with the i value to prevent duplicates from printing out
        for (int j = i; j < stop; ++j) {
            for (int k = 1; k < stop; ++k) {
                if (pow(i,n) + pow(j,n) == pow(k,n)) {
                    printf("Eureka! %d^%d + %d^%d = %d^%d\n",i,n,j,n,k,n);
                    count++;
                }
            }
        }
    }
    if (count == 0) {
        printf("meh :(\n");
    }
}

/**************************************************************************
 * Function name: IsDividedBy3RecHelper
 * Input: Number to process, and a tracker variable for tracking the mod
 * Output: 1 if it is divisible by 3, 0 if its not
 * Function Operation: At first, it takes the last two digits of the
 * number, since the the input number can only be made with 1 2 or 3s,
 * we then use that rule to check those 2 numbers, for example if the last
 * digit number was 1, and the second last digit was 2, it calls the
 * function with 0 as the new moduloTracker, then it goes on and on
 * until the number to process reaches zero, after that it checks the
 * moduloTracker, if its 0, its divisible, so it returns 1, anything other than that, return 0
 *************************************************************************/
int IsDividedBy3RecHelper(long int n, long int moduloTracker) {
    // Check if number is zero, if it is, check the moduloTracker, if its 0, its divisible, else return 0
    if (n == 0) {
        if (moduloTracker == 1 || moduloTracker == 2) {
            return 0;
        } else {
            return 1;
        }
    }
    // Gets the last digit
    long int lastDigit = n % 10;
    // If its 3, call the recursion function and keep the same moduloTracker (cause )
    if (lastDigit == 3) {
        return IsDividedBy3RecHelper(n / 10, moduloTracker);
    } else if (lastDigit == 2) {
        if (moduloTracker == 1) {
            return IsDividedBy3RecHelper(n / 10, 0);
        } else if (moduloTracker == 2) {
            return IsDividedBy3RecHelper(n / 10, 1);
        } else {
            return IsDividedBy3RecHelper(n / 10, 2);
        }
    } else if (lastDigit == 1) {
        if (moduloTracker == 1) {
            return IsDividedBy3RecHelper(n / 10, 1);
        } else if (moduloTracker == 2) {
            return IsDividedBy3RecHelper(n / 10, 0);
        } else {
            return IsDividedBy3RecHelper(n / 10, 2);
        }
    }
}

/**************************************************************************
 * Function name: IsDividedBy3Rec
 * Input: Number to check if its divisable by 3
 * Output: 1 if it is, 0 if its not
 * Function Operation: This function just calls the helper function
 * and returns whatever value that helper function returns
 *************************************************************************/
int IsDividedBy3Rec(long int n) {
    //Calls the helper class
    return IsDividedBy3RecHelper(n/10,n%10);
}

/**************************************************************************
 * Function name: IsDividedBy3Iter
 * Input: Number to check if it's divisible by 3
 * Output: 1 if it is, 0 if its not
 * Function Operation: The function goes through each digit, and adds it
 * to a sum variable, once it sums up all the digits, it checks the sum
 * if its bigger than 10, if it is, set the sum again as the number
 * variable to process, then sum the digits again, adding the digits is
 * over and the sum variable is less than 10, if checks if the number
 * is one of those 4 numbers, 3, 6, 9 and 0, because these are the only
 * single digit number that is divisible by 3 with no remains, if its
 * one of them, return 1, otherwise, return 0
 *************************************************************************/
int IsDividedBy3Iter(long int n) {
    long int count = 0;
    while (1) {
        count = count + n % 10;
        n = n/10;
        if (n == 0) {
            if (count > 10) {
                n = count;
                count = 0;
            } else {
                if (count == 3 || count == 6 || count == 9 || count == 0) {
                    return 1;
                } else {
                    return 0;
                }
            }
        }
    }
}

/**************************************************************************
 * Function name: FindCommonDigit
 * Input: 2 numbers to find the largest common digit
 * Output: The largest digit that is found
 * Function Operation: It compares the last digit of each number, if they
 * equal each other, return that number and end the function, otherwise,
 * check which of the numbers have the largest last digit number, then
 * call the recursion function from there with that digit removed, if the
 * number reached 0 (indicating that all the digits got removed), return -1
 *************************************************************************/
int FindCommonDigit(long int n1, long int n2) {
    if (n1 % 10 == n2 % 10) {
        return (int) (n1 % 10);
    } else {
        if (n1 / 10 == 0 || (n1 % 10 < n2 % 10)) {
            return FindCommonDigit(n1, n2 / 10);
        } else if (n2 / 10 == 0 || n1 / 10 == 0) {
            return -1;
        } else {
            return FindCommonDigit(n1 / 10, n2);
        }
    }
}

/**************************************************************************
 * Function name: CountDigit
 * Input: The number to count the digits from, and the digit to compare
 * with
 * Output: Return amount of digits that got repeated inside the number
 * Function Operation: A recursion function where it checks if its 0,
 * if its not it checks whether the last digit is equal to the number that
 * we need to compare with, and if its bigger than 10, then the expression
 * will return 1, which is then used within the recursion return, then it
 * calls the function with the last digit removed
 *************************************************************************/
int CountDigit(long int n, int d) {
    if (n == 0) {
        return (n % 10 == d);
    } else {
        return (n % 10 == d && n > 10) + CountDigit(n/10,d);
    }
}

/**************************************************************************
 * Function name: PrintReverse
 * Input: The number to print it in reverse
 * Output: The number but reversed
 * Function Operation: A Recursion function where it prints the last digit
 * of the number then divides it by 10, checks if the number is zero, if
 * its not call back the function with the new divided by 10 numnber,
 * otherwise print new line to indicate the end of recursion.
 *************************************************************************/
void PrintReverse(long int n) {
    printf("%li",n % 10);
    n = n/10;
    if (n != 0) {
        PrintReverse(n);
    } else {
        printf("\n");
    }
}
