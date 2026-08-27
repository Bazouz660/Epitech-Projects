/*
** EPITECH PROJECT, 2022
** fqsfs
** File description:
** sqdsqdsqd
*/

#include"rpg.h"
#include "defines.h"
#include "prototypes.h"

void create_exclamation_point(core_t *c)
{
    c->dialogue.exclamations = sfSprite_create();
    c->dialogue.exclamationt = sfTexture_createFromFile
    ("sprites/exclamation.png", NULL);
    sfSprite_setTexture(c->dialogue.exclamations, c->dialogue.exclamationt, 
    sfTrue);
}

static void draw_exclamation_point(core_t *c)
{
    sfVector2f pos = sfSprite_getPosition(STAGE.npc[1].npc_sp);
    sfVector2f blacksmith = sfSprite_getPosition(STAGE.npc[0].npc_sp);

    if ((c->dialogue.end_blacksmith == sfTrue || 
    c->dialogue.start_blacksmith == sfTrue) && c->scene_status == 3) {
        blacksmith.x += 10;
        blacksmith.y -= 230;
        sfSprite_setPosition(c->dialogue.exclamations, blacksmith);
        sfRenderWindow_drawSprite(c->window, c->dialogue.exclamations, NULL);
    }
    if (c->dialogue.start_quest == sfTrue) {
        pos.x -= 3;
        pos.y -= 120;
        sfSprite_setPosition(c->dialogue.exclamations, pos);
        sfRenderWindow_drawSprite(c->window, c->dialogue.exclamations, NULL);
    }
}

static void quest_steps(core_t *c)
{
    if (c->dialogue.quest_kills == 3 && c->dialogue.quest == sfTrue) {
        c->dialogue.quest_kills = 0;
        c->dialogue.start_blacksmith = sfFalse;
        c->dialogue.end_blacksmith = sfTrue;
        c->dialogue.quest = sfFalse;
    }
}

void render_quest(core_t *c)
{
    sfFloatRect npc = sfSprite_getGlobalBounds(STAGE.npc[1].npc_sp);
    sfFloatRect player = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfVector2f pos3 = sfSprite_getPosition(STAGE.npc[1].npc_sp);

    quest_steps(c);
    draw_exclamation_point(c);
    if (sfFloatRect_intersects(&npc, &player, NULL)) {
        pos3 = (sfVector2f) {pos3.x + 80, pos3.y - 30};
        sfSprite_setPosition(c->stage->campfires->key_prompt, pos3);
        sfRenderWindow_drawSprite(c->window, c->stage->campfires->key_prompt,
        NULL);
    }
    if (sfFloatRect_intersects(&npc, &player, NULL) &&
        sfKeyboard_isKeyPressed(c->keys.pray)){
        c->dialogue.speak_npc = sfTrue;
        c->dialogue.start_quest = sfFalse;
    }
}