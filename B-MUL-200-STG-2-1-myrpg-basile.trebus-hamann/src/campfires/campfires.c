/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** campfires.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

campfire_t create_campfire(core_t *c, float posx, float posy)
{
    campfire_t cf;
    sfVector2f pos = {posx, posy};

    cf.sprite = new_sprite("sprites/campfire.png", 1, 1);
    sfSprite_setOrigin(cf.sprite, get_sprite_center(cf.sprite));
    cf.lit = False;
    cf.particles = create_fire_particles(c, pos, 10000, 4);
    cf.aura = create_particles(c, 350, init_fvect(pos.x, pos.y + 100));
    cf.center_point = sfVertexArray_getVertex(cf.aura, 0);
    sfSprite_setPosition(cf.sprite, pos);
    cf.key_prompt = sfSprite_create();
    sfSprite_setTexture(cf.key_prompt, c->textures.interact_prompt, True);
    sfSprite_setOrigin(cf.key_prompt, get_sprite_center(cf.key_prompt));
    sfSprite_setScale(cf.key_prompt, init_fvect(0.7, 0.7));
    set_sprite_pos(cf.key_prompt, posx, posy - 80);
    return cf;
}
