/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** event.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void save_stats(core_t *c)
{
    c->p.health = c->p.health_mem;
    c->save.exp = c->p.exp;
    c->save.vigor = c->p.vigor;
    c->save.gold = c->p.gold;
    c->save.lvl = c->p.level;
    c->save.stam = c->p.stam_inv;
    c->save.agility = c->p.agility;
    c->save.strength = c->p.strength;
    c->save.stage_index = c->stage_index;
}

void reset_enemies(core_t *c, enemies_t *head)
{
    while (head != NULL) {
        delete_enemy(c, head, 0);
        head = head->next;
    }
    create_enemies(c, STAGE.enemies_nb);
}

static void handle_campfire(core_t *c)
{
    sfFloatRect rect1 = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfFloatRect rect2;

    for (int i = 0; STAGE.campfires[i].lit != -1; i++) {
        rect2 = sfSprite_getGlobalBounds(STAGE.campfires[i].sprite);
        if (sfFloatRect_intersects(&rect1, &rect2, NULL) && c->saving == 0) {
            sfSound_play(c->audio.camp);
            STAGE.campfires[i].lit = True;
            save_stats(c);
            c->clock.pray_clock = c->clock.seconds;
            c->pst.pray_state = 0;
            c->pst.praying = True;
            c->save.last_camp = sfSprite_getPosition(STAGE.campfires[i].sprite);
            c->clock.saving_clock = c->clock.seconds;
            c->saving = 1;
            save_in_file(c);
            reset_enemies(c, STAGE.e);
        }
    }
}

static void pause_event(core_t *c)
{
    sfVector2f pos;
    sfVector2f pos2 = {0, 0};
    static int can_click = 1;

    pos.x = sfRenderWindow_getSize(c->window).x / 2;
    pos.y = sfRenderWindow_getSize(c->window).y / 2;
    if (sfKeyboard_isKeyPressed(c->keys.back) && can_click == 1) {
        can_click = 0;
        c->paused == 1 ? (c->paused = 0) : (c->paused = 1);
        c->inventory.status = 0;
    } else if (c->event.type == sfEvtKeyReleased
        && !sfKeyboard_isKeyPressed(c->keys.back))
        can_click = 1;
}

void handle_events(core_t *c)
{
    sfRenderWindow_pollEvent(c->window, &c->event);
    if (c->event.type == sfEvtKeyReleased && c->mv.global_vect.y == 0
        && c->pst.grounded == True)
        c->mv.global_vect.x = 0;
    if (c->event.type == sfEvtMouseButtonReleased)
        c->keys.can_click = True;
    if (c->event.type == sfEvtClosed)
        sfRenderWindow_close(c->window);
    c->pst.memcrouching = sfFalse;
    pause_event(c);
    if (sfKeyboard_isKeyPressed(c->keys.pray) && c->pst.grounded == True)
        handle_campfire(c);
}
