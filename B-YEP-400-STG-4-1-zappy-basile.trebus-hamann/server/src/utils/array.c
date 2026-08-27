/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** array
*/

#include "common.h"

size_t get_arr_len(void *arr)
{
    size_t len = 0;

    if (arr == NULL)
        return 0;
    while (((char **) arr)[len] != NULL)
        len++;
    return len;
}

void free_arr(void *arr)
{
    if (arr == NULL)
        return;
    for (size_t i = 0; i < get_arr_len(arr); i++)
        free(((char **) arr)[i]);
    free(arr);
}

void arr_append(void **arr, void *to_append)
{
    size_t len = get_arr_len(arr);

    arr = realloc(arr, sizeof(arr) * (len + 2));
    arr[len] = to_append;
    arr[len + 1] = NULL;
}

void arr_remove(void **arr, size_t index)
{
    size_t len = get_arr_len(arr);

    if (index >= len)
        return;
    free(arr[index]);
    for (size_t i = index; i < len - 1; i++)
        arr[i] = arr[i + 1];
    arr[len - 1] = NULL;
    arr = realloc(arr, sizeof(void *) * (len));
}
