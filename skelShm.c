/* Write a multiple concurrent process program that does the following
   1. Displays "ascii modern art" composed of a series of 
      randomly generated blocks of 2 or more repeating characters

   The program should perform this task in the following way:
   1. Create a semaphore set of size 2 -- use IPC_PRIVATE as your key
      a. Initialize the semaphore representing the child to available
      b. Initialize the semaphore representing the parent to in use
   2. Create a segment of shared memory -- use IPC_PRIVATE as your key

   3. Create a child process that:
      a. Attaches the segment of shared memory
      b. Seeds the random number generator 
      c. Reserves the child semaphore
      d. Generates and stores the total number of blocks to generate. 
         This should be between 10 and 20
      c. For each block, generate and store the following values:
         1. The length of the block (i.e. the number of characters to display)
            This should be between 2 and 10
         2. The character that comprises the block.
            This should be between 'a' and 'z'
      d. Release the parent semaphore
      e. Reserve the child semaphore
      f. Detach the shared memory segment
      g. Release the parent semaphore

   4. Create a parent process that:
      a. Attaches the segment of shared memory
      b. Seeds the random number generator
      c. Reserve the parent semaphore 
      d. Generate a random width for the ASCII art. 
         This should be between 10 and 15
      e. Using the data stored in the shared memory segment, output an image
         Use the following tips: 
         1. One value stored in the segment should represent the number
            of (length, character) pairings. For each (length, character)
            pairing, you should output length instances of the given 
            character. This means if the pairing was (3, 'b'), you would
            output "bbb".
         2. The random image has basically been encoded use run-length
            encoding (RLE); RLE doesn't including the location of new lines.
            The location of new lines is determined by the random width 
            generated in step d. Each time you output width total characters,
            output a new line.
      f. Release the child semaphore
      g. Reserve the parent semaphore
      h. Detach the shared memory segment

   5. Delete the semaphore
   6. Delete the shared memory
   
   -- You can use/should use the binary semaphore protocol introduced in class
 */

/* Problem 3 -- List the inlcude files you need for this program. */
#include <stdio.h>
#include <stdlib.h>







#include "semun.h"
#include "binary_sem.h"

/* Problem 4 -- remember to declare a structure that represents the data
   stored in the shared memory */


/* Problem 5 -- create a function to handle the code for the child. 
   Be certain to pass this function the id values for both the semaphore 
   and the shared memory segment */


/* Problem 6 -- create a function to handle the code for the parent. 
   Be certain to pass this function the id values for both the semaphore 
   and the shared memory segment */


/* Problem 7 -- implement function main */

int main(int argc, char *argv[])
{
















  
}
