/*
** EPITECH PROJECT, 2023
** B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
** File description:
** linked_list
*/

#pragma once

#include "common.h"

typedef struct linked_list_s {
    void *data;
    struct linked_list_s *next;
    struct linked_list_s *prev;
} ll_node;

ll_node *ll_push_back(ll_node *list, void *data);
ll_node *ll_push_front(ll_node *list, void *data);
ll_node *ll_pop_back(ll_node *list);
void ll_pop_front(ll_node** head);
void ll_pop_node(ll_node **head, ll_node *node);
ll_node *ll_get_node(ll_node *list, void *data);
ll_node *ll_get_node_by_index(ll_node *list, int index);
ll_node *ll_front(ll_node *list);
ll_node *ll_back(ll_node *list);
ll_node *ll_clear(ll_node *list);
ll_node *ll_insert_node(ll_node *list, ll_node *node,
    void *data);
ll_node *ll_insert_node_by_index(ll_node *list, int index, void *data);
int ll_size(ll_node *list);
int ll_is_empty(ll_node *list);
int ll_find(ll_node *list, void *data);
