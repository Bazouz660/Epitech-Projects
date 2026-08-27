/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** move_all.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void move_enemies(core_t *c, enemies_t *head)
{
    sfVector2f pos;
    sfFloatRect rect;

    while (head != NULL) {
        sfRectangleShape_move(head->entity.hitbox, head->entity.vect);
        pos = sfRectangleShape_getPosition(head->entity.hitbox);
        rect = sfRectangleShape_getGlobalBounds(head->entity.hitbox);
        pos.x -= rect.width / 2;
        pos.y -= 20;
        sfRectangleShape_setPosition(head->entity.hb.coutour, pos);
        sfRectangleShape_setPosition(head->entity.hb.red_bar, pos);
        head = head->next;
    }
}

void move_hud(core_t *c)
{
    sfVector2f temp;
    sfVector2f pos = {view_bounds(c->view).left, view_bounds(c->view).top};

    set_sprite_pos(c->hud.hotbar.i_a, pos.x + 150, pos.y + 800);
    set_sprite_pos(c->hud.hotbar.i_b, pos.x + 95, pos.y + 900);
    set_sprite_pos(c->hud.hotbar.i_c, pos.x + 195, pos.y + 910);
    temp.x = view_bounds(c->view).left + 40;
    temp.y = view_bounds(c->view).top + 40;
    sfSprite_setPosition(c->hud.p_health.sp_bar_hpp, temp);
    sfSprite_setPosition(c->hud.p_health.sp_rbar_hpp, temp);
    temp.y += 20;
    sfSprite_setPosition(c->hud.p_stam.sp_bar_sp, temp);
    sfSprite_setPosition(c->hud.p_stam.sp_gbar_sp, temp);
    temp.y += 700;
    sfSprite_setPosition(c->hud.hotbar.bg, temp);
    set_map_pos(c, init_fvect(sfView_getCenter(c->view).x - 800,
    sfView_getCenter(c->view).y + 300));
    sfSprite_setPosition(c->you_died, sfView_getCenter(c->view));
    sfSprite_setPosition(c->p_saved, sfView_getCenter(c->view));
    temp.y -= 700;
    temp.x += 1700;
    sfSprite_setPosition(c->hud.inv_prom.bg, temp);
    temp.x += 40;
    temp.y += 17;
    sfText_setPosition(c->hud.inv_prom.key, temp);
}

void move_p_menu(core_t *c)
{
    sfVector2f pos = sfView_getCenter(c->view);

    sfSprite_setPosition(c->p_menu.bg, pos);
    pos.x -= 210;
    set_sprite_pos(c->p_menu.resume, pos.x, pos.y - 150);
    set_sprite_pos(c->p_menu.main_menu, pos.x, pos.y + 20);
    set_sprite_pos(c->p_menu.exit, pos.x, pos.y + 190);
}

void move_all(core_t *c)
{
    sfVector2f temp = {-c->mv.global_vect.x, -c->mv.global_vect.y};
    int x_offset = 0;

    sfSprite_move(c->p.player, temp);
    sfSprite_move(c->p.player_hitbox, temp);
    sfRectangleShape_move(c->p.hit_hitbox, temp);
    if (c->scene_status != 3)
        move_view(c);
    sfSprite_setPosition(c->black_layer, init_fvect(view_bounds(c->view).left,
    view_bounds(c->view).top));
    move_p_menu(c);
    if ((c->pst.hanging == True || (c->pst.sliding == True
        && c->mv.global_vect.y < -5)) && c->pst.grounded == False)
        x_offset = 23 * c->pst.p_direction;
    set_sprite_pos(c->p.player, sfSprite_getPosition(c->p.player_hitbox).x + \
    (sfSprite_getGlobalBounds(c->p.player_hitbox).width / 2) - x_offset,
    sfSprite_getPosition(c->p.player_hitbox).y + 48);
    move_enemies(c, STAGE.e);
    move_hud(c);
}
