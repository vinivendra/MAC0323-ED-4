#ifndef ED4_Hash1_h
#define ED4_Hash1_h

/*
 * This code is from "Algorithms in C, Third Edition,"
 * by Robert Sedgewick, Addison Wesley Longman, 1998.
 * (with some small alterations...)
 */
#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

typedef struct STnode *link;

struct STnode {
    Item *item;
    link next;
};

Item **getConflict();

link initTable();
void STinit();
Item **getConflict();
int STcount(link head[]);
Item *STsearch(Key v, link head[]);
link STinsert(link head[], Item *item);
Item STselect(link head[], int r);
void STsort(link head[], void(*visit)(Item));
void STshow_histogram(link head[]);
void STdump(link head[], void (*visit)(Item *));

#endif
