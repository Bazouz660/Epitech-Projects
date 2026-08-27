/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** create_map.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void create_wall_1(sfVector2f size, sfVertex tmp, sfVector2f pos,
sfVertexArray **walls)
{
    sfColor dark = sfColor_fromRGBA(100, 100, 100, 255);

    tmp.color = sfWhite;
    tmp.texCoords = init_fvect(0, 0);
    tmp.position = init_fvect(pos.x, pos.y);
    sfVertexArray_append(walls[0], tmp);
    tmp.color = dark;
    tmp.texCoords = init_fvect(500, 0);
    tmp.position = init_fvect(pos.x + size.x, pos.y - (size.y / 2));
    sfVertexArray_append(walls[0], tmp);
    tmp.color = dark;
    tmp.texCoords = init_fvect(500, 500);
    tmp.position = init_fvect(pos.x + size.x, pos.y + (size.y / 2));
    sfVertexArray_append(walls[0], tmp);
    tmp.color = sfWhite;
    tmp.texCoords = init_fvect(0, 500);
    tmp.position = init_fvect(pos.x, pos.y + size.y);
    sfVertexArray_append(walls[0], tmp);
    sfVertexArray_setPrimitiveType(walls[0], sfQuads);
}

void create_wall_2(sfVector2f size, sfVertex tmp, sfVector2f pos,
sfVertexArray **walls)
{
    sfColor dark = sfColor_fromRGBA(100, 100, 100, 255);

    tmp.color = dark;
    tmp.position = init_fvect(pos.x, pos.y - size.y / 2);
    tmp.texCoords = init_fvect(0, 0);
    sfVertexArray_append(walls[1], tmp);
    tmp.color = sfWhite;
    tmp.position = init_fvect(pos.x + size.x, pos.y);
    tmp.texCoords = init_fvect(500, 0);
    sfVertexArray_append(walls[1], tmp);
    tmp.color = sfWhite;
    tmp.position = init_fvect(pos.x + size.x, pos.y + size.y);
    tmp.texCoords = init_fvect(500, 500);
    sfVertexArray_append(walls[1], tmp);
    tmp.color = dark;
    tmp.position = init_fvect(pos.x, pos.y + size.y / 2);
    tmp.texCoords = init_fvect(0, 500);
    sfVertexArray_append(walls[1], tmp);
    sfVertexArray_setPrimitiveType(walls[1], sfQuads);
}

void create_wall_3(sfVector2f size, sfVertex tmp, sfVector2f pos,
sfVertexArray **walls)
{
    sfColor dark = sfColor_fromRGBA(100, 100, 100, 255);

    tmp.color = dark;
    tmp.position = init_fvect(pos.x, pos.y - size.y / 2);
    tmp.texCoords = init_fvect(0, 0);
    sfVertexArray_append(walls[2], tmp);
    tmp.color = sfWhite;
    tmp.position = init_fvect(pos.x + size.x, pos.y);
    tmp.texCoords = init_fvect(500, 0);
    sfVertexArray_append(walls[2], tmp);
    tmp.color = sfWhite;
    tmp.position = init_fvect(pos.x, pos.y + size.y / 2);
    tmp.texCoords = init_fvect(500, 500);
    sfVertexArray_append(walls[2], tmp);
    tmp.color = sfWhite;
    tmp.position = init_fvect(pos.x - size.x, pos.y);
    tmp.texCoords = init_fvect(0, 500);
    sfVertexArray_append(walls[2], tmp);
    sfVertexArray_setPrimitiveType(walls[2], sfQuads);
}

void create_wall_4(sfVector2f size, sfVertex tmp, sfVector2f pos,
sfVertexArray **walls)
{
    tmp.color = sfWhite;
    tmp.position = init_fvect(pos.x, pos.y - size.y / 2);
    tmp.texCoords = init_fvect(0, 0);
    sfVertexArray_append(walls[3], tmp);
    tmp.color = sfWhite;
    tmp.position = init_fvect(pos.x + size.x, pos.y);
    tmp.texCoords = init_fvect(500, 0);
    sfVertexArray_append(walls[3], tmp);
    tmp.color = sfWhite;
    tmp.position = init_fvect(pos.x, pos.y + size.y / 2);
    tmp.texCoords = init_fvect(500, 500);
    sfVertexArray_append(walls[3], tmp);
    tmp.color = sfWhite;
    tmp.position = init_fvect(pos.x - size.x, pos.y);
    tmp.texCoords = init_fvect(0, 500);
    sfVertexArray_append(walls[3], tmp);
    sfVertexArray_setPrimitiveType(walls[3], sfQuads);
}

void create_floor(sfVertexArray **walls, sfVector2f pos, sfVector2f size,
int top)
{
    sfVertex tmp;
    sfColor dark = sfColor_fromRGBA(100, 100, 100, 255);

    for (int i = 0; i < 4; i++)
        walls[i] = sfVertexArray_create();
    create_wall_1(size, tmp, pos, walls);
    pos.x += size.x;
    create_wall_2(size, tmp, pos, walls);
    pos.y += size.y;
    create_wall_3(size, tmp, pos, walls);
    pos.y -= size.y;
    if (top == 0) {
        walls[3] = NULL;
        return;
    }
    create_wall_4(size, tmp, pos, walls);
}
