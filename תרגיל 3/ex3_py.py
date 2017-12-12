"""
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 3
"""

import math

# This infinite loop keeps the program running and keeps asking
# for mission number input every time until it receives 0, then it breaks the loop
while True:
    # Input Mission Number
    missionChoice = input("please enter a mission number:\n")
    # Checks if mission input is 1
    if missionChoice == 1:
        # Input mission type
        firstMissionType = raw_input("please enter the mission type:\n")
        # Check if mission type is a
        if firstMissionType == "a":
            # Ask for number to process
            inputNumber = input("please enter a number:\n")
            # If its smaller than 2, print NO
            if inputNumber < 2:
                print("NO")
            # If its less or exactly 3, print YES (2 or 3)
            elif inputNumber <= 3:
                print("YES")
            else:
                # Flag for checking if prime or not from the loop
                PrimeFlag = True
                # Loops through every number starting from 2 till inputNumber - 1
                for i in range(2, inputNumber):
                    # If the number divides with i without remains then it means its prime
                    # print NO, set PrimeFlag to false to prevent YES from getting printed, and exit the loop
                    if inputNumber % i == 0:
                        print("NO")
                        PrimeFlag = False
                        break
                # If the flag is still true it means none of the numbers from 2 - inputNumber is dividable
                # by inputNumber without remains, which means its a prime number
                if PrimeFlag:
                    print("YES")
        # Check if mission type b (Which is the same as a but with square root of inputNumber as the range limit)
        elif firstMissionType == "b":
            # Ask for number to process
            inputNumber = input("please enter a number:\n")
            # If its less than two, print NO
            if inputNumber < 2:
                print("NO")
            # If its 2 or 3, print YES
            elif inputNumber <= 3:
                print("YES")
            else:
                # Take the square root of inputNumber
                squareRootOfInput = int(math.sqrt(inputNumber))
                # Setup a flag for prime number check
                PrimeFlag = True
                # Loop from 2 till square root of inputNumber plus one to include the number itself
                # then check if inputNumber is dividable by the numbers from 2 to squareRootOfInput without remains
                # if it is, then that means its not a prime number, print NO, Set PrimeFlag to true, and exit the loop
                for i in range(2, squareRootOfInput + 1):
                    if inputNumber % i == 0:
                        print("NO")
                        PrimeFlag = False
                        break
                # If PrimeFlag is still true, it means the number is prime, print YES
                if PrimeFlag:
                    print("YES")
        # Any other mission type
        else:
            # Ask for number to process
            inputNumber = input("please enter a number:\n")
            # if its less than one, print NO
            if inputNumber <= 1:
                print("NO")
            # If inputNumber is 2 or 3, print YES
            elif inputNumber <= 3:
                print("YES")
            # If the number is dividable by 2 or 3 without remains, print NO
            elif inputNumber % 2 == 0 or inputNumber % 3 == 0:
                print("NO")
            else:
                # The following code is called the Primality test algorithm
                i = 3
                # Set Flag for prime check
                PrimeFlag = True
                # While i to the power of 2 is less or equal to the input number
                # check if the inputNumber is dividable by i without remains, if its not add 2 to i
                # until the loop ends, or breaks (if inputNumber is dividable by i)
                while i * i <= inputNumber:
                    if inputNumber % i == 0:
                        print("NO")
                        PrimeFlag = False
                        break
                    i += 2
                # If PrimeFlag is true, it means the number is prime, print yes
                if PrimeFlag:
                    print("YES")
    # Check if mission number is 2
    elif missionChoice == 2:
        # Ask for two numbers to process
        inputNumber = raw_input("please enter two numbers:\n")
        a, b = inputNumber.split()
        a, b = int(a), int(b)
        # Set an empty array to add the dividable numbers
        numbersToPrint = []
        # Loop from 1 to 100 (The 101 is used so we can calculate the number 100 too), and check
        # if a or b is dividable by i with no remaining, if it is, add it to the list
        for i in range(1, 101):
            if i % a == 0 or i % b == 0:
                numbersToPrint.append(i)
        # After the loop ends, print whatever value the list has
        print(numbersToPrint)
    # If mission type is 0, exit the program by breaking the loop
    elif missionChoice == 0:
        break
