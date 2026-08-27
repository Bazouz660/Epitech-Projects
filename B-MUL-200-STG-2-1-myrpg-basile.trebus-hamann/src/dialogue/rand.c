/*
** EPITECH PROJECT, 2022
** sqfsqfqsf
** File description:
** sqfqsfsqf
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

char *get_word(char **tab, int min, int max)
{
    int c = (rand() % (max - min) + 1) + min;
    char *word = tab[c];

    return (word);
}

int nb_words(char **tab)
{
    int i;

    for (i = 0; tab[i]; i++);
    return (i);
}
