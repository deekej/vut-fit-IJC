/**
 * File:          htable_foreach.c
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
 * Description:   Module containing callback functions caller function for every
 *                item of the hash table.
 *
 * More info @:   http://www.fit.vutbr.cz/study/courses/IJC/public/DU2.html
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF HTABLE_FOREACH.C ]**********************************************
 ******************************************************************************/


/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <stdlib.h>

#include "htable.h"


/******************************************************************************
 ~~~[ PRIMARY FUNCTION ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Calls given function for every item of given hash table.
 */
void htable_foreach(TS_htable_t *t, void (*p_func)(TS_htable_listitem *item))
{{{
  TS_htable_listitem *p_item;         /* Helpful pointer. */

  /* Goes through every item of the hash table. */
  for (unsigned i = 0; i < t->htable_size; i++) {
    p_item = t->list[i];              /* Assign of actual linked list. */

    /* Goes through the linked list, if it exists. */
    while (p_item != NULL) {
      p_func(p_item);                 /* Calling the callback function. */
      p_item = p_item->next;          /* Accessing next item. */
    }
  }

  return;
}}}


/******************************************************************************
 ***[ END OF HTABLE_FOREACH.C ]************************************************
 ******************************************************************************/
 
