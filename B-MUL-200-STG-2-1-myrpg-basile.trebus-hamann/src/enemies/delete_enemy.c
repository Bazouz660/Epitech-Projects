/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** delete_enemy.c
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void delete_enemy(core_t *c, enemies_t *head, int r)
{
    if (r == 1) {
        c->dialogue.quest_kills++;
        c->p.exp += head->entity.reward_xp;
        c->p.gold += head->entity.reward_gold;
    }
    delete_node(&STAGE.e, head);
}
