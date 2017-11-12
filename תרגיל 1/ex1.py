"""
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 1
"""

# Global Variable to easily fine the value of hex digit through HEX_NUMBERS_LIST[hex_digit]
HEX_NUMBERS_LIST = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"]

# Task 1
def convertAnyBaseToDecimal(inputNumber, inputNumberBase):
    """
    Takes a number, converts it to decimal then return it

    :param inputNumber: Input number to convert
    :param inputNumberBase: Input number's original base
    :return: Converted decimal number
    """

    # Used to track the summary from the loop
    summary = 0

    # Create an enumerate object so we can track the index (or position of the list) during the loop
    # The enumerate object takes the input number reversed using the [::-1] selection command
    # In the loop takes each char in the string, converts to int, multiply it with the base power by the index
    for i, num in enumerate(inputNumber[::-1]):
        summary = summary + (int(num) * (inputNumberBase ** i))

    # Convert summary to string and return it
    return str(summary)

# Task 2
def convertAnyBaseToBytesRepresentation(inputNumber, inputNumberBase):
    """
    Takes a number and converts to to byte representation (00000011, 11110000)

    :param inputNumber: Input number to convert
    :param inputNumberBase: Input number's original base
    :return: Input number's byte representation
    """

    # Convert the input to list and converts each character of the input to uppercase character (for lazy inputs...)
    inputNumberList = [s.upper() for s in inputNumber]

    # Used for deciding how many bits each digit of the number represents
    numberOfBits = 0

    # If its octal number then it represents 3 bits for each digit, else if 16 then 4 bits for each digit
    if inputNumberBase == 8:
        numberOfBits = 3
    elif inputNumberBase == 16:
        numberOfBits = 4
    else:
        print "Error"

    # A list to keep track of converted digits
    binaryList = []

    # Takes the actual value of the digit using HEX_ARRAY_LIST and convert it to bit and adds to to binaryList
    for i, number in enumerate(inputNumberList[::-1]):
        decimalNumber = HEX_NUMBERS_LIST.index(number)

        # Takes the converted value, modulo byt 2 and save it to the list, then replace decimalNumber to its div by 2
        # If decimalNumber is 0 and the length of the binaryList is not part of numberOfBits then keep adding zeros
        while decimalNumber != 0:
            binaryList.insert(0, decimalNumber % 2)
            decimalNumber = decimalNumber / 2
            if decimalNumber == 0 and len(binaryList) % numberOfBits != 0:

                # Checks if binaryList is not part of numberOfBits, keep adding zero at the beginning of list till it is
                for count in range(numberOfBits - (len(binaryList) % numberOfBits)):
                    binaryList.insert(0, 0)

    # Convert back to string and return it
    return "".join(str(s) for s in binaryList)

# Task 3
def convertDecimalToSpecificBase(inputNumber, inputBase):
    """
    Converts decimal number to a specific input base

    :param inputNumber: Input number to convert
    :param inputBase: The base to convert to
    :return: The converted number
    """

    # Convert input number from string to int, initialize empty string to track the converted numbers
    inputNumber = int(inputNumber)
    conversionResult = []

    # While inputNumber is not zero, find the actual value using HEX_NUMBERS_LIST, modulo by inputBase and insert it
    # Replace input with its division by inputBase
    while inputNumber != 0:
        conversionResult.insert(0, HEX_NUMBERS_LIST[inputNumber % inputBase])
        inputNumber = inputNumber / inputBase

    # Convert the result back to string and return it
    return "".join(x for x in conversionResult)

# Task 4
def convertBinaryToSignedUnsigned(binaryNumberInput):
    """
    Converts the input binary number to its signed and unsigned value

    :param binaryNumberInput: The binary input to convert
    :return: Returns a dictionary with "unsignedSum" as unsigned value, and "signedSum" as signed value
    """

    # Initialize unsignedSum and signedSum to calculate the value for each and return it in the dictionary
    # Although these 2 lines are not needed because variables assigned inside if block is still scoped to the same func
    unsignedSum = 0
    signedSum = 0

    # Converts the binary input number to unsigned decimal like normal and saves it
    unsignedSum = convertAnyBaseToDecimal(binaryNumberInput, 2)

    # Checks if the first digit is one, if so it converts each negates each bit and then converts it to decimal
    if binaryNumberInput[0] == "1":
        # Negates each digit, loops through input binary, converts it to int, negate it then convert back to string
        negatedBinary = ''.join([str((1 - int(d))) for d in binaryNumberInput])

        # Convert back to decimal, adds one, then negate it
        signedSum = str((int(convertAnyBaseToDecimal(negatedBinary, 2)) + 1) * -1)

    # Else just take the unsigned value
    else:
        signedSum = unsignedSum

    # Create a dictionary and return it
    return {"unsignedSum": unsignedSum, "signedSum": signedSum}

# Inputs the task number
taskChoice = input("please enter the mission number:\n")

# If its 1 then it does "mission" 1, if its 2 then "mission" 2 and so on...
if taskChoice == 1:
    inputNumber = raw_input("please enter a number:\n")
    inputBase = input("please enter a base (2-9):\n")

    # Invokes convertAnyBaseToDecimal and prints the converted decimal output
    print(convertAnyBaseToDecimal(inputNumber, inputBase))

elif taskChoice == 2:
    inputNumber = raw_input("please enter a number:\n")
    inputBase = input("please enter a base (16 or 8):\n")

    # Invokes convertAnyBaseToBytesRepresentation with input num and base and prints the converted bits
    print(convertAnyBaseToBytesRepresentation(inputNumber, inputBase))

elif taskChoice == 3:
    inputNumber = input("please enter a number:\n")
    inputBase = input("please enter a base (16,8,4 or 2):\n")

    # Invokes convertDecimalToSpecificBase with input value and base, and prints the converted number to its target base
    print(convertDecimalToSpecificBase(inputNumber, inputBase))

elif taskChoice == 4:
    inputBinary = raw_input("please enter an 8-bit binary number\n")

    # Invokes convertBinaryToSignedUnsigned with input binary and saves the dictionary result
    signedUnsignedOutput = convertBinaryToSignedUnsigned(inputBinary)

    # Takes "unsignedSum" value and prints it
    print "unsigned: " + signedUnsignedOutput["unsignedSum"]

    # Takes "signedSum" value and prints it
    print "signed: " + signedUnsignedOutput["signedSum"]

# Else print error
else:
    print("Error")

