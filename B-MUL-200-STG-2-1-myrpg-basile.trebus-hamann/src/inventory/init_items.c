/*
** EPITECH PROJECT, 2022
** sfqsfsq
** File description:
** fsqfsqf
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void init_item_sprite(core_t *c)
{
    c->item = malloc(sizeof(item_t) * 30);
    for (int i = 0; i < 23; i++)
        c->item[i].object_s = sfSprite_create();
    c->item[23].object_s = NULL;
}

void init_ids(core_t *c)
{
    for (int i = 1; i < 23; i++) {
        i < 3 ? c->item[i].type = 1 : 0;
        i >= 3 && i < 13 ? c->item[i].type = 2 : 0;
        i >= 13 ? c->item[i].type = 3 : 0;
        c->item[i].id = i + 1;
    }
}

void init_item_texture(core_t *c)
{
    c->item[0].object_t = new_texture("sprites/items/empty.png", NULL);
    c->item[1].object_t = new_texture(LIFE_POT_PATH, NULL);
    c->item[2].object_t = new_texture(XP_POT_PATH, NULL);
    c->item[3].object_t = new_texture("sprites/items/sword1.png", NULL);
    c->item[4].object_t = new_texture("sprites/items/sword2.png", NULL);
    c->item[5].object_t = new_texture("sprites/items/sword3.png", NULL);
    c->item[6].object_t = new_texture("sprites/items/sword4.png", NULL);
    c->item[7].object_t = new_texture("sprites/items/sword5.png", NULL);
    c->item[8].object_t = new_texture("sprites/items/sword6.png", NULL);
    c->item[9].object_t = new_texture("sprites/items/sword7.png", NULL);
    c->item[10].object_t = new_texture("sprites/items/sword8.png", NULL);
    c->item[11].object_t = new_texture("sprites/items/sword9.png", NULL);
    c->item[12].object_t = new_texture("sprites/items/sword10.png", NULL);
    c->item[13].object_t = new_texture("sprites/items/armor1.png", NULL);
    c->item[14].object_t = new_texture("sprites/items/armor2.png", NULL);
    c->item[15].object_t = new_texture("sprites/items/armor3.png", NULL);
    c->item[16].object_t = new_texture("sprites/items/armor4.png", NULL);
    c->item[17].object_t = new_texture("sprites/items/armor5.png", NULL);
    c->item[18].object_t = new_texture("sprites/items/armor6.png", NULL);
    c->item[19].object_t = new_texture("sprites/items/armor7.png", NULL);
    c->item[20].object_t = new_texture("sprites/items/armor8.png", NULL);
    c->item[21].object_t = new_texture("sprites/items/armor9.png", NULL);
    c->item[22].object_t = new_texture("sprites/items/armor10.png", NULL);
    for (int i = 0; i < 23; i++)
        sfSprite_setTexture(c->item[i].object_s, c->item[i].object_t, sfTrue);
}

void init_items_stats(core_t *c)
{
    c->item[0].stats = (i_stats_t){0, 0, 0, 0, 0};
    c->item[1].stats = (i_stats_t){0, 0, 50, 0, 10};
    c->item[2].stats = (i_stats_t){0, 50, 0, 0, 50};
    c->item[3].stats = (i_stats_t){5, 0, 0, 0, 5};
    c->item[4].stats = (i_stats_t){5.5, 0, 0, 0, 7};
    c->item[5].stats = (i_stats_t){6, 0, 0, 0, 8};
    c->item[6].stats = (i_stats_t){6.5, 0, 0, 0, 12};
    c->item[7].stats = (i_stats_t){7, 0, 0, 0, 15};
    c->item[8].stats = (i_stats_t){7.5, 0, 0, 0, 18};
    c->item[9].stats = (i_stats_t){8, 0, 0, 0, 20};
    c->item[10].stats = (i_stats_t){8.5, 0, 0, 0, 25};
    c->item[11].stats = (i_stats_t){9, 0, 0, 0, 30};
    c->item[12].stats = (i_stats_t){9.5, 0, 0, 0, 40};
    c->item[13].stats = (i_stats_t){0, 0, 0, 0.08, 5};
    c->item[14].stats = (i_stats_t){0, 0, 0, 0.12, 7};
    c->item[15].stats = (i_stats_t){0, 0, 0, 0.15, 10};
    c->item[16].stats = (i_stats_t){0, 0, 0, 0.20, 15};
    c->item[17].stats = (i_stats_t){0, 0, 0, 0.25, 19};
    c->item[18].stats = (i_stats_t){0, 0, 0, 0.30, 22};
    c->item[19].stats = (i_stats_t){0, 0, 0, 0.35, 30};
    c->item[20].stats = (i_stats_t){0, 0, 0, 0.40, 35};
    c->item[21].stats = (i_stats_t){0, 0, 0, 0.45, 45};
    c->item[22].stats = (i_stats_t){0, 0, 0, 0.50, 50};
}

void init_item(core_t *c)
{
    init_item_sprite(c);
    init_item_texture(c);
    init_ids(c);
    init_items_stats(c);
}
