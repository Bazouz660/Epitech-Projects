/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** remove
*/

#include "linked_list.h"

ll_node *ll_pop_back(ll_node *list)
{
    ll_node *last = ll_back(list);

    if (last == NULL)
        return list;
    if (last->prev != NULL)
        last->prev->next = NULL;
    free(last);
    return list;
}

void ll_pop_front(ll_node** head)
{
    ll_node* tmp = *head;

    if (*head == NULL)
        return;

    *head = (*head)->next;
    free(tmp);
    return;
}

void ll_pop_node(ll_node** head, ll_node* del)
{
    if (*head == NULL || del == NULL)
        return;

    if (*head == del)
        *head = del->next;

    if (del->next != NULL)
        del->next->prev = del->prev;

    if (del->prev != NULL)
        del->prev->next = del->next;

    free(del);
    return;
}

ll_node *ll_clear(ll_node *list)
{
    ll_node *tmp = list;
    ll_node *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    return NULL;
}
