/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** mines_handler.c
*/

#include "../includes/my_runner.h"

h_p add_mine_to_list(h_p h, int posX, int posY)
{
    h.m_list = (mine_list_t *)malloc(sizeof(mine_list_t));
    h.m_list->exploded = 0;
    h.m_list->mine = new_sprite("sprites/mine.png", 1, 1);
    h.m_list->mine = update_animated_sprite(h.m_list->mine, 0, 100, 80);
    h.m_list->animation_pos = 0;
    h.m_list->mine_pos.x = posX;
    h.m_list->mine_pos.y = posY;
    sfSprite_setPosition(h.m_list->mine, h.m_list->mine_pos);
    h.m_list->next = NULL;
    if (h.m_b.end == NULL)
        h.m_b.start = h.m_b.end = h.m_list;
    else {
        h.m_b.end->next = h.m_list;
        h.m_b.end = h.m_list;
    }
    h.m_b.end->next = h.m_b.start;
    return (h);
}

h_p explode_mine(h_p h)
{
    sfVector2f mine_pos = sfSprite_getPosition(h.m_list->mine);
    if ((h.player_pos.x >= mine_pos.x
        && h.player_pos.x <= mine_pos.x + 165)
        && (h.player_pos.y >= mine_pos.y - 155
        && h.player_pos.y <= mine_pos.y + 20)) {
        if (h.m_list->exploded == 0) {
            sfSound_play(h.explosion);
            h.health_points--;
        }
        h.m_list->exploded = 1;
    }
    return h;
}

h_p manage_mines(h_p h)
{
    sfVector2f mine_offset = {-3, 0};

    if (h.mines > 0) {
        for (int i = 1; i <= h.mines; i++) {
            sfRenderWindow_drawSprite(h.window, h.m_list->mine, NULL);
            sfSprite_move(h.m_list->mine, mine_offset);
            h = explode_mine(h);
            if (h.m_list->exploded == 1) {
                h.r_explosion = h.seconds;
                h.m_list->animation_pos += 100;
                h.m_list->mine = update_animated_sprite(h.m_list->mine,
                h.m_list->animation_pos, 100, 80);
            }
            if (i <= h.mines - 1)
                h.m_list = h.m_list->next;
        }
    }
    return h;
}

h_p spawn_mines(h_p h)
{
    static int nb = 1;

    if (h.seconds - h.r_4 >= random_number(7, 50)) {
        h.r_4 = h.seconds;
        h = add_mine_to_list(h, 1900, nb + h.mines);
        h.mines++;
    }
    return h;
}
