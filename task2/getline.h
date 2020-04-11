/**
 * File:          getline.h
 * Version:       1.1.0.1
 * Date:          03-04-2012
 * Last update:   09-04-2012
 *
 * Course:        IJC (summer semester, 2012)
 * Project:       DU1 (Homework #2), part 2)
 *
 * Author:        David Kaspar (aka Dee'Kej), 1BIT
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies
 * E-mail:        xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   This is header provides functional prototypes for getline()
 *                and getdelim() functions same as <stdio.h> do, but only when
 *                no GNU extension of ISO/IEC 9899:1999 C standard is used.
 *
 * More info @:   https://www.fit.vutbr.cz/study/courses/IJC/public/DU1.html.cs
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/*
 * Conditional translation. Content of this module is only used when no GNU
 * extension of C language standard is used.
 */
#if !defined _GNU_SOURCE && _POSIX_C_SOURCE < 200809L && _XOPEN_SOURCE < 700


/******************************************************************************
 ***[ START OF GETLINE.H ]*****************************************************
 ******************************************************************************/

/* Safety mechanism against multi-including of this header file. */
#ifndef GETLINE_H
#define GETLINE_H


/******************************************************************************
 ~~~[ GLOBAL FUNCTIONAL PROTOTYPES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

int getline(char **lineptr, size_t *n, FILE *stream);
int getdelim(char **lineptr, size_t *n, int delim, FILE *stream);


/******************************************************************************
 ***[ END OF GETLINE.H ]*******************************************************
 ******************************************************************************/

#endif      /* End of GETLINE_H definition. */
#endif      /* End of conditional translation, see overhead comment. */

