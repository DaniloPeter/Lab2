#include <stdio.h>
#include <string.h>
#include "common.h"
#include "text.h"

void save_line(int index, char *contents, int cursor, void *data) {
    UNUSED(index);
    UNUSED(cursor);

    FILE *f = (FILE*)data;

    fprintf(f, "%s\n", contents);
}

/**
 * Сохраняет содержимое по имени файла
 */
void save(text txt, char *filename) {
    FILE *f;

    /* Открываем файл для чтения, контролируя ошибки */
    if ((f = fopen(filename, "w")) == NULL) {
        printf("The file %s cannot be opened\n", filename);
        return;
    }
    void *data = (void*)f;
    process_forward(txt, save_line, data);

    fclose(f);
}
