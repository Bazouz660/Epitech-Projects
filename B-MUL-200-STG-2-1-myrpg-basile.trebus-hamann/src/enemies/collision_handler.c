/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** collision_handler.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void e_collision_loop2(core_t *c, enemies_t *node)
{
	if (c->co.pbound.left < c->co.wbound.left
		&& c->co.pbound.left + c->co.pbound.width < c->co.wbound.left\
        + c->co.wbound.width
		&& c->co.pbound.top < c->co.wbound.top + c->co.wbound.height
		&& c->co.pbound.top + c->co.pbound.height > c->co.wbound.top) {
        e_right_collision(c, node);
        return;
    } else if (c->co.pbound.left > c->co.wbound.left
		&& c->co.pbound.left + c->co.pbound.width > c->co.wbound.left\
        + c->co.wbound.width
		&& c->co.pbound.top < c->co.wbound.top + c->co.wbound.height
		&& c->co.pbound.top + c->co.pbound.height > c->co.wbound.top) {
        e_left_collision(c, node);
        return;
    }
}

static void e_collision_loop(core_t *c, enemies_t *node)
{
	if (c->co.wbound.top > c->co.pbound.top
		&& c->co.wbound.top + c->co.wbound.height > c->co.pbound.top\
        + c->co.pbound.height
		&& c->co.wbound.left < c->co.pbound.left + c->co.pbound.width
		&& c->co.wbound.left + c->co.wbound.width > c->co.pbound.left) {
        e_bottom_collision(c, node);
        return;
    } else if (c->co.pbound.top > c->co.wbound.top
		&& c->co.pbound.top + c->co.pbound.height > c->co.wbound.top\
        + c->co.wbound.height
		&& c->co.pbound.left < c->co.wbound.left + c->co.wbound.width
		&& c->co.pbound.left + c->co.pbound.width > c->co.wbound.left) {
        e_top_collision(c, node);
        return;
    }
    e_collision_loop2(c, node);
}

static void handle_collision_loop(core_t *c, enemies_t *node)
{
    for (int i = 0; c->co.wall[i] != NULL; i++) {
        c->co.global_pos = sfRectangleShape_getPosition(c->co.wall[i]);
	    c->co.pbound = sfRectangleShape_getGlobalBounds(node->entity.hitbox);
	    c->co.wbound = sfRectangleShape_getGlobalBounds(c->co.wall[i]);
	    c->co.nextPos = c->co.pbound;
	    c->co.nextPos.left += node->entity.vect.x;
	    c->co.nextPos.top += node->entity.vect.y;
	    if (sfFloatRect_intersects(&c->co.wbound,
            &c->co.nextPos, &c->co.correction))
            e_collision_loop(c, node);
    }
}

void handle_enemies_collisions(core_t *c, enemies_t *head)
{
    sfVector2f temp;

    while (head != NULL) {
        handle_collision_loop(c, head);
        head->entity.pos = sfRectangleShape_getPosition(head->entity.hitbox);
        temp = head->entity.pos;
        temp.x += sfRectangleShape_getGlobalBounds(head->entity.hitbox).width / 2;
        temp.y += 35;
        sfSprite_setPosition(head->entity.sprite, temp);
        head = head->next;
    }
}
