/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** ladders.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

sfRectangleShape *create_ladder(core_t *c, sfVector2f pos)
{
    sfRectangleShape *ladder;

    ladder = sfRectangleShape_create();
    sfRectangleShape_setSize(ladder, init_fvect(150, 150));
    sfRectangleShape_setFillColor(ladder, sfWhite);
    sfRectangleShape_setPosition(ladder, pos);
    sfRectangleShape_setTexture(ladder, c->textures.ladder, sfFalse);
    return ladder;
}

void handle_climb_inputs(core_t *c)
{
    if (c->pst.climbing == True && c->inventory.status == 0) {
        if (sfKeyboard_isKeyPressed(c->keys.jump)) {
            c->pst.climbing = False;
            return;
        }
        if (sfKeyboard_isKeyPressed(c->keys.up)) {
            c->mv.global_vect.y = 2;
            return;
        }
        if (sfKeyboard_isKeyPressed(c->keys.down)) {
            c->mv.global_vect.y = -2;
            return;
        }
        if (!sfKeyboard_isKeyPressed(c->keys.up)
            && !sfKeyboard_isKeyPressed(c->keys.down)) {
            c->mv.global_vect.y = 0;
            return;
        }
    }
}

static int jump_off_ladder(core_t *c)
{
    if ((sfKeyboard_isKeyPressed(c->keys.up)
        || sfKeyboard_isKeyPressed(c->keys.down))
        && !sfKeyboard_isKeyPressed(c->keys.jump) && c->pst.jump_attack != 1) {
        c->pst.climbing = True;
        c->pst.grounded = False;
        c->pst.jumping = True;
        c->mv.global_vect.x = 0;
        return 1;
    }
    return 0;
}

void handle_ladders(core_t *c)
{
    sfFloatRect rect1 = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfFloatRect rect2;
    bool found = 0;

    for (int i = 0; STAGE.la[i].ladder; i++) {
        rect2 = sfRectangleShape_getGlobalBounds(STAGE.la[i].ladder);
        if (sfFloatRect_contains(&rect2, rect1.left,
            (rect1.top + (rect1.height)))
            && sfFloatRect_contains(&rect2, rect1.left + rect1.width,
            (rect1.top + (rect1.height)))) {
            found = 1;
            if (jump_off_ladder(c) == 1)
                break;
        }
    }
    if (found == 0)
        c->pst.climbing = False;
    handle_climb_inputs(c);
}
