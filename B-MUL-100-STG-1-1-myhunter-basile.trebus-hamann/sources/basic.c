/*
** EPITECH PROJECT, 2021
** MY_HUNTER_BST
** File description:
** basic.c
*/

#include "../includes/my_hunter.h"

int manage_click(sfMouseButtonEvent event, sfRenderWindow *window, int reload_time)
{
    if (sfMouse_isButtonPressed(sfMouseLeft) == sfTrue && reload_time == 0) {
        return (1);
    } else
        return (0);
}

int close_window(sfRenderWindow *window, sfEvent event)
{
    if (event.type == sfEvtClosed ||
    sfKeyboard_isKeyPressed(sfKeyEscape)) {
        return(1);
    }
    return 0;
}

sfSprite *new_sprite(sfRenderWindow *window, char *texture_name, float x, float y)
{
    sfSprite *sprite = sfSprite_create();
    sfVector2f sprite_scale = {x, y};
    sfTexture *sprite_texture = sfTexture_createFromFile(texture_name, sfFalse);

    sfSprite_setTexture(sprite, sprite_texture, sfFalse);
    sfSprite_setScale(sprite, sprite_scale);
    return (sprite);
}

sfSprite *update_animated_sprite(sfSprite *sprite, int offset, int width, int height)
{
    sfIntRect sheet_pos = {offset, 0, width, height};

    sfSprite_setTextureRect(sprite, sheet_pos);
    return (sprite);
}