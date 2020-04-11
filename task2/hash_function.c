/**
 * File:          hash_function.c
 * Version:       1.0
 * Date:          17-04-2012
 * Last update:   24-04-2012
 *
 * Course:        IJC (summer semester, 2012)
 * Project:       DU1 (Homework #2), part b)
 *
 * Author:        David Kaspar (aka Dee'Kej), 1BIT
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies
 * E-mail:        xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   Module containing default hash function for libhtable library.
 *
 * More info @:   http://www.fit.vutbr.cz/study/courses/IJC/public/DU2.html
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF HASH_FUNCTION.C ]***********************************************
 ******************************************************************************/

/**
 * Given default hash function from instructions. Returns index to hash table of
 * given size.
 */
unsigned hash_function(const char *str, unsigned htable_size)
{{{
  unsigned hash = 0;
  unsigned char *ptr;

  for (ptr = (unsigned char *) str; *ptr != '\0'; ptr++) {
    hash = 31 * hash + *ptr;
  }

  return hash % htable_size;
}}}

/******************************************************************************
 ***[ END OF HASH_FUNCTION.C ]*************************************************
 ******************************************************************************/
 
