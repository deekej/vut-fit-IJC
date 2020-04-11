/**
 * File:          error.h
 * Version:       1.01 Final
 * Date:          03-03-2012
 * Last update:   03-03-2012
 *
 * Course:        IJC (summer semester, 2012)
 * Project:       DU1 (Homework #1), part a) & b)
 *
 * Author:        David Kaspar (aka Dee'Kej), 1BIT
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies
 * E-mail:        xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   Header file for error.c module. See the functions description
 *                in error.c module.
 *
 * More info @:   https://www.fit.vutbr.cz/study/courses/IJC/public/DU1.html.cs
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF ERROR.H ]*******************************************************
 ******************************************************************************/

/* Safety mechanism against multi-including of this header file. */
#ifndef ERROR_H
#define ERROR_H


/******************************************************************************
 ~~~[ FUNCTIONAL PROTOTYPES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

void Error(const char *fmt, ...);
void FatalError(const char *fmt, ...);


/******************************************************************************
 ***[ END OF ERROR.H ]*********************************************************
 ******************************************************************************/

#endif
 
