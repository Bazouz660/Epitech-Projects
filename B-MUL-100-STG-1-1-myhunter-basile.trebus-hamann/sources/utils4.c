/*
** EPITECH PROJECT, 2021
** MY_HUNTER_BST
** File description:
** utils4.c
*/

#include "../includes/my_hunter.h"

char *fill_score(char *score, int score_count)
{
    int i = get_int_len(score_count) + 1;
    while (score[i] != '\0') {
        score[i] = '0';
        i++;
    }
    return score;
}

int random_number(int min_num, int max_num)
{
    int result = 0;
    int low_num = 0;
    int hi_num = 0;

    if (min_num < max_num) {
        low_num = min_num;
        hi_num = max_num + 1;
    } else {
        low_num = max_num + 1;
        hi_num = min_num;
    }
    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}