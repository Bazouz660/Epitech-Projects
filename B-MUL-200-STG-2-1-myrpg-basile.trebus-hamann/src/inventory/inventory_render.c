/*
** EPITECH PROJECT, 2022
** fsfsqf
** File description:
** sqfsqfsq
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void handle_inventory_items(core_t *c)
{
    sfVector2f pos;

    for (int i = 0; c->inventory.slots[i].rect != NULL; i++) {
        pos = sfRectangleShape_getPosition(c->inventory.slots[i].rect);
        if (c->inventory.slots[i].id > 0 && c->inventory.slots[i].id < 3) {
            sfSprite_setTexture(c->inventory.slots[i].obj,
            c->item[c->inventory.slots[i].id].object_t, True);
        }
    }
}

void draw_slots(core_t *c)
{
    sfVector2f pos = {sfSprite_getPosition(c->inventory.book_s).x + 380,
    sfSprite_getPosition(c->inventory.book_s).y + 276};
    sfVector2f pos2 = pos;
    sfVector2f pos3 = pos;

    pos3 = init_fvect(pos3.x - 177, pos3.y + 30);
    for (int i = 0; c->inventory.slots[i].rect != NULL; i++) {
        if (i % 4 == 0 && i != 0 && i < 16) {
            pos.y += 59.25;
            pos.x = pos2.x;
        }
        if (i < 16) {
            move_slot(c, i, pos);
            pos.x += 59.8;
        } else {
            move_slot(c, i, pos3);
            pos3.y += 60;
        }
        sfRenderWindow_drawSprite(c->window, c->inventory.slots[i].obj, NULL);
    }
}

static void set_hotbar(core_t *c)
{
    for (int i = 0; c->inventory.slots[i].rect != NULL; i++) {
        sfSprite_setTexture(c->inventory.slots[i].obj,
        c->item[c->inventory.slots[i].id].object_t, True);
    }
    sfSprite_setTexture(c->hud.hotbar.i_a,
    sfSprite_getTexture(c->inventory.slots[16].obj), True);
    sfSprite_setTexture(c->hud.hotbar.i_b,
    sfSprite_getTexture(c->inventory.slots[17].obj), True);
    sfSprite_setTexture(c->hud.hotbar.i_c,
    sfSprite_getTexture(c->inventory.slots[18].obj), True);
    sfSprite_setScale(c->hud.hotbar.i_a, init_fvect(2.21, 2.21));
    sfSprite_setScale(c->hud.hotbar.i_b, init_fvect(2.41, 2.41));
    sfSprite_setScale(c->hud.hotbar.i_c, init_fvect(2.11, 2.11));
}

static void set_stats_desc(core_t *c, int i, sfVector2f pos)
{
    sfText_setString(c->inventory.desc.txt_armor,
    my_int_to_str(c->item[c->inventory.slots[i].id].stats.armor * 100));
    sfText_setPosition(c->inventory.desc.txt_armor,
    init_fvect(pos.x + 200, pos.y + 37));
    sfText_setString(c->inventory.desc.txt_dmg,
    my_int_to_str(c->item[c->inventory.slots[i].id].stats.dmg_boost * 10));
    sfText_setPosition(c->inventory.desc.txt_dmg,
    init_fvect(pos.x + 200, pos.y + 62));
    sfText_setString(c->inventory.desc.txt_life_reg,
    my_int_to_str(c->item[c->inventory.slots[i].id].stats.life_reg));
    sfText_setPosition(c->inventory.desc.txt_life_reg,
    init_fvect(pos.x + 200, pos.y + 90));
    sfText_setString(c->inventory.desc.txt_xp_gain,
    my_int_to_str(c->item[c->inventory.slots[i].id].stats.xp_reward));
    sfText_setPosition(c->inventory.desc.txt_xp_gain,
    init_fvect(pos.x + 200, pos.y + 120));
    sfText_setString(c->inventory.desc.txt_cost,
    my_int_to_str(c->item[c->inventory.slots[i].id].stats.cost * 0.75));
    sfText_setPosition(c->inventory.desc.txt_cost,
    init_fvect(pos.x + 200, pos.y + 203));
}

static void update_inventory(core_t *c)
{
    move_rect(c);
    move_anim_inventory(c);
    money(c);
    level_str(c);
    vigor_inv(c);
    stam_inv(c);
    strength_inv(c);
    agility_inv(c);
    points_inv(c);
    if (c->p.points > 0) {
        handle_plus(c);
        move_plus(c);
    }
    handle_map_pan(c);
    draw_slots(c);
    handle_inventory_items(c);
    place_cursor(c);
    handle_selected_item(c);
    place_selected_i(c);
    show_description_inv(c);
}

void show_description_inv(core_t *c)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(c->window);
    sfVector2f cursor_pos = {mouse_pos.x + view_bounds(c->view).left,
    mouse_pos.y + view_bounds(c->view).top};

    for (int i = 0; c->inventory.slots[i].rect != NULL; i++) {
        if (get_mouse_intersect_view(c,
            sfSprite_getGlobalBounds(c->inventory.slots[i].obj))
            && c->inventory.slots[i].id != 0) {
            set_stats_desc(c, i, cursor_pos);
            set_sprite_pos(c->inventory.desc.bg, cursor_pos.x + 25,
            cursor_pos.y);
            sfRenderWindow_drawSprite(c->window, c->inventory.desc.bg, NULL);
            sfRenderWindow_drawText(c->window, c->inventory.desc.txt_armor, NULL);
            sfRenderWindow_drawText(c->window, c->inventory.desc.txt_dmg, NULL);
            sfRenderWindow_drawText(c->window, c->inventory.desc.txt_life_reg, NULL);
            sfRenderWindow_drawText(c->window, c->inventory.desc.txt_xp_gain, NULL);
            sfRenderWindow_drawText(c->window, c->inventory.desc.txt_cost, NULL);
        }
    }
}

void render_inventory(core_t *c)
{
    static int can_click = 1;
    sfVector2f pos;
    sfVector2f pos2 = {0, 0};

    c->pst.grounded == 1 &&
    c->inventory.status == 1 ? c->mv.global_vect.x = 0 : 0;
    if (sfKeyboard_isKeyPressed(c->keys.inventory) && can_click == 1) {
        can_click = 0;
        if (c->inventory.status == 0)
            c->inventory.status = 1;
        else
            c->inventory.status = 0;
        c->pst.climbing == True ? c->mv.global_vect.y = 0 : 0;
    } else if (c->event.type == sfEvtKeyReleased
        && !sfKeyboard_isKeyPressed(c->keys.inventory))
        can_click = 1;
    if (c->inventory.status == 1)
        update_inventory(c);
    set_hotbar(c);
    reset_selected_item(c);
}
