/**
 * File:          steg-decode.c
 * Version:       1.0 Final
 * Date:          14-03-2012
 * Last update:   16-03-2012
 *
 * Course:        IJC (summer semester, 2012)
 * Project:       DU1 (Homework #1), part b)
 *
 * Author:        David Kaspar (aka Dee'Kej), 1BIT
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies
 * E-mail:        xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   Program for decoding hidden text inside the PPM P6 picture.
 *                For more info see the algorithm description below.
 *
 * More info @:   https://www.fit.vutbr.cz/study/courses/IJC/public/DU1.html.cs
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF STEG-DECODE.C ]*************************************************
 ******************************************************************************/


/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bit-array.h"
#include "eratosthenes.h"
#include "ppm.h"


/******************************************************************************
 ~~~[ FUNCTIONAL PROTOTYPES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

void ppm_msg_decode(const char data[]);


/******************************************************************************
 ~~~[ PRIMARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Decodes the data of given PPM P6 file and prints the message hidden inside
 * it. The key for decoding of the message are the prime numbers. Each byte
 * "marked" with the prime number is taken and masked for the LSB. This masked
 * bit is then set inside the variable for printing, starting with LSB. Each
 * next bit is then set to next position respectively. Once the character is
 * decoded, it is printed to stdout. The Sieve of Eratosthenes is used for
 * generating of prime numbers.
 */
void ppm_msg_decode(const char data[])
{{{
  BitArray(eratosth, MAX_IMG_RES);    /* Creation of necessary bit-array. */
  Eratosthenes(eratosth);             /* Prime numbers gain. */

  int c = 0;                          /* Character to print. */
  int bit_pos = 0;                    /* Actual position. */
  unsigned long bit;                  /* Returned bit value. */

  /*
   * Getting bytes with the prime number index.
   */
  for (unsigned long i = 2; i <= BitArraySize(eratosth); i++) {

    /* Is actual index the prime number? */
    if (GetBit(eratosth, i) == 0) {
      bit = DU1_GET_BIT((&data[i]), 0);   /* Get LSB from indexed char. */
      DU1_SET_BIT((&c), bit_pos, bit);    /* Set this bit on actual position. */

      /* Not finished decoding of 1 character? */
      if (bit_pos < CHAR_BIT - 1) {
        bit_pos++;
      }
      /* Not finished yet? */
      else if (c != '\0') {
        fputc(c, stdout);                 /* Print decoded character. */
        bit_pos = 0;                      /* Position reseting. */
        c = 0;                            /* Character reseting. */
      }
      else {
        break;                            /* Decoding finished. */
      }
    }
  }

  fputc('\n', stdout);
  return;
}}}


/******************************************************************************
 ~~~[ MAIN FUNCTION ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

int main(int argc, char *argv[])
{{{
  switch (argc) {
    case 0 :
      /* THIS SHOULD NEVER OCCUR!!! */
      FatalError("Doslo k fatalnimu selhani.\n");
      break;

    case 1 :
      /* No argument used when calling of the program was performed. */
      FatalError("Ocekavan obrazek formatu PPM P6.\n");
      break;

    case 2 :
      /* One program argument has been used. Proceed. */
      break;

    default :
      /* More than one argument for the program has been used. */
      FatalError("Prekrocen pocet vstupnich souboru.\n");
      break;
  }

  struct ppm *p = ppm_read(argv[1]);  /* Reading content of given file. */

  /* Some error occurred. Stopping program. */
  if (p == NULL) {
    FatalError("Doslo k chybe, program ukoncen.\n");
  }

  /* Decoding & printing of message hidden in the picture. */
  ppm_msg_decode(p->data);
  
  free((void *) p);     /* Allocated memory freeing. */
  p = NULL;             /* Pointer "reseting". */
  
  return EXIT_SUCCESS;  /* Everything went fine. */
}}}


/******************************************************************************
 ***[ END OF STEG-DECODE.C ]***************************************************
 ******************************************************************************/
 
