/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** utils
*/

#pragma once

#include <stdbool.h>
#include <unistd.h>

void str_append(char **str, const char *to_append);
char** split_string(char* str, char* separators, bool keep_in_quotes);
char* str_assign(char **dest, const char *src);
void safe_free(void **ptr);
void free_arr(void *arr);
char* itoa(int num);
size_t get_arr_len(void *arr);
void arr_remove(void **arr, size_t index);
void arr_append(void **arr, void *to_append);
char* svaprintf_wish(const char *__restrict __format, ...);
