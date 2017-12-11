/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 4
******************************************/

/**************************************************************************
 * Function name: Collatz
 * Input: Number to use with collatz formula
 * Output: Prints the number during each iteration and then steps and
 * runtime-steps
 * Function Operation: Prints the number after being processed for each
 * iteration until it reaches 1 and prints the number of steps for the
 * number and total steps during the runtime of this function
 *************************************************************************/
void Collatz(long int n);

/**************************************************************************
 * Function name: CollatzNoPrint
 * Input: Number to use with collatz formula
 * Output: Returns the number of steps
 * Function Operation: Processes the number using collatz formula and
 * returns the number of steps for that number (which indicates how many
 * iterations)
 *************************************************************************/
unsigned long int CollatzNoPrint(long int n);

/**************************************************************************
 * Function name: ProofCollatzUntill
 * Input: Takes number input and loop from 1 to n
 * Output: Runs the function and prints the returned result
 * Function Operation: Loops from 1 to n and prints the passed: number of
 * steps message, also works with 1
 *************************************************************************/
void ProofCollatzUntill(long int n);

/**************************************************************************
 * Function name: Fermat
 * Input: Power of number and the stop limit
 * Output: Prints all of phythagoros equations of Fermat last theorem
 * Function Operation: It loops through all the possible numbers and check
 * which one of them applies to the theorem, then prints it, if nothing
 * prints, it prints "meh :(" instead
 *************************************************************************/
void Fermat(int n, int stop);

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
int IsDividedBy3Rec(long int n);

/**************************************************************************
 * Function name: IsDividedBy3Rec
 * Input: Number to check if its divisable by 3
 * Output: 1 if it is, 0 if its not
 * Function Operation: This function just calls the helper function
 * and returns whatever value that helper function returns
 *************************************************************************/
int IsDividedBy3Iter(long int n);

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
int FindCommonDigit(long int n1, long int n2);

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
int CountDigit(long int n, int d);


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
void PrintReverse(long int n);
