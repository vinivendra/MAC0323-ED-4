/*
 * This code is from "Algorithms in C, Third Edition,"
 * by Robert Sedgewick, Addison Wesley Longman, 1998.
 * (with small alterations...)
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Item.h"
#define o ++n_probes
#define null(A) (st[A] == NULLitem)
#define onull(A) (o, st[A] == NULLitem)
static int N, M;
static long n_probes=0, n_probes_hit=0, n_probes_miss=0;
static Item *st;

/***********************************************************************/

#define HASH_MULT 314159 /* random multiplier */
#define HASH_PRIME 516595003 /* the 27182818th prime; it's less than $2^{29}$ */

long hash_Knuth(char *t)
{ register long h;
    for (h=0; *t; t++) {
        h+=(h^(h>>1))+HASH_MULT*(unsigned char)*t;
        while (h>=HASH_PRIME) h-=HASH_PRIME;
    }
    return h;
}

/***********************************************************************/

#define hash(v,M) (hash_Knuth(v)%M)

/***********************************************************************/

/* #define hash(v,M) (hashU(v,M)) */

/***********************************************************************/


int p[] = {
    251,
    509,
    1021,
    2039,
    4093,
    8191,
    16381,
    32749,
    65521,
    131071,
    262139,
    524287,
    1048573,
    2097143,
    4194301,
    8388593,
    16777213,
    33554393,
    67108859,
    134217689,
    268435399,
    536870909,
    1073741789,
    2147483647
};

int prime_m(int m)
{
    int x;
    x = log(m)/log(2.0) + 1;
    if (x < 8)
        return p[0];
    else
        return p[x - 8];
}

int hash(char *v, int M)
{ int h = 0, a = 127; /* a = 128; */
    for (; *v != '\0'; v++)
        h = (a*h + *v) % M;
    return h;
}

void STinit(int max)
{ int i;
    N = 0; M = prime_m(2*max);
    st = malloc(M*sizeof(Item));
    for (i = 0; i < M; i++) st[i] = NULLitem;
}
int STcount() { return N; }
void STinsert(Item item)
{ Key v = key(item);
    int i = hash(v, M);
    while (!null(i)) i = (i+1) % M;
    st[i] = item; N++;
}
Item STsearch(Key v)
{ int i = hash(v, M);
    int t = n_probes;
    while (!onull(i))
        if (eq(v, key(st[i]))) {
            n_probes_hit+=n_probes-t;
            return st[i];
        } else i = (i+1) % M;
    n_probes_miss+=n_probes-t;
    return NULLitem;
}

/***********************************************************************
 * Programa 14.5
 ***********************************************************************/

void STdelete(Item item)
{ int j, i = hash(key(item), M); Item v;
    while (!null(i))
        if eq(key(item), key(st[i])) break;
        else i = (i+1) % M;
    if (null(i)) return;
    st[i] = NULLitem; N--;
    for (j = i+1; !null(j); j = (j+1) % M, N--)
    { v = st[j]; st[j] = NULLitem; STinsert(v); }
}

/***********************************************************************/

void STshow_all(int n_items)
{
    int i;
    
    for (i=0; i<M; i++)
        if (!null(i)) ITEMshow(st[i]);
    
    printf("\nFinal table load factor: %g\n", (double)N/M);
    printf("Total number of probes: %ld\n", n_probes);
    printf("Average number of probes per item: %g\n",
           (double)n_probes/n_items);
    printf("Average number of probes per miss: %g\n",
           (double)n_probes_miss/N);
    printf("Average number of probes per hit: %g\n\n",
           (double)n_probes_hit/(n_items-N));
}