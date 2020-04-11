/**
 * File:          ppm.h
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
 * Description:   This is header provides functional prototypes and data global
 *                data declarations for ppm.c file.
 *
 * More info @:   https://www.fit.vutbr.cz/study/courses/IJC/public/DU1.html.cs
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF PPM.H ]*********************************************************
 ******************************************************************************/

/* Safety mechanism against multi-including of this header file. */
#ifndef PPM_H
#define PPM_H


/******************************************************************************
 ~~~[ GLOBAL CONSTANTS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/*
 * Maximal supported resolution of the ppm.c. You should increase the stack
 * size if you increase this resolution, otherwise it is likely that
 * Segmentation fault will occur. Actual resolution is able to work with default
 * Linux stack size of 8192 kbytes.
 */
#define MAX_IMG_RES 4096 * 4096

/* Every pixel consists of 3 bytes (0..255) representing its color in RGB. */
#define MAX_IMG_SIZE 3 * MAX_IMG_RES


/******************************************************************************
 ~~~[ GLOBAL DATA TYPES DECLARATIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/* Structure for storing read PPM P6 picture file. */
struct ppm {
  unsigned xsize;             /* Number of pixels of x axis. */
  unsigned ysize;             /* Number of pixels of y axis. */
  char data[];                /* Pictures raw data. */
};


/******************************************************************************
 ~~~[ GLOBAL FUNCTIONAL PROTOTYPE ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

struct ppm *ppm_read(const char *filename);
int ppm_write(struct ppm *p, const char *filename);


/******************************************************************************
 ***[ END OF PPM.H ]***********************************************************
 ******************************************************************************/

#endif
 
