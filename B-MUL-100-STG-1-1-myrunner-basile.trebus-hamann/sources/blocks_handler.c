/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** blocks_handler.c
*/

#include "../includes/my_runner.h"

h_p add_block_to_list(h_p h, int posX, int posY)
{
    h.b_list = (block_list_t *)malloc(sizeof(block_list_t));
    h.b_list->block = new_sprite("sprites/block.jpg", 0.2, 0.2);
    h.b_list->animation_pos = 0;
    h.b_list->block_pos.x = posX;
    h.b_list->block_pos.y = posY;
    h.b_list->deleted = 0;
    sfSprite_setPosition(h.b_list->block, h.b_list->block_pos);
    h.b_list->next = NULL;
    if (h.b_b.end == NULL)
        h.b_b.start = h.b_b.end = h.b_list;
    else {
        h.b_b.end->next = h.b_list;
        h.b_b.end = h.b_list;
    }
    h.b_b.end->next = h.b_b.start;
    return (h);
}

h_p draw_or_delete_block(h_p h, sfVector2f block_pos)
{
    if (block_pos.x > -150 && h.b_list != NULL)
        sfRenderWindow_drawSprite(h.window, h.b_list->block, NULL);
    else if (block_pos.x < -200) {
        sfSprite_destroy(h.b_list->block);
        h.b_list->deleted = 1;
    }
    return h;
}

h_p move_block(h_p h)
{
    sfSprite_move(h.b_list->block, h.block_offset);
    return h;
}

h_p manage_blocks_collisions(h_p h)
{
    sfVector2f block_pos = sfSprite_getPosition(h.b_list->block);

    h.win = 0;
    if ((h.player_pos.x >= block_pos.x - 60
        && h.player_pos.x <= block_pos.x + 200))
        h = check_collision(h, block_pos);
    if (h.player_pos.y > 800) {
        h.fix.x = h.player_pos.x;
        h.fix.y = 800;
        sfSprite_setPosition(h.tank_man, h.fix);
    }
    h = move_block(h);
    if ((h.player_pos.y < 800) && (h.jumping == 0) && h.d_col == 0)
        h.falling = 1;
    h = draw_or_delete_block(h, block_pos);
    return h;
}

h_p manage_blocks(h_p h)
{
    static int offset = 0;
    static int idle_anim = 0;
    h.win = 1;

    for (int i = 1; i <= h.blocks; i++) {
        if (h.b_list->deleted == 0)
            h = manage_blocks_collisions(h);
        if (i <= h.blocks - 1)
            h.b_list = h.b_list->next;
    }
    if (((h.d_col == 0 && h.player_pos.x > 160) && h.f_col == 0 && h.sliding == 0
        && h.player_pos.y == 800) || sfKeyboard_isKeyPressed(sfKeyD)
        || sfKeyboard_isKeyPressed(sfKeyQ) || h.jumping == 1) {
        sfSprite_setTexture(h.tank_man, h.running_txt, sfFalse);
        offset = 0;
        h.idling = 0;
    }
    return h;
}
