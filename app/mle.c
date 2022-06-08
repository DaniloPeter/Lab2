#include <stdio.h>
#include "common.h"
#include "_text.h"
#include "text.h"

/**
 * перемещает курсор в конец строки
 */
void mle(text txt){
    if (txt == NULL || txt->length == 0) {
        fprintf(stderr, "There are already no any lines in the text!\n");
        return;
    }

    if (txt->cursor->line == NULL){
        fprintf(stderr, "No cursor!\n");
        return;
    }

    txt->cursor->position = strlen(txt->cursor->line);
}
