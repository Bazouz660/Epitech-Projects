/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** create
*/

#include "linked_list.h"

ll_node *ll_create(void *data)
{
    ll_node *list = malloc(sizeof(ll_node));

    list->data = data;
    list->next = NULL;
    list->prev = NULL;
    return list;
}

ll_node *ll_push_back(ll_node *list, void *data)
{
    ll_node *new_node = ll_create(data);
    ll_node *last = ll_back(list);

    if (last == NULL)
        return new_node;
    last->next = new_node;
    new_node->prev = last;
    new_node->next = NULL;
    return list;
}

ll_node *ll_push_front(ll_node *list, void *data)
{
    ll_node *new_node = ll_create(data);
    ll_node *first = ll_front(list);

    if (first == NULL)
        return new_node;
    first->prev = new_node;
    new_node->next = first;
    new_node->prev = NULL;
    return list;
}

ll_node *ll_insert_node(ll_node *list, ll_node *node,
    void *data)
{
    ll_node *new_node = ll_create(data);

    if (node == NULL)
        return list;
    if (node->prev != NULL)
        node->prev->next = new_node;
    new_node->prev = node->prev;
    new_node->next = node;
    node->prev = new_node;
    return list;
}

ll_node *ll_insert_node_by_index(ll_node *list, int index, void *data)
{
    ll_node *node = ll_get_node_by_index(list, index);

    return ll_insert_node(list, node, data);
}
