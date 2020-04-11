/**
 * File:          io.h
 * Version:       1.0
 * Date:          11-04-2012
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
 * Description:   This header file provides functional prototypes for functions
 *                defined in io.c module.
 *
 * More info @:   https://www.fit.vutbr.cz/study/courses/IJC/public/DU1.html.cs
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF IO.H ]**********************************************************
 ******************************************************************************/

/* Safety mechanism against multi-including of this header file. */
#ifndef IO_H
#define IO_H


/******************************************************************************
 ~~~[ GLOBAL FUNCTIONAL PROTOTYPES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

int fgetword(char *str, int max, FILE *fp);


/******************************************************************************
 ***[ END OF IO.H ]************************************************************
 ******************************************************************************/

#endif
 
