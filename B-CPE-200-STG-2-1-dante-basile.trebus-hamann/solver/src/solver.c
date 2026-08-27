/*
** EPITECH PROJECT, 2021
** Dante
** File description:
** main.c
*/

#include "../include/solver.h"

void go_to_last_cross(char **map, zinzin *z, vector2 map_size)
{
    vector2 temp = z->move;
    int w = 0;

    while (w < 6) {
        if (w == 0) {
            z->move.y = z->lastpos.y;
            z->move.x = z->lastpos.x;
        } else if (w == 1) {
            z->move.y = z->lastlastpos.y;
            z->move.x = z->lastlastpos.x;
        } else if (w > 1) {
            prevnode(&z->s);
            z->move.y = z->s.i;
            z->move.x = z->s.j;
        }
        temp = z->move;
        if (z->move.y > 0) {
            temp.y -= 1;
            if ((map[z->move.y - 1][z->move.x] == 'R'
                || map[z->move.y - 1][z->move.x] == 'o')) {
                if (check_for_blob(map, temp, map_size) == 0)
                    return;
            }
            temp.y += 1;
        }
        if (z->move.y > map_size.y - 1) {
            temp.y += 1;
            if ((map[z->move.y + 1][z->move.x] == 'R'
                || map[z->move.y + 1][z->move.x] == 'o')) {
                if (check_for_blob(map, temp, map_size) == 0)
                    return;
            }
            temp.y -= 1;
        }
        if (z->move.x > 0) {
            temp.x -= 1;
            if ((map[z->move.y][z->move.x - 1] == 'R'
                || map[z->move.y][z->move.x - 1] == 'o')) {
                if (check_for_blob(map, temp, map_size) == 0)
                    return;
            }
            temp.x += 1;
        }
        if (z->move.x < map_size.x - 1) {
            temp.x += 1;
            if ((map[z->move.y][z->move.x + 1] == 'R'
                || map[z->move.y][z->move.x + 1] == 'o')) {
                if (check_for_blob(map, temp, map_size) == 0)
                    return;
            }
            temp.x -= 1;
        }
        w++;
        map[z->move.y][z->move.x] = 'T';
    }
}

void update_lastpos(zinzin *z)
{
    z->lastlastpos = z->lastpos;
    z->lastpos.x = z->s.j;
    z->lastpos.y = z->s.i;
}

void find_next_move(char **map, zinzin *z, vector2 map_size)
{
    z->move = find_cheapest_move_backtracking(map, z->s, map_size);
    if (z->move.x == -1) {
        map[z->lastpos.y][z->lastpos.x] = 'K';
        z->s.i = z->lastlastpos.y;
        z->s.j = z->lastlastpos.x;
        z->move = find_cheapest_move_backtracking(map, z->s, map_size);
    }
    if (check_for_blob(map, z->move, map_size) == 1) {
        z->move = find_cheapest_move_backtracking(map, z->s, map_size);
        if (z->move.x == -1) {
            map[z->lastpos.y][z->lastpos.x] = 'K';
            z->s.i = z->lastlastpos.y;
            z->s.j = z->lastlastpos.x;
            z->move = find_cheapest_move_backtracking(map, z->s, map_size);
        }
    }
    if (check_for_blob(map, z->move, map_size) == 1) {
        go_to_last_cross(map, z, map_size);
    }
}

void init_backtracking(char **map, zinzin *z, vector2 map_size)
{
    z->s.sg = malloc(sizeof(solver_grid *) * map_size.y + 1);
    z->s.i = map_size.y - 1;
    z->s.j = map_size.x - 1;
    z->s.p = malloc(sizeof(path));
    z->s.p->next = NULL;
    z->s.p->y = map_size.y - 1;
    z->s.p->x = map_size.x - 1;
}

void linked_list_handler(int *first, zinzin *z)
{
        z->s.p->x = z->s.j;
        z->s.p->y = z->s.i;
        attach_prev_node(&z->s, first);
        z->s.p->next = malloc(sizeof(path));
        z->s.p->next->prev = z->s.p;
}

char **backtracking(vector2 map_size, char **map)
{
    zinzin z;
    int first = 0;

    map[0][0] = 'o';
    init_backtracking(map, &z, map_size);
    for (int x = 0; x <= map_size.x; x++)
        z.s.sg[x] = malloc(sizeof(solver_grid) * map_size.x + 1);
    while (1) {
        linked_list_handler(&first, &z);
        find_next_move(map, &z, map_size);
        z.s.i = z.move.y;
        z.s.j = z.move.x;
        map[z.move.y][z.move.x] = 'A';
        if (z.move.x == 0 && z.move.y == 0)
            break;
        update_lastpos(&z);
        z.s.p = z.s.p->next;
    }
    map[map_size.y - 1][map_size.x - 1] = 'A';
    return map;
}

char **solve_maze(vector2 map_size, char **map)
{
    solver s;
    int first = 0;

    init_solver(&s, map_size);
    map[0][0] = 'o';
    for (int x = 0; x <= map_size.x; x++)
        s.sg[x] = malloc(sizeof(solver_grid) * map_size.x + 1);
    while (s.j != s.exit.x || s.i != s.exit.y) {
        s.p->x = s.j;
        s.p->y = s.i;
        attach_prev_node(&s, &first);
        s.p->next = malloc(sizeof(path));
        s.p->next->prev = s.p;
        s.move = find_cheapest_move(map, s, map_size);
        s.i = s.move.y;
        s.j = s.move.x;
        update_path(map, map_size, s);
        s.p = s.p->next;
    }
    return map;
}

int main(int ac, char **av)
{
    vector2 map_size = {0, 0};
    char **map;

    if (ac < 2) {
        write(2, "Error: must provide a map as argument!\n", 39);
        return 84;
    }
    map = my_str_to_word_array(read_file(av[1]));
    for (int i = 0; map[i] != NULL; i++) {
        map_size.y++;
        map_size.x = strlen(map[i]);
    }
    map = solve_maze(map_size, map);
    map = backtracking(map_size, map);
    map = clean_map(map, map_size);
    print_map(map, map_size);
    return 0;
}
