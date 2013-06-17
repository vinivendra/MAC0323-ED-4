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
 Protótipos
*/

int compare(const void *link1, const void *link2);

/*
 Implementações
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
    
#warning achar um valor bom para o M
    
    N = 0;
    M = 1021;
    z = NEW(getNULLitem(), NULL);
    conflict = NULL;
}

link *initTable() {
    link *head;
    int i;
    head = malloc(M*sizeof(link *));
    for (i = 0; i < M; i++) head[i] = z;
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

int STinsert(link head[], Item *item) {
    int i = hash(key(item), M);
    link l;
    
    if (head[i]->item == getNULLitem()) {   /* Se ainda não existe nenhum item nesse espaço do vetor, */
        head[i] = NEW(item, head[i]);       /* É só adicionar direto. */
        N++;
        conflict = NULL;
        return 1;
    }
    
    for (l = head[i]; l != z; l = l->next)  /* Se já existe algum, percorremos a lista para ver se */
        if (eq(key(l->item), key(item))) {  /* o item já existia */
            conflict = l->item;
            return 0;
        }
    
    head[i] = NEW(item, head[i]);           /* Se não existia ainda, colocamos na lista */
    N++;
    conflict = NULL;
    return 1;
}

link *STsort(link head[]) {
    int i, j = 0;
    link k;
    link *copy;
    copy = malloc(N*sizeof(link *));
    
    for (i = 0; i < M; i++) {
        for (k = head[i]; k != z; k = k->next) {
            copy[j] = k;
            j++;
        }
    }
    for (; j < N; j++) {
        copy[j] = z;
    }
    
#warning TIRAR ESSE SEGUNDO FOR DAQUI

    qsort(copy, N, sizeof(link), &compare);
    
    
    return copy;
}

int compare(const void *link1, const void *link2) {
    if (*(link *)link1 == z) {
        return 1;
    }
    if (*(link *)link2 == z) {
        return -1;
    }
    if (less(key((*(link *)link1)->item), key((*(link *)link2)->item))) {
        return -1;
    }
    return 1;
}


void STdump(link head[], void (*visit)(Item)) {
    int i;
    
    for (i=0; i<N; i++) {
        if (head[i] != z)
            visit(*(head[i]->item));
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
