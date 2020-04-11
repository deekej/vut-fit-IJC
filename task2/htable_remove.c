/**
 * File:          htable_remove.c
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
 * Description:   Module containing function for removing the whole one item
 *                (record) from hash table.
 *
 * More info @:   http://www.fit.vutbr.cz/study/courses/IJC/public/DU2.html
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF HTABLE_REMOVE.C ]***********************************************
 ******************************************************************************/


/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "htable.h"


/******************************************************************************
 ~~~[ PRIMARY FUNCTION ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Removes one given item (record) from given hash table. 
 */
void htable_remove(TS_htable_t *t, const char *key)
{{{
  unsigned hash_index = hash_function(key, t->htable_size);   /* Table index. */
  TS_htable_listitem *p_item, *p_item_bef;  /* Helpful pointers. */

  p_item = t->list[hash_index];             /* Accessing linked list. */
  p_item_bef = p_item;                      /* Init. for testing below. */

  int cmp_retval = -1;                      /* Return value of strcmp(). */

  
  /*
   * Goes through linked list until given key is found or end of list reached.
   */
  while (p_item != NULL && (cmp_retval = strcmp(key, p_item->key)) != 0) {
    p_item_bef = p_item;                    /* Backup of actual pointer. */
    p_item = p_item->next;                  /* Accessing next item. */
  }

  
  /* Test if the key was found. */
  if (cmp_retval == 0) {

    /* Is the item with the key found on the 1st position within the list? */
    if (p_item_bef == p_item) {
      t->list[hash_index] = p_item->next;   /* Excluding from list's start. */
      free((void *) p_item);
    }
    else {
      p_item_bef->next = p_item->next;      /* Excluding item to delete. */
      free((void *) p_item);
    }
  }

  return;
}}}

/******************************************************************************
 ***[ END OF HTABLE_REMOVE.C ]*************************************************
 ******************************************************************************/
 
