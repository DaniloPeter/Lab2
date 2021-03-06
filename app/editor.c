/**
 * editor.c -- строковый текстовый редактор
 * 
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text.h"
#include "common.h"

#define MAXLINE 255

int main()
{
    char cmdline[MAXLINE + 1];
    char *cmd;
    char *arg;
    char *arg2;
    
    /* Создаем объект для представления текста */
    text txt = create_text();

    /* Цикл обработки команд */
    while (1) {
        printf("ed > ");
        
        /* Получаем команду */
        fgets(cmdline, MAXLINE, stdin);

        /* Извлекаем имя команды */
        if ((cmd = strtok(cmdline, " \n")) == NULL) {
            continue;
        }

        /* Распознаем поддерживаемую команду */
        
        /* Завершаем работу редактора */
        if (strcmp(cmd, "quit") == 0) {
            fprintf(stderr, "Bye!\n");
            break;
        }

        /* Загружаем содержимое файла, заданного параметром */
        if (strcmp(cmd, "load") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: load filename\n");
            } else {
                load(txt, arg);
            }
            continue;
        }

        /* Выводим текст */
        if (strcmp(cmd, "show") == 0) {
            show(txt);
            continue;
        }

        /* Сохраняем в файл по имени из аргумента */
        if (strcmp(cmd, "save") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL) {
                fprintf(stderr, "Usage: save filename\n");
            }else {
                save(txt, arg);
            }
            continue;
        }
	
        /* Перемещение курсора по указаной позиции из аргументов */
        if (strcmp(cmd, "move") == 0) {
            if ((arg = strtok(NULL, " \n")) == NULL || (arg2 = strtok(NULL, "\n")) == NULL) {
                fprintf(stderr, "Usage: move line row\n");
            }
            else {
                int line = atoi(arg);
                int position = atoi(arg2);
                if (line < 0 || position < 0){
                    fprintf(stderr, "Usage: move line position\n");
                }else{
                    move(txt, line, position);
                }
            }
            continue;
        }

        /* Выводим текст с капитализацией первых букв слов */
        if (strcmp(cmd, "showupfirst") == 0) {
            showupfirst(txt);
            continue;
        }

        /* Перемещает курсор в конец строки */
        if (strcmp(cmd, "mle") == 0) {
            mle(txt);
            continue;
        }

        /* Перемещает курсор в конец строки */
        if (strcmp(cmd, "r1ne") == 0) {
            r1ne(txt);
            continue;
        }

          /* Если команда не известна */
          fprintf(stderr, "Unknown command: %s\n", cmd);
        }

    return 0;
}
