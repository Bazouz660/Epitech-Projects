/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** str_to_word_array.c
*/

#include "../include/solver.h"

char **my_str_to_word_array(char *str)
{
    char **word_array;
    int i = 0;
    int j = 0;
    int lengh = strlen(str);

    word_array = malloc(sizeof(char *) * strlen(str));
    while (str[i] != '\0') {
        while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
            i++;
        word_array[j] = malloc(sizeof(char) * (lengh));
        for (int x = 0; str[i] != ' ' && str[i] != '\t'
            && str[i] != '\n' && str[i] != '\0'; x++) {
            word_array[j][x] = str[i];
            i++;
        }
        j++;
    }
    word_array[j - 1] = NULL;
    return word_array;
}
