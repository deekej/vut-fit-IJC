/**
 * File:          tail.c
 * Version:       1.1
 * Date:          29-03-2012
 * Last update:   10-04-2012
 *
 * Course:        IJC (summer semester, 2012)
 * Project:       DU1 (Homework #2), part a)
 *
 * Author:        David Kaspar (aka Dee'Kej), 1BIT
 * Faculty:       Faculty of Information Technologies,
 *                Brno University of Technologies
 * E-mail:        xkaspa34@stud.fit.vutbr.cz
 *
 * Description:   Simple rewrite of POSIX utility 'tail' with basic
 *                functionality. See the help of this program for more info.
 *
 * More info @:   http://www.fit.vutbr.cz/study/courses/IJC/public/DU2.html
 *
 * File encoding: en_US.utf8 (United States)
 * Compiler used: gcc 4.5.2 (Ubuntu/Linaro 4.5.2-8ubuntu4)
 */


/******************************************************************************
 ***[ START OF TAIL.C ]********************************************************
 ******************************************************************************/


/******************************************************************************
 ~~~[ HEADER FILES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/
// {{{
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getline.h"
// }}};

/******************************************************************************
 ~~~[ GLOBAL CONSTANTS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

const unsigned long LL2P_DEF = 10;    /* Last lines to be printed by default. */


/******************************************************************************
 ~~~[ DATA TYPES DECLARATIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/
// {{{
/* Enumerate representing which operation will be done upon option given. */
typedef enum {
  HELP = -1,                    /* Displaying help. */
  STANDARD = 0,                 /* Printing last n lines. */
  FROM_LINE = 1,                /* Printing all from nth line.*/

} TE_option;


/* Structure containing information about processed arguments of program. */
typedef struct arguments {
  TE_option option;             /* Option used. */

  /*
   * Number of lines to print (when option is STANDARD) or starting line of
   * printing (when option is FROM_LINE).
   */
  unsigned long lines;
  const char *p_filename;       /* Name of file to read from. */

} TS_arguments;


/* Structure used to create linked list used as a cyclic buffer. */
typedef struct node {
  size_t buff_size;             /* Buffer size of actual node. */
  char *p_line;                 /* Pointer to the buffer (line). */

  struct node *p_next;          /* Pointer to next node structure. */

} TS_node;
// }}}

/******************************************************************************
 ~~~[ FUNCTIONAL PROTOTYPES ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/
// {{{
void process_args(int argc, char *argv[], TS_arguments *p_arguments);
void display_help(void);

int print_from_line(unsigned long line_num);
int print_last_lines(unsigned long lines);


int flush_all(void);
int last_line(void);
TS_node *line_buffer_make(unsigned long buff_size);
void line_buffer_free(TS_node *p_node);
static inline int fput_str(const char *str, FILE *stream);
// }}}

/******************************************************************************
 ~~~[ PRIMARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Function which processes parameters & arguments of the program. The outcome
 * of processing is stored in the given TS_arguments structure. Function exits
 * if parameters or arguments were incorrect. No return value.
 */
void process_args(int argc, char *argv[], TS_arguments *p_arguments)
{{{
  int i = 1;                  /* Iterator through argv[]. */
  long long int result = 0;   /* Helpful variable for strtoll conversion. */
  char *endptr = NULL;        /* Pointer for strtoll conversion. */

  /*
   * Initialization of given structure for STANDARD behaviour. Can be changed 
   * below.
   */
  p_arguments->p_filename = NULL;
  p_arguments->option = STANDARD;
  p_arguments->lines = LL2P_DEF;

  
  /*
   * Parameter processing. Evaluates every parameter/argument by given
   * conditions.
   */
  while (i < argc) {
  
    /* Processing of optional '-n' argument. */
    if (strcmp("-n", argv[i]) == 0) {

      /* Will not proceed if it would cause Segmentation fault. */
      if ((i + 1) < argc) {
        i++;
        
        /* Leading plus sign of number represents printing from position. */
        if (argv[i][0] == '+') {
          p_arguments->option = FROM_LINE;
        }

        result = strtoll(argv[i], &endptr, 10);

        /* Not valid character found? */
        if (*endptr != '\0') {
          fprintf(stderr, "tail: %s: invalid number of lines\n", argv[i]);
          exit(EXIT_FAILURE);
        }
        /* Number too big? */
        else if (errno == ERANGE) {
          fprintf(stderr, "tail: %s: result value too large\n", argv[i]);
          exit(EXIT_FAILURE);
        }
        /* Value not able to be stored in size_t? */
        else if (result == LLONG_MIN) {
          fprintf(stderr, "tail: %s: value too large to be stored in data "
                          "type\n", argv[i]);
          exit(EXIT_FAILURE);
        }
        /* Negative value is taken as positive. */
        else if (result < 0 && result > LLONG_MIN) {
          result *= -1;
        }
      
        p_arguments->lines = (unsigned long) result;
        i++;    /* Iteration for next unprocessed argument. */
      }
      /* No other argument found after the '-n' parameter. */
      else {
        fprintf(stderr, "tail: option requires an argument -- 'n'\n"
                        "Try `tail --help' for more information.\n");
        exit(EXIT_FAILURE);
      }

    }
    /* Displaying help is required. */
    else if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0) {
      p_arguments->option = HELP;
      return;
    }
    /* First unrecognized argument is taken as a given filename. */
    else if (p_arguments->p_filename == NULL) {
      p_arguments->p_filename = argv[i];
      i++;
    }
    /* Another unrecognized argument is not allowed. */
    else {
      fprintf(stderr, "tail: invalid option -- '%s'\n"
                      "Try `tail --help' for more information.\n", argv[i]);
      exit(EXIT_FAILURE);
    }

  }

  return;   /* Return upon successful processing. */
}}}


/**
 * Program's help page.
 */
void display_help(void)
{{{
  printf("Usage: tail [OPTION] [FILE]\n"
         "Print the last 10 lines of FILE to standard output.\n"
         "With no FILE, read standard input.\n"
         "\n"
         "  -n,           output the last K lines, instead of the last 10;\n"
         "                or use -n +K to output lines starting with the Kth\n"
         "\n"
         "If the first character of K (the number of lines) is a `+',\n"
         "print beginning with the Kth item from the start of file, othewise,\n"
         "print the last K lines in the file.\n"
         "\n"
         "Written by David Kaspar (aka Dee'Kej)\n"
         "Report bugs to deekej.dj@gmail.com\n"
         "Part of IJC course project @ FIT, Brno University of Technology, "
         "2012.\n");
  return;
}}}


/**
 * Prints lines from nth position given by line_num, the first line number is 1.
 * Lines preceding the nth line will be skipped. Returns EXIT_FAILURE and sets
 * errno upon failure, otherwise returns EXIT_SUCCES and errno is set to 0.
 */
int print_from_line(unsigned long line_num)
{{{
  char *line = NULL;            /* Pointer to line buffer for getline(). */
  size_t line_length = 0;       /* Actual size of line buffer. */

  errno = 0;                    /* Reseting errno for error detection. */

  /* Skipping n - 1 lines. */
  for (unsigned long i = 1; i < line_num; i++) {

    if (getline(&line, &line_length, stdin) != EOF) {
      /* Line reading successful, proceed. */
      continue;
    }
    else if (errno != 0) {
      /* Error encountered, free buffer and return. */
      free((void *) line);
      return EXIT_FAILURE;
    }
    else {
      /* Nothing more to read, return. */
      free((void *) line);
      return EXIT_SUCCESS;
    }
  }

  
  /* Reading and printing of remaining lines. */
  while (getline(&line, &line_length, stdin) != EOF) {

    if (fputs(line, stdout) == EOF) {
      /* Printing to stdout failed. */
      free((void *) line);
      return EXIT_FAILURE;
    }
  }

  free((void *) line);
  return (errno != 0) ? EXIT_FAILURE : EXIT_SUCCESS;  /* Error test. */
}}}


/**
 * Prints the given number of last lines of the stream. Same return values as
 * with the print_from_line() function.
 */
int print_last_lines(unsigned long lines)
{{{
  switch (lines) {
    
    /* No output is required. */
    case 0 :
      return flush_all();
      break;

    /* Only last lineis required. */
    case 1 :
      return last_line();
      break;

    /* More than 1 line is required. */
    default :
      break;
  }


  TS_node *p_buffer = line_buffer_make(lines);    /* Cyclic buffer creating. */

  /* Has allocation failed? */
  if (p_buffer == NULL) {
    return EXIT_FAILURE;
  }

  errno = 0;                          /* Reseting errno for error detection. */
  
  /* Reads entire input into cyclic buffer until end-of-file is detected. */
  while (getline(&p_buffer->p_line, &p_buffer->buff_size, stdin) != EOF) {
    p_buffer = p_buffer->p_next;      /* Accesses next node. */
  }

  /* Test if reading was successful or not. */
  if (errno != 0) {
    line_buffer_free(p_buffer);
    return EXIT_FAILURE;
  }
  
  /* Printing content of the buffer. */
  for (unsigned long i = 0; i < lines; i++) {

    /* Prints & tests upon error. */
    if (fput_str(p_buffer->p_line, stdout) == EOF) {
      line_buffer_free(p_buffer);
      return EXIT_FAILURE;
    }
    p_buffer = p_buffer->p_next;      /* Accesses next node. */
  }


  /* No error, frees buffer and returns. */
  line_buffer_free(p_buffer);
  return EXIT_SUCCESS;
}}}


/******************************************************************************
 ~~~[ AUXILIARY FUNCTIONS ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

/**
 * Reads the entire input and throws it away. Used when user wants to "see" 0
 * lines of the stream. No output is generated. Returns EXIT_FAILURE and sets
 * errno upon error, otherwise returns EXIT_SUCCESS and errno is set to 0.
 */
int flush_all(void)
{{{
  char *line = NULL;            /* Pointer to line buffer for getline(). */
  size_t line_length = 0;       /* Actual size of line buffer. */

  errno = 0;                    /* Reseting errno for error detection. */

  /*
   * Reading every line of input and "flushing" it.
   */
  while (getline(&line, &line_length, stdin) != EOF)
    ;

  free((void *) line);
  return (errno != 0) ? EXIT_FAILURE : EXIT_SUCCESS;  /* Error test. */
}}}


/**
 * Prints last line of the stream. Because it is simple task and no buffer is
 * required for this task, it was decided to make this as a small function.
 * Same return values as with flush_all() function above.
 */
int last_line(void)
{{{
  char *line = NULL;            /* Pointer to line buffer for getline(). */
  size_t line_length = 0;       /* Actual size of line buffer. */
  int retval = EXIT_SUCCESS;    /* Default return value. */

  errno = 0;                    /* Reseting errno for error detection. */

  /*
   * Reads every line of input. If it is not the end of input, then flushes it.
   */
  while (getline(&line, &line_length, stdin) != EOF)
    ;
  
  /* Tests if there was an error, if not, trie to print the last line. */
  if (errno != 0 || fputs(line, stdout) == EOF) {
    retval = EXIT_FAILURE;      /* Reading or printing failed. */
  }

  free((void *) line);
  return retval;
}}}


/**
 * Creates cyclic line buffer of given size, which can be used with getline() or
 * getdelim() function. Returns NULL pointer and sets errno upon failure,
 * otherwise returns pointer to created buffer.
 */
TS_node *line_buffer_make(unsigned long buff_size)
{{{
  if (buff_size < 1) {
    errno = EINVAL;             /* Can't create buffer smaller than 1. */
    return NULL;
  }

  TS_node *p_node_bef = NULL;   /* Helpful pointer used as a backup. */
  TS_node *p_node = (TS_node *) malloc(sizeof(TS_node));

  /* Successful allocation of first (initial) node? */
  if (p_node == NULL) {
    errno = ENOMEM;
    return NULL;
  }
  
  /* First (initial) node initialization. */
  p_node->p_line = NULL;
  p_node->buff_size = 0;
  p_node->p_next = p_node;

  /* 
   * Creating more nodes if needed. Iterator is set to 1 because one node was
   * already created.
   */
  for (unsigned long i = 1; i < buff_size; i++) {
    p_node_bef = p_node;    /* Node backup. */
    TS_node *p_node = (TS_node *) malloc(sizeof(TS_node));
    
    /* Successful allocation? */
    if (p_node == NULL) {
      line_buffer_free(p_node_bef);   /* Freeing of buffer created so far. */
      errno = ENOMEM;
      return NULL;
    }

    /* New node initialization. */
    p_node->p_line = NULL;
    p_node->buff_size = 0;

    /* "Inserting" new node into buffer. */
    p_node->p_next = p_node_bef->p_next;
    p_node_bef->p_next = p_node;
  }

  return p_node;    /* Returning pointer to created buffer. */
}}}


/**
 * Frees the content of given cyclic line buffer and the buffer itself.
 */
void line_buffer_free(TS_node *p_node)
{{{
  if (p_node == NULL) {
    return;                               /* Nothing to free. */
  }

  TS_node *p_node_next;                   /* Pointer to next node to free. */

  /* Initialization for cycle below. (The buffer must be concatenated.) */
  p_node_next = p_node->p_next;
  p_node->p_next = NULL;
  p_node = p_node_next;

  /* Frees until the end of concatenated buffer is reached. */
  while (p_node != NULL) {
    p_node_next = p_node->p_next;
    free((void *) p_node->p_line);
    free((void *) p_node);
    p_node = p_node_next;
  }

  return;
}}}

/**
 * Simple patch to overcome that standard fputs() cannot process NULL pointer.
 * Passing NULL pointer to fputs() causes Segmentation fault.
 */
static inline int fput_str(const char *str, FILE *stream)
{{{
  return (str == NULL) ? fputs("", stream) : fputs(str, stream);
}}}


/******************************************************************************
 ~~~[ MAIN FUNCTION ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ******************************************************************************/

int main(int argc, char *argv[])
{{{
  TS_arguments args;

  process_args(argc, argv, &args);    /* Program's arguments processing. */

  /* -h or --help parameter was encountered. */
  if (args.option == HELP) {
    display_help();
    return EXIT_SUCCESS;
  }

  /* Rerouting of the stdin stream if there was a filename to use. */
  if (args.p_filename != NULL && freopen(args.p_filename, "r", stdin) == NULL) {
    perror("tail: error");            /* Rerouting failed. */
    return EXIT_FAILURE;
  }

  /* Calls appropriate wrapper function. */
  switch (args.option) {
    
    /* Standard behaviour of printing last lines of stdin. */
    case STANDARD :
      if (print_last_lines(args.lines) == EXIT_FAILURE) {
        perror("tail: error");
        return EXIT_FAILURE;
      }
      break;

    /* Printing everything from given line. */
    case FROM_LINE :
      if (print_from_line(args.lines) == EXIT_FAILURE) {
        perror("tail: error");
        return EXIT_FAILURE;
      }
      break;

    /* 
     * Just "safety" mechanism for intern error detection. This should never
     * happen!
     */
    default :
      fprintf(stderr, "tail: error: undefined operation\n");
      return EXIT_FAILURE;
      break;
  }

  return EXIT_SUCCESS;
}}}


/******************************************************************************
 ***[ END OF TAIL.C ]**********************************************************
 ******************************************************************************/
 
