/*
** EPITECH PROJECT, 2022
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** npc
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

npc_t create_npc(core_t *c, float posx, float posy, char *path)
{
    npc_t np;
    sfVector2f pos = {posx, posy};

    np.npc_sp = new_sprite(path, 1, 1);
    sfSprite_setOrigin(np.npc_sp, get_sprite_center(np.npc_sp));
    sfSprite_setPosition(np.npc_sp, pos);
    return np;
}

void blacksmith_anim(core_t *c)
{
    STAGE.npc[0].frame_index_bs = 1;
    init_animated_sprite(STAGE.npc[0].npc_sp, 13, 1);
    sfSprite_setOrigin(STAGE.npc[0].npc_sp,
    get_sprite_center(STAGE.npc[0].npc_sp));
    STAGE.npc[0].frames_bs.x = 13;
    STAGE.npc[0].frames_bs.y = 1;
    STAGE.npc[0].npc_bool = True;
    STAGE.npc[0].anim_bs = 0;
}

void npc_quest_anim(core_t *c)
{
    STAGE.npc[1].frame_index_bs = 1;
    init_animated_sprite(STAGE.npc[1].npc_sp, 5, 2);
    sfSprite_setOrigin(STAGE.npc[1].npc_sp,
    get_sprite_center(STAGE.npc[1].npc_sp));
    STAGE.npc[1].frames_bs.x = 5;
    STAGE.npc[1].frames_bs.y = 2;
    STAGE.npc[1].npc_bool = True;
    STAGE.npc[1].anim_bs = 0;
}

void npc_wizard_anim(core_t *c)
{
    STAGE.npc[2].frame_index_bs = 1;
    init_animated_sprite(STAGE.npc[2].npc_sp, 8, 1);
    sfSprite_setOrigin(STAGE.npc[2].npc_sp,
    get_sprite_center(STAGE.npc[2].npc_sp));
    STAGE.npc[2].frames_bs.x = 8;
    STAGE.npc[2].frames_bs.y = 1;
    STAGE.npc[2].npc_bool = True;
    STAGE.npc[2].anim_bs = 0;
}

void npc_bluewizard_anim(core_t *c)
{
    STAGE.npc[3].frame_index_bs = 1;
    init_animated_sprite(STAGE.npc[3].npc_sp, 6, 1);
    sfSprite_setOrigin(STAGE.npc[3].npc_sp,
    get_sprite_center(STAGE.npc[3].npc_sp));
    STAGE.npc[3].frames_bs.x = 6;
    STAGE.npc[3].frames_bs.y = 1;
    STAGE.npc[3].npc_bool = True;
    STAGE.npc[3].anim_bs = 0;
}