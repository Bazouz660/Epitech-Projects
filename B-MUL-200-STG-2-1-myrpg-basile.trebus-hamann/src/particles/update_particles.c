/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** update_particles.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void animate_light(core_t *c, sfVertex *center)
{
    if (c->clock.seconds > c->light_clock + random_float(0.5)) {
        c->light_clock = c->clock.seconds;
        center->color.a = 50 + random_float(15);
    }
}

void update_particle_life(core_t *c, particle_t *head, int i)
{
    while (head != NULL) {
        if (c->clock.seconds > (head->decay + head->life_time)) {
            del_part(&STAGE.campfires[i].particles->part_head, head);
            STAGE.campfires[i].particles->amount -= 1;
        }
        head = head->next;
    }
}

void update_vertices(core_t *c, particle_t *head, int i)
{
    for (int i = 0; head != NULL; i++) {
        if (head->vertex.color.r > 0)
            head->vertex.color.r -= 0.1;
        if (head->vertex.color.g > 0)
            head->vertex.color.g -= 0.1;
        head->vertex.position.x -= random_between(-head->speed, head->speed);
        head->vertex.position.y -= random_between(-1, head->speed);
        head->life_time = random_between(6, 10);
        head = head->next;
    }
    update_particle_life(c, STAGE.campfires[i].particles->part_head, i);
}

void update_campfire(core_t *c, int i)
{
    if (c->clock.seconds > STAGE.campfires[i].particles->clock + 0.001) {
        STAGE.campfires[i].particles->clock = c->clock.seconds;
        for (int x = 0; x < 10; x++) {
            add_part(c, &STAGE.campfires[i].particles->part_head, i);
            STAGE.campfires[i].particles->amount++;
        }
        update_vertices(c, STAGE.campfires[i].particles->part_head, i);
    }
}


void handle_particles(core_t *c)
{
    for (int i = 0; STAGE.campfires[i].lit != -1; i++) {
        if (STAGE.campfires[i].lit == True)
            update_campfire(c, i);
    }
}
