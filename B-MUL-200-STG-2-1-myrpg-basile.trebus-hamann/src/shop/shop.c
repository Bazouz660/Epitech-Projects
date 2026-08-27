/*
** EPITECH PROJECT, 2022
** dqdd
** File description:
** dqDd
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void event_shop(core_t *c)
{
    sfFloatRect rect = sfRectangleShape_getGlobalBounds(c->shop.shop_entrance);
    sfFloatRect player = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfVector2f pos = {4493, 3867};
    sfVector2f pos2 = sfRectangleShape_getPosition(c->shop.shop_entrance);
    static int can_click = 1;

    if (sfFloatRect_intersects(&rect, &player, NULL) == sfTrue &&
        sfKeyboard_isKeyPressed(c->keys.interaction)
        && c->clock.seconds > c->clock.shop_clock + 0.1) {
        c->clock.shop_clock = c->clock.seconds;
        sfView_setCenter(c->view, init_fvect(pos.x + 780, pos.y - 100));
        sfSprite_setPosition(c->p.player_hitbox, pos);
        sfRenderWindow_setView(c->window, c->view);
        randomise_shop_inventory(c);
        can_click = 0;
        c->scene_status = 3;
    }
    if (sfFloatRect_intersects(&rect, &player, NULL)) {
        pos2 = (sfVector2f){pos2.x + 40, pos2.y - 80};
        sfSprite_setPosition(c->stage->campfires->key_prompt, pos2);
        sfRenderWindow_drawSprite(c->window, c->stage->campfires->key_prompt,
        NULL);
    }
}

void trigger_dialogue(core_t *c)
{
    sfFloatRect rect = sfRectangleShape_getGlobalBounds(c->shop.blacksmith_rect);
    sfFloatRect player = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfVector2f pos2 = sfRectangleShape_getPosition(c->shop.blacksmith_rect);

    if (sfFloatRect_intersects(&rect, &player, NULL)
        && sfKeyboard_isKeyPressed(c->keys.pray))
        c->dialogue.speak_blacksmith = sfTrue;
    if (sfFloatRect_intersects(&rect, &player, NULL)) {
        init_trading(c);
        pos2.y -= 50;
        pos2.x += 40;
        sfSprite_setPosition(c->stage->campfires->key_prompt, pos2);
        sfRenderWindow_drawSprite(c->window,c->stage->campfires->key_prompt,
        NULL);
        set_sprite_pos(c->shop.trade_prompt, pos2.x + 30, pos2.y - 35);
        sfRenderWindow_drawSprite(c->window, c->shop.trade_prompt,
        NULL);
    }
}

void draw_prompt_leave(core_t *c)
{
    sfFloatRect leave = sfSprite_getGlobalBounds(c->shop.door_leaves);
    sfVector2f pos3 = sfSprite_getPosition(c->shop.door_leaves);
    sfFloatRect player = sfSprite_getGlobalBounds(c->p.player_hitbox);

    if (sfFloatRect_intersects(&leave, &player, NULL)) {
        pos3 = (sfVector2f) {pos3.x + 80, pos3.y - 30};
        sfSprite_setPosition(c->stage->campfires->key_prompt, pos3);
        sfRenderWindow_drawSprite(c->window, c->stage->campfires->key_prompt, NULL);
    }
}

void draw_shop_slots(core_t *c)
{
    sfVector2f pos = {sfSprite_getPosition(c->shop.shop_inv).x + 235.5,
    sfSprite_getPosition(c->shop.shop_inv).y + 270};
    sfVector2f pos2 = pos;
    sfVector2f pos3 = pos;

    pos3 = init_fvect(pos3.x - 177, pos3.y + 30);
    for (int i = 0; c->shop.slots[i].rect != NULL; i++) {
        if (i != 0 && i % 4 == 0) {
            pos.y += 60;
            pos.x = pos2.x;
        } else if (i != 0)
            pos.x += 59.8;
        sfRectangleShape_setPosition(c->shop.slots[i].rect, pos);
        sfRenderWindow_drawSprite(c->window, c->shop.slots[i].obj, NULL);
    }
}

static void set_stats_desc(core_t *c, int i, sfVector2f pos)
{
    sfText_setString(c->inventory.desc.txt_armor,
    my_int_to_str(c->item[c->shop.slots[i].id].stats.armor * 100));
    sfText_setPosition(c->inventory.desc.txt_armor,
    init_fvect(pos.x + 200, pos.y + 37));
    sfText_setString(c->inventory.desc.txt_dmg,
    my_int_to_str(c->item[c->shop.slots[i].id].stats.dmg_boost * 10));
    sfText_setPosition(c->inventory.desc.txt_dmg,
    init_fvect(pos.x + 200, pos.y + 62));
    sfText_setString(c->inventory.desc.txt_life_reg,
    my_int_to_str(c->item[c->shop.slots[i].id].stats.life_reg));
    sfText_setPosition(c->inventory.desc.txt_life_reg,
    init_fvect(pos.x + 200, pos.y + 90));
    sfText_setString(c->inventory.desc.txt_xp_gain,
    my_int_to_str(c->item[c->shop.slots[i].id].stats.xp_reward));
    sfText_setPosition(c->inventory.desc.txt_xp_gain,
    init_fvect(pos.x + 200, pos.y + 120));
    sfText_setString(c->inventory.desc.txt_cost,
    my_int_to_str(c->item[c->shop.slots[i].id].stats.cost));
    sfText_setPosition(c->inventory.desc.txt_cost,
    init_fvect(pos.x + 200, pos.y + 203));
}

void show_description_shop(core_t *c)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(c->window);
    sfVector2f cursor_pos = {mouse_pos.x + view_bounds(c->view).left,
    mouse_pos.y + view_bounds(c->view).top};

    for (int i = 0; c->shop.slots[i].rect != NULL; i++) {
        if (get_mouse_intersect_view(c,
            sfSprite_getGlobalBounds(c->shop.slots[i].obj))
            && c->shop.slots[i].id != 0) {
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

void draw_shop(core_t *c)
{
    sfVector2f pos = sfSprite_getPosition(c->p.player);
    sfVector2f pos_blacksmith = {6000, 3860};

    sfSprite_setPosition(STAGE.npc[0].npc_sp, pos_blacksmith);
    update_clock(c);
    handle_particles(c);
    handle_hit_hitbox(c);
    if (c->pst.climbing == False && c->p.health > 0
        && c->inventory.status == 0 && c->dialogue.speak_blacksmith == sfFalse
        && c->dialogue.speak_npc == sfFalse)
        player_inputs(c);
    handle_gravity(c);
    handle_collisions(c);
    animate(c);
    move_all(c);
    handle_events(c);
    sfRenderWindow_drawSprite(c->window, STAGE.npc[0].npc_sp, NULL);
    trigger_dialogue(c);
    render_dialogue(c);
    sfRenderWindow_drawSprite(c->window, c->shop.door_leaves, NULL);
    draw_prompt_leave(c);
    sfRenderWindow_drawSprite(c->window, c->p.player, NULL);
    render_inventory(c);
    if (c->inventory.status == 1 && c->shop.trading == 1) {
        handle_trading(c);
        draw_shop_slots(c);
        show_description_shop(c);
    }
    place_cursor(c);
}

void render_shop(core_t *c)
{
    sfVector2f pos = sfRectangleShape_getPosition(c->shop.shop_entrance);
    sfVector2f pos2 = {0 + view_bounds(c->view).left, 45 + view_bounds(c->view).top};
    sfFloatRect player = sfSprite_getGlobalBounds(c->p.player_hitbox);
    sfFloatRect leave = sfSprite_getGlobalBounds(c->shop.door_leaves);

    sfRenderWindow_clear(c->window, sfBlack);
    sfSprite_setPosition(c->shop.back_s, pos2);
    sfRenderWindow_drawSprite(c->window, c->shop.back_s, NULL);
    draw_shop(c);
    if (sfKeyboard_isKeyPressed(c->keys.pray) &&
    sfFloatRect_intersects(&player, &leave, NULL) == sfTrue &&
    c->clock.seconds > c->clock.shop_clock + 0.1){
        c->clock.shop_clock = c->clock.seconds;
        sfSprite_setPosition(c->p.player_hitbox, init_fvect(pos.x - 100, pos.y));
        c->scene_status = 1;
    }
}