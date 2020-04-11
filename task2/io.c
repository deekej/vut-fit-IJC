/**
 * File:          io.c
 * Version:       1.0
 * Date:          11-04-2012
 * Last update:   24-04-2012
 *
 * Course:        IJC (summer semester, 2012)
 * Project:       DU2 (Homework #2), part b)
 *
 * Author:        David Kaspar (aka Dee'Kej), 1BIT
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies
 * E-mail:        xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   Module with function similar to fgets(), but instead of line
 *                reads only one word - anything separated by white-space
 *                characters. Leading white-space characters before the word are
 *                skipped.
 *
 * More info @:   http://www.fit.vutbr.cz/study/courses/IJC/public/DU2.html
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF IO.C ]**********************************************************
 ******************************************************************************/


/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>

#include "io.h"


/******************************************************************************
 ~~~[ PRIMARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Reads one word from given file, separated by white-space characters. The read
 * word is stored into given string (array). Function reads only max - 1
 * characters into the string, the rest is skipped. Returns number of read
 * character, if end-of-file or error was encountered, then returns EOF and sets
 * errno respectively.
 */
int fgetword(char *str, int max, FILE *fp)
{{{
  /* Test of given arguments. */
  if (str == NULL || max < 1 || fp == NULL) {
    errno = EINVAL;
    return EOF;
  }


  int c = 0;                        /* Input character. */

  errno = 0;                        /* Reseting errno for error detection. */


  /* Skipping white-space characters before word. */
  while ((c = fgetc(fp)) != EOF && isspace(c))
    ;

  /* Terminates string and returns EOF if there was end-of-file or error. */
  if (errno != 0 || c == EOF) {
    *str = '\0';
    return EOF;
  }

  /* 
   * Returning read character to stream because +1 character has been read above
   * when skipping of white-space characters was performed.
   */
  if (ungetc(c, fp) == EOF) {
    errno = EIO;                    /* Character couldn't be returned. */
    return EOF;
  }

  
  int i = 0;                        /* Number of read characters. */

  max--;                            /* Only max - 1 characters can be read. */

  /*
   * Reading until end-of-file or white-space character is encountered and if
   * there's still remaining space in given string.
   */
  while ((c = fgetc(fp)) != EOF && !(isspace(c)) && i < max) {
    *str++ = (char) c;              /* Writes into string and moves pointer. */
    i++;
  }

  *str = '\0';                      /* Terminating string. */

  /* Test upon read error of fgetc(). */
  if (errno != 0) {
    return EOF;
  }


  /* Test if whole word has been read. */
  if (c != EOF && !(isspace(c))) {

    /* Skipping rest of the word. */
    while ((c = fgetc(fp)) != EOF && !(isspace(c)))
      ;
    
    /* Test upon read error of fgetc(). */
    if (errno != 0) {
      return EOF;
    }

    errno = ENOBUFS;
  }

  
  /* 
   * Returns number of read characters if there wasn't end-of-file, otherwise
   * returns EOF.
   */
  return (c != EOF) ? i : EOF;
}}}


/******************************************************************************
 ~~~[ SELF-TESTING PART ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/* Conditional translation if -DIO_DEBUG was defined. */
#ifdef IO_DEBUG

#include <stdlib.h>

/**
 * Prints words read from stdin to stdout.
 */
int main(void)
{{{
  char str[255] = "";             /* Buffer. */

  errno = 0;                      /* Reseting errno for error detection. */

  while (fgetword(str, 255, stdin) != EOF) {
    fprintf(stdout, "%s\n", str);
  }

  if (errno != 0) {
    perror("io: error");
  }

  return (errno != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}}}

#endif


/******************************************************************************
 ***[ END OF IO.C ]************************************************************
 ******************************************************************************/
 
