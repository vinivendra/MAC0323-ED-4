/*
 * This code is from "Algorithms in C, Third Edition,"
 * by Robert Sedgewick, Addison Wesley Longman, 1998.
 * (Mescla de prog12.5.c e prog14.3.c)
 */
#include "Item.h"
#include "Hash1.h"

static link z;
static int N, M;
static Item *conflict;

/*
link initTable();
void STinit();
Item **getConflict();
int STcount(link head[]);
Item *STsearch(Key v, link head[]);
link STinsert(link head, Item *item);
Item STselect(link head, int r);
void STsort(link head, void(*visit)(Item));
void STshow_histogram();
void STdump(void (*visit)(Item *));
 */



Item **getConflict() {      /* Getter do conflito */
    return &conflict;
}

static link NEW(Item *item, link next)
{
    link x = malloc(sizeof *x);
    x->item = item;
    x->next = next;
    return x;
}

int STcount(link head[]) {
    return N;
}

/* prog14.1 */

int hash(char *v, int M)
{ int h = 0, a = 127; /* a = 128; */
    for (; *v != '\0'; v++)
        h = (a*h + *v) % M;
    return h;
}

#define hash(v,M) (hash(v,M))

void STinit(int max)
{
    N = 0;
    M = 97;
    z = NEW(getNULLitem(), NULL);
    conflict = NULL;
}

link initTable() {
    link head;
    int i;
    head = malloc(M*sizeof(link));
    for (i = 0; i < M; i++) head[i] = *z;
    return head;
}

Item *searchR(link t, Key v)
{
    if (t == z) return getNULLitem();
    if (eq(key(t->item), v)) return t->item;
    return searchR(t->next, v);
}

Item *STsearch(Key v, link *head) {
    return searchR(head[hash(v, M)], v);
}

link STinsert(link head[], Item *item) {
    int i = hash(key(item), M);
    head[i] = NEW(item, head[i]);
    N++;
    return head[0];
}

void STsort(link head[], void(*visit)(Item)) {
    printf("STsort ainda não foi implementado!!");
#warning implement STSort.
}


void STdump(link head[], void (*visit)(Item *))
{
    int i;
    link t;
    
    for (i=0; i<M; i++) {
        if (head[i] != z)
            for (t = head[i]; t != z; t = t->next)
                visit(t->item);
    }
}

void STshow_histogram(link head[])
{
    int i, j, no_per_list, max_list = -1;
    link t;
    
    for (i=0; i<M; i++) {
        printf("\n+ list %d: ", i);
        for (no_per_list=0, t = head[i]; t != z; no_per_list++, t = t->next);
        printf("[%d] ", no_per_list);
        j = no_per_list;
        while (j-- > 0)
            printf("*");
        if (no_per_list>max_list) max_list=no_per_list;
    }
    
    printf("\nMax no. of items in the lists: %d\n", max_list);
    printf("Average no. of items in the lists: %g\n\n", (double)N/M);
}
