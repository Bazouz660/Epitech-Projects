/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** particles.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void draw_particles(core_t *c, particle_t *head, particle_t *head2)
{
    int i = 0;
    sfVertex *array;

    while (head != NULL) {
        i++;
        head = head->next;
    }
    array = malloc(sizeof(sfVertex) * i + 1);
    for (int x = 0; head2 != NULL; x++) {
        array[x] = head2->vertex;
        head2 = head2->next;
    }
    sfRenderWindow_drawPrimitives(c->window, array, i, sfPoints, NULL);
}

void add_part(core_t *c, particle_t **head, int i)
{
	particle_t *new_part = malloc(sizeof(particle_t));

    new_part->speed = 4;
    new_part->decay = c->clock.seconds;
    new_part->vertex.color.r = 255;
    new_part->vertex.color.g = 150;
    new_part->vertex.color.b = 0;
    new_part->vertex.color.a = 255;
    new_part->vertex.position = STAGE.campfires[i].particles->emmiter;
	new_part->next = (*head);
	new_part->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_part;
	(*head) = new_part;
}

void del_part(particle_t **head, particle_t *del_node)
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

sfVertexArray *create_particles(core_t *c, float radius, sfVector2f pos)
{
    sfVector2f center = pos;
    sfVertexArray *array;

    array = sfVertexArray_create();
    for (float i = 0; i < 100; i++)
        sfVertexArray_append(array, add_vertex_circular(c,
        &radius, i, center));
    sfVertexArray_setPrimitiveType(array, sfTriangleFan);
}

particles_t *create_fire_particles(core_t *c, sfVector2f emmiter_pos,
int amount, int speed)
{
    particles_t *p = malloc(sizeof(particles_t));

    p->part_head = NULL;
    p->emmiter = emmiter_pos;
    p->clock = 0;
    p->update = 0;
    p->amount = 0;
    p->max = amount;
    return p;
}
