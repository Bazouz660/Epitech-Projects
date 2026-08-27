/*
** EPITECH PROJECT, 2021
** MY_HUNTER_BST
** File description:
** events.c
*/

#include "../includes/my_hunter.h"

h_p manage_imputs(h_p h, sfEvent event)
{
    if (sfMouse_isButtonPressed(sfMouseLeft) == sfTrue && h.reload_time <= 0)
        sfRenderWindow_drawSprite(h.window, h.gunshot, sfFalse);
    if ((sfMouse_getPositionRenderWindow(h.window).x >= 1600 && (sfMouse_getPositionRenderWindow(h.window).x <= 1710)))
        if ((sfMouse_getPositionRenderWindow(h.window).y >= 635 && (sfMouse_getPositionRenderWindow(h.window).y <= 770)))
            sfSound_play(h.easter_egg_sound);
    if (h.reload_time >= 120)
        if (sfKeyboard_isKeyPressed(sfKeyR) == sfTrue) {
            sfSound_play(h.reload_sound);
            h.reloading = 1;
        }
    manage_click(h.event.mouseButton, h.window, h.reload_time);
    if (close_window(h.window, h.event) == 1)
        h.exit = 1;
    return h;
}

h_p manage_hit1(h_p h)
{
    if (h.reporterpos.x >= (sfMouse_getPositionRenderWindow(h.window)).x - 150 && h.reporterpos.x <= (sfMouse_getPositionRenderWindow(h.window)).x - 10)
        if (h.reporterpos.y >= (sfMouse_getPositionRenderWindow(h.window)).y - 150 && h.reporterpos.y <= (sfMouse_getPositionRenderWindow(h.window)).y + 20 && h.reload_time <= 0) {
            h.score_count += 10;
            sfSprite_setPosition(h.blood_splatter, h.reporterpos);
            h.reporterpos.x = -200 - (random_number(-100, 400));
            sfRenderWindow_drawSprite(h.window, h.blood_splatter, sfFalse);
            sfSound_play(h.reporter_sound);
            h.score_str = my_revstr(int_to_string(h.result, h.score_count));
            h.score_str = fill_score(h.score_str, h.score_count / 10);
            h.score_str = my_revstr(h.score_str);
        }
    return h;
}

h_p manage_hit2(h_p h)
{
    if (h.heli_pos.x >= (sfMouse_getPositionRenderWindow(h.window)).x - 450 && h.heli_pos.x <= (sfMouse_getPositionRenderWindow(h.window)).x - 100)
        if (h.heli_pos.y >= (sfMouse_getPositionRenderWindow(h.window)).y - 250 && h.heli_pos.y <= (sfMouse_getPositionRenderWindow(h.window)).y - 110 && h.reload_time <= 0) {
            if (h.heli_health == 0) {
                h.score_count += 25;
                sfSprite_setPosition(h.explosion, h.heli_pos);
                h.heli_pos.x = -800;
                sfRenderWindow_drawSprite(h.window, h.explosion, sfFalse);
                sfSound_play(h.ricochet_sound);
                sfSound_play(h.explosion_sound);
                h.score_str = my_revstr(int_to_string(h.result, h.score_count));
                h.score_str = fill_score(h.score_str, h.score_count / 10);
                h.score_str = my_revstr(h.score_str);
                h.heli_health = 1;
            } else {
                sfSound_play(h.ricochet_sound);
                h.heli_health--;
            }
        }
    return h;
}

h_p manage_hit3(h_p h)
{
    if (h.reporterpos2.x >= (sfMouse_getPositionRenderWindow(h.window)).x - 150 && h.reporterpos2.x <= (sfMouse_getPositionRenderWindow(h.window)).x - 10)
        if (h.reporterpos2.y >= (sfMouse_getPositionRenderWindow(h.window)).y - 150 && h.reporterpos2.y <= (sfMouse_getPositionRenderWindow(h.window)).y + 20 && h.reload_time <= 0) {
            h.score_count += 10;
            sfSprite_setPosition(h.blood_splatter, h.reporterpos2);
            h.reporterpos2.x = -300 - (random_number(-100, 400));
            sfRenderWindow_drawSprite(h.window, h.blood_splatter, sfFalse);
            sfSound_play(h.reporter_sound);
            h.score_str = my_revstr(int_to_string(h.result, h.score_count));
            h.score_str = fill_score(h.score_str, h.score_count / 10);
            h.score_str = my_revstr(h.score_str);
        }
    return h;
}

h_p manage_events(h_p h)
{
    while (sfRenderWindow_pollEvent(h.window, &h.event)) {
        if (h.event.type == sfEvtMouseButtonPressed || h.event.type == sfEvtKeyPressed) {
            h = manage_imputs(h, h.event);
        }
        if (manage_click(h.event.mouseButton, h.window, h.reload_time) == 1) {
            sfSound_play(h.shot);
            h = manage_hit1(h);
            h = manage_hit2(h);
            h = manage_hit3(h);
            h.reload_time = 120;
        }
    }
    return h;
}