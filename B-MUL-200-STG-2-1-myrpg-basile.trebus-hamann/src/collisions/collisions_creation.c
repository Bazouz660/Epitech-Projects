/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** collisions_creation.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void create_wall(core_t *c, sfVector2f pos, sfVector2f size, int i)
{
    sfRectangleShape_setFillColor(c->co.wall[i], c->color.transparent_red);
    sfRectangleShape_setPosition(c->co.wall[i], pos);
    sfRectangleShape_setSize(c->co.wall[i], size);
}

void init_stage_0_cols(core_t *c)
{
    sfVector2f rect_pos;
    sfVector2f rect_size;

    for (int i = 0; i < 20; i++)
        c->co.wall[i] = sfRectangleShape_create();
    c->co.wall[20] = NULL;
    create_wall(c, init_fvect(0, 2796), init_fvect(8000, 450), 0);
    create_wall(c, init_fvect(-240, 1796), init_fvect(300, 1000), 1);
    create_wall(c, init_fvect(-240, 1687), init_fvect(4700, 354), 2);
    create_wall(c, init_fvect(4329, 1687), init_fvect(311, 853), 3);
    create_wall(c, init_fvect(4952, 800), init_fvect(311, 2000), 4);
    create_wall(c, init_fvect(1717, -200), init_fvect(311, 2000), 5);
    create_wall(c, init_fvect(2320, 625), init_fvect(5000, 352), 6);
    create_wall(c, init_fvect(2283, 625), init_fvect(311, 808), 7);
    create_wall(c, init_fvect(2000, -500), init_fvect(4167, 490), 8);
    create_wall(c, init_fvect(6373, -500), init_fvect(300, 490), 9);
    create_wall(c, init_fvect(6615, -200), init_fvect(300, 1000), 10);
    create_wall(c, init_fvect(4000, 4000), init_fvect(2500, 60), 11);
    create_wall(c, init_fvect(6310, 3200), init_fvect(50, 1000), 12);
    create_wall(c, init_fvect(4300, 3200), init_fvect(50, 1000), 13);
}

void init_stage_1_cols(core_t *c)
{
    sfVector2f rect_pos;
    sfVector2f rect_size;

    for (int i = 0; i < 24; i++)
        c->co.wall[i] = sfRectangleShape_create();
    c->co.wall[24] = NULL;
    create_wall(c, init_fvect(675, 2840), init_fvect(8000, 450), 0);
    create_wall(c, init_fvect(-175, 1376), init_fvect(300, 1480), 1);
    create_wall(c, init_fvect(0, 730), init_fvect(5310, 680), 2);
    create_wall(c, init_fvect(1248, 1376), init_fvect(842, 790), 3);
    create_wall(c, init_fvect(1248, 2525), init_fvect(842, 310), 4);
    create_wall(c, init_fvect(2350, 1770), init_fvect(1665, 433), 5);
    create_wall(c, init_fvect(3950, 1832), init_fvect(300, 250), 6);
    create_wall(c, init_fvect(3211, 988), init_fvect(2858, 973), 7);
    create_wall(c, init_fvect(2350, 1770), init_fvect(310, 730), 8);
    create_wall(c, init_fvect(4018, 2720), init_fvect(3100, 130), 9);
    create_wall(c, init_fvect(4253, 2600), init_fvect(2950, 130), 10);
    create_wall(c, init_fvect(6993, 1900), init_fvect(100, 750), 11);
    create_wall(c, init_fvect(6410, 1990), init_fvect(640, 100), 12);
    create_wall(c, init_fvect(6374, 0), init_fvect(120, 2088), 13);
    create_wall(c, init_fvect(2100, -306), init_fvect(4400, 368), 14);
    create_wall(c, init_fvect(2074, -306), init_fvect(320, 780), 15);
    create_wall(c, init_fvect(1498, -1090), init_fvect(320, 2000), 16);
    create_wall(c, init_fvect(1498, -1440), init_fvect(2813, 450), 17);
    create_wall(c, init_fvect(4875, -1140), init_fvect(100, 1000), 18);
    create_wall(c, init_fvect(0, 2840), init_fvect(458, 400), 19);
    create_wall(c, init_fvect(4526, -1440), init_fvect(500, 450), 20);
    create_wall(c, init_fvect(2660, 2394), init_fvect(181, 107), 21);
    create_wall(c, init_fvect(314, 1908), init_fvect(208, 636), 22);
    create_wall(c, init_fvect(426, 1908), init_fvect(957, 259), 23);
}

void init_stage_3_cols(core_t *c)
{

    sfVector2f rect_pos;
    sfVector2f rect_size;

    for (int i = 0; i < 35; i++)
        c->co.wall[i] = sfRectangleShape_create();
    c->co.wall[35] = NULL;
    create_wall(c, init_fvect(-580, 2854), init_fvect(1400, 336), 0);
    create_wall(c, init_fvect(-888, 2698), init_fvect(314, 492), 1);
    create_wall(c, init_fvect(510, 1700), init_fvect(367, 1490), 2);
    create_wall(c, init_fvect(-1400, 2043), init_fvect(2220, 100), 3);
    create_wall(c, init_fvect(-1461, 1805), init_fvect(150, 600), 4);
    create_wall(c, init_fvect(-1400, 3905), init_fvect(4900, 100), 5);
    create_wall(c, init_fvect(3460, 2800), init_fvect(150, 1350), 6);
    create_wall(c, init_fvect(1900, 3414), init_fvect(1311, 210), 7);
    create_wall(c, init_fvect(1651, 2603), init_fvect(363, 1021), 8);
    create_wall(c, init_fvect(1651, 2603), init_fvect(3450, 254), 9);
    create_wall(c, init_fvect(800, 1655), init_fvect(3880, 234), 10);
    create_wall(c, init_fvect(3795, 1000), init_fvect(200, 700), 11);
    create_wall(c, init_fvect(4930, 1632), init_fvect(250, 1050), 12);
    create_wall(c, init_fvect(4930, 1632), init_fvect(2760, 100), 13);
    create_wall(c, init_fvect(3795, 800), init_fvect(883, 366), 14);
    create_wall(c, init_fvect(4300, 745), init_fvect(4300, 150), 15);
    create_wall(c, init_fvect(8326, 800), init_fvect(200, 2900), 16);
    create_wall(c, init_fvect(7505, 1632), init_fvect(200, 987), 17);
    create_wall(c, init_fvect(7005, 2420), init_fvect(670, 200), 18);
    create_wall(c, init_fvect(7020, 2420), init_fvect(130, 1000), 19);
    create_wall(c, init_fvect(7110, 3293), init_fvect(592, 150), 20);
    create_wall(c, init_fvect(7410, 3293), init_fvect(292, 500), 21);
    create_wall(c, init_fvect(7550, 3588), init_fvect(900, 200), 22);
    create_wall(c, init_fvect(8112, 3130), init_fvect(250, 100), 23);
    create_wall(c, init_fvect(7667, 2385), init_fvect(250, 100), 24);
    create_wall(c, init_fvect(8112, 2083), init_fvect(250, 100), 25);
    create_wall(c, init_fvect(7670, 1775), init_fvect(250, 100), 26);
    create_wall(c, init_fvect(848, 2753), init_fvect(238, 100), 27);
    create_wall(c, init_fvect(680, 3742), init_fvect(220, 500), 28);
    create_wall(c, init_fvect(1055, 3523), init_fvect(210, 100), 29);
    create_wall(c, init_fvect(1402, 3312), init_fvect(208, 100), 30);
    create_wall(c, init_fvect(1135, 3015), init_fvect(208, 100), 31);
    create_wall(c, init_fvect(1255, 2620), init_fvect(208, 100), 32);
    create_wall(c, init_fvect(-1315, 2695), init_fvect(185, 100), 33);
    create_wall(c, init_fvect(-1461, 2695), init_fvect(150, 1500), 34);
}

void init_stage_2_cols(core_t *c)
{

    sfVector2f rect_pos;
    sfVector2f rect_size;

    for (int i = 0; i < 25; i++)
        c->co.wall[i] = sfRectangleShape_create();
    c->co.wall[25] = NULL;
    create_wall(c, init_fvect(-1800, 2840), init_fvect(2340, 450), 0);
    create_wall(c, init_fvect(1250, 2870), init_fvect(2200, 450), 1);
    create_wall(c, init_fvect(1120, 1695), init_fvect(370, 1200), 2);
    create_wall(c, init_fvect(-1827, 800), init_fvect(200, 2200), 3);
    create_wall(c, init_fvect(-1810, 760), init_fvect(3260, 200), 4);
    create_wall(c, init_fvect(-1365, 1695), init_fvect(525, 875), 5);
    create_wall(c, init_fvect(-1200, 1930), init_fvect(2400, 200), 6);
    create_wall(c, init_fvect(-840, 1695), init_fvect(220, 350), 7);
    create_wall(c, init_fvect(-287, 1695), init_fvect(610, 300), 8);
    create_wall(c, init_fvect(660, 1695), init_fvect(600, 300), 9);
    create_wall(c, init_fvect(400, 385), init_fvect(4235, 243), 10);
    create_wall(c, init_fvect(1200, 420), init_fvect(287, 540), 11);
    create_wall(c, init_fvect(1775, 1567), init_fvect(370, 100), 12);
    create_wall(c, init_fvect(2403, 1458), init_fvect(370, 100), 13);
    create_wall(c, init_fvect(3030, 1437), init_fvect(200, 1600), 14);
    create_wall(c, init_fvect(3030, 1437), init_fvect(2200, 300), 15);
    create_wall(c, init_fvect(4983, -400), init_fvect(150, 2200), 16);
    create_wall(c, init_fvect(1400, -665), init_fvect(3800, 373), 17);
    create_wall(c, init_fvect(604, -1400), init_fvect(330, 1465), 18);
    create_wall(c, init_fvect(604, -1440), init_fvect(3800, 100), 19);
    create_wall(c, init_fvect(4292, -1400), init_fvect(250, 500), 20);
    create_wall(c, init_fvect(410, -500), init_fvect(250, 900), 21);
    create_wall(c, init_fvect(746, 2840), init_fvect(450, 450), 22);
}
