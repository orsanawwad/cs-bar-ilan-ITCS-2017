/*****************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 3
******************************/

#include <stdio.h>
#include <math.h>


int main()
{
    /*
     * This infinite loop keeps the program running and keeps asking
     * for mission number input every time until it receives 0, then it breaks the loop
     */
    while (1) {
        int missionInput = 0;
        printf("please enter a mission number:\n");
        // Input Mission Number
        scanf("%d", &missionInput);
        // Checks if mission input is 1
        if (missionInput == 1) {
            char missionType = ' ';
            printf("please enter the mission type:\n");
            // Input Mission Type
            scanf("\n%c",&missionType);
            int numberToProcess = 0;
            printf("please enter a number:\n");
            // Ask for number to process
            scanf("\n%d",&numberToProcess);
            // Setup loopLimit number for prime number checking
            int loopLimit = 0;
            // If mission type is a, set the loopLimit as the input number
            if (missionType == 'a') {
                loopLimit = numberToProcess - 1;
            }
            // If misison type is b, set the loopLomit as the sqwuare root of input number
            else if (missionType == 'b') {
                loopLimit = (int)sqrt(numberToProcess);
            }
            if (missionType == 'a' || missionType == 'b') {
                int i;
                // Check if input number is less or equals one, if it is print NO
                if (numberToProcess <= 1) {
                    printf("NO\n");
                }
                // If the input number is 2 or 3, print YES
                else if (numberToProcess <= 3) {
                    printf("YES\n");
                }
                // If the input number is dividable by 2 or 3 without remains, print NO
                else if (numberToProcess % 2 == 0 || numberToProcess % 3 == 0) {
                    printf("NO\n");
                }
                // Anything else, proceed with the loop
                else {
                    /*
                     * Loop through each number from 2 till the loopLimit (which was set above)
                     * and check if the input number is dividable by i, if it is, print NO and break the loop,
                     * if the loop reached the end, it means the number is prime, print YES
                     */
                    for (i = 2; i <= loopLimit; i++) {
                        if (numberToProcess % i == 0) {
                            printf("NO\n");
                            break;
                        }
                        if (i == loopLimit) {
                            printf("YES\n");
                        }
                    }
                }
            }
            // Any other mission type, run the Primality test algorithm
            else {
                // Check if its less or equals one
                if (numberToProcess <= 1) {
                    printf("NO\n");
                }
                // If the input number is 2 or 3, print YES
                else if (numberToProcess <= 3) {
                    printf("YES\n");
                }
                // If the input number is dividable by 2 or 3 without remains, print NO
                else if (numberToProcess % 2 == 0 || numberToProcess % 3 == 0) {
                    printf("NO\n");
                }
                // Anything else, proceed with the algorithm
                else {
                    int i = 3;
                    // Set Flag for prime check
                    int PrimeFlag = 1;
                    /*
                     * While i to the power of 2 is less or equal to the input number
                     * check if the inputNumber is dividable by i without remains, if its not add 2 to i
                     * until the loop ends, or breaks (if inputNumber is dividable by i)
                     */
                    while (i * i <= numberToProcess) {
                        if (numberToProcess % i == 0) {
                            printf("NO\n");
                            PrimeFlag = 0;
                            break;
                        }
                        i += 2;
                    }
                    // If PrimeFlag is true, it means the number is prime, print yes
                    if (PrimeFlag) {
                        printf("YES\n");
                    }
                }
            }
        }
        // Check if mission number is 2
        else if (missionInput == 2) {
            int a,b;
            printf("please enter two numbers:\n");
            // Ask for two numbers to process
            scanf("\n%d %d", &a, &b);
            int i = 0;
            // Print the first bracket of the array
            printf("[");
            // Set a flag for checking if the first number was printed out so that we can print commas after that
            int commaPrintFlag = 0;
            /*
             * Loop from 1 to 100, and check if a or b is dividable by i with no
             * remaining, if it is, print it, if its the first time printing
             * the number (by checking commaPrintFlag flag), print the number as is, then after that print comma space
             * before each other number
             */
            for (i = 1; i <= 100; i++)  {
                if (i % a == 0 || i % b == 0) {
                    if (commaPrintFlag) {
                        printf(", ");
                    }
                    printf("%d",i);
                    commaPrintFlag = 1;
                }
            }
            // Print the end of array bracket
            printf("]\n");

        }
        // If mission number is 0, exit the program by exiting the loop
        else if (missionInput == 0) {
            break;
        }
    }
    return 0;
}


/* Run time for case a: python 2.20331597 c 0.07563305
 * Run time for case b: python 0.01691604 c 0.00412202
 * Run time for case c: python 0.01582408 c 0.00392485 */
