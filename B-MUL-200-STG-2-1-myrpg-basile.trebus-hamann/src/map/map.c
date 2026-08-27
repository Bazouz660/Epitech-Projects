/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** map.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void move_floor(core_t *c, m_floor_t floor, sfVector2f vect)
{
    sfVertex *tmp;

    for (int j = 0; j < 4; j++) {
        if (!floor.walls[j])
            return;
        for (int i = 0; i < 4; i++) {
            tmp = sfVertexArray_getVertex(floor.walls[j], i);
            tmp->position.x -= vect.x;
            tmp->position.y -= vect.y;
        }
    }
}

void move_map(core_t *c, sfVector2f vect)
{
    sfVector2f pos;
    for (int i = 0; i < 5; i++) {
        move_floor(c, c->map.m_floor[i], vect);
    }
}

void set_map_pos(core_t *c, sfVector2f pos)
{
    sfVertex *tmp = sfVertexArray_getVertex(c->map.m_floor->walls[2], 3);
    sfVector2f mem = tmp->position;
    sfVector2f diff;

    tmp->position = pos;
    diff.x = mem.x - pos.x;
    diff.y = mem.y - pos.y;
    move_map(c, diff);
    tmp = sfVertexArray_getVertex(c->map.m_floor->walls[2], 3);
    tmp->position = pos;
    pos.x = sfVertexArray_getVertex(c->map.m_floor[c->stage_index].walls[2],
    1)->position.x + ((sfVertexArray_getVertex(c->map.m_floor[c->stage_index].\
    walls[2], 3)->position.x - sfVertexArray_getVertex(c->map.m_floor\
    [c->stage_index].walls[2], 1)->position.x) / 2);
    pos.y = sfVertexArray_getVertex(c->map.m_floor[c->stage_index].walls[2],
    3)->position.y;
    sfSprite_setPosition(c->map.p_logo, pos);
}

void create_render_states(core_t *c)
{
    c->map.f_state.blendMode = sfBlendNone;
    c->map.f_state.shader = NULL;
    c->map.f_state.transform = sfTransform_Identity;
    c->map.f_state.texture = c->textures.wall;
    c->map.w_state.blendMode = sfBlendNone;
    c->map.w_state.shader = NULL;
    c->map.w_state.transform = sfTransform_Identity;
    c->map.w_state.texture = c->textures.floor;
}

void map(core_t *c)
{
    sfVector2f size = {150, 130};
    sfVector2f pos = {500, 750};

    c->map.size = size;
    c->map.m_floor = malloc(sizeof(m_floor_t) * 6);
    c->map.m_floor[0].walls = malloc(sizeof(sfVertexArray *) * 5);
    c->map.m_floor[1].walls = malloc(sizeof(sfVertexArray *) * 5);
    c->map.m_floor[2].walls = malloc(sizeof(sfVertexArray *) * 5);
    c->map.m_floor[3].walls = malloc(sizeof(sfVertexArray *) * 5);
    c->map.m_floor[4].walls = malloc(sizeof(sfVertexArray *) * 5);
    create_render_states(c);
    for (int i = 0; i < 4; i++) {
        create_floor(c->map.m_floor[i].walls, pos, size, 0);
        pos.y -= size.y - 30;
    }
    c->map.p_logo = new_sprite("sprites/p_logo.png", 4, 4);
    sfSprite_setOrigin(c->map.p_logo, get_sprite_center(c->map.p_logo));
    create_floor(c->map.m_floor[4].walls, pos, size, 1);
}
