/*
** EPITECH PROJECT, 2021
** csfml.c
** File description:
** TREBUS BASILE
*/

#include "../includes/my_hunter.h"

h_p execute_game_loop(h_p h)
{
    h.time = sfClock_getElapsedTime(h.clock);
    h.seconds = h.time.microseconds / 1000000.0;
    h = check_for_defeat(h);
    h = refresh_image(h);
    h = manage_reload(h);
    h = loop_sprite_pos_h(h);
    h = manage_events(h);
    h = difficulty_adapter(h);
    h = rotate_reload_ico(h);
    h = animations_handler(h);
    sfRenderWindow_display(h.window);
    return h;
}

int main_menu_handler(h_p h)
{
    sfRenderWindow_drawSprite(h.window, h.main_menu, sfFalse);
    sfRenderWindow_display(h.window);
    while (sfRenderWindow_pollEvent(h.window, &h.event)) {
        if (sfMouse_isButtonPressed(sfMouseLeft) == sfTrue) {
            if ((sfMouse_getPositionRenderWindow(h.window).x >= 1464 && (sfMouse_getPositionRenderWindow(h.window).x <= 1781)))
                if ((sfMouse_getPositionRenderWindow(h.window).y >= 395 && (sfMouse_getPositionRenderWindow(h.window).y <= 514)))
                    return 1;
            if ((sfMouse_getPositionRenderWindow(h.window).x >= 1464 && (sfMouse_getPositionRenderWindow(h.window).x <= 1781)))
                if ((sfMouse_getPositionRenderWindow(h.window).y >= 574 && (sfMouse_getPositionRenderWindow(h.window).y <= 693)))
                    return -1;
        }
    }
    return 0;
}

void defeat_screen_handler(h_p h, int highscore, char *highscore_str)
{
    display_defeat_screen(h, highscore);
    manage_defeat_screen(h, highscore, highscore_str);
}

int hunter(int highscore, char *highscore_str)
{
    h_p h;

    h.window = create_window("CSFML");
    h = initialize_all_h(h, highscore_str);
    sfSound_play(h.main_menu_music);
    while (h.main_menu_choice != 1) {
        h.main_menu_choice = main_menu_handler(h);
        if (h.main_menu_choice == -1)
            return 0;
    }
    initialize_music(h);
    while (sfRenderWindow_isOpen(h.window) && h.defeat == sfFalse) {
        h = execute_game_loop(h);
        if (h.exit == 1) {
            sfSound_stop(h.music);
            sfRenderWindow_destroy(h.window);
            hunter(highscore, highscore_str);
            return 0;
        }
    }
    defeat_screen_handler(h, highscore, highscore_str);
    return 0;
}

void read_readme(void)
{
    char *buff;
    int fd = open("misc/README", 0, O_RDONLY);

    buff = malloc(sizeof(char) * 190 + 1);
    read(fd, buff, 190);
    write (1, buff, 190);
}

int main(int ac, char **av)
{
    int highscore;
    char *buff;
    int size = 20;
    int fd = open("misc/highscore", 0, O_RDONLY);
    
    if (ac > 1)
        if (my_strcmp(av[1], "-h") == 0) {
            read_readme();
            return 0;
        }
    buff = malloc(sizeof(char) * size + 1);
    read(fd, buff, size);
    highscore = my_getnbr(buff);
    close(fd);
    hunter(highscore, buff);
    free(buff);
    return (0);
}
