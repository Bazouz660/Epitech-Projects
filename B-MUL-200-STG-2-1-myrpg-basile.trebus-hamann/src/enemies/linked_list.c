/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** linked_list.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void add_node(core_t *c, enemies_t **head, int type, int i)
{
	enemies_t *new_node;

    if (i > STAGE.spawn_nb)
	    i = 0;
	new_node = malloc(sizeof(enemies_t));
    type == 1 ? create_type1(c, &new_node->entity, i) : 0;
    type == 2 ? create_type2(c, &new_node->entity) : 0;
    type == 3 ? create_type3(c, &new_node->entity) : 0;
    type == 4 ? create_type4(c, &new_node->entity) : 0;
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void delete_node(enemies_t **head, enemies_t *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
	free(del_node);
}

int count_nodes(enemies_t *node)
{
	int i = 0;

	for (; node != NULL; i++)
	    node = node->next;
	return i;
}
