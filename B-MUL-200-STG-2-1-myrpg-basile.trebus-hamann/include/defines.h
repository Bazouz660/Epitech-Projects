/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann (copie 2)
** File description:
** defines.h
*/

#pragma once

#define E_KEY "sprites/keys/E_Key_Dark.png"

#define new_texture(path, intrect) sfTexture_createFromFile(path, intrect)

#define IDLE_PATH "sprites/player/idle.png"
#define RUN_PATH "sprites/player/run.png"
#define JUMP_PATH "sprites/player/jump.png"
#define FALL_PATH "sprites/player/fall.png"
#define CROUCH_PATH "sprites/player/crouch_idle.png"
#define ROLL_PATH "sprites/player/roll.png"
#define PRAY_START_PATH "sprites/player/pray_start.png"
#define PRAY_IDLE_PATH "sprites/player/pray_idle.png"
#define PRAY_END_PATH "sprites/player/pray_end.png"
#define HANGING_PATH "sprites/player/hanging.png"
#define STAND_ATCK_PATH "sprites/player/attacks/standing_attack.png"
#define STAND_ATCK2_PATH "sprites/player/attacks/standing_attack2.png"
#define STAND_ATCK3_PATH "sprites/player/attacks/standing_attack3.png"
#define RUN_ATCK_PATH "sprites/player/attacks/run_attack.png"
#define FALL_ATCK_PATH "sprites/player/attacks/attack_from_air1.png"
#define FALL_ATCK2_PATH "sprites/player/attacks/attack_from_air2.png"
#define JUMP_ATCK_PATH "sprites/player/attacks/jump_attack.png"
#define DEATH_PATH "sprites/player/death.png"
#define HEAL_PATH "sprites/player/heal.png"
#define CLIMB_PATH "sprites/player/climb.png"
#define BUTTON_PLAY_PATH "sprites/button/play.png"
#define BUTTON_OPTION_PATH "sprites/button/option.png"
#define BUTTON_EXIT_PATH "sprites/button/exit.png"
#define BUTTON_30FPS_PATH "sprites/button/30fps.png"
#define BUTTON_60FPS_PATH "sprites/button/60fps.png"
#define BUTTON_90FPS_PATH "sprites/button/90fps.png"
#define BUTTON_120FPS_PATH "sprites/button/120fps.png"
#define BUTTON_LEAVE_PATH "sprites/button/leave.png"
#define BUTTON_UP_PATH "sprites/button/template_sound.png"
#define BUTTON_DOWN_PATH "sprites/button/template_sound_moins.png"
#define SOUND_EFFECT_PATH "sounds/button_se.wav"
#define MENU_BACKGROUND "./sprites/background/background_no_char.jpg"
#define TYPE1_WALK "sprites/enemies/type1/walk.png"
#define TYPE1_DEATH "sprites/enemies/type1/death.png"
#define TYPE1_IDLE "sprites/enemies/type1/idle.png"
#define TYPE1_ATK1 "sprites/enemies/type1/attack_a.png"
#define ENTER_PROMPT "sprites/keys/Enter_Key_Dark.png"

#define LIFE_POT_PATH "sprites/items/life_pot.png"
#define XP_POT_PATH "sprites/items/xp_pot.png"

#define SOUND_TYPE1_DEATH1 "sounds/type1/death1.ogg"
#define SOUND_TYPE1_DEATH2 "sounds/type1/death2.ogg"
#define SOUND_TYPE1_DEATH3 "sounds/type1/death3.ogg"
#define SOUND_TYPE1_DEATH4 "sounds/type1/death4.ogg"
#define SOUND_TYPE1_HURT "sounds/type1/hurt.ogg"

#define G_FORCE 0.8
#define G_FORCE2 0.2
#define MAX_FALL_SPD -75
#define MAX_SLIDE_SPD -10

#define HB_EMPTY "sprites/hud/emptybar_hpp.png"
#define HB_REDBAR "sprites/hud/redbar_hpp.png"

#define LIM_LEFT c->stage[c->stage_index].floor_rect[c->stage[c->stage_index]\
.floor_index].left
#define LIM_TOP c->stage[c->stage_index].floor_rect[c->stage[c->stage_index]\
.floor_index].top
#define LIM_WIDTH c->stage[c->stage_index].floor_rect[c->stage[c->stage_index]\
.floor_index].width
#define LIM_HEIGHT c->stage[c->stage_index].floor_rect[c->stage[c->stage_index]\
.floor_index].height
#define G_LIM_TOP c->stage[c->stage_index].map_boundaries.top

#define STAGE c->stage[c->stage_index]

#define True 1
#define False 0

#define bool int
