/**
 * File:          wordcount.c
 * Version:       1.0
 * Date:          24-04-2012
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
 * Description:   Program for counting of read words from stdin using hash
 *                table. Output is printed to stdout.
 *
 * More info @:   http://www.fit.vutbr.cz/study/courses/IJC/public/DU2.html
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF HTABLE_LOOKUP.C ]***********************************************
 ******************************************************************************/


/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "htable.h"
#include "io.h"


/******************************************************************************
 ~~~[ GLOBAL CONSTANTS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/* Default buffer size for fgetword() function. */
#define BUFFER_SIZE 256U

/*
 * Default size of hash table. I've chosen this value because in my opinion it
 * suits the needs of this "testing" program (homeworks) and it's still enough
 * for good spread of hashes. And if you need better hashing spread, you can
 * always increase this value as you want.
 */
#define HTABLE_SIZE 1024U


/******************************************************************************
 ~~~[ FUNCTIONAL PROTOTYPES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

void print_count(TS_htable_listitem *p_item);


/******************************************************************************
 ~~~[ PRIMARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Callback function for printing content of one item of hash table.
 */
void print_count(TS_htable_listitem *p_item)
{{{
  fprintf(stdout, "%s\t%u\n", p_item->key, p_item->data);
  return;
}}}


/******************************************************************************
 ~~~[ MAIN FUNCTION ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

int main(void)
{{{
  char buffer[BUFFER_SIZE] = "";                    /* Buffer creating. */
  bool long_word = false;                           /* Sign of too long word. */

  TS_htable_t *table = htable_init(HTABLE_SIZE);    /* Hash table creation. */

  errno = 0;                        /* Reseting errno for error detection. */


  /* Reads every word until error occurs or EOF is reached. */
  while (fgetword(buffer, BUFFER_SIZE, stdin) != EOF) {

    if (errno == ENOBUFS) {
      long_word = true;             /* Word bigger than buffer detected. */
    }

    if (htable_lookup(table, buffer) == NULL) {
      break;                        /* Allocation failed. */
    }
  }


  /* Warning in case of a too much long word. */
  if (long_word == true) {
    fprintf(stderr, "wordcount: warning: some of the words exceeding the buffer"
                    " size have been reduced\n");
  }
  
  /* 
   * Error warning printing upon error. Warning for ENOBUFS is being printed
   * above.
   */
  if (errno != 0 && errno != ENOBUFS) {
    perror("wordcount: error");
  }

  
  /*
   * Printing the content of hash table if no error or too much long word
   * occurred.
   */
  if (errno == 0 || errno == ENOBUFS) {
    htable_foreach(table, print_count);
  }

  htable_free(table);                 /* Hash table freeing. */

  return (errno != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}}}


/******************************************************************************
 ***[ END OF HTABLE_LOOKUP.C ]*************************************************
 ******************************************************************************/
 
