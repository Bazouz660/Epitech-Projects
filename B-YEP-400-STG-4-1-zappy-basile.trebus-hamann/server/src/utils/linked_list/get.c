/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** get
*/

#include "linked_list.h"

ll_node *ll_get_node(ll_node *list, void *data)
{
    ll_node *tmp = list;

    while (tmp != NULL) {
        if (tmp->data == data)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

ll_node *ll_get_node_by_index(ll_node *list, int index)
{
    ll_node *tmp = list;

    for (int i = 0; i < index; i++) {
        if (tmp == NULL)
            return NULL;
        tmp = tmp->next;
    }
    return tmp;
}

ll_node *ll_front(ll_node *list)
{
    if (list == NULL)
        return NULL;
    return ll_get_node_by_index(list, 0);
}

ll_node *ll_back(ll_node *list)
{
    ll_node *tmp = list;

    while (tmp != NULL && tmp->next != NULL)
        tmp = tmp->next;
    return tmp;
}
