/*
** EPITECH PROJECT, 2021
** MY_HUNTER_BST
** File description:
** utils3.c
*/

#include "../includes/my_hunter.h"

void set_sprites_settings(h_p h)
{
    sfSprite_setOrigin(h.reload_ico, h.reload_ico_origin);
    sfSprite_setOrigin(h.explosion, h.explosion_origin);
    sfSprite_setPosition(h.leZ_bg, h.leZpos);
    sfSprite_setPosition(h.leZ, h.leZpos);
    sfSprite_setPosition(h.health_bar, h.health_bar_pos);
    sfSprite_setPosition(h.gunshot, h.gunshot_pos);
    update_animated_sprite(h.health_bar, h.health_spritesheet_offset, 991, 397);
    h.reporter2 = sfSprite_copy(h.reporter);
    update_animated_sprite(h.heli, 0, 600, 2524);
    update_animated_sprite(h.reporter, 0, 0, 397);
}

h_p initialize_other(h_p h)
{
    h.exit = 0;
    h.main_menu_choice = 0;
    set_sprites_settings(h);
    sfSound_setVolume(h.shot, 70);
    sfSound_setVolume(h.ricochet_sound, 50);
    sfSound_setVolume(h.reporter_sound, 35);
    sfRenderWindow_setFramerateLimit(h.window, 60);
    sfRenderWindow_setKeyRepeatEnabled(h.window, sfTrue);
    h.clock = sfClock_create();
    return h;
}

h_p manage_reload(h_p h)
{
    if (h.reload_time > 0 && h.reloading != 1)
        sfRenderWindow_drawSprite(h.window, h.reload_key_ico, sfFalse);
    if (h.reload_time > 0 && h.reloading == 1)
        sfRenderWindow_drawSprite(h.window, h.reload_ico, sfFalse);
    else
        h.angle = 0;
    return h;
}

void display_defeat_screen(h_p h, int highscore)
{
    if (h.defeat == sfTrue) {
        sfSprite_setPosition(h.end_text, h.end_text_pos);
        sfSprite_setPosition(h.exit_text, h.exit_text_pos);
        sfSound_stop(h.music);
        sfSound_play(h.defeat_sound);
        update_animated_sprite(h.health_bar, 0, 991, 397);
        sfRenderWindow_drawSprite(h.window, h.health_bar, sfFalse);
        sfRenderWindow_drawSprite(h.window, h.end_text, sfFalse);
        sfRenderWindow_drawSprite(h.window, h.exit_text, sfFalse);
        sfRenderWindow_display(h.window);
        if (h.score_count > highscore) {
               h.fp = fopen( "misc/highscore" , "w" );
               fwrite(int_to_string(h.result, h.score_count) , 1 , my_strlen_num(int_to_string(h.result, h.score_count)), h.fp );
               fclose(h.fp);
        }
    }
}

int manage_defeat_screen(h_p h, int highscore, char *highscore_str)
{
    while (h.defeat == sfTrue) {
        while (sfRenderWindow_pollEvent(h.window, &h.event)) {
            if (close_window(h.window, h.event) == 1)
                return 0;
            if (sfKeyboard_isKeyPressed(sfKeyEnter) == sfTrue) {
                sfRenderWindow_destroy(h.window);
                hunter(highscore, highscore_str);
            }
        }
    }
}