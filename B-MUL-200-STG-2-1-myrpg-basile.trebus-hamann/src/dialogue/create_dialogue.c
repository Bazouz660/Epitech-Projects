/*
** EPITECH PROJECT, 2022
** sqsf
** File description:
** sq
*/

#include "rpg.h"
#include "defines.h"
#include "prototypes.h"

static void create_text_box(core_t *c)
{
    c->dialogue.text_boxs = sfSprite_create();
    c->dialogue.text_boxt = sfTexture_createFromFile("sprites/dialogue.png", 
    NULL);
    sfSprite_setTexture(c->dialogue.text_boxs, c->dialogue.text_boxt, sfTrue);
}

static void create_dialogue_txt(core_t *c)
{
    char *str = open_text("forgeron.txt");

    c->dialogue.dictionnary = str_to_word(str, "\n");
    c->dialogue.nb_words = nb_words(c->dialogue.dictionnary);
    c->dialogue.index = 0;
    c->dialogue.dialogue_cpy = NULL;
    c->dialogue.dialogue_text = sfText_create();
    sfText_setFont(c->dialogue.dialogue_text, c->menu.title_font);
    sfText_setCharacterSize(c->dialogue.dialogue_text, 30);
    sfText_setFillColor(c->dialogue.dialogue_text, sfWhite);
}

static void create_enterprompt(core_t *c)
{
    c->dialogue.enter_prompts = sfSprite_create();
    c->dialogue.enter_promptt = sfTexture_createFromFile(ENTER_PROMPT, NULL);
    sfSprite_setTexture(c->dialogue.enter_prompts, c->dialogue.enter_promptt, 
    sfTrue);
}

void create_dialogue(core_t *c)
{
    create_exclamation_point(c);
    create_text_box(c);
    create_dialogue_txt(c);
    create_enterprompt(c);
}