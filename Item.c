/*
 * Much of this code is adapted from "Algorithms in C, Third Edition,"
 * by Robert Sedgewick, Addison Wesley Longman, 1998, and from
 * Sedgewick's own Java code for left-leaning red-black trees.
 * Much of it has been adapted to better suit the needs of this particular problem.
 *
 * Though this code has been changed considerably from Sedgewick's original
 * implementation, it is mostly uncomplicated and thus is not deeply commented.
 * For further information and explanations, please refer to the file Relatório.pdf.
 */
#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include <string.h>

#define YES 1
#define NO 0
#define STRING_MAX 50   /* A maior palavra no dicionário inglês é um termo técnico da biologia, que tem 45 caracteres. */

static Item *NULLitem;  /* NULLitem é global, resultado da adaptação da
                         implementação antiga de Item para a nova.*/

Item *ITEMscan(Item *x) {
    char *t = malloc(STRING_MAX*sizeof(char));
    Item *palavra = malloc(sizeof(Item));
    scanf("%s", t);
    palavra->literal = t;
    palavra->prox = palavra->lema = NULL;
    palavra->list = NULL;
    return palavra;
}

void ITEMshow(Item x) {
    printf("%s\n", x.literal);
}

Key key(Item *item) {               /* Retorna a chave do item */
    return item->literal;
}

int eq(Key key1, Key key2) {        /* Compara a string key1 com a key2; não diferencia maiúsculas de minúsculas */
    int i = 0;
    char a, b;
    
    for (i = 0; *(key1+i) != '\0' && *(key2+i) != '\0'; i++) {
        a = (*(key1+i));            /* Comparamos key1 com key2, caracter por caracter */
        b = (*(key2+i));
        
        if (a >= 'A' || a <= 'Z')   /* Se o caracter for maiúsculo, transformamos em minúsculo */
            a = a | 32;
        if (b >= 'A' || b <= 'Z')
            b = b | 32;
        
        if (a != b)
            return 0;
    }
    
    if ((*(key1+i)) != (*(key2+i)))
        return 0;
    
    return 1;
}

int less(Key key1, Key key2) {      /* Mesma ideia de 'eq', mas retorna 1 caso key1 vier antes de key2, alfabeticamente */
    int i = 0;
    char a, b;
    
    for (i = 0; *(key1+i) != '\0' && *(key2+i) != '\0'; i++) {
        a = (*(key1+i));
        b = (*(key2+i));
        
        if (a >= 'A' || a <= 'Z')
            a = a | 32;
        if (b >= 'A' || b <= 'Z')
            b = b | 32;
        
        if (a < b)
            return 1;
        else if (a > b)
            return 0;
    }
    
    return 0;
}

void initItem () {                  /* Inicializa o NULLitem */
    NULLitem = malloc(sizeof(Item));
    NULLitem->literal = NULL;
    NULLitem->lema = NULLitem->prox = NULL;
    NULLitem->list = NULL;
}

Item *getNULLitem () {              /* Getter do NULLitem */
    return NULLitem;
}