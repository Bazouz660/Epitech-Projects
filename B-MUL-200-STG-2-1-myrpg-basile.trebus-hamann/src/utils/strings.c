/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** strings.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

char **my_str_to_word_array(char *str)
{
    char **word_array;
    int i = 0;
    int j = 0;
    int x = 0;
    int lengh = my_strlen(str);

    word_array = malloc(sizeof(char *) * my_strlen(str));
    for (;str[i] != '\0'; j++) {
        while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
            i++;
        word_array[j] = malloc(sizeof(char) * (lengh));
        for (; str[i] != ' ' && str[i] != '\t'
            && str[i] != '\n' && str[i] != '\0'; x++, i++)
            word_array[j][x] = str[i];
        word_array[j][x] = '\0';
        x = 0;
    }
    word_array[j] = NULL;
    return word_array;
}

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *my_strcat(char *dest, char const *src)
{
    int dest_len = my_strlen(dest);
    int i = 0;

    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

int my_atoi(char *str)
{
    int res = 0;
    int sign = (str[0] == '-') ? -1 : 1;

    for (int i = (str[0] == '-') ? 1 : 0; str[i]; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            res *= 10;
            res += str[i] - '0';
        } else
            return (res);
    }
    return (res * sign);
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i++;
    if (s1[i] < s2[i] || s1[i] == '\0' && s1[i] != s2[i])
        return (-1);
    else if (s1[i] > s2[i] || s2[i] == '\0' && s1[i] != s2[i])
        return (1);
    return (0);
}
