/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** main.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void end_game(core_t *c)
{
    sfFloatRect rect1 = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfFloatRect rect2 = {7152, 2836, 453, 467};

    if (sfFloatRect_intersects(&rect1, &rect2, NULL) && c->stage_index == 3) {
        sfSprite_setPosition(c->end, sfView_getCenter(c->view));
        sfRenderWindow_drawSprite(c->window, c->end, NULL);
    }
}

void render_game(core_t *c)
{
    update_clock(c);
    if (c->paused == 0) {
        handle_particles(c);
        handle_hit_hitbox(c);
        if (c->pst.climbing == False && c->p.health > 0
            && c->inventory.status == 0)
            player_inputs(c);
        handle_gravity(c);
        handle_lvl_stats(c);
        handle_collisions(c);
        handle_chests(c);
        handle_dmg(c);
        handle_stam(c);
        handle_exp(c);
        handle_enemies_direction(c);
        animate(c);
        move_all(c);
        handle_respawn(c);
    }
    handle_lvl_change(c);
    handle_events(c);
    if (c->paused == 1)
        handle_p_menu(c);
    draw_scene(c);
    end_game(c);
    c->p.gold = 1000;
    c->dialogue.blacksmith_str = get_word(c->dialogue.dictionnary, -1, 2);
    c->dialogue.npc_str = get_word(c->dialogue.dictionnary, 2, 6);
}

void analyse_events(core_t *c)
{
    if (c->event.type == sfEvtClosed)
        sfRenderWindow_close(c->window);
    if (c->bt_pressed == 8 && (c->event.type == sfEvtKeyReleased
        || c->event.type == sfEvtMouseButtonReleased)) {
        c->scene_status = 0;
        c->bt_pressed = 0;
        c->menu.fade_out_time = 0;
        c->menu.fade_out_curb = 0;
    }
}

int game_loop(void)
{
    core_t *c = malloc(sizeof(core_t));


    variables_declarations(c);
    sfSprite_setPosition(c->p.player_hitbox, c->co.global_pos);
    sfRenderWindow_setVerticalSyncEnabled(c->window, True);
    sfRenderWindow_setFramerateLimit(c->window, 60);
    map(c);
    srand(c->clock.seconds);
    while (sfRenderWindow_isOpen(c->window)) {
        if (c->scene_status == 0)
            render_menu(c);
        if (c->scene_status == 1)
            render_game(c);
        if (c->scene_status == 2)
            render_options(c);
        if(c->scene_status == 3)
            render_shop(c);
        while (sfRenderWindow_pollEvent(c->window, &c->event))
            analyse_events(c);
        sfRenderWindow_display(c->window);
    }
    return 0;
}

int main(int ac, char **av)
{
    return game_loop();
}