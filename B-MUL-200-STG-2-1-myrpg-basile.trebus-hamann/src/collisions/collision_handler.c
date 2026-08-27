/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** collision_handler.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void grounded_handler(core_t *c)
{
    if (c->mv.global_vect.y == 0 && c->pst.jumping == False
        && c->pst.grounded == False && c->pst.hanging == False
        && c->pst.falling == False) {
        sfSound_play(c->audio.landing_sound);
        c->pst.grounded = True;
        c->pst.sliding = False;
    }
    if (c->mv.global_vect.y != 0 || c->pst.sliding == True) {
        c->pst.grounded = False;
    }
}

void handle_collision_loop(core_t *c)
{
    for (int i = 0; c->co.wall[i] != NULL; i++) {
        c->co.global_pos = sfRectangleShape_getPosition(c->co.wall[i]);
	    c->co.pbound = sfSprite_getGlobalBounds(c->p.player_hitbox);
	    c->co.wbound = sfRectangleShape_getGlobalBounds(c->co.wall[i]);
	    c->co.nextPos = c->co.wbound;
	    c->co.nextPos.left += c->mv.global_vect.x;
	    c->co.nextPos.top += c->mv.global_vect.y;
	    if (sfFloatRect_intersects(&c->co.pbound,
            &c->co.nextPos, &c->co.correction))
            collision_loop(c, i);
    }
}

void handle_collisions(core_t *c)
{
    c->pst.sliding = False;
    c->pst.can_grab = False;
    handle_collision_loop(c);
    if (c->p.health > 0)
        handle_ladders(c);
    if (c->p.health <= 0)
        c->pst.climbing = False;
    if (c->pst.climbing == False) {
        grounded_handler(c);
        hanging_handler(c);
    }
    handle_enemies_collisions(c, STAGE.e);
}

void collision_loop2(core_t *c, int i)
{
	if (c->co.pbound.left < c->co.wbound.left
		&& c->co.pbound.left + c->co.pbound.width < c->co.wbound.left\
        + c->co.wbound.width
		&& c->co.pbound.top < c->co.wbound.top + c->co.wbound.height
		&& c->co.pbound.top + c->co.pbound.height > c->co.wbound.top) {
        right_collision(c, i);
        return;
    } else if (c->co.pbound.left > c->co.wbound.left
		&& c->co.pbound.left + c->co.pbound.width > c->co.wbound.left\
        + c->co.wbound.width
		&& c->co.pbound.top < c->co.wbound.top + c->co.wbound.height
		&& c->co.pbound.top + c->co.pbound.height > c->co.wbound.top) {
        left_collision(c, i);
        return;
    }
}

void collision_loop(core_t *c, int i)
{
	if (c->co.wbound.top > c->co.pbound.top
		&& c->co.wbound.top + c->co.wbound.height > c->co.pbound.top\
        + c->co.pbound.height
		&& c->co.wbound.left < c->co.pbound.left + c->co.pbound.width
		&& c->co.wbound.left + c->co.wbound.width > c->co.pbound.left) {
        bottom_collision(c, i);
        return;
    } else if (c->co.pbound.top > c->co.wbound.top
		&& c->co.pbound.top + c->co.pbound.height > c->co.wbound.top\
        + c->co.wbound.height
		&& c->co.pbound.left < c->co.wbound.left + c->co.wbound.width
		&& c->co.pbound.left + c->co.pbound.width > c->co.wbound.left) {
        top_collision(c, i);
        return;
    }
    collision_loop2(c, i);
}
