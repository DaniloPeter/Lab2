/**
 * common.h -- прототипы функций реализации команд редактора
 * 
 * Copyright (c) 2017, Alexander Borodin <aborod@petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#ifndef COMMON_H
#define COMMON_H

#include "text.h"

/* Декларирует неиспользуемый аргумент,
 * корректно подавляя предупреждение вида "unused parameter" */
#define UNUSED(x) (void)(x)

/**
 * Выводит содержимое указанного файла на экран
 */
void show(text txt);

/**
 * Загружает содержимое указанного файла
 */
void load(text txt, char *filename);

/**
 * Сохраняем файл 
 */
void save(text txt, char *filename);

/**
 * Перемещение курсора
 */
void move(text txt, int line, int position);

/**
 * Выводит содержимое указанного файла на экран, где каждое слово с заглавной буквы
 */
void showupfirst(text txt);

/**
 * перемещает курсор в конец строки
 */
void mle(text txt);

/**
 * удаление 1 непустой строки
 */
void r1ne(text txt);

#endif
