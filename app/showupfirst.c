#include <stdio.h>
#include <assert.h>
#include "common.h"
#include <string.h>
#include "text.h"

static void show_line(int index, char *contents, int cursor, void *data);

/**
 * Выводит содержимое указанного файла на экран, где каждое слово с заглавной буквы
 */
void showupfirst(text txt)
{
    /* Применяем функцию show_line к каждой строке текста */
    process_forward(txt, show_line, NULL);
}

static void show_line(int index, char *contents, int cursor, void *data)
{
    /* Функция обработчик всегда получает существующую строку */
    assert(contents != NULL);
    
    /* Декларируем неиспользуемые параметры */
    UNUSED(index);
    UNUSED(data);
    
    int len = strlen(contents);
    for (int i = 0; i < len; i++) {
        if (i == cursor){
            printf("|");
        }

        if (i > 0 && contents[i - 1] == ' ' && contents[i] >= 'a' && contents[i] <= 'z'){
            printf("%c", contents[i] - 'a' + 'A');
            continue;
        }
        printf("%c", contents[i]);
    }
    if (len == cursor ) {
        printf("|");
    }

    printf("\n");
}
