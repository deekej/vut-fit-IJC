/**
 * File:          htable_clear.c
 * Version:       1.0
 * Date:          22-04-2012
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
 * Description:   Module containing function for removing (clearing) the whole
 *                content of hash table, but not the hash table itself.
 *
 * More info @:   http://www.fit.vutbr.cz/study/courses/IJC/public/DU2.html
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF HTABLE_CLEAR.C ]************************************************
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
 * Removes (clears) whole content of hash table (all items), but not the table
 * itself. After clearing the table is in state as it was after calling
 * htable_init() function.
 */
void htable_clear(TS_htable_t *t)
{{{
  TS_htable_listitem *p_item, *p_item_next;       /* Helpful pointers. */

  /*
   * Goes through the hash table and removes the actual linked list, if it
   * exists.
   */
  for (unsigned i = 0; i < t->htable_size; i++) {
    p_item = t->list[i];                          /* New initialization. */
    
    /* Removing of linked list, if it exists. */
    while (p_item != NULL) {
      p_item_next = p_item->next;                 /* Backup of next item. */
      free((void *) p_item);                      /* Item removing. */
      p_item = p_item_next;                       /* New item to restore. */
    }

    t->list[i] = NULL;                        /* Reseting hash table pointer. */
  }

  return;
}}}

/******************************************************************************
 ***[ END OF HTABLE_CLEAR.C ]**************************************************
 ******************************************************************************/

