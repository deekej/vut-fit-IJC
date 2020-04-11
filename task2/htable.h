/**
 * File:          htable.h
 * Version:       1.0
 * Date:          12-04-2012
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
 * Description:   Header file for defining API of libhtable library.
 *
 * More info @:   http://www.fit.vutbr.cz/study/courses/IJC/public/DU2.html
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF HTABLE.H ]******************************************************
 ******************************************************************************/

/* Safety mechanism against multi-including of this header file. */
#ifndef HTABLE_H
#define HTABLE_H


/******************************************************************************
 ~~~[ GLOBAL DATA TYPES DECLARATIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/* Item (node) of linked list used inside of the hash table. */
typedef struct htable_listitem {
  struct htable_listitem *next;         /* Pointer to next item. */
  unsigned data;                        /* Count of the word seen so far.  */
  char key[];                           /* Word. */
} TS_htable_listitem;


/* Wrapping structure for the hash table. */
typedef struct htable_t {
  unsigned htable_size;                 /* Hash table size. */
  TS_htable_listitem *list[];           /* Hash table. */
} TS_htable_t;


/******************************************************************************
 ~~~[ GLOBAL FUNCTIONAL PROTOTYPE ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

unsigned hash_function(const char *str, unsigned htable_size);

TS_htable_t *htable_init(unsigned size);
TS_htable_listitem *htable_lookup(TS_htable_t *t, const char *key);
void htable_foreach(TS_htable_t *t, void (*p_func)(TS_htable_listitem *item));
void htable_remove(TS_htable_t *t, const char *key);
void htable_clear(TS_htable_t *t);
void htable_free(TS_htable_t *t);


/******************************************************************************
 ***[ END OF HTABLE.H ]********************************************************
 ******************************************************************************/

#endif
 
