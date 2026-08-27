/*
** EPITECH PROJECT, 2022
** sfqfsqfsqf
** File description:
** sqfsqfsqf
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

void reset_dialogue(core_t *c)
{
    c->dialogue.index = 0;
    sfText_destroy(c->dialogue.dialogue_text);
    c->dialogue.dialogue_text = sfText_create();
    sfText_setFont(c->dialogue.dialogue_text, c->menu.title_font);
    sfText_setCharacterSize(c->dialogue.dialogue_text, 30);
    sfText_setFillColor(c->dialogue.dialogue_text, sfWhite);
}

void display_box(core_t *c)
{
    sfVector2f pos = {0 + view_bounds(c->view).left, 900 + view_bounds(c->view).top};

    sfSprite_setPosition(c->dialogue.text_boxs, pos);
    sfRenderWindow_drawSprite(c->window, c->dialogue.text_boxs, NULL);
}

void display_dialogue(core_t *c, char *str)
{
    char current;
    sfVector2f ipos = sfSprite_getPosition(c->dialogue.text_boxs);
    sfVector2f pos = {ipos.x + 20, ipos.y + 30};

    if (c->dialogue.init == 0) {
        c->dialogue.init = 1;
        c->dialogue.dialogue_cpy = malloc(sizeof(char) * my_strlen(str));
    }
    if (c->clock.seconds > c->clock.dialogue_clock + 0.05 && str[c->dialogue.index]) {
        c->clock.dialogue_clock = c->clock.seconds;
        c->dialogue.dialogue_cpy[c->dialogue.index] = str[c->dialogue.index];
        c->dialogue.index++;
    }
    c->dialogue.dialogue_cpy[c->dialogue.index] = '\0';
    sfText_setString(c->dialogue.dialogue_text, c->dialogue.dialogue_cpy);
    sfText_setPosition(c->dialogue.dialogue_text, pos);
    sfRenderWindow_drawText(c->window, c->dialogue.dialogue_text, NULL);
}

void stop_dialogue(core_t *c, char *str)
{
    sfVector2f pos = sfSprite_getPosition(c->dialogue.text_boxs);

    if (my_strcmp(str, c->dialogue.dialogue_cpy) == 0
        && sfKeyboard_isKeyPressed(sfKeyEnter)) {
        reset_dialogue(c);
        c->dialogue.blacksmith_str = get_word(c->dialogue.dictionnary, 0, 2);
        c->dialogue.npc_str = get_word(c->dialogue.dictionnary, 3, 6);
        c->dialogue.speak_blacksmith = sfFalse;
        c->dialogue.speak_npc = sfFalse;
        c->dialogue.end_blacksmith = sfFalse;
    }
    if (my_strcmp(str, c->dialogue.dialogue_cpy) == 0) {
        pos = (sfVector2f) {pos.x + 930, pos.y + 72};
        sfSprite_setPosition(c->dialogue.enter_prompts, pos);
        sfRenderWindow_drawSprite(c->window, c->dialogue.enter_prompts, NULL);
    }
}


void render_dialogue(core_t *c)
{
    if (c->dialogue.quest == True)
        render_quest(c);
    blacksmith_dialogue(c);
    firstnpc_dialogue(c);
}
