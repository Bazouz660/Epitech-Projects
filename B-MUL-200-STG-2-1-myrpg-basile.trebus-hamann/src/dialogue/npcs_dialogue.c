/*
** EPITECH PROJECT, 2022
** dfdfqf
** File description:
** qsfsqfsqf
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void blacksmith_dialogue(core_t *c)
{
    static int once = 0;
    char *finished = "Congrats you just won your first quest here take your\
 gold!";
    char *blacksmith = "Hello adventurer, you found me good job,\nnow i need you\
 to get rid of the three enemies just above us!";

    if (c->dialogue.speak_blacksmith == sfTrue) {
        display_box(c);
        if (c->dialogue.start_blacksmith == sfTrue) {
            display_dialogue(c, blacksmith);
            stop_dialogue(c, blacksmith);
        }
        if (c->dialogue.end_blacksmith == sfTrue) {
            once == 0 ? c->p.gold += 10 : 0;
            once = 1;
            display_dialogue(c, finished);
            stop_dialogue(c, finished);
        }else if (c->dialogue.start_blacksmith == sfFalse &&
                  c->dialogue.end_blacksmith == sfFalse){
            display_dialogue(c, c->dialogue.blacksmith_str);
            stop_dialogue(c, c->dialogue.blacksmith_str);
        }
    }
}

void firstnpc_dialogue(core_t *c)
{
    char *quest_str = "Hello adventurer, go see the blacksmith to\
 accomplish\nyour first quest!";

    if (c->dialogue.speak_npc == sfTrue) {
        display_box(c);
        if (c->dialogue.quest == sfTrue) {
            display_dialogue(c, quest_str);
            stop_dialogue(c, quest_str);
        }else {
            display_dialogue(c, c->dialogue.npc_str);
            stop_dialogue(c, c->dialogue.npc_str);
        }
    }
}
