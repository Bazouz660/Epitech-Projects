/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** move_view.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

int view_boundaries_x(core_t *c)
{
    sfVector2f view_limit;

    view_limit.x = LIM_LEFT - view_bounds(c->view).left;
    if (view_bounds(c->view).left < LIM_LEFT) {
        sfView_setCenter(c->view, init_fvect((sfView_getCenter(c->view).x \
        + view_limit.x), sfView_getCenter(c->view).y));
        sfRenderWindow_setView(c->window, c->view);
        return 1;
    }
    view_limit.x = (LIM_LEFT + LIM_WIDTH) - (view_bounds(c->view).left \
    + view_bounds(c->view).width);
    if ((view_bounds(c->view).left + view_bounds(c->view).width) > \
    (LIM_LEFT + LIM_WIDTH)) {
        sfView_setCenter(c->view, init_fvect((sfView_getCenter(c->view).x + \
        view_limit.x), sfView_getCenter(c->view).y));
        sfRenderWindow_setView(c->window, c->view);
        return 1;
    }
    return 0;
}

int view_boundaries_y(core_t *c)
{
    sfVector2f view_limit;

    view_limit.y = LIM_TOP - view_bounds(c->view).top;
    if (view_bounds(c->view).top < LIM_TOP && STAGE.floor_index == STAGE.floors - 1) {
        sfView_setCenter(c->view, init_fvect((sfView_getCenter(c->view).x),
        sfView_getCenter(c->view).y + view_limit.y));
        sfRenderWindow_setView(c->window, c->view);
        return 1;
    }
    view_limit.y = (LIM_TOP + LIM_HEIGHT) - (view_bounds(c->view).top \
    + view_bounds(c->view).height);
    if ((view_bounds(c->view).top + view_bounds(c->view).height) > \
        (LIM_TOP + LIM_HEIGHT) && STAGE.floor_index == 0) {
        sfView_setCenter(c->view, init_fvect((sfView_getCenter(c->view).x),
        sfView_getCenter(c->view).y + view_limit.y));
        sfRenderWindow_setView(c->window, c->view);
        return 1;
    }
    return 0;
}

void view_boundaries(core_t *c)
{
    sfVector2f view_limit;

    if (sfSprite_getPosition(c->p.player_hitbox).y < LIM_TOP
        && STAGE.floor_index < STAGE.floors - 1) {
        c->stage[c->stage_index].floor_index++;
    } else if (sfSprite_getPosition(c->p.player_hitbox).y >
        LIM_TOP + LIM_HEIGHT && STAGE.floor_index > 0)
        c->stage[c->stage_index].floor_index--;
    view_limit.y = G_LIM_TOP - view_bounds(c->view).top;
    if (view_bounds(c->view).top < G_LIM_TOP) {
        sfView_setCenter(c->view, init_fvect(sfView_getCenter(c->view).x,
        (sfView_getCenter(c->view).y + view_limit.y)));
        sfRenderWindow_setView(c->window, c->view);
    }
    view_boundaries_y(c);
    if (view_boundaries_x(c) == 0) {
        reset_backgroundx(c);
        move_background(c);
    }
    reset_backgroundy(c);
}

void move_view(core_t *c)
{
    c->co.pbound = sfSprite_getGlobalBounds(c->p.player_hitbox);
    c->co.global_pos.x = c->co.pbound.left + (c->co.pbound.width / 2);
    c->co.global_pos.y = c->co.pbound.top - (c->co.pbound.height / 2);
    sfView_setCenter(c->view, c->co.global_pos);
    sfRenderWindow_setView(c->window, c->view);
    view_boundaries(c);
}
