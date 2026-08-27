/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** splitstr
*/

#include "common.h"

static void remove_all_occurence(char **str, char to_remove)
{
    int i = 0;
    int j = 0;
    char *new_str = malloc(sizeof(char) * (strlen(*str) + 1));

    while ((*str)[i] != '\0') {
        if ((*str)[i] != to_remove) {
            new_str[j] = (*str)[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';
    free(*str);
    *str = new_str;
}

static void copy_word(char*** words, int *word_count, char* start, int word_len)
{
    (*words)[*word_count] = malloc(sizeof(char) * (word_len + 1));
    strncpy((*words)[*word_count], start, word_len);
    (*words)[*word_count][word_len] = '\0';
    remove_all_occurence(&((*words)[*word_count]), '\"');
    (*word_count)++;
}

char** split_string(char* str, char* separators, bool keep_in_quotes)
{
    int len = strlen(str);
    char** words = malloc(sizeof(char*) * (len + 1));
    int word_count = 0;
    bool in_quotes = false;
    char* start = str;
    for (int i = 0; i <= len; i++) {
        char c = str[i];
        bool is_separator = strchr(separators, c) != NULL;
        if (c == '"' && keep_in_quotes) {
            in_quotes = !in_quotes;
            continue;
        }
        if (is_separator && !in_quotes) {
            int word_len = &str[i] - start;
            copy_word(&words, &word_count, start, word_len);
            start = &str[i + 1];
        }
    }
    words[word_count] = NULL;
    return words;
}
