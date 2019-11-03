# cs3500project
Implementation of calculator for CS3500 C project

# System Overview

## Tokenizer
The Tokenizer will read in the input file and parse the characters into tokens.
It will go through each character and hold the them in a buffer until an operator is reached.
It will then decide if the number inside the buffer is an integer or float by checking if there was a decimal point.
It will then make a token struct out of this with a type and value attributes.
These will be added to an array until the end of a file is reached. Operators will be added as tokens in the same way
and put straight into the array as they are single characters.
Output will be the array of tokens.

## I2P
I2P will read in the array from the Tokenizer and use Shunting-yard algorithm to convert Infix to Postfix.
It will use two stacks: an output stack and an operator stack.
Output will be the tokens in Postfix order in an array.

## Code Generator
The Code Generator will read in the array from I2P and start generating instructions for the VM to follow.
It will place these instructions onto an array.
It will look at the token type and value to determine what the instructions should be,
e.g. LOADINT if type is integer or MUL if type is operator and value is “\*”.
Output will be the array.

## VM
The VM will start reading instructions from the start of the array passed in by the Code Generator.
It will load numbers into memory (keeping track with a pointer to act as a stack)
and will start to perform arithmetic on them when an operator is reached.
It will use the pointer to pop numbers from memory.
The last value in memory will be the result, which’ll be outputted to the user.

# Functional Requirements
* Calculator should accept valid user input e.g. any real number +-/* any real number
* Input file should not have illegal expressions, e.g. 1++ or 2/0
* A full range of operations should be available e.g. + / ^ etc.
* Component output is what is expected by the next component

* Tokenizer can read input file
* Tokenizer makes input file into tokens
* Able to parse all necessary information for operands/operators from input file
* Should be able to read input file with or without spaces
* Can differentiate integers, floats, and operators in input file

* I2P converts expression from Infix to Postfix

* Code Generator generates instructions
* Code should have formatted structure

* VM runs instructions and outputs result to user
* Should only execute instructions
* Output human-readable

# Interfaces between the system components:
## Tokenizer -> I2P
Tokenizer will output an array of tokens indicating what it is by a type and what is the value of
the token, e.g. 12 → {type=”d”, value=”12”}.
I2P will read this array, go through each item and process each token according to rules
associated with its type in accordance to Shunting-yard algorithm.

## I2P -> Code Generator
I2P will use Shunting-yard algorithm to structure the conversion.
This outputs an array of tokens.
The Code Generator will expect this array and can read each item in it to generate code. It
will know to load integers/floats by reading the token’s type attribute. It can read operators by
the token type/value and generate their appropriate arithmetic instruction.

## Code Generator -> VM
The Code Generator will output an array of string instructions.
Each item in the Code Generator array will be an instruction on what the VM should do, such
as LOADINT or ADD. The VM can read these and perform the instructions by having it follow
rules assigned to them.
