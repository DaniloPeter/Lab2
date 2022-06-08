#include <stdio.h>
#include "common.h"
#include "_text.h"
#include "text.h"

/**
 * перемещает курсор в указанную строку и позицию
 */
void move(text txt, int line, int position){
    if (txt == NULL || txt->length == 0) {
      fprintf(stderr, "There are already no any lines in the text!\n");
      return;
    }

    if (line < 0){
        line = 0;
    }
    if (position < 0){
        position = 0;
    }

    node *current = txt->begin;
    if (line){
        while (--line && current != txt->end){
            current = current->next;
        }
    }

    txt->cursor->line = current;

    txt->cursor->position = strlen(current->contents);
    if (position < txt->cursor->position){
        txt->cursor->position = position;
    }
}
