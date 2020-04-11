/**
 * File:          ppm.c
 * Version:       1.0 Final
 * Date:          13-03-2012
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
 * Description:   This module provides functions for reading and writing the PPM
 *                P6 picture format.
 *
 * More info @:   https://www.fit.vutbr.cz/study/courses/IJC/public/DU1.html.cs
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF PPM.C ]*********************************************************
 ******************************************************************************/


/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "ppm.h"

/******************************************************************************
 ~~~[ PRIMARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Reads the content of PPM P6 picture file of given filename and stores its
 * content into ppm structure. Function returns pointer to this structure or
 * NULL in case of any failure. (Only 255 color value is allowed.)
 */
struct ppm *ppm_read(const char *filename)
{{{
  FILE *f_rb;                 /* File to read. */

  /* Opening file for binary reading. */
  if ((f_rb = fopen(filename, "rb")) == NULL) {
    Error("Nepodarilo se otevrit soubor pro cteni: %s\n", filename);
    return NULL;
  }


  char ppm_magic_num[3];      /* String for P6 magic file number. */
  unsigned f_xsize, f_ysize;  /* X & Y pixel size of the picture. */
  unsigned f_max_color;       /* Maximal possible color value of pixel. */
  
  /* Reading magic number and header of the file. */
  if (fscanf(f_rb, "%2s %u %u %u%*c", ppm_magic_num, &f_xsize, &f_ysize,
             &f_max_color) != 4) {
    Error("Nepodarilo se nacist hlavicku souboru: %s\n", filename);
    fclose(f_rb);
    return NULL;
  }
  /* Testing file's magic number. */
  else if ((ppm_magic_num[0] != 'P') || (ppm_magic_num[1] != '6')) {
    Error("Nepodporovany format souboru: %s\n", filename);
    fclose(f_rb);
    return NULL;
  }
  /* Testing maximal possible color value. */
  else if (f_max_color != 255) {
    Error("Nepodporovana barevna hloubka obrazku: %s\n", filename);
    fclose(f_rb);
    return NULL;
  }

 
  /* Actual size of picture's data part. */ 
  unsigned data_size = 3 * sizeof(char) * f_xsize * f_ysize;
  
  /* Is size of data big too much? */
  if (data_size > MAX_IMG_SIZE) {
    Error("Prilis velka velikost obrazku: %s\n", filename);
    fclose(f_rb);
    return NULL;
  }


  struct ppm *p = NULL;       /* Structure pointer to return. */

  /* Memory allocation for all data needed. */
  if ((p = (struct ppm *) malloc(sizeof(struct ppm) + data_size)) == NULL) {
    Error("Alokace pameti selhala.\n");
    fclose(f_rb);
    return NULL;
  }

  /* Storing pictures size in the structure. */
  p->xsize = f_xsize;
  p->ysize = f_ysize;

  /* Reading the raw data. */
  if (fread(&p->data, sizeof(char), data_size, f_rb) != data_size) {
    Error("Nepodarilo se nacist obsah obrazku: %s\n", filename);
    free((void *) p);
    fclose(f_rb);
    return NULL;
  }

  
  /* Test if any error occurred during the raw data reading. */
 if (ferror(f_rb) != 0) {
    Error("Selhalo cteni dat obrazku: %s\n", filename);
    free((void *) p);
    fclose(f_rb);
    return NULL;
  }
  /* Test for expected end-of-file. */
  else if (fgetc(f_rb) != EOF) {
    Error("Velikost dat neodpovida hlavicce obrazku: %s\n", filename);
    free((void *) p);
    fclose(f_rb);
    return NULL;
  }

  
  fclose(f_rb);               /* File no more needed. */
  return p;                   /* Everything went fine. */
}}}


int ppm_write(struct ppm *p, const char *filename)
{{{
  FILE *f_wb;

  /* Opening file for binary writing. */
  if ((f_wb = fopen(filename, "wb")) == NULL) {
    Error("Nepodarilo se otevrit soubor pro zapis: %s\n", filename);
    return EOF;
  }

  if (fprintf(f_wb, "P6\n%u %u\n255\n", p->xsize, p->ysize) < 0) {
    Error("Nepodarilo se zapsat hlavicku obrazku: %s\n", filename);
    fclose(f_wb);
    return EOF;
  }

  /* Actual size of picture's data part. */ 
  unsigned data_size = 3 * sizeof(char) * p->xsize * p->ysize;

  if (fwrite(p->data, sizeof(char), data_size, f_wb) != data_size) {
    Error("Selhal zapis obrazku do souboru: %s\n", filename);
    fclose(f_wb);
    return EOF;
  }
  
  fclose(f_wb);
  return 0;
}}}

/******************************************************************************
 ~~~[ SELF-TESTING PART ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/* Conditional translation if -DPPM_DEBUG parameter was used. */
#ifdef PPM_DEBUG

int main (int argc, char *argv[])
{{{
  if (argc != 2) {
    fprintf(stderr, "Please, provide 1 PPM P6 picture file. Terminating...\n");
    return EXIT_FAILURE;
  }

  printf("This testing will duplicate given PPM P6 picture file into "
         "image_copy.ppm file.\n");

  struct ppm *p = ppm_read(argv[1]);

  if (p == NULL) {
    fprintf(stderr, "An error occurred, terminating...\n");
    return EXIT_FAILURE;
  }

  if (ppm_write(p, "image_copy.ppm") < 0) {
    fprintf(stderr, "An error occurred, terminating...\n");
    free((void *) p);
    p = NULL;
    return EXIT_FAILURE;
  }

  free((void *) p);
  p = NULL;

  return EXIT_SUCCESS;
}}}

#endif            /* End of conditional translation. */


/******************************************************************************
 ***[ END OF PPM.C ]***********************************************************
 ******************************************************************************/
 
