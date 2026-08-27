/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** linked_list
*/

#include "linked_list.h"

int ll_size(ll_node *list)
{
    ll_node *tmp = list;
    int size = 0;

    while (tmp != NULL) {
        size++;
        tmp = tmp->next;
    }
    return size;
}

int ll_is_empty(ll_node *list)
{
    return list == NULL;
}

int ll_find(ll_node *list, void *data)
{
    ll_node *tmp = list;

    while (tmp != NULL) {
        if (tmp->data == data)
            return 1;
        tmp = tmp->next;
    }
    return 0;
}
