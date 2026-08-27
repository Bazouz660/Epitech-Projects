/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** variables.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void init_clocks(core_t *c)
{
    c->clock.clock = sfClock_create();
    c->clock.seconds = 0;
    c->clock.mvt_clock = 0;
    c->clock.gravity_clock = 0;
    c->clock.jump_clock = 0;
    c->clock.player_anim_clock = 0;
    c->clock.pray_clock = 0;
    c->clock.roll_cooldown = 0;
    c->light_clock = 0;
    c->clock.side_jump_clock = 0;
    c->clock.stam_clock = 0;
    c->clock.stam_cooldown = 0;
    c->clock.saving_clock = 0;
    c->clock.respawn_clock = 0;
    c->clock.inventory_clock = 0;
    c->clock.dialogue_clock = 0;
    c->clock.shop_clock = 0;
}

static void init_texture_dic(core_t *c)
{
    c->textures.ladder = sfTexture_createFromFile("sprites/ladder.png", NULL);
    c->textures.wall = sfTexture_createFromFile("sprites/wall.png", NULL);
    c->textures.floor = sfTexture_createFromFile("sprites/floor.jpg", NULL);
    c->textures.spikes = sfTexture_createFromFile("sprites/spikes.png", NULL);
    c->textures.interact_prompt = sfTexture_createFromFile(E_KEY, NULL);
    c->textures.empty = sfTexture_createFromFile("sprites/items/empty.png", NULL);
}

static void variables_declarations1(core_t *c)
{
    sfFloatRect rect = {0, 0, 1920, 1080};

    c->window = create_window("Dark Sus");
    c->co.wall = malloc(sizeof(sfRectangleShape *) * 200);
    init_texture_dic(c);
    init_defaut_sprites(c);
    init_colors(c);
    c->mv.global_vect.x = 0;
    c->mv.global_vect.y = 0;
    c->view = sfView_createFromRect(rect);
    c->dialogue.init = 0;
    c->saving = 0;
    c->dialogue.quest_kills = 0;
    c->dialogue.speak_blacksmith = sfFalse;
    c->dialogue.speak_npc = sfFalse;
    c->dialogue.quest = sfTrue;
    c->dialogue.start_quest = sfTrue;
    c->dialogue.start_blacksmith = sfTrue;
    c->dialogue.end_blacksmith = sfFalse;
}

static void variables_declarations2(core_t *c)
{
    c->stage = malloc(sizeof(stage_t) * 5);
    c->co.global_pos.x = 150;
    c->co.global_pos.y = 2700;
    c->save.last_camp = c->co.global_pos;
    c->change_scene = 0;
    c->paused = 0;
    c->p.player_pos.x = c->co.global_pos.x;
    init_animated_sprite(c->p.player, 2, 4);
    c->p.player_scale = sfSprite_getScale(c->p.player);
    sfSprite_setOrigin(c->p.player, get_sprite_center(c->p.player));
    set_sprite_pos(c->p.player, sfRenderWindow_getSize(c->window).x / 2 , 600);
    c->mv.acceleration = 1;
    c->p.player_speed = 10;
    init_sftext(c, &c->hud.inv_prom.key, 30);
    sfText_setString(c->hud.inv_prom.key, "I");
    sfText_setScale(c->hud.inv_prom.key, init_fvect(1.5, 1.5));
}

void init_p_menu(core_t *c)
{
    c->end = new_sprite("sprites/end.png", 1, 1);
    sfSprite_setOrigin(c->end, get_sprite_center(c->end));
    c->p_menu.resume = new_sprite("sprites/button/resume.png", 1, 1);
    c->p_menu.main_menu = new_sprite("sprites/button/main_menu.png", 1, 1);
    c->p_menu.exit = new_sprite("sprites/button/exit.png", 1, 1);
    init_animated_sprite(c->p_menu.resume, 3, 1);
    init_animated_sprite(c->p_menu.exit, 3, 1);
    init_animated_sprite(c->p_menu.main_menu, 3, 1);
}

void variables_declarations(core_t *c)
{
    init_menu(c);
    init_inventory(c);
    init_option(c);
    init_keyboard(c);
    create_dialogue(c);
    variables_declarations1(c);
    variables_declarations2(c);
    init_clocks(c);
    init_player_states(c);
    init_player_textures(c);
    init_sounds(c);
    init_hud(c);
    init_p_menu(c);
    init_shop_scene(c);
    sfRenderWindow_setMouseCursorVisible(c->window, False);
    c->fps = 60;
    c->scene_status = 0;
    c->bt_pressed = 0;
}
