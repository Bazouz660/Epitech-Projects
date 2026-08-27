/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** commands
*/

#pragma once

#include "server.h"

typedef struct gui_commands_s {
    char* command;
    void (*func)(client_t *, server_t *, char **);
} gui_commands_t;

typedef struct ai_commands_s {
    char* command;
    int (*func)(client_t *, server_t *, char **);
} ai_commands_t;

// ai commands
int forward(client_t *, server_t *, char **);
int right(client_t *, server_t *, char **);
int left(client_t *, server_t *, char **);
int take(client_t* client, server_t* server, char** args);

// gui commands
void bct(client_t *, server_t *, char **);
void mct(client_t *, server_t *, char **);
void tna(client_t *, server_t *, char **);
void pnw(client_t *, server_t *, char **);
void ppo(client_t *, server_t *, char **);
void plv(client_t *, server_t *, char **);
void pin(client_t *, server_t *, char **);
void pdi(client_t *, server_t *, char **);
void pex(client_t *, server_t *, char **);
void pbc(client_t *, server_t *, char **);
void pfk(client_t *, server_t *, char **);
void sgt(client_t *, server_t *, char **);
void sst(client_t *, server_t *, char **);
void sbp(client_t *, server_t *, char **);
void suc(client_t *, server_t *, char **);
void smg(client_t *, server_t *, char **);
void msz(client_t *, server_t *, char **);
void seg(client_t *, server_t *, char **);
void edi(client_t *, server_t *, char **);
void ebo(client_t *, server_t *, char **);
void enw(client_t *, server_t *, char **);
void pgt(client_t *, server_t *, char **);
void pdr(client_t *, server_t *, char **);

static const gui_commands_t gui_cmdtable[] = {
    {"msz", msz},
    {"bct", bct},
    {"mct", mct},
    {"tna", tna},
    {"pnw", pnw},
    {"ppo", ppo},
    {"plv", plv},
    {"pin", pin},
    {"pdi", pdi},
    {"pex", pex},
    {"pbc", pbc},
    {"pfk", pfk},
    {"seg", seg},
    {"smg", smg},
    {"sgt", sgt},
    {"sst", sst},
    {"EOF", NULL}
};

static const ai_commands_t ai_cmdtable[] = {
    {"Forward", forward},
    {"Right", right},
    {"Left", left},
    {"Take", take},
    {"EOF", NULL}
};
