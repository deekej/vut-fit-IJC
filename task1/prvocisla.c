/**
 * File:          prvocisla.c
 * Version:       1.0 Final
 * Date:          12-03-2012
 * Last update:   12-03-2012
 *
 * Course:        IJC (summer semester, 2012)
 * Project:       DU1 (Homework #1), part a)
 *
 * Author:        David Kaspar (aka Dee'Kej), 1BIT
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies
 * E-mail:        xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   Prints last prime numbers of given size of array. The count of
 *                prime numbers to print is specified below.
 *
 * More info @:   https://www.fit.vutbr.cz/study/courses/IJC/public/DU1.html.cs
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF PRVOCISLA.C ]***************************************************
 ******************************************************************************/


/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bit-array.h"
#include "eratosthenes.h"


/******************************************************************************
 ~~~[ LOCAL CONSTANTS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/* Size of bit array to create. */
#define ARRAY_SIZE 99000000

/* Number of last prime numbers to print. */
#define PN2P 10


/******************************************************************************
 ~~~[ MAIN FUNCTION ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

int main(void)
{{{
  unsigned long prime_numbers[PN2P];      /* Helpful array of prime numbers. */
  BitArray(array, ARRAY_SIZE);            /* Bit array of given size. */

  Eratosthenes(array);                    /* Getting the prime numbers. */

  int i = PN2P - 1;                       /* Helpful value for iterating. */
  unsigned long index = ARRAY_SIZE;       /* Value for indexing in bit array. */
  
  
  /*
   * Stores the last required prime numbers in the prime_numbers array.
   */
  while (i >= 0) {
    index--;

    /* Is prime number? */
    if (GetBit(array, index) == 0) {
      prime_numbers[i] = index;
      i--;
    }
  }


  /*
   * Prints the last required prime numbers of given size of array.
   */
  for (i = 0; i < PN2P; i++) {
    fprintf(stdout, "%lu\n", prime_numbers[i]);
  }

  return EXIT_SUCCESS;
}}}


/******************************************************************************
 ***[ END OF PRVOCISLA.C ]*****************************************************
 ******************************************************************************/
 
