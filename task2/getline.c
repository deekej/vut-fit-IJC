/**
 * File:          getline.c
 * Version:       1.1.0.1
 * Date:          29-03-2012
 * Last update:   09-04-2012
 *
 * Course:        IJC (summer semester, 2012)
 * Project:       DU2 (Homework #2), part a)
 *
 * Author:        David Kaspar (aka Dee'Kej), 1BIT
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies
 * E-mail:        xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   Simple rewrite of getline() and getdelim() functions of
 *                POSIX.1-2008 using only ISO/IEC 9899:1999 constructions,
 *                without using multi-thread locks.
 *
 * More info @:   http://www.fit.vutbr.cz/study/courses/IJC/public/DU2.html
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF GETLINE.C ]*****************************************************
 ******************************************************************************/

/*
 * Conditional translation. Content of this module is only used when no GNU
 * extension of C language standard is used.
 */
#if !defined _GNU_SOURCE && _POSIX_C_SOURCE < 200809L && _XOPEN_SOURCE < 700



/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "getline.h"


/******************************************************************************
 ~~~[ LOCAL CONSTANTS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

static const size_t BUFF_SIZE_DEF = 162;    /* Default line size. */
static const size_t BUFF_SIZE_MULT = 2;     /* Multiplication constant. */


/******************************************************************************
 ~~~[ LOCAL FUNCTIONAL PROTOTYPES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

static inline int getdelim_resize(char **lineptr, size_t *n);


/******************************************************************************
 ~~~[ PRIMARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Wrapping function, getline() is same as getdelim(), only '\n' is always used
 * as a delimiter.
 */
int getline(char **lineptr, size_t *n, FILE *stream)
{{{
  return getdelim(lineptr, n, '\n', stream);
}}}


/**
 * Function with same functionality as POSIX.1-2008 getdelim() function, but
 * uses simpler FILE stream checking and does not uses multi-thread lockouts.
 * For more info about functionality just see 'man 3 getline' manual page.
 */
int getdelim(char **lineptr, size_t *n, int delim, FILE *stream)
{{{
  /* Check of given arguments. */
  if (lineptr == NULL || n == NULL || stream == NULL) {
    errno = EINVAL;
    return EOF;
  }

  bool malloc_used = false;       /* Used for detection if '\0' is required. */

  /* Empty buffer? */
  if (*lineptr == NULL || *n <= 0) {
    *n = BUFF_SIZE_DEF;

    *lineptr = (char *) malloc(*n * sizeof(char));
    
    /* Correct allocation? */
    if (*lineptr == NULL) {
      errno = ENOMEM;
      return EOF;
    }

    malloc_used = true;
  }


  size_t i = 0;                           /* Buffer iterator. */
  int c;                                  /* Character read. */

  /*
   * Reads until EOF or given delimiter is encountered.
   */
  while ((c = fgetc(stream)) != EOF && c != delim) {
    
    /* No more space in buffer? */
    if (i == *n && getdelim_resize(lineptr, n) == EXIT_FAILURE) {
      return EOF;                         /* Resizing of buffer failed. */
    }

    (*lineptr)[i++] = (char) c;           /* Character adding. */
  }

  /* Checking upon error of fgetc(). */
  if (errno != 0) {
    return EOF;                           /* Reading of stream failed. */
  }

  
  /* Enough space for storing another characters? */
  if ((i + 1) == *n && getdelim_resize(lineptr, n) == EXIT_FAILURE) {
    return EOF;                           /* Resizing of buffer failed. */
  }


  /* Adding delimiter character to the buffer if it was encountered. */
  if (c == delim) {
    (*lineptr)[i++] = (char) c;
  }
  
  /* If there was reading or memory allocation, then adds '\0' so allocated
   * memory for the string is properly ended. */
  if (i > 0 || malloc_used == true) {
    (*lineptr)[i] = '\0';
  }

  
  /*
   * Returns number of characters read or EOF if the reading of the stream has
   * come to the end.
   */
  return (c != EOF) ? (int) i : EOF;  
}}}


/******************************************************************************
 ~~~[ SUBSIDIARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Function used for resizing of given buffer. Returns EXIT_FAILURE if
 * reallocation have failed and the given pointer stays unchanged. Otherwise the
 * given buffer is extended and lineptr and buffer size n is changed
 * appropriately.
 */
static inline int getdelim_resize(char **lineptr, size_t *n)
{{{
  char *lineptr_backup;

  lineptr_backup = *lineptr;    /* Backup in case realloc fails. */
  *n *= BUFF_SIZE_MULT;         /* Buffer size extending. */

  /* Buffer extending. */
  *lineptr = (char *) realloc(*lineptr, *n * sizeof(char));

  /* Reallocation testing. */
  if (*lineptr == NULL) {
    *lineptr = lineptr_backup;
    errno = ENOMEM;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}}}


/******************************************************************************
 ~~~[ SELF-TESTING PART ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Some primitive unit testing - reads the file of given filename and prints it
 * to stdout.
 */
#ifdef GETLINE_DEBUG

int main(int argc, char *argv[])
{{{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;

  errno = 0;

  if (argc != 2) {
    fprintf(stderr, "getline: error: No input file specified\n");
    return EXIT_FAILURE;
  }
  else if ((fp = fopen(argv[1], "r")) == NULL) {
    perror("getline: error");
    return EXIT_FAILURE;
  }

  /* Reading the given file line by line and printing it immediately. */
  while (getline(&line, &len, fp) != EOF) {
    printf("%s", line);
  }

  /* Test upon error of getline. */
  if (errno != 0) {
    perror("getline: error");
    free(line);
    return EXIT_FAILURE;
  }

  free(line);
  fclose(fp);
  return EXIT_SUCCESS;
}}}

#endif


/******************************************************************************
 ***[ END OF GETLINE.C ]*******************************************************
 ******************************************************************************/

#endif
 
