/*
** EPITECH PROJECT, 2021
** B-MUL-100-STG-1-1-myrunner-basile.trebus-hamann
** File description:
** map_handler.c
*/

#include "../includes/my_runner.h"

map init_map_vars(map m, char **av)
{
    m.buff = malloc(sizeof(char) * 3000);
    m.fd = open(av[1], 0, O_RDONLY);
    m.entities = 0;
    m.offset_b = 0;
    m.offset_m = 0;
    m.lines = 0;
    m.x = 0;
    m.mem = 0;
    m.w = 0;
    return m;
}

map get_entities_values(map m, int j)
{
    m.w++;
    m.map_array[j][m.mem + 1] = '\0';
    if (m.map_array[j][0] == '@') {
        m.map_array[j]++;
        m.type = 1;
    } else
        m.type = 0;
    m.entities = my_atoi(m.map_array[j]);
    m.map_array[j] += get_int_len(m.entities);
    m.entity_pos.x = my_atoi(m.map_array[j]);
    m.map_array[j] += get_int_len(m.entity_pos.x);
    m.entity_pos.y = my_atoi(m.map_array[j]);
    return m;
}

map set_array_memory(map m, int j)
{
    for (; m.buff[m.x] != '\n'; m.x++)
        m.mem++;
    m.map_array[j] = malloc(sizeof(char) * m.mem);
    for (int i = 0; m.buff[m.w] != '\n'; i++, m.w++) {
        m.map_array[j][i] = m.buff[m.w];
    }
    return m;
}

h_p add_entity_to_list(h_p h)
{
    for (int i = 0; i < h.map.entities; i++) {
       if (h.map.type == 0) {
           h = add_block_to_list(h,
           h.map.entity_pos.x + h.map.offset_b, h.map.entity_pos.y);
           h.blocks++;
           h.map.offset_b += 125;
       } else if (h.map.type == 1) {
           h = add_mine_to_list(h,
           h.map.entity_pos.x + h.map.offset_m, h.map.entity_pos.y);
           h.mines++;
           h.map.offset_m += 125;
       }
    }
    return h;
}

h_p init_map(h_p h, int ac, char **av)
{
    int i = 0;

    h.map = init_map_vars(h.map, av);
    i = read(h.map.fd, h.map.buff, 3000);
    h.map.buff[i + 1] = '\0';
    for (int i = 0; h.map.buff[i] != '\0'; i++) {
        if (h.map.buff[i] == '\n')
            h.map.lines++;
    }
    h.map.map_array = malloc(sizeof(char *) * h.map.lines);
    for (int j = 0; j < h.map.lines; j++) {
        h.map = set_array_memory(h.map, j);
        h.map = get_entities_values(h.map, j);
        h = add_entity_to_list(h);
    }
    return h;
}
