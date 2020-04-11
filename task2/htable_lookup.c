/**
 * File:          htable_lookup.c
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
 * Description:   Module containing function for key looking inside the hash
 *                table. See function description for more information.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htable.h"


/******************************************************************************
 ~~~[ FUNCTIONAL PROTOTYPES OF AUXILIARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

static inline TS_htable_listitem *htable_create_item(const char *key);


/******************************************************************************
 ~~~[ PRIMARY FUNCTION ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Checks if the given key is located inside given hash table. If not, then
 * creates the item containing the given key. Returns pointer to the item or
 * NULL upon failure. Since these instructions, it is logical that in case the
 * key is found within the given hash table, this function automatically
 * increases the read key count. Also errno is set upon error.
 */
TS_htable_listitem *htable_lookup(TS_htable_t *t, const char *key)
{{{
  /* Index to the hash table to be used below. */
  unsigned hash_index = hash_function(key, t->htable_size);

  /* Helpful pointer initialization. */
  TS_htable_listitem *p_item = t->list[hash_index];

  /*
   * Creates new item and adds it to the hash table in case there's nothing yet.
   */
  if (p_item == NULL) {
    p_item = htable_create_item(key);           /* Item creating. */
    t->list[hash_index] = p_item;               /* Item adding. */
    return p_item;                              /* Item address return. */
  }

  /* Helpful pointer of item before. */
  TS_htable_listitem *p_item_bef = NULL;
  int cmp_retval = -1;                          /* Return value of strcmp(). */

  
  /*
   * Goes through the actual linked list until the key is found or end of list
   * reached.
   */
  while (p_item != NULL && (cmp_retval = strcmp(key, p_item->key)) != 0) {
    p_item_bef = p_item;                        /* Backup of actual pointer. */
    p_item = p_item->next;                      /* Accessing next item. */
  }

  /* 
   * Increases the counter in case the key was found, otherwise creates new
   * item.
   */
  if (cmp_retval == 0) {
    p_item->data++;
  }
  else {
    p_item = htable_create_item(key);           /* Item creating. */
    p_item_bef->next = p_item;                  /* Linking item in. */
  }

  return p_item;                                /* Item address return. */
}}}


/******************************************************************************
 ~~~[ AUXILIARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Creates new item of linked list of the hast table. Returns pointer to the
 * created item or NULL in case of failure. Also sets errno upon error.
 */
static inline TS_htable_listitem *htable_create_item(const char *key)
{{{
  /* Size of given key in bytes used for allocation and memcpy() below. */
  size_t key_size = sizeof(char) * (strlen(key) + 1);

  TS_htable_listitem *p_item = NULL;      /* Helpful pointer to be returned. */

  p_item = (TS_htable_listitem *) malloc(sizeof(TS_htable_listitem) + key_size);

  /* New item initialization upon successful allocation. */
  if (p_item != NULL) {
    p_item->next = NULL;
    p_item->data = 1;
    memcpy(p_item->key, key, key_size);
  }
  else {
    errno = ENOMEM;
  }

  return p_item;                          /* Return of result. */
}}}


/******************************************************************************
 ***[ END OF HTABLE_LOOKUP.C ]*************************************************
 ******************************************************************************/
 
