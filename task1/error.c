/**
 * File:          error.c
 * Version:       1.01 Final
 * Date:          01-03-2012
 * Last update:   03-03-2012
 *
 * Course:        IJC (summer semester, 2012)
 * Project:       DU1 (Homework #1), part a) & b)
 *
 * Author:        David Kaspar (aka Dee'Kej), 1BIT
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies
 * E-mail:        xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   This module contains definitions of variadic error functions.
 *                For more information see the functions description.
 *
 * More info @:   https://www.fit.vutbr.cz/study/courses/IJC/public/DU1.html.cs
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF ERROR.C ]*******************************************************
 ******************************************************************************/

/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "error.h"


/******************************************************************************
 ~~~[ PRIMARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Variadic error function given from assignment. Prints Czech translation of
 * 'error', then the given variadic arguments just as printf(). Everything is
 * printed to stderr.
 */
void Error(const char *fmt, ...)
{{{
  va_list ap;                           /* Stack pointer. */

  va_start(ap, fmt);                    /* Stack pointer initialization. */
  fprintf(stderr, "CHYBA: ");           /* Czech translation of 'error'. */
  (void) vfprintf(stderr, fmt, ap);     /* Print of the variadic arguments. */
  va_end(ap);                           /* End of work with stack. */

  return;
}}}


/**
 * Same function as Error() above, but at the end this function terminates the
 * program with EXIT_FAILURE.
 */
void FatalError(const char *fmt, ...)
{{{
  va_list ap;                           /* Stack pointer. */

  va_start(ap, fmt);                    /* Stack pointer initialization. */
  fprintf(stderr, "CHYBA: ");           /* Czech translation of 'error'. */
  (void) vfprintf(stderr, fmt, ap);     /* Print of the variadic arguments. */
  va_end(ap);                           /* End of work with stack. */

  exit(EXIT_FAILURE);                   /* Program termination. */
}}}


/******************************************************************************
 ~~~[ SELF-TESTING PART ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/* Conditional translation if -DERROR_DEBUG parameter was used. */
#ifdef ERROR_DEBUG

int main (void)
{{{
  printf("Testing of 2 error functions. You should see 2 error messages "
         "starting with:\n"
         "'CHYBA:'\n"
         "Testing should end-up with exit code <> 0, type echo $? for "
         "conformation.\n\n"
         "Starting:\n");

  Error("Testing Error() function. Test of number printing: %d\n", 42);
  FatalError("Testing FatalError() function. Test of floating number "
             "printing: %f\n", 0.125);

  return EXIT_SUCCESS;
}}}

#endif          /* End of conditional translation. */


/******************************************************************************
 ***[ END OF ERROR.C ]*********************************************************
 ******************************************************************************/
 
