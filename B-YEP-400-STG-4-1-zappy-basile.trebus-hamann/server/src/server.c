/*
** EPITECH PROJECT, 2023
** B-NWP-400-STG-4-1-myteams-clement1.thomas
** File description:
** command
*/

#include "commands.h"
#include "sutils.h"

void sendmessage(client_t* client, const char* code)
{
    char* msg = malloc(strlen(code) + 4);
    strcpy(msg, code);
    strcat(msg, "\n");
    if (write(client->fd_con, msg, strlen(msg)) < 0)
        exit(ERR_EX);
    free(msg);
}

bool getcmd(server_t* server, client_t* client)
{
    char* command = NULL;
    char buffer[MAX_BUFFER_SIZE];
    memset(buffer, 0, MAX_BUFFER_SIZE);
    if ((read(client->fd_con, buffer, MAX_BUFFER_SIZE)) == 0) {
        disconnect_client(server, client);
        return false;
    }

    char *token = strtok(buffer, "\n");
    if (token != NULL)
        command = strdup(token);

    if (ll_size(client->command_list) < 10)
        client->command_list = ll_push_back(client->command_list, command);
    else {
        sendmessage(client, "ko");
        free(command);
    }

    return true;
}

void dispatchcmd_gui(client_t* client, server_t* server, char** args)
{
    char* cmd = strdup(args[0]);

    if (cmd[strlen(cmd) - 1] == '\n')
        cmd[strlen(cmd) - 1] = '\0';

    for (int i = 0; strcmp(gui_cmdtable[i].command, "EOF") != 0; i++) {
        if (strcmp(cmd, gui_cmdtable[i].command) == 0) {
            gui_cmdtable[i].func(client, server, args);
            free(cmd);
            return;
        }
    }
    suc(client, server, NULL);
    free(cmd);
}

int dispatchcmd_ai(client_t* client, server_t* server, char** args)
{
    char* cmd = strdup(args[0]);

    if (cmd[strlen(cmd) - 1] == '\n')
        cmd[strlen(cmd) - 1] = '\0';

    for (int i = 0; strcmp(ai_cmdtable[i].command, "EOF") != 0; i++) {
        if (strcmp(cmd, ai_cmdtable[i].command) == 0) {
            int status = ai_cmdtable[i].func(client, server, args);
            free(cmd);
            return status;
        }
    }
    sendmessage(client, "Invalid command");
    free(cmd);
    return -1;
}

bool check_command(client_t* client, char* command)
{
    //dprintf(2, "Received data: <%s>\n", command);
    if (command == NULL) {
        if (ll_size(client->command_list) > 0)
            ll_pop_front(&client->command_list);
        return false;
    }
    return true;
}

void handlecmd(client_t *client, server_t* server)
{
    if (!getcmd(server, client))
        return;
    char* command = ll_front(client->command_list)->data;

    if (!check_command(client, command))
        return;
    if (!client->authentified) {
        authentify(client, server, command);
        ll_pop_front(&client->command_list);
        free(command);
        return;
    }
    if (command) {
        char** args = split_string(command, " ", false);
        if (strcmp(client->session->team, "GRAPHIC") == 0) {
            dispatchcmd_gui(client, server, args);
            ll_pop_front(&client->command_list);
            free(command);
        }
        free_arr(args);
    }
}
