/**
 * File:          htable_init.c
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
 * Description:   Module containing function for creating and initialization of 
 *                hash table.
 *
 * More info @:   http://www.fit.vutbr.cz/study/courses/IJC/public/DU2.html
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF HTABLE_INIT.C ]*************************************************
 ******************************************************************************/


/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "htable.h"


/******************************************************************************
 ~~~[ PRIMARY FUNCTION ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Creates and initializes structure containing the hash table of given size.
 * Returns pointer to the created hash table structure. In case of failure
 * returns NULL and sets errno.
 */
TS_htable_t *htable_init(unsigned size)
{{{
  TS_htable_t *p_htable;              /* Pointer to be returned. */

  p_htable = (TS_htable_t *) malloc(sizeof(TS_htable_t) +
                                    size * sizeof(TS_htable_listitem *));
  
  /* Successful allocation? */
  if (p_htable == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  p_htable->htable_size = size;       /* Setting of size information. */

  /*
   * Can speed up creation in case of very big size of hash table. However, NULL
   * pointer must be equal to 0x0, so it's HW dependent.
   */
  if (NULL == 0x0) {
    memset(p_htable->list, 0x0, size * sizeof(TS_htable_listitem *));
  }
  else {
    for (unsigned i = 0; i < size; i++) {
      p_htable->list[i] = NULL;
    }
  }

  return p_htable;                    /* Return of pointer to table. */
}}}


/******************************************************************************
 ***[ END OF HTABLE_INIT.C ]***************************************************
 ******************************************************************************/
 
