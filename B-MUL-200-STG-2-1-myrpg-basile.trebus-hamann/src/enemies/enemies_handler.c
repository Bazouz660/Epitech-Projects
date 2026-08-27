/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** enemies_handler.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

sfVector2f find_dp(core_t *c, enemies_t *node)
{
    sfVector2f distance = {0, 0};

    distance.x = node->entity.pos.x - c->p.player_pos.x;
    if (distance.x < 0)
        distance.x *= -1;
    distance.y = node->entity.pos.y - c->p.player_pos.y;
    if (distance.y < 0)
        distance.y *= -1;
    return distance;
}

void follow_player(core_t *c, enemies_t *node)
{
    if (c->p.player_pos.x < node->entity.pos.x) {
        node->entity.vect.x = -2;
        if (node->entity.direction != 1) {
            node->entity.direction = 1;
            node->entity.scale.x *= -1;
            sfSprite_setScale(node->entity.sprite, node->entity.scale);
        }
    } else {
        node->entity.vect.x = 2;
        if (node->entity.direction != -1) {
            node->entity.direction = -1;
            node->entity.scale.x *= -1;
            sfSprite_setScale(node->entity.sprite, node->entity.scale);
        }
    }
    if (find_dp(c, node).x < 120 && find_dp(c, node).y < 200) {
        node->entity.vect.x = 0;
        if (node->entity.atk_cooldown == 0)
            node->entity.attacking = True;
    }
}

void create_e_hitbox(core_t *c, sfFloatRect bounds, enemies_t *node)
{
    sfVector2f size = {bounds.width, bounds.height};
    sfVector2f pos = sfSprite_getPosition(node->entity.sprite);

    pos.x += bounds.left;
    pos.y += bounds.top;
    sfRectangleShape_setFillColor(node->entity.hit_hitbox,
    c->color.transparent_red);
    sfRectangleShape_setSize(node->entity.hit_hitbox, size);
    sfRectangleShape_setOrigin(node->entity.hit_hitbox,
    get_rect_center(node->entity.hit_hitbox));
    sfRectangleShape_setPosition(node->entity.hit_hitbox, pos);
}

void find_dir_to_player(core_t *c, enemies_t *head)
{
    sfFloatRect bounds;

    while (head != NULL) {
        head->entity.pos = sfSprite_getPosition(head->entity.sprite);
        head->entity.scale = sfSprite_getScale(head->entity.sprite);
        sfRectangleShape_setSize(head->entity.hit_hitbox, init_fvect(0, 0));
        if (head->entity.attacking == True && head->entity.frame_index >= 3
            && head->entity.frame_index < 4 && head->entity.health > 0) {
            bounds = init_frect(120 * -head->entity.direction, 45, 100, 50);
            create_e_hitbox(c, bounds, head);
        }
        if (find_dp(c, head).x <= 800 && find_dp(c, head).y <= 300
            && head->entity.attacking == False)
            follow_player(c, head);
        else if (find_dp(c, head).x > 800
            || find_dp(c, head).y > 300)
            head->entity.vect.x = 0;
        head->entity.health <= 0 ? head->entity.vect.x = 0 : 0;
        head = head->next;
    }
}

void handle_enemies_direction(core_t *c)
{
    c->p.player_pos = sfSprite_getPosition(c->p.player);
    find_dir_to_player(c, STAGE.e);
}
