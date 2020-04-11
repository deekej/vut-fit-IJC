/**
 * File:          bit-array.h
 * Version:       1.1 Final
 * Date:          04-03-2012
 * Last update:   17-03-2012
 *
 * Course:        IJC (summer semester, 2012)
 * Project:       DU1 (Homework #1), part a) & b)
 *
 * Author:        David Kaspar (aka Dee'Kej), 1BIT
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies
 * E-mail:        xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   This header file contains macro definitions for work with bit
 *                arrays. It also contains inline functions which can be used
 *                instead of these macros with the same effect. To use these
 *                inline functions, pass the USE_INLINE definition to compiler.
 *                (gcc -DUSE_INLINE)
 *
 * More info @:   https://www.fit.vutbr.cz/study/courses/IJC/public/DU1.html.cs
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF BIT-ARRAY.H ]***************************************************
 ******************************************************************************/

/* Safety mechanism against multi-including of this header file. */
#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H


/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <limits.h>
#include <string.h>

#include "error.h"


/******************************************************************************
 ~~~[ GLOBAL CONSTANTS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/*
 * Number of bits that WORD of actual HW has. Used for array creation, so it has
 * to be hard constant.
 */
#define ULONG_BITS (sizeof(unsigned long) * CHAR_BIT)


/******************************************************************************
 ~~~[ GLOBAL DATA TYPES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/* Type of bit-array so it can be easily pass to an inline function. */
typedef unsigned long BitArray_t[];


/******************************************************************************
 ~~~[ SUBSIDIARY MACROS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Computes necessary size of bit array of unsigned long integers with
 * consideration, that the first member of the array contains the bit size of
 * rest of the array.
 */
#define array_size(bit_size)                                                   \
  ((bit_size) % ULONG_BITS > 0) ?                                              \
  (((bit_size) / ULONG_BITS) + 2) : (((bit_size) / ULONG_BITS) + 1)


/* Conditional assembly for compilation. ------------------------------------ */
#ifndef USE_INLINE


/**
 * Macro that calls FatalError() function in case of index is out of bounds.
 */
#define out_of_index(array_name, index)                                        \
  FatalError("Index %ld mimo rozsah 0..%ld\n", (long)(index), (long)array_name[0])


/**
 * Computes position of proper unsigned long integer inside the array which
 * contains wanted bit, correspondingly to the given index.
 */
#define array_pos(index)                                                       \
  (((index) / ULONG_BITS) + 1)


/* End of conditional assembly of this part. -------------------------------- */
#endif


/**
 * Helpful macro that computes the size of array member of given bit array for
 * DU1 macros.
 */
#define DU1_type_size(array_name)                                              \
  (sizeof(*array_name) * CHAR_BIT)


/**
 * Macro with same functionality as array_pos() macro above, but edited to suit
 * the needs of DU1 macros. 
 */
#define DU1_pos(array_name, index)                                             \
  ((index) / DU1_type_size(array_name)) 


/******************************************************************************
 ~~~[ GLOBAL UNSIGNED LONG MACROS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Defines the bit-array of given size. The unsigned long members of the array
 * are set to zero, the first member contains maximal possible index of array.
 */
#define BitArray(array_name, bit_size)                                         \
  unsigned long array_name[array_size(bit_size)] = {(bit_size) - 1, 0}


/* Conditional assembly for compilation. ------------------------------------ */
#ifndef USE_INLINE


/**
 * Returns the bit-size of given bit array.
 */
#define BitArraySize(array_name)                                               \
  array_name[0]


/**
 * Sets the bit of given index (of given bit-array) to 0, if given expression
 * was 0 or to 1, if given expression was non-zero. It also controls first that
 * the given index is inside bounds of given array. If not, then it calls the
 * FatalError() function.
 */
#define SetBit(array_name, index, expr)                                        \
  do {                                                                         \
    if ((index) > BitArraySize(array_name))                                    \
      out_of_index(array_name, index);                                         \
                                                                               \
    /* Setting the proper bit. */                                              \
    if ((expr) != 0)                                                           \
      array_name[array_pos(index)] |=  (1LU << ((index) % ULONG_BITS));        \
    else                                                                       \
      array_name[array_pos(index)] &= ~(1LU << ((index) % ULONG_BITS));        \
  } while (0)


/**
 * Returns zero if the bit of given index (of given bit-array) is zero or
 * non-zero value if the bit is 1. Also controls the bounds as the SetBit()
 * macro above.
 */
#define GetBit(array_name, index)                                              \
  (((index) > BitArraySize(array_name)) ? out_of_index(array_name, index), 0 : \
  array_name[array_pos(index)] & (1LU << ((index) % ULONG_BITS)))


/* End of conditional assembly of this part. -------------------------------- */
#endif


/******************************************************************************
 ~~~[ GLOBAL GENERAL MACROS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Macro with same functionality as SetBit() macro above, however without bounds
 * control. It also works with bit-array of any data type, not just unsigned
 * long.
 */
#define DU1_SET_BIT(array_name, index, expr)                                   \
  do {                                                                         \
    if ((expr) != 0)                                                           \
      array_name[DU1_pos(array_name, index)] |=  (1LU << ((index) % DU1_type_size(array_name))); \
    else                                                                       \
      array_name[DU1_pos(array_name, index)] &= ~(1LU << ((index) % DU1_type_size(array_name))); \
  } while (0)


/**
 * Same functionality as GetBit() macro above, but without bounds control. Also
 * works with bit-array of any data type, not just unsigned long.
 */
#define DU1_GET_BIT(array_name, index)                                         \
  (array_name[DU1_pos(array_name, index)] & (1LU << ((index) % DU1_type_size(array_name))))


/* Conditional assembly for compilation. ------------------------------------ */
#ifdef USE_INLINE


/******************************************************************************
 ~~~[ FUNCTIONAL PROTOTYPES OF INLINE FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

static inline unsigned long BitArraySize(BitArray_t array_name);
static inline unsigned long GetBit(BitArray_t array_name, unsigned long index);
static inline void SetBit(BitArray_t array_name, unsigned long index,
                   unsigned long expr);


/******************************************************************************
 ~~~[ GLOBAL INLINE FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Inline function which can substitute the BitArraySize macro defined above.
 */
static inline unsigned long BitArraySize(BitArray_t array_name)
{{{
  return array_name[0];
}}}


/**
 * Inline function with same functionality as SetBit macro defined above.
 */
static inline void SetBit(BitArray_t array_name, unsigned long index,
                   unsigned long expr)
{{{
  /* Bounds control of given index. */
  if (index > array_name[0]) {
    FatalError("Index %ld mimo rozsah 0..%ld\n", (long)index,
               (long)array_name[0]);
  }
  
  /* Helpful variable to access corresponding unsigned long in given array. */
  unsigned long array_pos = (index / ULONG_BITS) + 1;
  
  /* Setting the proper bit. */
  if (expr != 0)
    array_name[array_pos] |=  ((unsigned long)1 << (index % ULONG_BITS));
  else
    array_name[array_pos] &= ~((unsigned long)1 << (index % ULONG_BITS));

  return;
}}}


/**
 * Inline function with same functionality as GetBit macro defined above.
 */
static inline unsigned long GetBit(BitArray_t array_name, unsigned long index)
{{{
  /* Bounds control of given index. */
  if (index > array_name[0]) {
    FatalError("Index %ld mimo rozsah 0..%ld\n", (long)index,
               (long)array_name[0]);
  }

  /* Helpful variable to access corresponding unsigned long in given array. */
  unsigned long array_pos = (index / ULONG_BITS) + 1;

  /* Get the bit value. */
  return array_name[array_pos] & ((unsigned long)1 << (index % ULONG_BITS));  
}}}


/* End of conditional assembly of this part. -------------------------------- */
#endif


/******************************************************************************
 ***[ END OF BIT-ARRAY.H ]*****************************************************
 ******************************************************************************/

#endif
  
