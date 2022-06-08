#include <stdio.h>
#include "common.h"
#include "_text.h"
#include "text.h"

/**
 * удаление 1 непустой строки
 */
void r1ne(text txt){
    if (txt == NULL || txt->length == 0) {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    }

    node *current = txt->begin;

    while (current != txt->end){
        if (strlen(current->contents) > 0){
            break;
        }
        current = current->next;
    }

    if (strlen(current->contents) == 0){
        fprintf(stderr, "The text is not empty lines\n");
        return;
    }

    node *last = current->previous;
    node *next = current->next;

    if (current == txt->begin){
        txt->begin = next;
    }

    if (current == txt->end){
        txt->end = last;
    }

    if (last != NULL){
        last->next = next;
    }
    if (next != NULL){
        next->previous = last;
    }

    txt->length--;
}
