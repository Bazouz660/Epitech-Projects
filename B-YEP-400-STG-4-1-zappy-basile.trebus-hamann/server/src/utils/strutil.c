/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** strutil
*/

#include "common.h"
#include <stdarg.h>

void str_append(char **str, const char *to_append)
{
    int len = 0;
    int len2 = 0;

    if (*str == NULL)
        *str = strdup("\0");
    for (; (*str)[len] != '\0'; len++);
    for (; to_append[len2] != '\0'; len2++);
    *str = realloc(*str, sizeof(char) * (len + len2 + 1));
    for (int i = 0; i < len2; i++)
        (*str)[len + i] = to_append[i];
    (*str)[len + len2] = '\0';
}

void safe_free(void **ptr)
{
    if (ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}

char* str_assign(char **dest, const char *src)
{
    safe_free((void **)dest);
    *dest = strdup(src);
    return *dest;
}

char* itoa(int num)
{
    int size = snprintf(NULL, 0, "%d", num) + 1;
    char* str = (char*) malloc(size * sizeof(char));
    snprintf(str, size, "%d", num);

    return str;
}

char* svaprintf_wish(const char *__restrict __format, ...)
{
    char* str = NULL;

    va_list args;
    va_start(args, __format);
    int size = vsnprintf(NULL, 0, __format, args) + 1;
    va_end(args);
    str = (char*) malloc(size * sizeof(char));
    va_start(args, __format);
    vsprintf(str, __format, args);
    va_end(args);
    return str;
}
