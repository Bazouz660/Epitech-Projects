/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** save.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void write_value(FILE *f, int value)
{
    fwrite(my_int_to_str(value), 1, my_strlen(my_int_to_str(value)), f);
    fwrite("\n", 1, 1, f);
}

static void write_all_values(FILE *f, core_t *c)
{
    write_value(f, c->save.gold);
    write_value(f, c->save.lvl);
    write_value(f, c->save.exp);
    write_value(f, c->save.vigor);
    write_value(f, c->save.stam);
    write_value(f, c->save.strength);
    write_value(f, c->save.agility);
    write_value(f, c->save.stage_index);
    write_value(f, c->save.last_camp.x);
    write_value(f, c->save.last_camp.y);
    write_value(f, c->p.points);
    for (int i = 0; c->inventory.slots[i].rect != NULL; i++)
        write_value(f, c->inventory.slots[i].id);
    write_value(f, c->dialogue.quest);
}

void save_in_file(core_t *c)
{
    FILE *f;
    char *save = malloc(sizeof(char) * 1000);
    int x = 0;
    char *filepath = malloc(sizeof(char) * 100);

    my_strcpy(filepath, "saves/");
    my_strcat(filepath, "save1");
    my_strcat(filepath, ".save");
    f = fopen(filepath, "w");
    fwrite("", 1, 0, f);
    fclose(f);
    f = fopen(filepath, "a");
    write_all_values(f, c);
    fclose(f);
}

static void set_vars(core_t *c, char **tmp)
{
    c->p.gold = my_atoi(tmp[0]);
    c->p.level = my_atoi(tmp[1]);
    c->p.exp = my_atoi(tmp[2]);
    c->p.vigor = my_atoi(tmp[3]);
    c->p.stam_inv = my_atoi(tmp[4]);
    c->p.strength = my_atoi(tmp[5]);
    c->p.agility = my_atoi(tmp[6]);
    c->save.last_camp.x = my_atoi(tmp[8]);
    c->save.last_camp.y = my_atoi(tmp[9]);
    c->p.points = my_atoi(tmp[10]);
    for (int i = 0; c->inventory.slots[i].rect != NULL; i++)
        c->inventory.slots[i].id = my_atoi(tmp[11 + i]);
    c->p.exp_buff = c->p.exp;
    c->dialogue.quest = my_atoi(tmp[30]);
    sfSprite_setPosition(c->p.player_hitbox, c->save.last_camp);
}

void load_save(core_t *c)
{
    int fd;
    char *buff = malloc(sizeof(char) * 1000);
    int x = 0;
    char *filepath = malloc(sizeof(char) * 100);
    char **tmp;

    my_strcpy(filepath, "saves/");
    my_strcat(filepath, "save1");
    my_strcat(filepath, ".save");
    fd = open(filepath, 0, O_RDONLY);
    read(fd, buff, 1000);
    tmp = my_str_to_word_array(buff);
    c->p.player_pos = c->save.last_camp;
    sfSprite_setPosition(c->p.player_hitbox, c->p.player_pos);
    close(fd);
    c->menu.how_to_play_open = False;
    c->stage_index = my_atoi(tmp[7]);
    if (c->stage_index == 0)
        init_stage_0(c);
    if (c->stage_index == 1)
        init_stage_1(c);
    if (c->stage_index == 2)
        init_stage_2(c);
    if (c->stage_index == 3)
        init_stage_3(c);
    set_vars(c, tmp);
}
