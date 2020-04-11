/**
 * File:          eratosthenes.c
 * Version:       1.1 Final
 * Date:          11-03-2012
 * Last update:   17-03-2012
 *
 * Course:        IJC (summer semester, 2012)
 * Project:       DU1 (Homework #1), part a) & b)
 *
 * Author:        David Kaspar (aka Dee'Kej), 1BIT
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies
 * E-mail:        xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   This module contains function that implements algorithm know
 *                as Sieve of Eratosthenes upon given bit array.
 *
 * More info @:   https://www.fit.vutbr.cz/study/courses/IJC/public/DU1.html.cs
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF ERATOSTHENES.C ]************************************************
 ******************************************************************************/


/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <math.h>

#include "bit-array.h"
#include "eratosthenes.h"


/******************************************************************************
 ~~~[ PRIMARY FUNCTION ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Function that implements Eratosthenes sieve for prime numbers. It operates
 * upon given array of BitArray_t type. Function assumes, that the given array
 * is zeroed, otherwise it wont function properly!
 */
void Eratosthenes(BitArray_t array)
{{{
  unsigned long i, index, stop_index;   /* Helpful variables for indexation. */

  /*
   * Value which crossing means that there are only prime numbers left in the
   * bit array. This value is square root of maximal possible bit array index
   * + 1 because of truncation.
   */
  stop_index = ((unsigned long) sqrt((double) BitArraySize(array))) + 1;

  /*
   * Small optimization for most often encountered non-prime numbers.
   * Excluding every number that is multiple of 2.
   */
  for (index = 4; index <= BitArraySize(array); index += 2) {
    SetBit(array, index, 1);
  }
  
  /* Excluding every number that is multiple of 3. */
  for (index = 9; index <= BitArraySize(array); index += 6) {
    SetBit(array, index, 1);
  }

  /* Excluding every number that is multiple of 5. */
  for (index = 25; index <= BitArraySize(array); index += 10) {
    SetBit(array, index, 1);
  }

  /*
   * Excluding rest of non-prime numbers. Optimizations for multiples of more
   * than 5 would probably don't make any difference because of complexity that
   * comes with that.
   */
  for (i = 7; i <= stop_index; i++) {
    if (GetBit(array, i) == 0) {
      for (index = i * i; index <= BitArraySize(array); index += i) {
        SetBit(array, index, 1);
      }
    }
  }
  
  return;
}}}


/******************************************************************************
 ~~~[ SELF-TESTING PART ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/* Conditional translation if -DERATOSTHENES_DEBUG parameter was used. */
#ifdef ERATOSTHENES_DEBUG

#include <stdio.h>

/**
 * Printing prime numbers from 2 to N (=1000) exclusive.
 */
int main (void)
{{{
  BitArray(array, 1000);

  Eratosthenes(array);

  for (unsigned long i = 2; i < BitArraySize(array); i++) {
    if (GetBit(array, i) == 0)
      printf("%lu\n", i);
  }

  return 0;
}}}

#endif          /* End of conditional translation. */


/******************************************************************************
 ***[ END OF ERATOSTHENES.C ]**************************************************
 ******************************************************************************/
 
