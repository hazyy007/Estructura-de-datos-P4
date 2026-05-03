/**
 * @file types.h
 * @author Alejandro Dominguez
 * @date March 2026
 * @brief ADT Boolean and Status
 *
 * @details Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by @.
 * 
 * @see 
 */
#ifndef TYPES_H_
#define TYPES_H_

#include <stdio.h>

typedef enum {
    FALSE=0,
    TRUE=1
} Bool;

typedef enum {
    ERROR=0,
    OK=1
} Status;

typedef int (*P_ele_print) (FILE *f, const void *);
typedef int (*P_ele_cmp)(const void *, const void *);

#define MAX_QUEUE 8

#endif
