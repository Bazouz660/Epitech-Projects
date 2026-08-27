/*
** EPITECH PROJECT, 2021
** tower defense
** File description:
** main.c
*/

#include "../includes/towerdefense.h"

sfRenderWindow *create_window(char const *title)
{
    sfRenderWindow *Window;    
    sfVideoMode mode = sfVideoMode_getDesktopMode();

    mode.bitsPerPixel = 32;
    mode.width = 1920;
    mode.height = 1080;
    Window = sfRenderWindow_create(mode, title, 0 | sfClose, NULL);
    return (Window);
}

void entity_sethealth(entity *this, int value)
{
    this->health = value;
}

void entity_setdmg(entity *this, int value)
{
    this->dmg = value;
}

void entity_setspeed(entity *this, float value)
{
    this->speed = value;
}

void entity_setstatus(entity *this, int value)
{
    this->status = value;
}

void entity_setsprite(entity *this, sfTexture *texture)
{
    this->sprite = new_sprite2(texture, 0.2, 0.2);
}

void entity_setpos(entity *this, float x, float y)
{
    this->pos.x = x;
    this->pos.y = y;
    sfSprite_setPosition(this->sprite, this->pos);
}

sfSprite *new_sprite2(sfTexture *texture, float x, float y)
{
    sfSprite *sprite = sfSprite_create();
    sfVector2f sprite_scale = {x, y};

    sfTexture_setRepeated(texture, sfTrue);
    sfSprite_setTexture(sprite, texture, sfFalse);
    sfSprite_setScale(sprite, sprite_scale);
    return (sprite);
}

entity create_new_enemy(tower_defense td, int level, int type)
{
    entity new_enemy;
    sfVector2f hb_size = {0, 0};
    sfVector2f origin = {0, 0};

    new_enemy.anim = 0;
    new_enemy.mirrored = 0;
    new_enemy.death_delay = 0;
    new_enemy.effect = 0;
    new_enemy.exploding = 0;
    new_enemy.expl_cooldown = 0;
    new_enemy.weakness = 0;
    new_enemy.hb.red_bar = sfRectangleShape_create();
    new_enemy.hb.green_bar = sfRectangleShape_create();
    switch (type) {
        case (1):
            entity_sethealth(&new_enemy, 100 + (2 * level));
            entity_setdmg(&new_enemy, 50 + (1 * level));
            entity_setspeed(&new_enemy, 1.0 + (level / 15.5));
            entity_setstatus(&new_enemy, 0);
            entity_setsprite(&new_enemy, td.type1_texture);
            init_animated_sprite(new_enemy.sprite, 10);
            new_enemy.type = 1;
            new_enemy.reward = 2;
            break;
        case (2):
            entity_sethealth(&new_enemy, 350 + (5 * level));
            entity_setdmg(&new_enemy, 130 + (5 * level));
            entity_setspeed(&new_enemy, 0.5 + (level / 15.5));
            entity_setstatus(&new_enemy, 0);
            entity_setsprite(&new_enemy, td.type2_texture);
            init_animated_sprite(new_enemy.sprite, 10);
            new_enemy.type = 2;
            new_enemy.reward = 4;
            break;
    }
    new_enemy.speed_mem = new_enemy.speed;
    new_enemy.anim_spd = new_enemy.speed;
    new_enemy.health_mem = new_enemy.health;
    new_enemy.health_mem2 = new_enemy.health;
    new_enemy.hb.hb_pos = sfSprite_getPosition(new_enemy.sprite);
    origin.x = get_sprite_center(new_enemy.sprite).x;
    origin.y = (sfSprite_getTextureRect(new_enemy.sprite).height - 80);
    sfSprite_setOrigin(new_enemy.sprite, origin);
    new_enemy.projectile = sfSprite_create();
    new_enemy.effect_sprite = sfSprite_copy(new_enemy.sprite);
    new_enemy.weakness_sprite = sfSprite_copy(new_enemy.sprite);
    sfSprite_setTexture(new_enemy.effect_sprite, td.empty_texture, sfFalse);
    sfSprite_setTexture(new_enemy.weakness_sprite, td.empty_texture, sfFalse);
    hb_size.x = sfSprite_getGlobalBounds(new_enemy.sprite).width;
    hb_size.y = 6;
    new_enemy.hb.hb_origin.x = hb_size.x / 2;
    new_enemy.hb.hb_origin.y = hb_size.y / 2;
    sfRectangleShape_setSize(new_enemy.hb.green_bar, hb_size);
    sfRectangleShape_setFillColor(new_enemy.hb.green_bar, sfGreen);
    new_enemy.hb.hb_pos.x -= new_enemy.hb.hb_pos.x / 2;
    new_enemy.hb.hb_pos.y = origin.y;
    sfRectangleShape_setPosition(new_enemy.hb.green_bar, new_enemy.hb.hb_pos);
    sfRectangleShape_setOrigin(new_enemy.hb.green_bar, new_enemy.hb.hb_origin);
    new_enemy.hb.red_bar = sfRectangleShape_copy(new_enemy.hb.green_bar);
    sfRectangleShape_setFillColor(new_enemy.hb.red_bar, sfRed);
    sfRectangleShape_setOutlineColor(new_enemy.hb.red_bar, sfBlack);
    sfRectangleShape_setOutlineThickness(new_enemy.hb.red_bar, 2);
    return new_enemy;
}

int random_between(int lower, int upper)
{
    int num = 0;

    for (int i = 0; i < 10; i++)
        num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

int count_entry_points(tower_defense td)
{
    int x = 0;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 17; j++) {
            if (td.grid[i][j].entry_point == 2) {
                x++;
            }
        }
    }
    return x;
}

enemy_s_p *get_entry_points(tower_defense td, int *index)
{
    enemy_s_p *sp = malloc(sizeof(enemy_s_p) * 50);
    int x = 0;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 17; j++) {
            if (td.grid[i][j].entry_point == 2) {
                sp[x].pos.x = td.grid[i][j].rect_pos.x;
                sp[x].pos.y = td.grid[i][j].rect_pos.y;
                sp[x].type = td.grid[i][j].type;
                x++;
                *index += 1;
            }
        }
    }
    return sp;
}

void addlast(tower_defense td, wave **head, int level, int index, int type, sfVector2f pos, int sp_type, int offset)
{
    wave *newNode = malloc(sizeof(wave));
    wave *lastNode;
    sfVector2f dist = {0, 0};
    sfVector2f mvt = {0, 0};

    newNode->enemy = create_new_enemy(td, level, type);
    switch (sp_type) {
        case (1):
            dist.x = -80;
            dist.y = 0;
            mvt.x = newNode->enemy.speed;
            break;
        case (2):
            dist.y = -80;
            dist.x = 0;
            mvt.y = newNode->enemy.speed;
            break;
        case (3):
            dist.x = 80;
            dist.y = 0;
            mvt.x = -newNode->enemy.speed;
            break;
        case (4):
            dist.y = 80;
            dist.x = 0;
            mvt.y = -newNode->enemy.speed;
            break;
    }
    entity_setpos(&newNode->enemy, pos.x + (offset * dist.x), pos.y + (offset * dist.y));
    newNode->enemy.spd_vect = mvt;
    newNode->index = index;
    newNode->next = NULL;
    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
    } else {
        lastNode = *head;
        while(lastNode->next != NULL) {
            lastNode->next->prev = lastNode;
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
    index++;
}

wave *create_new_wave(tower_defense td, wave *head, int enemy_nb, int level, enemy_s_p *sp, int index)
{
    int i = 0;
    int type = 1;
    int offset = 0;

    head = NULL;
    for (int w = 0; w < index; w++) {
        td.time = sfClock_getElapsedTime(td.clock);
        td.seconds = td.time.microseconds/1000000.0;
        srand((int)(td.seconds * 100000000));
        offset = 0;
        for (int x = 0; x < enemy_nb; x++, i++) {
            if (x + random_between((td.wave_index - 1), (td.wave_index + (level - 1))) >= enemy_nb) {
                type != 2 ? offset = 0 : 0;
                type = 2;
            }
            addlast(td, &head, random_between(level - 1, level + 2), i, type, sp[w].pos, sp[w].type, (offset + 1));
            offset ++;
        }
        type = 1;
    }
    return head;
}

sfVector2f get_sprite_center(sfSprite *sprite)
{
    sfVector2f origin;
    sfIntRect rect = sfSprite_getTextureRect(sprite);

    origin.x = rect.width / 2;
    origin.y = rect.height / 2;
    return origin;
}

sfVector2f get_text_center(sfText *text)
{
    sfVector2f origin;
    sfFloatRect rect = sfText_getGlobalBounds(text);

    origin.x = rect.width / 2;
    origin.y = rect.height / 2;
    return origin;
}


tower_defense exit_game(tower_defense td)
{
    sfMusic_destroy(td.menu_music);
    sfRenderWindow_close(td.window);
    td.exit = 1;
    return td;
}

tower_defense switch_window_mode(tower_defense td, sfBool fullscreen)
{    
    sfVideoMode mode = sfVideoMode_getDesktopMode();
    int type = 0;

    if (fullscreen == sfFalse) {
        sfRenderWindow_close(td.window);
        type = 0;
    }
    if (fullscreen == sfTrue) {
        sfRenderWindow_close(td.window);
        td.g_scale = 1;
        type = sfFullscreen;
    }
    td.window = sfRenderWindow_create(mode, "Tower Defense", type | sfClose, NULL);
    return (td);
}

sfSprite *new_sprite(char *texture_name, float x, float y)
{
    sfSprite *sprite = sfSprite_create();
    sfVector2f sprite_scale = {x, y};
    sfTexture *sprite_texture = sfTexture_createFromFile(texture_name,
    sfFalse);

    sfTexture_setRepeated(sprite_texture, sfTrue);
    sfSprite_setTexture(sprite, sprite_texture, sfFalse);
    sfSprite_setScale(sprite, sprite_scale);
    return (sprite);
}


sfBool get_mouse_intersect(tower_defense td, sfSprite *to_check)
{
    int posX = sfSprite_getPosition(to_check).x;
    int posY = sfSprite_getPosition(to_check).y;
    int posX_offset = (sfSprite_getGlobalBounds(to_check).width + posX);
    int posY_offset = (sfSprite_getGlobalBounds(to_check).height + posY);

    if ((td.mouse_pos.x >= posX && td.mouse_pos.x <= posX_offset)
        && (td.mouse_pos.y >= posY && td.mouse_pos.y <= posY_offset))
        return sfTrue;
    else
        return sfFalse;
}

sfBool get_mouse_intersectb(tower_defense td, sfSprite *to_check)
{
    int posX = sfSprite_getPosition(to_check).x - (sfSprite_getGlobalBounds(to_check).width / 2);
    int posY = sfSprite_getPosition(to_check).y - (sfSprite_getGlobalBounds(to_check).height / 2);
    int posX_offset = ((sfSprite_getGlobalBounds(to_check).width) + posX);
    int posY_offset = ((sfSprite_getGlobalBounds(to_check).height) + posY);

    if ((td.mouse_pos.x >= posX && td.mouse_pos.x <= posX_offset)
        && (td.mouse_pos.y >= posY && td.mouse_pos.y <= posY_offset))
        return sfTrue;
    else
        return sfFalse;
}

sfText *new_text(tower_defense td, sfColor color)
{
    sfText *text = sfText_create();

    sfText_setFont(text, td.font);
    sfText_setFillColor(text, color);
    sfText_setOutlineThickness(text, 3);
    sfText_setOutlineColor(text, sfBlack);
    return text;
}

tower lvl_archer(tower tw)
{
    switch (tw.level) {
        case (2):
            tw.texture = sfTexture_createFromFile("sprites/towers/archer_lvl2.png", NULL);
            break;
        case (3):
            tw.texture = sfTexture_createFromFile("sprites/towers/archer_lvl3.png", NULL);
            break;
    }
    return tw;
}

tower lvl_magic(tower tw)
{
    switch (tw.level) {
        case (2):
            tw.texture = sfTexture_createFromFile("sprites/towers/mage_lvl2.png", NULL);
            break;
        case (3):
            tw.texture = sfTexture_createFromFile("sprites/towers/mage_lvl3.png", NULL);
            break;
    }
    return tw;
}

tower lvl_bomb(tower tw)
{
    switch (tw.level) {
        case (2):
            tw.texture = sfTexture_createFromFile("sprites/towers/catapulte_lvl2.png", NULL);
            break;
        case (3):
            tw.texture = sfTexture_createFromFile("sprites/towers/catapulte_lvl3.png", NULL);
            break;
    }
    return tw;
}

tower lvl_support(tower tw)
{
    switch (tw.level) {
        case (2):
            tw.texture = sfTexture_createFromFile("sprites/towers/supp2.png", NULL);
            break;
        case (3):
            tw.texture = sfTexture_createFromFile("sprites/towers/supp3.png", NULL);
            break;
    }
    return tw;
}

tower upgrade_tower(tower tw, int type)
{
    tw.atck_spd *= 1.02;
    tw.dmg *= 1.2;
    tw.level++;
    tw.cost = tw.up_cost;
    tw.up_cost *= 2;
    switch (type) {
        case (1):
            tw = lvl_archer(tw);
            break;
        case (2):
            tw = lvl_magic(tw);
            break;
        case (3):
            tw = lvl_bomb(tw);
            break;
        case (4):
            tw = lvl_support(tw);
            break;
    }
    sfTexture_setRepeated(tw.texture, sfTrue);
    return tw;
}

int my_strlen(char *dest)
{
    int i = 0;

    while (dest[i] != '\0')
        i++;
    return i;
}

char *my_revstr(char *str)
{
    int i = 0;;
    int l = my_strlen(str) - 1;
    char x;

    while (i < l) {
        x = str[i];
        str[i] = str[l];
        str[l] = x;
        i = i + 1;
        l = l - 1;
    }
    return (str);
}

void reverse(char *str, int len)
{
	int i = 0;
    int j = len - 1;
    int temp;

	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

int my_pow(int base, int exp)
{
    int result = 1;

    while (exp) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

int get_floatingpoint(int x, char *str, int d)
{
	int i = 0;

	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	while (i < d)
		str[i++] = '0';
	reverse(str, i);
	str[i] = '\0';
	return i;
}

void my_ftoa(char *res, float n ,int afterpoint)
{
	int ipart = (int)n;
	float fpart = n - (float)ipart;
	int i = get_floatingpoint(ipart, res, 0);

	if (afterpoint != 0) {
		res[i] = '.';
		fpart = fpart * my_pow(10, afterpoint);
		get_floatingpoint((int)fpart, res + i + 1, afterpoint);
	}
    if (res[0] == '.') {
        my_revstr(res);
        res[my_strlen(res)] = '0';
        res[my_strlen(res) + 1] = '\0';
        my_revstr(res);
    }
}

char *int_to_string(char *str, int nb)
{
    int i = 0;
    int mem_nb = nb;
    int remains;

    if (nb == 0) {
        str[i] = '0';
        str[i + 1] = '\0';
        return (str);
    }
    (nb < 0) ? nb = -nb : 0;
    for (; nb != 0; i++) {
        remains = nb % 10;
        str[i] = remains + '0';
        nb /= 10;
    }
    mem_nb < 0 ? str[i + 1] = '-' : 0;
    str[i] = '\0';
    my_revstr(str);
    return (str);
}

tower create_tower(int type)
{
    tower tw;

    tw.type = type;
    tw.level = 1;
    tw.sound_delay = 0;
    tw.atck_delay = 0;
    switch (type) {
        case (1):
            tw.atck_spd = 1.0;
            tw.frames = 6;
            tw.cost = 20;
            tw.up_cost = tw.cost * 2;
            tw.effect = 0;
            tw.dmg = 1.5;
            tw.anim_spd = tw.atck_spd;
            tw.range = 3;
            tw.texture = sfTexture_createFromFile("sprites/towers/archer_lvl1.png", NULL);
            sfTexture_setRepeated(tw.texture, sfTrue);
            return tw;
        case (2):
            tw.atck_spd = 0.2;
            tw.cost = 30;
            tw.frames = 1;
            tw.up_cost = tw.cost * 2;
            tw.dmg = 0.1;
            tw.anim_spd = tw.atck_spd;
            tw.effect = 1;
            tw.range = 2;
            tw.texture = sfTexture_createFromFile("sprites/towers/mage_lvl1.png", NULL);
            sfTexture_setRepeated(tw.texture, sfTrue);
            return tw;
        case (3):
            tw.atck_spd = 0.05;
            tw.frames = 16;
            tw.cost = 45;
            tw.up_cost = tw.cost * 2;
            tw.effect = 0;
            tw.anim_spd = 0.2;
            tw.dmg = 30;
            tw.range = 2;
            tw.texture = sfTexture_createFromFile("sprites/towers/catapulte_lvl1.png", NULL);
            sfTexture_setRepeated(tw.texture, sfTrue);
            return tw;
        case (4):
            tw.atck_spd = 0.2;
            tw.cost = 25;
            tw.frames = 1;
            tw.up_cost = tw.cost * 2;
            tw.dmg = 0;
            tw.anim_spd = tw.atck_spd;
            tw.effect = 1;
            tw.range = 2;
            tw.texture = sfTexture_createFromFile("sprites/towers/supp1.png", NULL);
            sfTexture_setRepeated(tw.texture, sfTrue);
            return tw;
    }
    return tw;
}

void delete_node(wave *temp)
{
    if (temp->prev == NULL) {
        if (temp->next == NULL) {
            temp = NULL;
            return ;
        }
        temp->next->prev = NULL;
    } else {
        if (temp->next == NULL) {
            temp->prev->next = NULL;
            return ;
        } else {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
        }
    }
    return ;
}

tower_defense follow_path(tower_defense td)
{
    wave *temp = td.cur_wave[td.wave_index];
    wave * lastNode = NULL;
    int delete = 0;

    while (temp != NULL) {
        temp->prev = lastNode;
        lastNode = temp;
        if (temp->next == NULL)
            break;
        temp = temp->next;
    }
    while (temp->prev != NULL) {
        temp = temp->prev;
    }
    lastNode = NULL;
    while (temp != NULL) {
        temp->enemy.pos = sfSprite_getPosition(temp->enemy.sprite);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 17; j++) {
                if (temp->enemy.status != 1) {
                    if (td.grid[i][j].entry_point == 1)
                        if ((temp->enemy.pos.x >= td.grid[i][j].rect_pos.x - (td.grid[i][j].size.x / 2)
                            && temp->enemy.pos.x <= td.grid[i][j].rect_pos.x + td.grid[i][j].size.x)
                            && (temp->enemy.pos.y >= td.grid[i][j].rect_pos.y - 5
                            && temp->enemy.pos.y <= td.grid[i][j].rect_pos.y + 5) && temp->enemy.status != 1) {
                            if (temp->enemy.status != 2) {
                                td.enemies_left--;
                                td.player_health -= temp->enemy.dmg;
                                if (td.player_health < 0)
                                    td.player_health = 0;
                                temp->enemy.status = 2;
                            }
                            delete = 1;
                        }
                    if (td.grid[i][j].type == 0)
                        if ((temp->enemy.pos.x >= td.grid[i][j].rect_pos.x - (td.grid[i][j].size.x / 2)
                            && temp->enemy.pos.x <= td.grid[i][j].rect_pos.x + td.grid[i][j].size.x)
                            && (temp->enemy.pos.y >= td.grid[i][j].rect_pos.y - 5
                            && temp->enemy.pos.y <= td.grid[i][j].rect_pos.y + 15)) {
                            temp->enemy.spd_vect.x = 0;
                            temp->enemy.spd_vect.y = 0;
                        }
                    if (td.grid[i][j].type == 1)
                        if ((temp->enemy.pos.x >= td.grid[i][j].rect_pos.x - (td.grid[i][j].size.x / 2)
                            && temp->enemy.pos.x <= td.grid[i][j].rect_pos.x + td.grid[i][j].size.x)
                            && (temp->enemy.pos.y >= td.grid[i][j].rect_pos.y - 5
                            && temp->enemy.pos.y <= td.grid[i][j].rect_pos.y + 15)) {
                            temp->enemy.spd_vect.x = (temp->enemy.speed);
                            temp->enemy.spd_vect.y = 0;
                        }
                    if (td.grid[i][j].type == 2)
                        if ((temp->enemy.pos.x >= td.grid[i][j].rect_pos.x - 5
                            && temp->enemy.pos.x <= td.grid[i][j].rect_pos.x + 5)
                            && (temp->enemy.pos.y >= td.grid[i][j].rect_pos.y - (td.grid[i][j].size.x / 2)
                            && temp->enemy.pos.y <= td.grid[i][j].rect_pos.y + td.grid[i][j].size.x)) {
                            temp->enemy.spd_vect.x = 0;
                            temp->enemy.spd_vect.y = (temp->enemy.speed);
                        }
                    if (td.grid[i][j].type == 3)
                        if ((temp->enemy.pos.x >= td.grid[i][j].rect_pos.x - td.grid[i][j].size.x
                            && temp->enemy.pos.x <= td.grid[i][j].rect_pos.x + (td.grid[i][j].size.x / 2))
                            && (temp->enemy.pos.y >= td.grid[i][j].rect_pos.y - 5
                            && temp->enemy.pos.y <= td.grid[i][j].rect_pos.y + 15)) {
                            temp->enemy.spd_vect.x = -(temp->enemy.speed);
                            temp->enemy.spd_vect.y = 0;
                        }
                    if (td.grid[i][j].type == 4)
                        if ((temp->enemy.pos.x >= td.grid[i][j].rect_pos.x - 2
                            && temp->enemy.pos.x <= td.grid[i][j].rect_pos.x + 2)
                            && (temp->enemy.pos.y >= td.grid[i][j].rect_pos.y - td.grid[i][j].size.x
                            && temp->enemy.pos.y <= td.grid[i][j].rect_pos.y + (td.grid[i][j].size.x / 2))) {
                            temp->enemy.spd_vect.x = 0;
                            temp->enemy.spd_vect.y = -(temp->enemy.speed);
                        }
                }
            }
        }
        if (delete == 1) {
            delete_node(temp);
            if (td.enemies_left == 0) {
                td.cur_wave[td.wave_index] = NULL;
                return td;
            }
            delete = 0;
        }
        if (temp->next == NULL) {
            break;
        }
        lastNode = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        td.cur_wave[td.wave_index] = NULL;
        return td;
    }
    while (temp->prev != NULL)
        temp = temp->prev;
    td.cur_wave[td.wave_index] = temp;
    return td;
}


tower_defense check_case_con_type1(tower_defense td, int i, int j)
{
    if (i > 0) {
        if (td.grid[i - 1][j].type == 2)
            td.grid[i][j].cc.u = 1;
        else
            td.grid[i][j].cc.u = 0;
    }
    if (td.grid[i + 1][j].type == 4)
        td.grid[i][j].cc.d = 1;
    else
        td.grid[i][j].cc.d = 0;
    if (td.grid[i][j + 1].type == 1 || td.grid[i][j + 1].type == 2 || td.grid[i][j + 1].type == 4)
            td.grid[i][j].cc.r = 1;
    else
        td.grid[i][j].cc.r = 0;
    if (j > 0) {
        if (td.grid[i][j - 1].type == 1)
                td.grid[i][j].cc.l = 1;
        else
            td.grid[i][j].cc.l = 0;
    }
    return td;
}

tower_defense check_case_con_type2(tower_defense td, int i, int j)
{
    if (i > 0) {
        if (td.grid[i - 1][j].type == 2)
            td.grid[i][j].cc.u = 1;
        else
            td.grid[i][j].cc.u = 0;
    }
    if (td.grid[i + 1][j].type == 1 || td.grid[i + 1][j].type == 2 || td.grid[i + 1][j].type == 3)
        td.grid[i][j].cc.d = 1;
    else
        td.grid[i][j].cc.d = 0;
    if (td.grid[i][j + 1].type == 3)
        td.grid[i][j].cc.r = 1;
    else
        td.grid[i][j].cc.r = 0;
    if (j > 0) {
        if (td.grid[i][j - 1].type == 1)
            td.grid[i][j].cc.l = 1;
        else
            td.grid[i][j].cc.l = 0;
    }
    return td;
}

tower_defense check_case_con_type3(tower_defense td, int i, int j)
{
    if (i > 0) {
        if (td.grid[i - 1][j].type == 2)
            td.grid[i][j].cc.u = 1;
        else
            td.grid[i][j].cc.u = 0;
    }
    if (td.grid[i + 1][j].type == 4)
        td.grid[i][j].cc.d = 1;
    else
        td.grid[i][j].cc.d = 0;
    if (td.grid[i][j + 1].type == 3)
        td.grid[i][j].cc.r = 1;
    else
        td.grid[i][j].cc.r = 0;
    if (j > 0) {
        if (td.grid[i][j - 1].type == 3 || td.grid[i][j - 1].type == 2 || td.grid[i][j - 1].type == 4)
            td.grid[i][j].cc.l = 1;
        else
            td.grid[i][j].cc.l = 0;
    }
    return td;
}

tower_defense check_case_con_type4(tower_defense td, int i, int j)
{
    if (i > 0) {
        if (td.grid[i - 1][j].type == 1 || td.grid[i - 1][j].type == 3 || td.grid[i - 1][j].type == 4)
            td.grid[i][j].cc.u = 1;
        else
            td.grid[i][j].cc.u = 0;
    }
    if (td.grid[i + 1][j].type == 4)
        td.grid[i][j].cc.d = 1;
    else
        td.grid[i][j].cc.d = 0;
    if (td.grid[i][j + 1].type == 3)
        td.grid[i][j].cc.r = 1;
    else
        td.grid[i][j].cc.r = 0;
    if (j > 0) {
        if (td.grid[i][j - 1].type == 1)
            td.grid[i][j].cc.l = 1;
        else
            td.grid[i][j].cc.l = 0;
    }
    return td;
}

int count_connections(tower_defense td, int i, int j)
{
    int connections = 0;

    td.grid[i][j].cc.u == 1 ? connections++ : 0;
    td.grid[i][j].cc.d == 1 ? connections++ : 0;
    td.grid[i][j].cc.r == 1 ? connections++ : 0;
    td.grid[i][j].cc.l == 1 ? connections++ : 0;
    return connections;
}

tower_defense update_con_texture_type3(tower_defense td, int i, int j)
{
    td.grid[i][j].cc.u = 0;
    td.grid[i][j].cc.d = 0;
    td.grid[i][j].cc.r = 0;
    td.grid[i][j].cc.l = 0;
    td = check_case_con_type3(td, i, j);
    td.connections = count_connections(td, i, j);
    if (td.connections == 2)
        if (td.grid[i][j].cc.u == 1 || td.grid[i][j].cc.d == 1) {
            sfRectangleShape_setTexture(td.grid[i][j].unit, td.L_path, sfFalse);
            if (td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.u == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
            if (td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.d == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
            if (td.grid[i][j].cc.r == 1 && td.grid[i][j].cc.u == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
            if (td.grid[i][j].cc.r == 1 && td.grid[i][j].cc.d == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 270);
        } else {
            sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfFalse);
            sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
        }
    else if (td.connections == 1) {
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfFalse);
        sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
    }
    if (td.connections == 3) {
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.T_path, sfFalse);
        if (td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, -90);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.l == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
    }
    if (td.connections == 4)
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.X_path, sfFalse);
    return td;
}

tower_defense update_con_texture_type4(tower_defense td, int i, int j)
{
    td.grid[i][j].cc.u = 0;
    td.grid[i][j].cc.d = 0;
    td.grid[i][j].cc.r = 0;
    td.grid[i][j].cc.l = 0;
    td = check_case_con_type4(td, i, j);
    td.connections = count_connections(td, i, j);
    if (td.connections == 2)
        if (td.grid[i][j].cc.r == 1 || td.grid[i][j].cc.l == 1) {
            sfRectangleShape_setTexture(td.grid[i][j].unit, td.L_path, sfFalse);
            if (td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.u == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
            if (td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.d == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
            if (td.grid[i][j].cc.r == 1 && td.grid[i][j].cc.u == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
            if (td.grid[i][j].cc.r == 1 && td.grid[i][j].cc.d == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 270);
        } else {
            sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfFalse);
            sfRectangleShape_setRotation(td.grid[i][j].unit, -90);
        }
    else if (td.connections == 1) {
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfFalse);
        sfRectangleShape_setRotation(td.grid[i][j].unit, -90);
    }
    if (td.connections == 3) {
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.T_path, sfFalse);
        if (td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, -90);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.l == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
    }
    if (td.connections == 4)
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.X_path, sfFalse);
    return td;
}

tower_defense update_con_texture_type1(tower_defense td, int i, int j) 
{
    td.grid[i][j].cc.u = 0;
    td.grid[i][j].cc.d = 0;
    td.grid[i][j].cc.r = 0;
    td.grid[i][j].cc.l = 0;
    td = check_case_con_type1(td, i, j);
    td.connections = count_connections(td, i, j);
    if (td.connections == 2)
        if (td.grid[i][j].cc.u == 1 || td.grid[i][j].cc.d == 1) {
            sfRectangleShape_setTexture(td.grid[i][j].unit, td.L_path, sfFalse);
            if (td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.u == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
            if (td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.d == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
            if (td.grid[i][j].cc.r == 1 && td.grid[i][j].cc.u == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
            if (td.grid[i][j].cc.r == 1 && td.grid[i][j].cc.d == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 270);
        } else {
            sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfFalse);
            sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
        }
    else if (td.connections == 1) {
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfFalse);
        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
    }
    if (td.connections == 3) {
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.T_path, sfFalse);
        if (td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, -90);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.l == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
    }
    if (td.connections == 4)
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.X_path, sfFalse);
    return td;
}

tower_defense update_con_texture_type2(tower_defense td, int i, int j)
{
    td.grid[i][j].cc.u = 0;
    td.grid[i][j].cc.d = 0;
    td.grid[i][j].cc.r = 0;
    td.grid[i][j].cc.l = 0;
    td = check_case_con_type2(td, i, j);
    td.connections = count_connections(td, i, j);
    if (td.connections == 2)
        if (td.grid[i][j].cc.r == 1 || td.grid[i][j].cc.l == 1) {
            sfRectangleShape_setTexture(td.grid[i][j].unit, td.L_path, sfFalse);
            if (td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.u == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
            if (td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.d == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
            if (td.grid[i][j].cc.r == 1 && td.grid[i][j].cc.u == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
            if (td.grid[i][j].cc.r == 1 && td.grid[i][j].cc.d == 1)
                sfRectangleShape_setRotation(td.grid[i][j].unit, 270);
        } else {
            sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfFalse);
            sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
        }
    else if (td.connections == 1) {
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfFalse);
        sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
    }
    if (td.connections == 3) {
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.T_path, sfFalse);
        if (td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.l == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.r == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, -90);
        if (td.grid[i][j].cc.u == 1 && td.grid[i][j].cc.d == 1 && td.grid[i][j].cc.l == 1)
            sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
    }
    if (td.connections == 4)
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.X_path, sfFalse);
    return td;
}

tower_defense update_con_texture(tower_defense td, int i, int j, int type)
{
    if (type == 1)
        td = update_con_texture_type1(td, i, j);
    else if (type == 2)
        td = update_con_texture_type2(td, i, j);
    type = type;
    if (type == 3)
        td = update_con_texture_type3(td, i, j);
    else if (type == 4)
        td = update_con_texture_type4(td, i, j);
    return td;
}

sfBool is_touching_border(tower_defense td, int i, int j)
{
    if (i > 0)
        if (td.grid[i - 1][j].type == -1)
            return 1;
    if (td.grid[i + 1][j].type == -1)
        return 1;
    if (j > 0)
        if (td.grid[i][j - 1].type == -1)
            return 1;
    if (td.grid[i][j + 1].type == -1)
        return 1;
    return 0;
}

void init_animated_rect(sfRectangleShape *sprite, int frames)
{
    sfIntRect rect = sfRectangleShape_getTextureRect(sprite);

    rect.width /= frames;
    sfRectangleShape_setTextureRect(sprite, rect);
}

void init_animated_sprite(sfSprite *sprite, int frames)
{
    sfIntRect rect = sfSprite_getTextureRect(sprite);

    rect.width /= frames;
    sfSprite_setTextureRect(sprite, rect);
}

tower destroy_tower(tower_defense td, tower tw)
{
    tw.type = 0;
    tw.dmg = 0;
    tw.atck_spd = 0;
    tw.range = 0;
    tw.level = 0;
    tw.cost = 0;
    tw.frames = 1;
    tw.texture = td.buildable;
    return tw;
}

tower_defense handle_game_input(tower_defense td)
{
    static int m_i = 0;
    static int m_j = 0;
    int clicked = 0;
    sfVector2f origin = {60, 60};
    sfVector2f build_menu_pos = {0, 0};
    sfVector2f upgrade_menu_pos = {0, 0};
    sfVector2f scale0 = {0.5, 0.5};
    sfVector2f scale1 = {0.55, 0.55};
    sfVector2f tscale0 = {0.70, 0.70};
    sfVector2f tscale1 = {0.80, 0.80};
    sfVector2f txt_displacement = {0, 1.5};

    sfText_setScale(td.upgrade_txt_1, tscale0);
    sfText_setScale(td.upgrade_txt_2, tscale0);
    sfText_setScale(td.build_txt_1, tscale0);
    sfText_setScale(td.build_txt_2, tscale0);
    sfText_setScale(td.build_txt_3, tscale0);
    sfText_setScale(td.build_txt_4, tscale0);
    sfText_setString(td.build_txt_1, "20");
    sfText_setOrigin(td.build_txt_1, get_text_center(td.build_txt_1));
    sfText_setString(td.build_txt_2, "30");
    sfText_setOrigin(td.build_txt_2, get_text_center(td.build_txt_2));
    sfText_setString(td.build_txt_3, "45");
    sfText_setOrigin(td.build_txt_3, get_text_center(td.build_txt_3));
    sfText_setString(td.build_txt_4, "25");
    sfText_setOrigin(td.build_txt_4, get_text_center(td.build_txt_4));
    if (td.build_menu_open == 1) {
        if (td.b_m_button == 0 && sfMouse_isButtonPressed(sfMouseLeft))
            td.build_menu_open = 0;
        if (get_mouse_intersectb(td, td.build_menu_1)) {
            if (td.b_m_button != 1)
                td.b_m_button = 0;
            if (td.b_m_button == 0) {
                sfSound_play(td.click_sound);
                sfText_move(td.build_txt_1, txt_displacement);
                sfSprite_setTexture(td.selected_tower, td.archer1_preview, sfTrue);
                td.stats_visible = 1;
                sfText_setString(td.hud_tw_dmg_txt, "1.50");
                sfText_setString(td.hud_tw_range_txt, "2.00");
                sfText_setString(td.hud_tw_atckspd_txt, "1.00");
            }
            td.b_m_button = 1;
            sfSprite_setScale(td.build_menu_1, scale1);
            sfText_setScale(td.build_txt_1, tscale1);
            if (sfMouse_isButtonPressed(sfMouseLeft) && td.gold_a >= 20) {
                td.stats_visible = 0;
                td.grid[m_i][m_j].tw = create_tower(1);
                sfSound_play(td.build_sound);
                td.gold_a -=  td.grid[m_i][m_j].tw.cost;
                sfRectangleShape_setTexture(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.texture, sfTrue);
                init_animated_rect(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.frames);
                td.build_menu_open = 0;
                td.build_menu_delay = td.seconds;
                sfSprite_setScale(td.build_menu_1, scale0);
            }
        } else {
            if (td.b_m_button == 1) {
                td.b_m_button = 0;
                txt_displacement.y *= -1;
                sfText_move(td.build_txt_1, txt_displacement);
                td.stats_visible = 0;
                txt_displacement.y *= -1;
            }
            sfText_setScale(td.build_txt_1, tscale0);
            sfSprite_setScale(td.build_menu_1, scale0);
        }
        if (get_mouse_intersectb(td, td.build_menu_2)) {
            if (td.b_m_button != 2)
                td.b_m_button = 0;
            if (td.b_m_button == 0) {
                sfSound_play(td.click_sound);
                sfSprite_setTexture(td.selected_tower, td.mage1_preview, sfTrue);
                td.stats_visible = 1;
                sfText_move(td.build_txt_2, txt_displacement);
                sfText_setString(td.hud_tw_dmg_txt, "0.10");
                sfText_setString(td.hud_tw_range_txt, "1.00");
                sfText_setString(td.hud_tw_atckspd_txt, "0.20");
            }
            td.b_m_button = 2;
            sfSprite_setScale(td.build_menu_2, scale1);
            sfText_setScale(td.build_txt_2, tscale1);
            if (sfMouse_isButtonPressed(sfMouseLeft) && td.gold_a >= 30) {
                td.stats_visible = 0;
                td.grid[m_i][m_j].tw = create_tower(2);
                sfSound_play(td.build_sound);
                td.gold_a -=  td.grid[m_i][m_j].tw.cost;
                sfRectangleShape_setTexture(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.texture, sfTrue);
                init_animated_rect(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.frames);
                td.build_menu_open = 0;
                td.build_menu_delay = td.seconds;
                sfSprite_setScale(td.build_menu_2, scale0);
            }
        } else {
            if (td.b_m_button == 2) {
                td.b_m_button = 0;
                txt_displacement.y *= -1;
                sfText_move(td.build_txt_2, txt_displacement);
                td.stats_visible = 0;
                txt_displacement.y *= -1;
            }
            sfText_setScale(td.build_txt_2, tscale0);
            sfSprite_setScale(td.build_menu_2, scale0);
        }
        if (get_mouse_intersectb(td, td.build_menu_3)) {
            if (td.b_m_button != 3)
                td.b_m_button = 0;
            if (td.b_m_button == 0) {
                sfSound_play(td.click_sound);
                sfText_move(td.build_txt_3, txt_displacement);
                sfSprite_setTexture(td.selected_tower, td.catapult1_preview, sfTrue);
                sfText_setString(td.hud_tw_dmg_txt, "30.00");
                sfText_setString(td.hud_tw_range_txt, "1.00");
                sfText_setString(td.hud_tw_atckspd_txt, "0.05");
                td.stats_visible = 1;
            }
            td.b_m_button = 3;
            sfSprite_setScale(td.build_menu_3, scale1);
            sfText_setScale(td.build_txt_3, tscale1);
            if (sfMouse_isButtonPressed(sfMouseLeft) && td.gold_a >= 45) {
                td.stats_visible = 0;
                td.grid[m_i][m_j].tw = create_tower(3);
                sfSound_play(td.build_sound);
                td.gold_a -=  td.grid[m_i][m_j].tw.cost;
                sfRectangleShape_setTexture(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.texture, sfTrue);
                init_animated_rect(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.frames);
                td.build_menu_open = 0;
                td.build_menu_delay = td.seconds;
                sfSprite_setScale(td.build_menu_3, scale0);
            }
        } else {
            if (td.b_m_button == 3) {
                td.b_m_button = 0;
                txt_displacement.y *= -1;
                sfText_move(td.build_txt_3, txt_displacement);
                td.stats_visible = 0;
                txt_displacement.y *= -1;
            }
            sfSprite_setScale(td.build_menu_3, scale0);
        }
        if (get_mouse_intersectb(td, td.build_menu_4)) {
            if (td.b_m_button != 4)
                td.b_m_button = 0;
            if (td.b_m_button == 0) {
                sfSound_play(td.click_sound);
                sfText_move(td.build_txt_3, txt_displacement);
                sfSprite_setTexture(td.selected_tower, td.supp1_preview, sfTrue);
                sfText_setString(td.hud_tw_dmg_txt, "0.00");
                sfText_setString(td.hud_tw_range_txt, "1.00");
                sfText_setString(td.hud_tw_atckspd_txt, "0.2");
                td.stats_visible = 1;
            }
            td.b_m_button = 4;
            sfSprite_setScale(td.build_menu_4, scale1);
            sfText_setScale(td.build_txt_4, tscale1);
            if (sfMouse_isButtonPressed(sfMouseLeft) && td.gold_a >= 25) {
                td.stats_visible = 0;
                td.grid[m_i][m_j].tw = create_tower(4);
                sfSound_play(td.build_sound);
                td.gold_a -=  td.grid[m_i][m_j].tw.cost;
                sfRectangleShape_setTexture(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.texture, sfTrue);
                init_animated_rect(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.frames);
                td.build_menu_open = 0;
                td.build_menu_delay = td.seconds;
                sfSprite_setScale(td.build_menu_4, scale0);
            }
        } else {
            if (td.b_m_button == 4) {
                td.b_m_button = 0;
                txt_displacement.y *= -1;
                sfText_move(td.build_txt_4, txt_displacement);
                td.stats_visible = 0;
                txt_displacement.y *= -1;
            }
            sfSprite_setScale(td.build_menu_4, scale0);
        }
    }

    if (td.build_menu_open == 2) {
        switch (td.grid[m_i][m_j].tw.type) {
            case (1):
                sfSprite_setTexture(td.selected_tower, td.archer1_preview, sfTrue);
                break;
            case (2):
                sfSprite_setTexture(td.selected_tower, td.mage1_preview, sfTrue);
                break;
            case (3):
                sfSprite_setTexture(td.selected_tower, td.catapult1_preview, sfTrue);
                break;
            case (4):
                sfSprite_setTexture(td.selected_tower, td.supp1_preview, sfTrue);
                break;
        }
        td.stats_visible = 1;
        my_ftoa(td.hud_tw_dmg_str, td.grid[m_i][m_j].tw.dmg, 2);
        my_ftoa(td.hud_tw_range_str, td.grid[m_i][m_j].tw.range - 1, 2);
        my_ftoa(td.hud_tw_atckspd_str, td.grid[m_i][m_j].tw.atck_spd, 2);
        sfText_setString(td.hud_tw_dmg_txt, td.hud_tw_dmg_str);
        sfText_setString(td.hud_tw_range_txt, td.hud_tw_range_str);
        sfText_setString(td.hud_tw_atckspd_txt, td.hud_tw_atckspd_str);
        if (td.b_m_button == 0 && sfMouse_isButtonPressed(sfMouseLeft)) {
            td.stats_visible = 0;
            td.build_menu_open = 0;
        }
        if (get_mouse_intersectb(td, td.upgrade_menu_1)) {
            if (td.b_m_button != 5)
                td.b_m_button = 0;
            if (td.b_m_button == 0) {
                sfSound_play(td.click_sound);
                sfText_move(td.upgrade_txt_1, txt_displacement);
            }
            td.b_m_button = 5;
            sfSprite_setScale(td.upgrade_menu_1, scale1);
            sfText_setScale(td.upgrade_txt_1, tscale1);
            if (sfMouse_isButtonPressed(sfMouseLeft)) {
                td.gold_a += td.grid[m_i][m_j].tw.cost * 0.6;
                td.grid[m_i][m_j].tw = destroy_tower(td, td.grid[m_i][m_j].tw);
                td.stats_visible = 0;
                sfSound_play(td.sell_sound);
                sfRectangleShape_setTexture(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.texture, sfTrue);
                init_animated_rect(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.frames);
                td.build_menu_open = 0;
                td.build_menu_delay = td.seconds;
            }
        } else {
            if (td.b_m_button == 5) {
                td.b_m_button = 0;
                txt_displacement.y *= -1;
                sfText_move(td.upgrade_txt_1, txt_displacement);
                txt_displacement.y *= -1;
            }
            sfText_setScale(td.upgrade_txt_1, tscale0);
            sfSprite_setScale(td.upgrade_menu_1, scale0);
        }
        if (get_mouse_intersectb(td, td.upgrade_menu_2)) {
            if (td.b_m_button != 6)
                td.b_m_button = 0;
            if (td.b_m_button == 0) {
                sfSound_play(td.click_sound);
                sfText_move(td.upgrade_txt_2, txt_displacement);
            }
            if (td.grid[m_i][m_j].tw.level < 3) {
                my_ftoa(td.hud_tw_dmg_str, td.grid[m_i][m_j].tw.dmg * 1.2, 2);
                my_ftoa(td.hud_tw_atckspd_str, td.grid[m_i][m_j].tw.atck_spd * 1.02, 2);
                sfText_setString(td.hud_tw_dmg_txt, td.hud_tw_dmg_str);
                sfText_setString(td.hud_tw_atckspd_txt, td.hud_tw_atckspd_str);
                sfText_setFillColor(td.hud_tw_dmg_txt, sfGreen);
                sfText_setFillColor(td.hud_tw_atckspd_txt, sfGreen);
            }
            td.b_m_button = 6;
            sfSprite_setScale(td.upgrade_menu_2, scale1);
            sfText_setScale(td.upgrade_txt_2, tscale1);
            if (sfMouse_isButtonPressed(sfMouseLeft) && td.grid[m_i][m_j].tw.level < 3 && td.gold_a >= td.grid[m_i][m_j].tw.up_cost) {
                sfSound_play(td.build_sound);
                td.grid[m_i][m_j].tw = upgrade_tower(td.grid[m_i][m_j].tw, td.grid[m_i][m_j].tw.type);
                td.gold_a -= td.grid[m_i][m_j].tw.cost;
                sfRectangleShape_setTexture(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.texture, sfTrue);
                init_animated_rect(td.grid[m_i][m_j].unit, td.grid[m_i][m_j].tw.frames);
                td.build_menu_open = 0;
                sfText_setFillColor(td.hud_tw_dmg_txt, sfWhite);
                sfText_setFillColor(td.hud_tw_atckspd_txt, sfWhite);
                td.build_menu_delay = td.seconds;
                td.stats_visible = 0;
            }
        } else {
            if (td.b_m_button == 6) {
                td.b_m_button = 0;
                txt_displacement.y *= -1;
                sfText_move(td.upgrade_txt_2, txt_displacement);
                txt_displacement.y *= -1;
            }
            sfText_setFillColor(td.hud_tw_dmg_txt, sfWhite);
            sfText_setFillColor(td.hud_tw_atckspd_txt, sfWhite);
            sfText_setScale(td.upgrade_txt_2, tscale0);
            sfSprite_setScale(td.upgrade_menu_2, scale0);
        }
    }


    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 17; j++) {
            if ((td.mouse_pos.x >= td.grid[i][j].rect_pos.x - 60 && td.mouse_pos.x <= td.grid[i][j].rect_pos.x + 60)
                && (td.mouse_pos.y >= td.grid[i][j].rect_pos.y - 60 && td.mouse_pos.y <= td.grid[i][j].rect_pos.y + 60)) {
                if (sfMouse_isButtonPressed(sfMouseLeft) && td.grid[i][j].tw.type == 0 && td.grid[i][j].type == 7 && td.b_m_button == 0) {
                    td.build_menu_open = 1;
                    m_i = i;
                    m_j = j;
                    build_menu_pos.x = td.grid[i][j].rect_pos.x;
                    build_menu_pos.y = td.grid[i][j].rect_pos.y;
                    sfSprite_setPosition(td.build_menu, build_menu_pos);
                    build_menu_pos.y -= 54;
                    build_menu_pos.x -= 77;
                    sfSprite_setPosition(td.build_menu_1, build_menu_pos);
                    build_menu_pos.y += 18;
                    sfText_setPosition(td.build_txt_1, build_menu_pos);
                    build_menu_pos.y -= 18;
                    build_menu_pos.x += 155;
                    sfSprite_setPosition(td.build_menu_2, build_menu_pos);
                    build_menu_pos.y += 18;
                    sfText_setPosition(td.build_txt_2, build_menu_pos);
                    build_menu_pos.y += 108;
                    sfSprite_setPosition(td.build_menu_3, build_menu_pos);
                    build_menu_pos.y += 18;
                    sfText_setPosition(td.build_txt_3, build_menu_pos);
                    build_menu_pos.y -= 18;
                    build_menu_pos.x -= 155;
                    sfSprite_setPosition(td.build_menu_4, build_menu_pos);
                    build_menu_pos.y += 18;
                    sfText_setPosition(td.build_txt_4, build_menu_pos);
                    build_menu_pos.y -= 18;
                    return td;
                }
                if (sfMouse_isButtonPressed(sfMouseLeft) && td.grid[i][j].tw.type >= 0 && td.grid[i][j].type == 7 && td.b_m_button == 0) {
                    td.build_menu_open = 2;
                    m_i = i;
                    m_j = j;
                    upgrade_menu_pos.x = td.grid[i][j].rect_pos.x;
                    upgrade_menu_pos.y = td.grid[i][j].rect_pos.y;
                    sfSprite_setPosition(td.upgrade_menu, upgrade_menu_pos);
                    upgrade_menu_pos.y += 84;
                    upgrade_menu_pos.x -= 1;
                    sfSprite_setPosition(td.upgrade_menu_1, upgrade_menu_pos);
                    sfText_setString(td.upgrade_txt_1, int_to_string(td.upgrade_txt_str1, td.grid[i][j].tw.cost * 0.6));
                    sfText_setOrigin(td.upgrade_txt_1, get_text_center(td.upgrade_txt_1));
                    upgrade_menu_pos.y += 18;
                    sfText_setPosition(td.upgrade_txt_1, upgrade_menu_pos);
                    upgrade_menu_pos.y -= 192;
                    if (td.grid[i][j].tw.level < 3) {
                        sfText_setString(td.upgrade_txt_2, int_to_string(td.upgrade_txt_str2, td.grid[i][j].tw.up_cost));
                    } else
                        sfText_setString(td.upgrade_txt_2, "MAX");
                    sfText_setOrigin(td.upgrade_txt_2, get_text_center(td.upgrade_txt_2));
                    sfSprite_setPosition(td.upgrade_menu_2, upgrade_menu_pos);
                    upgrade_menu_pos.y += 18;
                    sfText_setPosition(td.upgrade_txt_2, upgrade_menu_pos);
                    return td;
                }
            }
        }
    }
    return td;
}

tower_defense handle_path(tower_defense td, int button)
{
    int i = 0;
    int j = 0;
    int clicked = 0;
    sfVector2f origin = {60, 60};

    while (i < 10) {
        while (j < 17) {
            if ((td.mouse_pos.x >= td.grid[i][j].rect_pos.x - 60 && td.mouse_pos.x <= td.grid[i][j].rect_pos.x + 60)
                && (td.mouse_pos.y >= td.grid[i][j].rect_pos.y - 60 && td.mouse_pos.y <= td.grid[i][j].rect_pos.y + 60)) {
                if (sfMouse_isButtonPressed(sfMouseRight) && td.grid[i][j].type != -1) {
                    td.grid[i][j].type = 0;
                    if (td.grid[i][j].entry_point >= 1)
                        sfSprite_destroy(td.grid[i][j].entry);
                    td.grid[i][j].entry_point = 0;
                    sfRectangleShape_setFillColor(td.grid[i][j].unit, sfTransparent);
                } else if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    if (button == 10 && td.grid[i][j].type >= 1 && td.grid[i][j].type <= 4 && is_touching_border(td, i, j) == sfTrue) {
                        td.grid[i][j].entry_point = 1;
                        td.grid[i][j].entry = new_sprite("sprites/map/defend_point.png", 1, 1);
                        sfSprite_setOrigin(td.grid[i][j].entry, origin);
                        sfSprite_setPosition(td.grid[i][j].entry, td.grid[i][j].rect_pos);
                        return td;
                    }
                    if (button == 11 && td.grid[i][j].type >= 1 && td.grid[i][j].type <= 4 && is_touching_border(td, i, j) == sfTrue) {
                        td.grid[i][j].entry_point = 2;
                        td.grid[i][j].entry = new_sprite("sprites/map/enemy_point.png", 1, 1);
                        sfSprite_setOrigin(td.grid[i][j].entry, origin);
                        sfSprite_setPosition(td.grid[i][j].entry, td.grid[i][j].rect_pos);
                        return td;
                    }
                    if (button == 7 && td.grid[i][j].type != -1) {
                        td.grid[i][j].type = 5;
                        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
                        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
                        sfRectangleShape_setTexture(td.grid[i][j].unit, td.tree, sfTrue);
                        return td;
                    }
                    if (button == 6 && td.grid[i][j].type != -1) {
                        td.grid[i][j].type = 6;
                        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
                        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
                        sfRectangleShape_setTexture(td.grid[i][j].unit, td.rock, sfTrue);
                        return td;
                    }
                    if (button == 8 && td.grid[i][j].type != -1) {
                        td.grid[i][j].type = 7;
                        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
                        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
                        sfRectangleShape_setTexture(td.grid[i][j].unit, td.buildable, sfTrue);
                        return td;
                    }
                    if (button == 4 && td.grid[i][j].type != -1) {
                        sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
                        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
                        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfTrue);
                        td = update_con_texture_type3(td, i, j);
                        td.grid[i][j].type = 3;
                        return td;
                    }
                    if (button == 2 && td.grid[i][j].type != -1) {
                        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
                        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
                        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfTrue);
                        sfRectangleShape_setRotation(td.grid[i][j].unit, -90);
                        td = update_con_texture_type4(td, i, j);
                        td.grid[i][j].type = 4;
                        return td;
                    }
                    if (button == 5 && td.grid[i][j].type != -1) {
                        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
                        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
                        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfTrue);
                        td = update_con_texture_type1(td, i, j);
                        td.grid[i][j].type = 1;
                        return td;
                    }
                    if (button == 3 && td.grid[i][j].type != -1) {
                        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
                        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
                        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfTrue);
                        sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
                        td = update_con_texture_type2(td, i, j);
                        td.grid[i][j].type = 2;
                        return td;
                    }
                }
            }
           j++;
        }
        i++;
        j = 0;
    }
    return td;
}

sfSprite *update_button_sprite(sfSprite *sprite, sfBool pressed)
{
    sfIntRect sheet_pos;
    sfFloatRect rect = sfSprite_getGlobalBounds(sprite);

    sheet_pos.height = rect.height;
    sheet_pos.width = rect.width;
    sheet_pos.top = 0;
    if (pressed == 1)
        sheet_pos.left = rect.width;
    else
        sheet_pos.left = 0;
    sfSprite_setTextureRect(sprite, sheet_pos);
    return (sprite);
}

sfSprite *update_animated_sprite(sfSprite *sprite)
{
    sfIntRect sheet_pos = sfSprite_getTextureRect(sprite);

    sheet_pos.left += sheet_pos.width;
    sheet_pos.top = 0;
    sfSprite_setTextureRect(sprite, sheet_pos);
    return (sprite);
}

int update_animated_sprite_finite(sfSprite *sprite, int frames)
{
    sfIntRect sheet_pos = sfSprite_getTextureRect(sprite);

    sheet_pos.left += sheet_pos.width;
    sheet_pos.top = 0;
    sfSprite_setTextureRect(sprite, sheet_pos);
    if (sheet_pos.left >= ((frames  + 1) * sheet_pos.width))
        return 0;
    return 1;
}

sfSprite *update_animated_spriteV(sfSprite *sprite, int offset, int width, int height)
{
    sfIntRect sheet_pos = {0, offset, width, height};

    sfSprite_setTextureRect(sprite, sheet_pos);
    return (sprite);
}

sfSprite *setSprite_pos(sfSprite *sprite, int posX, int posY)
{
    sfVector2f pos = {posX, posY};

    sfSprite_setPosition(sprite, pos);
    return (sprite);
}

void setText_pos(sfText *text, int posX, int posY)
{
    sfVector2f pos = {posX, posY};

    sfText_setPosition(text, pos);
}

sfSound *set_up_new_sound(sfSound *new_sound, const char *buffer_location)
{
    sfSoundBuffer *new_sound_buffer = sfSoundBuffer_createFromFile(buffer_location);

    new_sound = sfSound_create();
    sfSound_setBuffer(new_sound, new_sound_buffer);
    return (new_sound);
}

tower_defense handle_settings_menu(tower_defense td, int location, sfSprite *screen_capture_sprite)
{
    int apply = 0;
    int back = 0;
    int button = 0;
    tower_defense save = td;

    update_button_sprite(td.vol_up_button, 0);
    update_button_sprite(td.back_button, 0);
    update_button_sprite(td.vol_down_button, 0);
    update_animated_spriteV(td.vol_bar, td.vol_bar_offset, 960, 110);
    while (apply == 0 && back == 0) {
        sfMusic_setVolume(td.menu_music, td.volume);
        sfSound_setVolume(td.click_sound, td.volume);
        sfSound_setVolume(td.type1_death_sound, td.volume);
        sfSound_setVolume(td.build_sound, td.volume);
        sfSound_setVolume(td.type2_death_sound, td.volume);
        sfSound_setVolume(td.sell_sound, td.volume);
        sfSound_setVolume(td.lose_sound, td.volume);
        sfSound_setVolume(td.win_sound, td.volume);
        sfSound_setVolume(td.stab_sound, td.volume);
        sfSound_setVolume(td.explosion_sound, td.volume);
        td.mouse_pos = sfMouse_getPositionRenderWindow(td.window);
        td.mouse_pos.x *= save.g_scale;
        td.mouse_pos.y *= save.g_scale;
        sfRenderWindow_drawSprite(td.window, screen_capture_sprite, NULL);
        sfRenderWindow_drawSprite(td.window, td.dark, NULL);
        sfRenderWindow_drawSprite(td.window, td.settings_menu, NULL);
        sfRenderWindow_drawSprite(td.window, td.vol_up_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.vol_down_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.vol_bar, NULL);
        sfRenderWindow_drawSprite(td.window, td.apply_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.back_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.x640_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.x960_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.x1280_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.x1920_button, NULL);
        while (sfRenderWindow_pollEvent(td.window, &td.event)) {
            if (get_mouse_intersect(td, td.back_button)) {
                if (button != 1)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 1;
                update_button_sprite(td.back_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft))
                    return save;
            } else {
                if (button == 1)
                    button = 0;
                update_button_sprite(td.back_button, 0);
            }
            if (get_mouse_intersect(td, td.apply_button)) {
                if (button != 2)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 2;
                update_button_sprite(td.apply_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft))
                    return td;
            } else {
                if (button == 2)
                    button = 0;
                update_button_sprite(td.apply_button, 0);
            }
            if (get_mouse_intersect(td, td.x1920_button)) {
                if (button != 3)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 3;
                update_button_sprite(td.x1920_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.window_size.x = 1920;
                    td.window_size.y = 1080;
                    td.g_scale = 1;
                }
            } else {
                if (button == 3)
                    button = 0;
                update_button_sprite(td.x1920_button, 0);
            }
            if (get_mouse_intersect(td, td.x1280_button)) {
                if (button != 4)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 4;
                update_button_sprite(td.x1280_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.window_size.x = 1920/1.5;
                    td.window_size.y = 1080/1.5;
                    td.g_scale = 1.5;
                }
            } else {
                if (button == 4)
                    button = 0;
                update_button_sprite(td.x1280_button, 0);
            }
            if (get_mouse_intersect(td, td.x960_button)) {
                if (button != 5)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 5;
                update_button_sprite(td.x960_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.window_size.x = 1920/2;
                    td.window_size.y = 1080/2;
                    td.g_scale = 2;
                }
            } else {
                if (button == 5)
                    button = 0;
                update_button_sprite(td.x960_button, 0);
            }
            if (get_mouse_intersect(td, td.x640_button)) {
                if (button != 6)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 6;
                update_button_sprite(td.x640_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.window_size.x = 1920/3;
                    td.window_size.y = 1080/3;
                    td.g_scale = 3;
                }
            } else {
                if (button == 6)
                    button = 0;
                update_button_sprite(td.x640_button, 0);
            }
            if (get_mouse_intersect(td, td.vol_up_button)) {
                if (button != 7)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 7;
                update_button_sprite(td.vol_up_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft))
                    if (td.volume < 100) {
                        td.volume += 5;
                        td.vol_bar_offset -= 110;
                        update_animated_spriteV(td.vol_bar, td.vol_bar_offset, 960, 110);
                    }
            } else {
                if (button == 7)
                    button = 0;
                update_button_sprite(td.vol_up_button, 0);
            }
            if (get_mouse_intersect(td, td.vol_down_button)) {
                if (button != 8)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 8;
                update_button_sprite(td.vol_down_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft))
                    if (td.volume > 0) {
                        td.volume -= 5;
                        td.vol_bar_offset += 110;
                        update_animated_spriteV(td.vol_bar, td.vol_bar_offset, 960, 110);
                    }
            } else {
                if (button == 8)
                    button = 0;
                update_button_sprite(td.vol_down_button, 0);
            }
        }
        sfRenderWindow_display(td.window);
    }  
    return td;
}

tower_defense handle_start_loop(tower_defense td)
{
    sfTexture *screen_capture = sfTexture_create(td.window_size.x, td.window_size.y);
    sfSprite *screen_capture_sprite = sfSprite_create();
    sfVector2f capture_scale;
    int button = 0;
    float error_delay = -2;
    sfVector2f error_text_pos = {750, 900};
    sfText *error_text = sfText_create();

    sfText_setCharacterSize(error_text, 30);
    sfText_setFillColor(error_text, sfRed);
    sfText_setOutlineColor(error_text, sfBlack);
    sfText_setOutlineThickness(error_text, 4);
    sfText_setFont(error_text, td.font);
    sfText_setPosition(error_text, error_text_pos);
    sfText_setString(error_text, "Error: map could not be found");
    sfRenderWindow_drawSprite(td.window, td.main_menu, NULL);
    sfRenderWindow_display(td.window);
    sfTexture_updateFromRenderWindow(screen_capture, td.window, 0, 0);
    sfSprite_setTexture(screen_capture_sprite, screen_capture, sfTrue);
    update_button_sprite(td.map_editor_button, 0);
    update_button_sprite(td.back_start_button, 0);
    capture_scale.x = td.g_scale;
    capture_scale.y = td.g_scale;
    sfSprite_setScale(screen_capture_sprite, capture_scale);
    while (td.main_menu_button == 0) {
        td.time = sfClock_getElapsedTime(td.clock);
        td.seconds = td.time.microseconds/1000000.0;
        td.mouse_pos = sfMouse_getPositionRenderWindow(td.window);
        td.mouse_pos.x *= td.g_scale;
        td.mouse_pos.y *= td.g_scale;
        td.mouse_posF.x = td.mouse_pos.x;
        td.mouse_posF.y = td.mouse_pos.y;
        sfRenderWindow_drawSprite(td.window, td.main_menu, NULL);
        sfRenderWindow_drawSprite(td.window, td.campaign_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.custom_level_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.map_editor_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.back_start_button, NULL);
        while (sfRenderWindow_pollEvent(td.window, &td.event)) {
            if (sfKeyboard_isKeyPressed(sfKeyEscape) && td.seconds > td.level_back_delay + 0.1) {
                td.delay_exit = td.seconds; 
                return td;
            }
            if (get_mouse_intersect(td, td.map_editor_button)) {
                if (button != 1)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 1;
                update_button_sprite(td.map_editor_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.main_menu_button = 1;
                    return td;
                }
            } else {
                if (button == 1)
                    button = 0;
                update_button_sprite(td.map_editor_button, 0);
            }
            if (get_mouse_intersect(td, td.back_start_button)) {
                if (button != 2)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 2;
                update_button_sprite(td.back_start_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.delay_exit = td.seconds; 
                    return td;
                }
            } else {
                if (button == 2)
                    button = 0;
                update_button_sprite(td.back_start_button, 0);
            }
            if (get_mouse_intersect(td, td.custom_level_button) && td.seconds > td.start_delay + 0.1) {
                if (button != 3)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 3;
                update_button_sprite(td.custom_level_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td = load_map_loop(td);
                    error_delay = td.seconds;
                    if (td.load_success == 1) {
                        td.main_menu_button = 2;
                        td.custom_level = 1;
                        return td;
                    }
                }
            } else {
                if (button == 3)
                    button = 0;
                update_button_sprite(td.custom_level_button, 0);
            }
            if (get_mouse_intersect(td, td.campaign_button)) {
                if (button != 4)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 4;
                update_button_sprite(td.campaign_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.level_selection_delay = td.seconds;
                    td = level_selection(td);
                    if (td.chapter > 0) {
                        td.main_menu_button = 2;
                        return td;
                    }
                }
            } else {
                if (button == 4)
                    button = 0;
                update_button_sprite(td.campaign_button, 0);
            }
        }
        if (td.load_success == 0 && td.seconds < error_delay + 2)
            sfRenderWindow_drawText(td.window, error_text, NULL);
        sfRenderWindow_display(td.window);
    }
    return td;
}

tower_defense handle_main_menu_loop(tower_defense td)
{
    sfTexture *screen_capture = sfTexture_create(td.window_size.x, td.window_size.y);
    sfSprite *screen_capture_sprite = sfSprite_create();
    sfVector2f capture_scale;
    sfIntRect sheet_pos;
    int button = 0;

    sfRenderWindow_drawSprite(td.window, td.main_menu, NULL);
    sfRenderWindow_drawSprite(td.window, td.start_button, NULL);
    sfRenderWindow_drawSprite(td.window, td.settings_button, NULL);
    sfRenderWindow_drawSprite(td.window, td.exit_button, NULL);
    sfRenderWindow_drawSprite(td.window, td.help_button, NULL);
    sfRenderWindow_display(td.window);
    sfTexture_updateFromRenderWindow(screen_capture, td.window, 0, 0);
    sfSprite_setTexture(screen_capture_sprite, screen_capture, sfTrue);
    capture_scale.x = td.g_scale;
    capture_scale.y = td.g_scale;
    sfSprite_setScale(screen_capture_sprite, capture_scale);
    while (td.main_menu_button == 0) {
        td.time = sfClock_getElapsedTime(td.clock);
        td.seconds = td.time.microseconds/1000000.0;
        td.mouse_pos = sfMouse_getPositionRenderWindow(td.window);
        td.mouse_pos.x *= td.g_scale;
        td.mouse_pos.y *= td.g_scale;
        td.mouse_posF.x = td.mouse_pos.x;
        td.mouse_posF.y = td.mouse_pos.y;
        sfRectangleShape_setPosition(td.cursor_hitbox, td.mouse_posF);
        sfRenderWindow_drawSprite(td.window, td.main_menu, NULL);
        sfRenderWindow_drawSprite(td.window, td.start_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.settings_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.exit_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.help_button, NULL);
        if (td.how_to_play_open == 1) {
            sfRenderWindow_drawSprite(td.window, td.how_to_play_sprite, NULL);
            sfRenderWindow_drawSprite(td.window, td.back_how_to_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.next_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.prev_button, NULL);
        }
        while (sfRenderWindow_pollEvent(td.window, &td.event)) {
            if (td.event.type == sfEvtClosed) {
                td = exit_game(td);
                if (td.exit == 1)
                    return td;
            }
            if (get_mouse_intersect(td, td.start_button) && td.how_to_play_open == 0) {
                if (button != 1)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 1;
                update_button_sprite(td.start_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.start_delay = td.seconds;
                    td = handle_start_loop(td);
                    if (td.main_menu_button > 0)
                        return td;
                }
            } else {
                if (button == 1)
                    button = 0;
                update_button_sprite(td.start_button, 0);
            }
            if (get_mouse_intersect(td, td.settings_button) && td.how_to_play_open == 0) {
                if (button != 2)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 2;
                update_button_sprite(td.settings_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td = handle_settings_menu(td, 0, screen_capture_sprite);
                    if (sfVideoMode_getDesktopMode().height == td.window_size.y && sfVideoMode_getDesktopMode().width == td.window_size.x) {
                        if (td.fullscreen == 0) {
                            td.fullscreen = 1;
                            td = switch_window_mode(td, 1);
                        }
                    } else if (td.fullscreen == 1) {
                        td.fullscreen = 0;
                        td = switch_window_mode(td, 0);
                        sfRenderWindow_setPosition(td.window, td.window_pos);
                    }
                    sfRenderWindow_setSize(td.window, td.window_size);
                    sfMusic_setVolume(td.menu_music, td.volume);
                }
            } else {
                if (button == 2)
                    button = 0;
                update_button_sprite(td.settings_button, 0);
            }
            if (get_mouse_intersect(td, td.exit_button) && td.how_to_play_open == 0) {
                if (button != 3)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 3;
                update_button_sprite(td.exit_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft) && (td.seconds - (td.delay_exit + 0.5) > 0))
                    td = exit_game(td);
                    if (td.exit == 1)
                        return td;
            } else {
                if (button == 3)
                    button = 0;
                update_button_sprite(td.exit_button, 0);
            }
            if (get_mouse_intersect(td, td.help_button) && td.how_to_play_open == 0) {
                if (button != 4)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 4;
                update_button_sprite(td.help_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft) && (td.seconds - (td.delay_exit + 0.5) > 0))
                    td.how_to_play_open = 1;
            } else {
                if (button == 4)
                    button = 0;
                update_button_sprite(td.help_button, 0);
            }
            if (get_mouse_intersect(td, td.back_how_to_button) && td.how_to_play_open == 1) {
                if (button != 5)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 5;
                update_button_sprite(td.back_how_to_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft) && (td.seconds - (td.delay_exit + 0.5) > 0))
                    td.how_to_play_open = 0;
            } else {
                if (button == 5)
                    button = 0;
                update_button_sprite(td.back_how_to_button, 0);
            }
            if (get_mouse_intersect(td, td.next_button) && td.how_to_play_open == 1) {
                if (button != 6)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 6;
                update_button_sprite(td.next_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft) && (td.seconds - (td.delay_exit + 0.5) > 0)) {
                    sheet_pos = sfSprite_getTextureRect(td.how_to_play_sprite);
                    sheet_pos.left += sheet_pos.width;
                    sheet_pos.top = 0;
                    sfSprite_setTextureRect(td.how_to_play_sprite, sheet_pos);
                }
            } else {
                if (button == 6)
                    button = 0;
                update_button_sprite(td.next_button, 0);
            }
            if (get_mouse_intersect(td, td.prev_button) && td.how_to_play_open == 1) {
                if (button != 7)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 7;
                update_button_sprite(td.prev_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft) && (td.seconds - (td.delay_exit + 0.5) > 0)) {
                    sheet_pos = sfSprite_getTextureRect(td.how_to_play_sprite);
                    sheet_pos.left -= sheet_pos.width;
                    sheet_pos.top = 0;
                    sfSprite_setTextureRect(td.how_to_play_sprite, sheet_pos);
                }
            } else {
                if (button == 7)
                    button = 0;
                update_button_sprite(td.prev_button, 0);
            }
        }
        sfRenderWindow_display(td.window);
    }
    return td;
}

tower_defense handle_pause_menu(tower_defense td)
{
    int resume = 0;
    int exit = 0;
    sfTexture *screen_capture = sfTexture_create(td.window_size.x, td.window_size.y);
    sfSprite *screen_capture_sprite = sfSprite_create();
    sfVector2f capture_scale;
    sfVector2u old_win_size = td.window_size;
    int button = 0;

    sfTexture_updateFromRenderWindow(screen_capture, td.window, 0, 0);
    sfSprite_setTexture(screen_capture_sprite, screen_capture, sfTrue);
    capture_scale.x = td.g_scale;
    capture_scale.y = td.g_scale;
    sfSprite_setScale(screen_capture_sprite, capture_scale);
    while (exit == 0 && resume == 0) {
        old_win_size = td.window_size;
        td.mouse_pos = sfMouse_getPositionRenderWindow(td.window);
        td.mouse_pos.x *= td.g_scale;
        td.mouse_pos.y *= td.g_scale;
        sfRenderWindow_drawSprite(td.window, screen_capture_sprite, NULL);
        sfRenderWindow_drawSprite(td.window, td.dark, NULL);
        sfRenderWindow_drawSprite(td.window, td.pause_menu, NULL);
        sfRenderWindow_drawSprite(td.window, td.resume_button, NULL);
        sfRenderWindow_drawSprite(td.window, td.settings_button_p, NULL);
        sfRenderWindow_drawSprite(td.window, td.exit_button_p, NULL);
        while (sfRenderWindow_pollEvent(td.window, &td.event)) {
            if (get_mouse_intersect(td, td.resume_button)) {
                if (button != 1)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 1;
                update_button_sprite(td.resume_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft))
                    return td;
            } else {
                if (button == 1)
                    button = 0;
                update_button_sprite(td.resume_button, 0);
            }
            if (get_mouse_intersect(td, td.settings_button_p)) {
                if (button != 2)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 2;
                update_button_sprite(td.settings_button_p, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td =  handle_settings_menu(td, 1, screen_capture_sprite);
                    if (sfVideoMode_getDesktopMode().height == td.window_size.y && sfVideoMode_getDesktopMode().width == td.window_size.x) {
                        if (td.fullscreen == 0) {
                            td.fullscreen = 1;
                            td = switch_window_mode(td, 1);
                            sfRenderWindow_setVerticalSyncEnabled(td.window, sfTrue);
                        }
                    } else if (td.fullscreen == 1) {
                        td.fullscreen = 0;
                        td = switch_window_mode(td, 0);
                        sfRenderWindow_setVerticalSyncEnabled(td.window, sfTrue);
                        sfRenderWindow_setPosition(td.window, td.window_pos);
                    }
                    sfRenderWindow_setSize(td.window, td.window_size);
                    sfMusic_setVolume(td.menu_music, td.volume);
                }
            } else {
                if (button == 2)
                    button = 0;
                update_button_sprite(td.settings_button_p, 0);
            }
            if (get_mouse_intersect(td, td.exit_button_p)) {
                if (button != 3)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 3;
                update_button_sprite(td.exit_button_p, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.exit_code = 1;
                    return td;
                }
            } else {
                if (button == 3)
                    button = 0;
                update_button_sprite(td.exit_button_p, 0);
            }
        }
        sfRenderWindow_display(td.window);
    }
}

char *my_strcat(char *dest, char const *src)
{
    int dest_len = my_strlen(dest);
    int i = 0;

    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

void init_animated_button(sfSprite *sprite)
{
    sfIntRect rect = sfSprite_getTextureRect(sprite);

    rect.width /= 2;
    sfSprite_setTextureRect(sprite, rect);
}

int get_int_len(int nb)
{
    int len = 0;

    while (nb > 0) {
        nb = nb/10;
        len++;
    }
    return (len + 1);
}

char *my_itoa(int nb)
{
    int i = 0;
    int mem_nb = nb;
    int remains;
    char *str = malloc(sizeof(char) * get_int_len(nb) + 1);

    if (nb == 0) {
        str[i] = '0';
        str[i + 1] = '\0';
        return (str);
    }
    if (nb < 0) nb = -nb;
    while (nb != 0) {
        remains = nb % 10;
        str[i] = remains + '0';
        nb = nb / 10;
        i = i + 1;
    }
    if (mem_nb < 0) {
        str[i] = '-';
        str[i + 1] = '\0';
    } else
        str[i] = '\0';
    my_revstr(str);
    return (str);
}

void write_save(tower_defense td)
{
    FILE *f;
    char *save = malloc(sizeof(char) * 1000);
    int x = 0;
    char *filepath = malloc(sizeof(char) * 100);
    my_strcpy(filepath, "maps/");
    my_strcat(filepath, sfText_getString(td.player_text));
    my_strcat(filepath, ".map");

    f = fopen(filepath, "w");
    fwrite("", 1, 0, f);
    fclose(f);
    f = fopen(filepath, "a");
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 17; j++) {
            fwrite(my_itoa(td.grid[i][j].type), 1, my_strlen(my_itoa(td.grid[i][j].type)), f);
            fwrite(my_itoa(td.grid[i][j].entry_point), 1, my_strlen(my_itoa(td.grid[i][j].entry_point)), f);
        }
        fwrite("\n", 1, 1, f);
    }
    fclose(f);
}

tower_defense set_tiles_attributes(tower_defense td, int i, int j)
{
    sfVector2f origin = {60, 60};

    if (td.grid[i][j].entry_point == 1) {
        td.grid[i][j].entry = new_sprite("sprites/map/defend_point.png", 1, 1);
        sfSprite_setOrigin(td.grid[i][j].entry, origin);
        sfSprite_setPosition(td.grid[i][j].entry, td.grid[i][j].rect_pos);
    }
    if (td.grid[i][j].entry_point == 2) {
        td.grid[i][j].entry = new_sprite("sprites/map/enemy_point.png", 1, 1);
        sfSprite_setOrigin(td.grid[i][j].entry, origin);
        sfSprite_setPosition(td.grid[i][j].entry, td.grid[i][j].rect_pos);
    }
    if (td.grid[i][j].type == 5) {
        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.tree, sfTrue);
        return td;
    }
    if (td.grid[i][j].type == 6) {
        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.rock, sfTrue);
        return td;
    }
    if (td.grid[i][j].type == 7) {
        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.buildable, sfTrue);
        return td;
    }
    if (td.grid[i][j].type == 3) {
        sfRectangleShape_setRotation(td.grid[i][j].unit, 180);
        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfTrue);
        td = update_con_texture_type3(td, i, j);
        return td;
    }
    if (td.grid[i][j].type == 4) {
        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfTrue);
        sfRectangleShape_setRotation(td.grid[i][j].unit, -90);
        td = update_con_texture_type4(td, i, j);
        return td;
    }
    if (td.grid[i][j].type == 1) {
        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfTrue);
        td = update_con_texture_type1(td, i, j);
        return td;
    }
    if (td.grid[i][j].type == 2) {
        sfRectangleShape_setRotation(td.grid[i][j].unit, 0);
        sfRectangleShape_setFillColor(td.grid[i][j].unit, sfWhite);
        sfRectangleShape_setTexture(td.grid[i][j].unit, td.straight_path, sfTrue);
        sfRectangleShape_setRotation(td.grid[i][j].unit, 90);
        td = update_con_texture_type2(td, i, j);
        return td;
    }
    return td;
}

tower_defense load_level(tower_defense td, char *path)
{
    int fd;
    char *buff = malloc(sizeof(char) * 1000);
    int x = 0;
    char *filepath = malloc(sizeof(char) * 100);
    sfVector2f case_pos = {-60, -60};
    sfVector2f case_origin = {60, 60};

    td.straight_path = sfTexture_createFromFile("sprites/map/straight_path.png", NULL);
    td.load_success = 0;
    my_strcpy(filepath, "maps/");
    my_strcat(filepath, path);
    my_strcat(filepath, ".map");
    fd = open(filepath, 0, O_RDONLY);
    if (fd == -1)
        return td;
    td.load_success = 1;
    read(fd, buff, 1000);
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 17; j++) {
            td.grid[i][j].size.x = 120;
            td.grid[i][j].size.y = 120;
            td.grid[i][j].entry_point = 0;
            td.grid[i][j].rect_pos.x = case_pos.x;
            td.grid[i][j].rect_pos.y = case_pos.y;
            td.grid[i][j].tw.type = 0;
            td.grid[i][j].tw.dmg = 0;
            td.grid[i][j].tw.atck_spd = 0;
            td.grid[i][j].tw.range = 0;
            td.grid[i][j].tw.level = 0;
            td.grid[i][j].tw.cost = 0;
            td.grid[i][j].cc.u = 0;
            td.grid[i][j].cc.d = 0;
            td.grid[i][j].cc.r = 0;
            td.grid[i][j].cc.l = 0;
            td.grid[i][j].unit = sfRectangleShape_create();
            sfRectangleShape_setSize(td.grid[i][j].unit, td.grid[i][j].size);
            sfRectangleShape_setFillColor(td.grid[i][j].unit, sfTransparent);
            sfRectangleShape_setOrigin(td.grid[i][j].unit, case_origin);
            sfRectangleShape_setPosition(td.grid[i][j].unit, td.grid[i][j].rect_pos);
            if (i > 0 && i < 9 && j > 0 && j < 17) {
                if (buff[x] == '\n')
                    x++;
                td.grid[i][j].type = buff[x] - 48;
                x++;
                td.grid[i][j].entry_point = buff[x] - 48;
                x++;
                td = set_tiles_attributes(td, i, j);
            }
            case_pos.x += 120;
        }
        case_pos.y += 120;
        case_pos.x = -60;
    }
    close(fd);
    return td;
}

tower_defense load_map(tower_defense td)
{
    int fd;
    char *buff = malloc(sizeof(char) * 1000);
    int x = 0;
    char *filepath = malloc(sizeof(char) * 100);
    sfVector2f case_pos = {280, 80};
    sfVector2f case_origin = {50, 50};

    td.load_success = 0;
    my_strcpy(filepath, "maps/");
    my_strcat(filepath, sfText_getString(td.player_text2));
    my_strcat(filepath, ".map");
    fd = open(filepath, 0, O_RDONLY);
    if (fd == -1)
        return td;
    td.load_success = 1;
    read(fd, buff, 1000);
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 17; j++) {
            td.grid[i][j].size.x = 100;
            td.grid[i][j].size.y = 100;
            td.grid[i][j].entry_point = 0;
            td.grid[i][j].rect_pos.x = case_pos.x;
            td.grid[i][j].rect_pos.y = case_pos.y;
            td.grid[i][j].cc.u = 0;
            td.grid[i][j].cc.d = 0;
            td.grid[i][j].cc.r = 0;
            td.grid[i][j].cc.l = 0;
            sfRectangleShape_setSize(td.grid[i][j].unit, td.grid[i][j].size);
            sfRectangleShape_setFillColor(td.grid[i][j].unit, sfTransparent);
            sfRectangleShape_setOrigin(td.grid[i][j].unit, case_origin);
            sfRectangleShape_setPosition(td.grid[i][j].unit, td.grid[i][j].rect_pos);
            if (i > 0 && i < 9 && j > 0 && j < 17) {
                if (buff[x] == '\n')
                    x++;
                td.grid[i][j].type = buff[x] - 48;
                x++;
                td.grid[i][j].entry_point = buff[x] - 48;
                x++;
                td = set_tiles_attributes(td, i, j);
            }
            case_pos.x += 100;
        }
        case_pos.y += 100;
        case_pos.x = 280;
    }
    close(fd);
    return td;
}

tower_defense load_map_loop(tower_defense td)
{
    sfVector2f player_text_pos = {885, 50};
    sfVector2f cursor_sprite_pos;
    sfVector2f text_box_size;
    sfVector2f test = {150, 150};
    sfSprite *text_zone = new_sprite("sprites/hud/text_zone.png", 1, 1);
    sfTexture *screen_capture = sfTexture_create(td.window_size.x, td.window_size.y);
    sfSprite *screen_capture_sprite = sfSprite_create();
    sfVector2f capture_scale;

    sfTexture_updateFromRenderWindow(screen_capture, td.window, 0, 0);
    sfSprite_setTexture(screen_capture_sprite, screen_capture, sfTrue);
    capture_scale.x = td.g_scale;
    capture_scale.y = td.g_scale;
    sfSprite_setScale(screen_capture_sprite, capture_scale);
    setSprite_pos(text_zone, 870, 40);
    td.erase = 0;
    td.load_delay = 0;
    td.player_text2 = sfText_create();
    sfText_setCharacterSize(td.player_text2, 20);
    sfText_setFillColor(td.player_text2, sfBlack);
    sfText_setFont(td.player_text2, td.font);
    sfText_setPosition(td.player_text2, player_text_pos);
    td.player_string2 = malloc(sizeof(char) * 100);
    td.player_string2[0] = '\0';
    while (sfRenderWindow_isOpen(td.window)) {
        td.mouse_pos = sfMouse_getPositionRenderWindow(td.window);
        td.mouse_pos.x *= td.g_scale;
        td.mouse_pos.y *= td.g_scale;
        td.time = sfClock_getElapsedTime(td.clock);
        td.seconds = td.time.microseconds/1000000.0;
        if ((td.main_clock + 0.016) < td.seconds) {
            td.main_clock = td.seconds;
            text_box_size.x = sfText_getGlobalBounds(td.player_text2).width;
            text_box_size.y = sfText_getGlobalBounds(td.player_text2).height;
            sfRenderWindow_drawSprite(td.window, screen_capture_sprite, NULL);
            sfRenderWindow_drawSprite(td.window, text_zone, NULL);
            sfRenderWindow_drawText(td.window, td.player_text2, NULL);
            while (sfRenderWindow_pollEvent(td.window, &td.event)) {
                if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
                    td.load_delay = td.seconds;
                    return td;
                }
                if (sfKeyboard_isKeyPressed(sfKeyEnter) && td.seconds > td.load_delay + 0.03) {
                    td = load_map(td);
                    td.load_delay = td.seconds;
                    return td;
                }
                if (sfKeyboard_isKeyPressed(sfKeyBackspace) && (td.seconds > td.erase + 0.01)) {
                    td.erase = td.seconds;
                    my_strcpy(td.player_string2, sfText_getString(td.player_text2));
                    td.player_string2[my_strlen(td.player_string2) - 1] = '\0';
                    sfText_setString(td.player_text2, td.player_string2);
                } else if (td.event.type == sfEvtTextEntered && sfKeyboard_isKeyPressed(sfKeyBackspace) == sfFalse && sfKeyboard_isKeyPressed(sfKeyEnter) == sfFalse && text_box_size.x < 203) {
                    sfText_setUnicodeString(td.player_text2, &td.event.text.unicode);
                    my_strcat(td.player_string2, sfText_getString(td.player_text2));
                    sfText_setString(td.player_text2, td.player_string2);
                }
                if (td.event.type == sfEvtClosed)
                    td = exit_game(td);
                    if (td.exit == 1)
                        return td;
            }
            sfRenderWindow_display(td.window);
        }
    }
}

tower_defense execute_editor_loop(tower_defense td)
{
    int i = 0;
    int j = 0;
    int grid_visible = 1;
    int button = 0;
    int selected = 0;
    float error_delay = 0;
    sfVector2f player_text_pos = {40, 900};
    sfVector2f error_text_pos = {400, 40};
    sfSprite *cursor = new_sprite("sprites/empty.png", 0.5, 0.5);
    sfTexture *empty = sfTexture_createFromFile("sprites/empty.png", NULL);
    sfVector2f cursor_sprite_pos;
    sfVector2f text_box_size;
    sfVector2f test = {150, 150};
    sfText *error_text = sfText_create();

    td.buildable = sfTexture_createFromFile("sprites/map/buildable.png", NULL);
    td.L_path = sfTexture_createFromFile("sprites/map/L_path.png", NULL);
    td.X_path = sfTexture_createFromFile("sprites/map/X_path.png", NULL);
    td.T_path = sfTexture_createFromFile("sprites/map/T_path.png", NULL);
    td.straight_path = sfTexture_createFromFile("sprites/map/straight_path_arrow.png", NULL);
    td.player_text = sfText_create();
    td.font = sfFont_createFromFile("misc/font.ttf");
    sfSprite_setTexture(td.background, sfTexture_createFromFile("sprites/map/background.jpg", NULL), sfFalse);
    sfText_setCharacterSize(error_text, 30);
    sfText_setFillColor(error_text, sfRed);
    sfText_setOutlineColor(error_text, sfBlack);
    sfText_setOutlineThickness(error_text, 4);
    sfText_setFont(error_text, td.font);
    sfText_setPosition(error_text, error_text_pos);
    sfText_setString(error_text, "Error: map could not be found");
    sfText_setCharacterSize(td.player_text, 20);
    sfText_setFillColor(td.player_text, sfBlack);
    sfText_setFont(td.player_text, td.font);
    sfText_setPosition(td.player_text, player_text_pos);
    td.player_string = malloc(sizeof(char) * 100);
    td.player_string[0] = '\0';
    td.erase = 0;
    td.load_success = -1;
    td.load_delay = 0;
    while (sfRenderWindow_isOpen(td.window)) {
        td.mouse_pos = sfMouse_getPositionRenderWindow(td.window);
        td.mouse_pos.x *= td.g_scale;
        td.mouse_pos.y *= td.g_scale;
        cursor_sprite_pos.x = td.mouse_pos.x;
        cursor_sprite_pos.y = td.mouse_pos.y;
        sfSprite_setPosition(cursor, cursor_sprite_pos);
        td.time = sfClock_getElapsedTime(td.clock);
        td.seconds = td.time.microseconds/1000000.0;
        if ((td.main_clock + 0.016) < td.seconds) {
            td.main_clock = td.seconds;
            td.choice = 0;
            sfRenderWindow_clear(td.window, sfBlack);
            sfRenderWindow_drawSprite(td.window, td.background, NULL);
            j = 0;
            i = 0;
            while (i < 9) {
                while (j < 17) {
                    if (i > 0)
                        td = update_con_texture(td, i - 1, j, td.grid[i - 1][j].type);
                    td = update_con_texture(td, i + 1, j, td.grid[i + 1][j].type);
                    td = update_con_texture(td, i, j + 1, td.grid[i][j + 1].type);
                    if (j > 0)
                        td = update_con_texture(td, i, j - 1, td.grid[i][j - 1].type);
                    sfRenderWindow_drawRectangleShape(td.window, td.grid[i][j].unit, NULL);
                    if (td.grid[i][j].entry_point >= 1)
                        sfRenderWindow_drawSprite(td.window, td.grid[i][j].entry, NULL);
                    j++;
                }
                i++;
                j = 0;
            }
            text_box_size.x = sfText_getGlobalBounds(td.player_text).width;
            text_box_size.y = sfText_getGlobalBounds(td.player_text).height;
            sfRenderWindow_drawSprite(td.window, td.menu_editor, NULL);
            sfRenderWindow_drawSprite(td.window, td.erase_hint, NULL);
            sfRenderWindow_drawSprite(td.window, td.toggle_grid_hint, NULL);
            sfRenderWindow_drawSprite(td.window, td.tree_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.enemy_point_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.defend_point_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.buildable_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.rock_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.u_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.d_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.r_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.l_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.text_zone, NULL);
            sfRenderWindow_drawSprite(td.window, td.save_button, NULL);
            sfRenderWindow_drawSprite(td.window, td.load_button, NULL);
            sfRenderWindow_drawText(td.window, td.player_text, NULL);
            while (sfRenderWindow_pollEvent(td.window, &td.event)) {
                if (get_mouse_intersect(td, td.save_button)) {
                    if (button != 1)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 1;
                    update_button_sprite(td.save_button, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        write_save(td);
                    }
                } else {
                    if (button == 1)
                        button = 0;
                    update_button_sprite(td.save_button, 0);
                }
                if (get_mouse_intersect(td, td.u_button)) {
                    if (button != 2)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 2;
                    update_button_sprite(td.u_button, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        sfSprite_setTexture(cursor, sfSprite_getTexture(td.u_button), sfTrue);
                        init_animated_button(cursor);
                        selected = 2;
                    }
                } else {
                    if (button == 2)
                        button = 0;
                    update_button_sprite(td.u_button, 0);
                }
                if (get_mouse_intersect(td, td.d_button)) {
                    if (button != 3)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 3;
                    update_button_sprite(td.d_button, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        sfSprite_setTexture(cursor, sfSprite_getTexture(td.d_button), sfTrue);
                        init_animated_button(cursor);
                        selected = 3;
                    }
                } else {
                    if (button == 3)
                        button = 0;
                    update_button_sprite(td.d_button, 0);
                }
                if (get_mouse_intersect(td, td.l_button)) {
                    if (button != 4)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 4;
                    update_button_sprite(td.l_button, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        sfSprite_setTexture(cursor, sfSprite_getTexture(td.l_button), sfTrue);
                        init_animated_button(cursor);
                        selected = 4;
                    }
                } else {
                    if (button == 4)
                        button = 0;
                    update_button_sprite(td.l_button, 0);
                }
                if (get_mouse_intersect(td, td.r_button)) {
                    if (button != 5)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 5;
                    update_button_sprite(td.r_button, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        sfSprite_setTexture(cursor, sfSprite_getTexture(td.r_button), sfTrue);
                        init_animated_button(cursor);
                        selected = 5;
                    }
                } else {
                    if (button == 5)
                        button = 0;
                    update_button_sprite(td.r_button, 0);
                }
                if (get_mouse_intersect(td, td.rock_button)) {
                    if (button != 6)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 6;
                    update_button_sprite(td.rock_button, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        sfSprite_setTexture(cursor, sfSprite_getTexture(td.rock_button), sfTrue);
                        init_animated_button(cursor);
                        selected = 6;
                    }
                } else {
                    if (button == 6)
                        button = 0;
                    update_button_sprite(td.rock_button, 0);
                }
                if (get_mouse_intersect(td, td.tree_button)) {
                    if (button != 7)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 7;
                    update_button_sprite(td.tree_button, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        sfSprite_setTexture(cursor, sfSprite_getTexture(td.tree_button), sfTrue);
                        init_animated_button(cursor);
                        selected = 7;
                    }
                } else {
                    if (button == 7)
                        button = 0;
                    update_button_sprite(td.tree_button, 0);
                }
                if (get_mouse_intersect(td, td.buildable_button)) {
                    if (button != 8)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 8;
                    update_button_sprite(td.buildable_button, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        sfSprite_setTexture(cursor, sfSprite_getTexture(td.buildable_button), sfTrue);
                        init_animated_button(cursor);
                        selected = 8;
                    }
                } else {
                    if (button == 8)
                        button = 0;
                    update_button_sprite(td.buildable_button, 0);
                }
                if (get_mouse_intersect(td, td.defend_point_button)) {
                    if (button != 10)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 10;
                    update_button_sprite(td.defend_point_button, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        sfSprite_setTexture(cursor, sfSprite_getTexture(td.defend_point_button), sfTrue);
                        init_animated_button(cursor);
                        selected = 10;
                    }
                } else {
                    if (button == 10)
                        button = 0;
                    update_button_sprite(td.defend_point_button, 0);
                }
                if (get_mouse_intersect(td, td.enemy_point_button)) {
                    if (button != 11)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 11;
                    update_button_sprite(td.enemy_point_button, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        sfSprite_setTexture(cursor, sfSprite_getTexture(td.enemy_point_button), sfTrue);
                        init_animated_button(cursor);
                        selected = 11;
                    }
                } else {
                    if (button == 11)
                        button = 0;
                    update_button_sprite(td.enemy_point_button, 0);
                }
                if (get_mouse_intersect(td, td.text_zone)) {
                    if (button != 12)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 12;
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        sfSprite_setTexture(cursor, empty, sfTrue);
                        init_animated_button(cursor);
                        selected = 12;
                    }
                } else {
                    if (sfMouse_isButtonPressed(sfMouseLeft) && selected == 12)
                        selected = 0;
                    if (button == 12)
                        button = 0;
                }
                if (selected == 12) {
                    if (sfKeyboard_isKeyPressed(sfKeyEnter && selected == 12))
                        selected = 0;
                    if (sfKeyboard_isKeyPressed(sfKeyBackspace) && (td.seconds > td.erase + 0.01)) {
                        td.erase = td.seconds;
                        my_strcpy(td.player_string, sfText_getString(td.player_text));
                        td.player_string[my_strlen(td.player_string) - 1] = '\0';
                        sfText_setString(td.player_text, td.player_string);
                    } else if (td.event.type == sfEvtTextEntered
                        && sfKeyboard_isKeyPressed(sfKeyBackspace) == sfFalse
                        && sfKeyboard_isKeyPressed(sfKeyEnter) == sfFalse
                        && text_box_size.x < 203) {
                        sfText_setUnicodeString(td.player_text, &td.event.text.unicode);
                        my_strcat(td.player_string, sfText_getString(td.player_text));
                        sfText_setString(td.player_text, td.player_string);
                    }
                }
                if (get_mouse_intersect(td, td.load_button)) {
                    if (button != 13)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 13;
                    update_button_sprite(td.load_button, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        sfSprite_setTexture(cursor, empty, sfTrue);
                        init_animated_button(cursor);
                        selected = 13;
                        td = load_map_loop(td);
                        error_delay = td.seconds;
                    }
                } else {
                    if (button == 13)
                        button = 0;
                    update_button_sprite(td.load_button, 0);
                }
                if (sfKeyboard_isKeyPressed(sfKeyT) && td.seconds > td.toggle_delay + 0.01 && selected != 12) {
                    td.toggle_delay = td.seconds;
                    for (int x = 0; x < 10; x++) {
                        for (int w = 0; w < 17; w++) {
                            if (grid_visible == 1 && td.grid[x][w].type != -1) {
                                sfRectangleShape_setOutlineColor(td.grid[x][w].unit, sfTransparent);
                            } else if (td.grid[x][w].type != -1)
                                sfRectangleShape_setOutlineColor(td.grid[x][w].unit, sfBlack);               
                        }
                    }
                    grid_visible *= -1;
                }
                if (sfMouse_isButtonPressed(sfMouseLeft) || sfMouse_isButtonPressed(sfMouseRight)) {
                    td = handle_path(td, selected);
                }
                if (td.event.type == sfEvtClosed) {
                    td = exit_game(td);
                    if (td.exit == 1)
                        return td;
                }
                if (sfKeyboard_isKeyPressed(sfKeyEscape) && td.seconds > td.load_delay + 0.01) {
                    td = handle_pause_menu(td);
                    if (td.exit_code == 1)
                        return td;
                }
            }
            if (td.load_success == 0 && td.seconds < error_delay + 2) {
                sfRenderWindow_drawText(td.window, error_text, NULL);
            }
            sfRenderWindow_drawSprite(td.window, cursor, NULL);
            sfRenderWindow_display(td.window);
        }
    }
}

tower_defense create_editor_grid(tower_defense td)
{
    sfVector2f case_pos = {280, 80};
    sfVector2f case_origin = {50, 50};

    td.grid = malloc(sizeof(grid_rect *) * 11);
    for (int i = 0; i <= 9; i++)
        td.grid[i] = malloc(sizeof(grid_rect) * 18);
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 17; j++) {
            td.grid[i][j].size.x = 100;
            td.grid[i][j].size.y = 100;
            td.grid[i][j].entry_point = 0;
            td.grid[i][j].rect_pos.x = case_pos.x;
            td.grid[i][j].rect_pos.y = case_pos.y;
            td.grid[i][j].unit = sfRectangleShape_create();
            sfRectangleShape_setOutlineThickness(td.grid[i][j].unit, 2);
            if (i == 0 || i == 9 || j == 0 || j == 17) {
                td.grid[i][j].type = -1;
                sfRectangleShape_setOutlineColor(td.grid[i][j].unit, sfTransparent);
            } else {
                td.grid[i][j].type = 0;
                sfRectangleShape_setOutlineColor(td.grid[i][j].unit, sfBlack);
            }
            td.grid[i][j].cc.u = 0;
            td.grid[i][j].cc.d = 0;
            td.grid[i][j].cc.r = 0;
            td.grid[i][j].cc.l = 0;
            sfRectangleShape_setSize(td.grid[i][j].unit, td.grid[i][j].size);
            sfRectangleShape_setFillColor(td.grid[i][j].unit, sfTransparent);
            sfRectangleShape_setOrigin(td.grid[i][j].unit, case_origin);
            sfRectangleShape_setPosition(td.grid[i][j].unit, td.grid[i][j].rect_pos);
            case_pos.x += 100;
        }
        case_pos.y += 100;
        case_pos.x = 280;
    }
    return td;
}

tower_defense create_game_grid(tower_defense td)
{
    sfVector2f case_pos = {-60, -60};
    sfVector2f case_origin = {60, 60};

    td.grid = malloc(sizeof(grid_rect *) * 11);
    for (int i = 0; i <= 9; i++)
        td.grid[i] = malloc(sizeof(grid_rect) * 18);
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 17; j++) {
            td.grid[i][j].size.x = 120;
            td.grid[i][j].size.y = 120;
            td.grid[i][j].anim_spd = 0;
            td.grid[i][j].entry_point = 0;
            td.grid[i][j].rect_pos.x = case_pos.x;
            td.grid[i][j].rect_pos.y = case_pos.y;
            td.grid[i][j].tw.type = 0;
            td.grid[i][j].unit = sfRectangleShape_create();
            if (i == 0 || i == 9 || j == 0 || j == 17) {
                td.grid[i][j].type = -1;
            } else {
                td.grid[i][j].type = 0;
            }
            td.grid[i][j].cc.u = 0;
            td.grid[i][j].cc.d = 0;
            td.grid[i][j].cc.r = 0;
            td.grid[i][j].cc.l = 0;
            sfRectangleShape_setSize(td.grid[i][j].unit, td.grid[i][j].size);
            sfRectangleShape_setFillColor(td.grid[i][j].unit, sfTransparent);
            sfRectangleShape_setOrigin(td.grid[i][j].unit, case_origin);
            sfRectangleShape_setPosition(td.grid[i][j].unit, td.grid[i][j].rect_pos);
            case_pos.x += 120;
        }
        case_pos.y += 120;
        case_pos.x = -60;
    }
    return td;
}

sfRectangleShape *update_animated_rect(sfRectangleShape *sprite, int frames)
{
    sfIntRect rect = sfRectangleShape_getTextureRect(sprite);

    rect.left += rect.width;
    sfRectangleShape_setTextureRect(sprite, rect);
}

void *reset_animated_sprite(sfSprite *sprite)
{
    sfIntRect rect = sfSprite_getTextureRect(sprite);

    rect.left = 0;
    sfSprite_setTextureRect(sprite, rect);
}

sfRectangleShape *reset_animated_rect(sfRectangleShape *sprite)
{
    sfIntRect rect = sfRectangleShape_getTextureRect(sprite);

    rect.left = 0;
    sfRectangleShape_setTextureRect(sprite, rect);
}

tower_defense draw_lvl_scene(tower_defense td)
{
    wave *temp = td.cur_wave[td.wave_index];
    sfVector2f mirror = {0, 0};

    sfRenderWindow_drawSprite(td.window, td.background, NULL);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 17; j++) {
            if (i > 0)
                td = update_con_texture(td, i - 1, j, td.grid[i - 1][j].type);
            td = update_con_texture(td, i + 1, j, td.grid[i + 1][j].type);
            td = update_con_texture(td, i, j + 1, td.grid[i][j + 1].type);
            if (j > 0)
                td = update_con_texture(td, i, j - 1, td.grid[i][j - 1].type);
            sfRenderWindow_drawRectangleShape(td.window, td.grid[i][j].unit, NULL);
            if (td.grid[i][j].entry_point >= 1)
                sfRenderWindow_drawSprite(td.window, td.grid[i][j].entry, NULL);
        }
    sfRenderWindow_drawSprite(td.window, td.background3, NULL);
    if (td.cur_wave != NULL) {
        while (temp != NULL) {
            temp->enemy.pos = sfSprite_getPosition(temp->enemy.sprite);
            temp->enemy.hb.hb_pos.y = (temp->enemy.pos.y - sfSprite_getGlobalBounds(temp->enemy.sprite).height) + 15;
            temp->enemy.hb.hb_pos.x = temp->enemy.pos.x;
            sfRectangleShape_setPosition(temp->enemy.hb.red_bar, temp->enemy.hb.hb_pos);
            sfRectangleShape_setPosition(temp->enemy.hb.green_bar, temp->enemy.hb.hb_pos);
            if (td.seconds > (temp->enemy.anim + 0.15 - (temp->enemy.anim_spd / 12))) {
                if (temp->enemy.spd_vect.x < 0 && temp->enemy.mirrored == sfFalse) {
                    mirror = sfSprite_getScale(temp->enemy.sprite);
                    mirror.x *= -1;
                    sfSprite_setScale(temp->enemy.sprite, mirror);
                    temp->enemy.mirrored = sfTrue;
                } else if (temp->enemy.spd_vect.x >= 0 && temp->enemy.mirrored == sfTrue) {
                    mirror = sfSprite_getScale(temp->enemy.sprite);
                    mirror.x *= -1;
                    sfSprite_setScale(temp->enemy.sprite, mirror);
                    temp->enemy.mirrored = sfFalse;
                }
                temp->enemy.anim = td.seconds;
                update_animated_sprite(temp->enemy.sprite);
            }
            sfSprite_setPosition(temp->enemy.effect_sprite, temp->enemy.pos);
            sfSprite_setPosition(temp->enemy.weakness_sprite, temp->enemy.pos);
            sfRenderWindow_drawSprite(td.window, temp->enemy.sprite, NULL);
            sfRenderWindow_drawSprite(td.window, temp->enemy.effect_sprite, NULL);
            sfRenderWindow_drawSprite(td.window, temp->enemy.weakness_sprite, NULL);
            sfRenderWindow_drawSprite(td.window, temp->enemy.projectile, NULL);
            temp = temp->next;
        }
        temp = td.cur_wave[td.wave_index];
        while (temp != NULL) {
            sfRenderWindow_drawRectangleShape(td.window, temp->enemy.hb.red_bar, NULL);
            sfRenderWindow_drawRectangleShape(td.window, temp->enemy.hb.green_bar, NULL);
            temp = temp->next;
        }
    }
    sfRenderWindow_drawSprite(td.window, td.background2, NULL);
    sfRenderWindow_drawSprite(td.window, td.background4, NULL);
    sfRenderWindow_drawSprite(td.window, td.hud_down, NULL);
    sfRenderWindow_drawText(td.window, td.p_hp_text, NULL);
    sfRenderWindow_drawText(td.window, td.gold_text, NULL);
    sfRenderWindow_drawText(td.window, td.wave_text, NULL);
    sfRenderWindow_drawText(td.window, td.wave_index_text, NULL);
    sfRenderWindow_drawSprite(td.window, td.heart, NULL);
    sfRenderWindow_drawSprite(td.window, td.gold, NULL);
    if (td.stats_visible == 1) {
        sfRenderWindow_drawSprite(td.window, td.selected_tower, NULL);
        sfRenderWindow_drawText(td.window, td.hud_tw_atckspd_txt, NULL);
        sfRenderWindow_drawText(td.window, td.hud_tw_dmg_txt, NULL);
        sfRenderWindow_drawText(td.window, td.hud_tw_range_txt, NULL);
        sfRenderWindow_drawSprite(td.window, td.hud_tw_dmg_sprt, NULL);
        sfRenderWindow_drawSprite(td.window, td.hud_tw_range_sprt, NULL);
        sfRenderWindow_drawSprite(td.window, td.hud_tw_atckspd_sprt, NULL);
    }
    if (td.build_menu_open == 1) {
        sfRenderWindow_drawSprite(td.window, td.build_menu, NULL);
        sfRenderWindow_drawSprite(td.window, td.build_menu_1, NULL);
        sfRenderWindow_drawSprite(td.window, td.build_menu_2, NULL);
        sfRenderWindow_drawSprite(td.window, td.build_menu_3, NULL);
        sfRenderWindow_drawSprite(td.window, td.build_menu_4, NULL);
        sfRenderWindow_drawText(td.window, td.build_txt_1, NULL);
        sfRenderWindow_drawText(td.window, td.build_txt_2, NULL);
        sfRenderWindow_drawText(td.window, td.build_txt_3, NULL);
        sfRenderWindow_drawText(td.window, td.build_txt_4, NULL);
    }
    if (td.build_menu_open == 2) {
        sfRenderWindow_drawSprite(td.window, td.upgrade_menu, NULL);
        sfRenderWindow_drawSprite(td.window, td.upgrade_menu_1, NULL);
        sfRenderWindow_drawSprite(td.window, td.upgrade_menu_2, NULL);
        sfRenderWindow_drawText(td.window, td.upgrade_txt_1, NULL);
        sfRenderWindow_drawText(td.window, td.upgrade_txt_2, NULL);
    }
    return td;
}

tower_defense gold_tempgain(tower_defense td)
{
    if (td.gold_cooldown == 300) {
        td.gold_a += 1;
        td.gold_cooldown = 0;
    } else
        td.gold_cooldown++;
    return (td);
}

tower_defense init_hud_txt(tower_defense td)
{
    sfVector2f player_health_pos = {90, 975};
    sfVector2f gold_text_pos = {90, 1025};
    char *gold_string = malloc(sizeof(char) * 1000);

    gold_string[0] = '0';
    gold_string[1] = '\0';
    sfText_setFont(td.p_hp_text, td.font);
    sfText_setCharacterSize(td.p_hp_text, 35);
    sfText_setFillColor(td.p_hp_text, sfWhite);
    sfText_setOutlineColor(td.p_hp_text, sfBlack);
    sfText_setOutlineThickness(td.p_hp_text, 3);
    sfText_setString(td.p_hp_text, "1000");
    sfText_setPosition(td.p_hp_text, player_health_pos);
    td.gold_text = sfText_create();
    sfText_setFont(td.gold_text, td.font);
    sfText_setCharacterSize(td.gold_text, 35);
    sfText_setOutlineColor(td.gold_text, sfBlack);
    sfText_setString(td.gold_text, gold_string);
    sfText_setOutlineThickness(td.gold_text, 3);
    sfText_setFillColor(td.gold_text, sfYellow);
    sfText_setPosition(td.gold_text, gold_text_pos);
    return td;
}

tower_defense init_new_wave(tower_defense td, int level_offset, int difficulty)
{
    int index = 0;
    enemy_s_p *sp = get_entry_points(td, &index);

    td.cur_wave[td.wave_index] = create_new_wave(td, td.cur_wave[td.wave_index], (level_offset * 2), difficulty, sp, index);
    td.head = td.cur_wave[td.wave_index];
    td.enemies_left = (level_offset * 2) * index;
    return td;
}

void trigger_sprint(tower_defense td, entity *enemy)
{
    sfIntRect rect = sfSprite_getTextureRect(enemy->sprite);

    rect.left = 0;
    sfTexture_setRepeated(td.type2_run, sfTrue);
    enemy->status = 3;
    enemy->spd_vect.x *= 2;
    enemy->spd_vect.y *= 2;
    enemy->speed = 2;
    enemy->speed_mem = 2;
    enemy->anim_spd = 0.8;
    sfSprite_setTexture(enemy->sprite, td.type2_run, sfFalse);
    sfSprite_setTextureRect(enemy->sprite, rect);
}

void play_death(tower_defense td, entity *enemy)
{
    sfTexture *death_texture;
    sfIntRect rect = sfSprite_getTextureRect(enemy->sprite);

    switch (enemy->type) {
        case (1):
            sfSound_play(td.type1_death_sound);
            death_texture = sfTexture_copy(td.type1_death);
            break;
        case (2):
            death_texture = sfTexture_copy(td.type2_death);
            sfSound_play(td.type2_death_sound);
            break;
    }
    rect.left = 0;
    enemy->status = 1;
    enemy->death_delay = td.seconds;
    enemy->spd_vect.x = 0;
    enemy->spd_vect.y = 0;
    enemy->speed = 1;
    enemy->speed_mem = 1;
    sfTexture_setRepeated(death_texture, sfTrue);
    sfSprite_setTexture(enemy->sprite, death_texture, sfFalse);
    sfSprite_setTextureRect(enemy->sprite, rect);
}

tower_defense enemy_death(tower_defense td)
{
    wave *temp = td.cur_wave[td.wave_index];
    wave *lastNode = NULL;
    int delete = 0;
    int index = 0;

    while (temp != NULL) {
        temp->prev = lastNode;
        lastNode = temp;
        if (temp->next == NULL)
            break;
        temp = temp->next;
        index++;
    }
    while (temp->prev != NULL) {
        temp = temp->prev;
    }
    lastNode = NULL;
    while (temp != NULL) {
        if (temp->enemy.health <= 0 && temp->enemy.status != 1) {
            play_death(td, &temp->enemy);
            td.gold_a += temp->enemy.reward;
            td.enemies_left -= 1;
        } else if (temp->enemy.status == 1) {
            if (td.seconds > temp->enemy.death_delay + 0.5) {
                delete = 1;
            }
        }
        if ((temp->enemy.type == 2 && temp->enemy.status != 3 && temp->enemy.status != 1) && temp->enemy.health <= temp->enemy.health_mem / 2)
            trigger_sprint(td, &temp->enemy);
        if (delete == 1) {
            delete_node(temp);
            if (td.enemies_left == 0) {
                td.cur_wave[td.wave_index] = NULL;
                return td;
            }
            delete = 0;
        }
        if (temp->next == NULL) {
            break;
        }
        lastNode = temp;
        temp = temp->next;
    }
    while (temp->prev != NULL) {
        temp = temp->prev;
    }
    td.cur_wave[td.wave_index] = temp;
    return td;
}

sfBool check_if_enemy_in_range(tower_defense td, int i, int j, wave *temp)
{
    sfFloatRect rect1;
    sfFloatRect rect2;
    int range = td.grid[i][j].tw.range;

    rect1 = sfSprite_getGlobalBounds(temp->enemy.sprite);
    for (int x = 1; x < range; x++) {
        if (i - x > 0) {
            rect2 = sfRectangleShape_getGlobalBounds(td.grid[i - x][j].unit);
            if (sfFloatRect_intersects(&rect1, &rect2, NULL) == sfTrue)
                return sfTrue;
        }
    }
    for (int x = 1; x < range; x++) {
        if (i + x < 9) {
            rect2 = sfRectangleShape_getGlobalBounds(td.grid[i + x][j].unit);
            if (sfFloatRect_intersects(&rect1, &rect2, NULL) == sfTrue)
                return sfTrue;
        }
    }
    for (int x = 1; x < range; x++) {
        if (j - x > 0) {
            rect2 = sfRectangleShape_getGlobalBounds(td.grid[i][j - x].unit);
            if (sfFloatRect_intersects(&rect1, &rect2, NULL) == sfTrue)
                return sfTrue;
        }
    }
    for (int x = 1; x < range; x++) {
        if (j + x < 17) {
            rect2 = sfRectangleShape_getGlobalBounds(td.grid[i][j + x].unit);
            if (sfFloatRect_intersects(&rect1, &rect2, NULL) == sfTrue)
                return sfTrue;
        }
    }
    for (int x = 1; x < range; x++) {
        if (j + x < 17 && i + x < 10) {
            rect2 = sfRectangleShape_getGlobalBounds(td.grid[i + x][j + x].unit);
            if (sfFloatRect_intersects(&rect1, &rect2, NULL) == sfTrue)
                return sfTrue;
        }
    }
    for (int x = 1; x < range; x++) {
        if (i - x > 0 && j - x > 0) {
            rect2 = sfRectangleShape_getGlobalBounds(td.grid[i - x][j - x].unit);
            if (sfFloatRect_intersects(&rect1, &rect2, NULL) == sfTrue)
                return sfTrue;
        }
    }
    for (int x = 1; x < range; x++) {
        if (i - x > 0 && j + x < 17) {
            rect2 = sfRectangleShape_getGlobalBounds(td.grid[i - x][j + x].unit);
            if (sfFloatRect_intersects(&rect1, &rect2, NULL) == sfTrue)
                return sfTrue;
        }
    }
    for (int x = 1; x < range; x++) {
        if (i + x < 9 && j - x > 0) {
            rect2 = sfRectangleShape_getGlobalBounds(td.grid[i + x][j - x].unit);
            if (sfFloatRect_intersects(&rect1, &rect2, NULL) == sfTrue)
                return sfTrue;
        }
    }
    return sfFalse;
}

void apply_zone_dmg(wave *temp, sfFloatRect location, tower tw)
{
    sfFloatRect r2;
    sfVector2f hb_scale = {1, 1};
    int found = 0;

    r2 = sfSprite_getGlobalBounds(temp->enemy.sprite);
    if (sfFloatRect_intersects(&location, &r2, NULL)) {
        hb_scale.x = ((float)temp->enemy.health / (float)temp->enemy.health_mem);
        temp->enemy.health -= tw.dmg;
        if (hb_scale.x < 0)
            hb_scale.x = 0;
        sfRectangleShape_setScale(temp->enemy.hb.green_bar, hb_scale);
    }
}

tower_defense handle_tower_dmg(tower_defense td)
{
    wave *temp = td.cur_wave[td.wave_index];
    sfVector2f hb_scale = {1, 1};
    int found = 0;
    sfFloatRect dmg_zone;
    int zone = 0;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 17; j++) {
            zone = 0;
            while (temp != NULL) {
                if (td.grid[i][j].tw.type == 1) {
                    if (check_if_enemy_in_range(td, i, j, temp) == sfTrue) {
                        found = 1;
                        if (temp->enemy.health > 0 && (td.seconds > (td.grid[i][j].anim_spd + 1.1 - td.grid[i][j].tw.atck_spd))) {
                            td.grid[i][j].anim_spd = td.seconds;
                            update_animated_rect(td.grid[i][j].unit, 6);
                            temp->enemy.health -= td.grid[i][j].tw.dmg;
                            hb_scale.x = ((float)temp->enemy.health / (float)temp->enemy.health_mem);
                            if (hb_scale.x < 0)
                                hb_scale.x = 0;
                            sfRectangleShape_setScale(temp->enemy.hb.green_bar, hb_scale);
                        }
                        if (td.seconds > (td.grid[i][j].tw.sound_delay + 1.65 - td.grid[i][j].tw.atck_spd)) {
                            sfSound_play(td.stab_sound);
                            td.grid[i][j].tw.sound_delay = td.seconds;
                        }
                    }
                }
                if (td.grid[i][j].tw.type == 3) {
                    if (check_if_enemy_in_range(td, i, j, temp) == sfTrue) {
                        found = 1;
                        if (temp->enemy.health > 0 && (td.seconds > td.grid[i][j].tw.anim_spd + 0.05)) {
                            td.grid[i][j].tw.anim_spd = td.seconds;
                            update_animated_rect(td.grid[i][j].unit, 6);
                        }
                        if (temp->enemy.health > 0 && (td.seconds > (td.grid[i][j].anim_spd + 1.1 - td.grid[i][j].tw.atck_spd))) {
                            if (temp->enemy.exploding == 0) {
                                sfSprite_destroy(temp->enemy.projectile);
                                temp->enemy.projectile = sfSprite_create();
                                sfSprite_setTexture(temp->enemy.projectile, td.explosion_effect, sfFalse);
                                init_animated_sprite(temp->enemy.projectile, 8);
                                sfSprite_setOrigin(temp->enemy.projectile, get_sprite_center(temp->enemy.projectile));
                                temp->enemy.explodion_frame = 0;
                                temp->enemy.exploding = 1;
                                sfSound_play(td.explosion_sound);
                            }
                            zone = 1;
                            sfSprite_setPosition(temp->enemy.projectile, temp->enemy.pos);
                            td.grid[i][j].anim_spd = td.seconds;
                            dmg_zone = sfSprite_getGlobalBounds(temp->enemy.sprite);
                            hb_scale.x = ((float)temp->enemy.health / (float)temp->enemy.health_mem);
                            if (hb_scale.x < 0)
                                hb_scale.x = 0;
                            sfRectangleShape_setScale(temp->enemy.hb.green_bar, hb_scale);
                        }
                    }
                }
                if (td.seconds > temp->enemy.expl_cooldown + 0.1) {
                    temp->enemy.expl_cooldown = td.seconds;
                    update_animated_sprite(temp->enemy.projectile);
                    temp->enemy.explodion_frame++;
                    if (temp->enemy.explodion_frame >= 8) {
                        sfSprite_setTexture(temp->enemy.projectile, td.empty_texture, sfFalse);
                        temp->enemy.exploding = 0;
                    }
                }
                temp = temp->next;
            }
            temp = td.cur_wave[td.wave_index];
            if (found != 1)
                reset_animated_rect(td.grid[i][j].unit);
            if (zone == 1) {
                while (temp != NULL) {
                    apply_zone_dmg(temp, dmg_zone, td.grid[i][j].tw);
                    hb_scale.x = ((float)temp->enemy.health / (float)temp->enemy.health_mem);
                    if (hb_scale.x < 0)
                        hb_scale.x = 0;
                    sfRectangleShape_setScale(temp->enemy.hb.green_bar, hb_scale);
                    temp = temp->next;
                }
            temp = td.cur_wave[td.wave_index];
            }
        }
    }
}

tower_defense handle_tower_effect(tower_defense td)
{
    wave *temp = td.cur_wave[td.wave_index];
    wave * lastNode = NULL;
    sfVector2f hb_scale = {1, 1};
    int frozen = 0;

    while (temp != NULL) {
        temp->prev = lastNode;
        lastNode = temp;
        if (temp->next == NULL)
            break;
        temp = temp->next;
    }
    while (temp->prev != NULL) {
        temp = temp->prev;
    }
    lastNode = NULL;
    while (temp != NULL) {
        frozen = 0;
        temp->enemy.pos = sfSprite_getPosition(temp->enemy.sprite);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 17; j++) {
                if (td.grid[i][j].tw.type == 2) {
                    if (check_if_enemy_in_range(td, i, j ,temp) == sfTrue) {
                        frozen = 1;
                        if (temp->enemy.health > 0) {
                            update_animated_rect(td.grid[i][j].unit, 6);
                            temp->enemy.health -= td.grid[i][j].tw.dmg;
                            hb_scale.x = ((float)temp->enemy.health / (float)temp->enemy.health_mem);
                            if (hb_scale.x < 0)
                                hb_scale.x = 0;
                            sfRectangleShape_setScale(temp->enemy.hb.green_bar, hb_scale);
                        }
                        if (td.grid[i][j].tw.effect == 1 && temp->enemy.effect != 1) {
                            temp->enemy.speed -= 0.4 + (0.2 * td.grid[i][j].tw.level);
                            if (temp->enemy.speed <= 0.2)
                                temp->enemy.speed = 0.25;
                            temp->enemy.effect = 1;
                            sfSprite_setTexture(temp->enemy.effect_sprite, td.frost_effect, sfTrue);
                            sfSprite_setOrigin(temp->enemy.effect_sprite, get_sprite_center(temp->enemy.effect_sprite));
                        }
                    }
                }
                if (td.grid[i][j].tw.type == 4) {
                    if (check_if_enemy_in_range(td, i, j ,temp) == sfTrue) {
                        if (temp->enemy.health > 0 && temp->enemy.weakness == 0) {
                            temp->enemy.health_mem *= 0.8 - (0.1 * td.grid[i][j].tw.level);
                            temp->enemy.health_diff = temp->enemy.health * 0.2  + (0.1 * td.grid[i][j].tw.level);
                            temp->enemy.health *= 0.8 - (0.1 * td.grid[i][j].tw.level);
                            update_animated_rect(td.grid[i][j].unit, 6);
                            hb_scale.x = ((float)temp->enemy.health / (float)temp->enemy.health_mem);
                            if (hb_scale.x < 0)
                                hb_scale.x = 0;
                            sfRectangleShape_setScale(temp->enemy.hb.green_bar, hb_scale);
                            sfSprite_setTexture(temp->enemy.weakness_sprite, td.weakness_effect, sfTrue);
                            sfSprite_setOrigin(temp->enemy.weakness_sprite, get_sprite_center(temp->enemy.weakness_sprite));
                            temp->enemy.weakness = 1;
                        }
                    } else {
                        temp->enemy.weakness = 0;
                        temp->enemy.health += temp->enemy.health_diff;
                        temp->enemy.health_diff = 0;
                        temp->enemy.health_mem = temp->enemy.health_mem2;
                        hb_scale.x = ((float)temp->enemy.health / (float)temp->enemy.health_mem);
                        if (hb_scale.x < 0)
                            hb_scale.x = 0;
                        sfRectangleShape_setScale(temp->enemy.hb.green_bar, hb_scale);
                        sfSprite_setTexture(temp->enemy.weakness_sprite, td.empty_texture, sfFalse);
                    }
                }
            }
            if (frozen != 1) {
                temp->enemy.speed = temp->enemy.speed_mem;
                temp->enemy.effect = 0;
                sfSprite_setTexture(temp->enemy.effect_sprite, td.empty_texture, sfFalse);
            }
        }
        if (temp->next == NULL)
            break;
        lastNode = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        td.cur_wave[td.wave_index] = NULL;
        return td;
    }
    while (temp->prev != NULL)
        temp = temp->prev;
    td.cur_wave[td.wave_index] = temp;
    return td;
}

sfSprite *advance_to_frame(sfSprite *sprite, int frame)
{
    for (int i = 0; i < frame; i++)
        sprite = update_animated_sprite(sprite);
    return sprite;
}

sfVector2f get_txt_center(sfText *text)
{
    sfFloatRect rect = sfText_getGlobalBounds(text);
    sfVector2f center;

    center.x = rect.width / 2;
    center.y = rect.height / 2;
    return center;
}

tower_defense end_of_level(tower_defense td)
{
    sfTexture *screen_capture = sfTexture_create(td.window_size.x, td.window_size.y);
    sfSprite *screen_capture_sprite = sfSprite_create();
    sfVector2f capture_scale;
    sfSprite *contretry;
    sfVector2f textpos = {960, 550};
    sfVector2f textpos2 = {960, 630};
    int button = 0;
    int end_state;

    reset_animated_sprite(td.stars);
    if (td.player_health <= 0) {
        end_state = 0;
    } else if (td.player_health <= 450) {
        td.stars = advance_to_frame(td.stars, 1);
        end_state = 1;
    } else if (td.player_health <= 700) {
        td.stars = advance_to_frame(td.stars, 2);
        end_state = 2;
    } else if (td.player_health <= 1000) {
        td.stars = advance_to_frame(td.stars, 3);
        end_state = 3;
    }
    sfTexture_updateFromRenderWindow(screen_capture, td.window, 0, 0);
    sfSprite_setTexture(screen_capture_sprite, screen_capture, sfTrue);
    capture_scale.x = td.g_scale;
    capture_scale.y = td.g_scale;
    sfSprite_setScale(screen_capture_sprite, capture_scale);
    sfMusic_stop(td.menu_music);
    sfText_setCharacterSize(td.endwin_text1, 50);
    if (end_state == 0) {
        sfSound_play(td.lose_sound);
        contretry = sfSprite_copy(td.retry_button);
        sfText_setString(td.endwin_text1, "U suck bruh");
        sfText_setString(td.endwin_text2, "Level failed!");
        sfText_setOrigin(td.endwin_text1, get_text_center(td.endwin_text1));
        sfText_setOrigin(td.endwin_text2, get_text_center(td.endwin_text2));
        sfText_setPosition(td.endwin_text1, textpos);
        sfText_setPosition(td.endwin_text2, textpos2);
        sfSprite_setTexture(td.winlose_header, td.header_lose, sfFalse);
    } else {
        sfSound_play(td.win_sound);
        contretry = sfSprite_copy(td.continue_button);
        sfText_setString(td.endwin_text1, "Congratulations!");
        sfText_setString(td.endwin_text2, "Level complete");
        sfText_setOrigin(td.endwin_text1, get_text_center(td.endwin_text1));
        sfText_setOrigin(td.endwin_text2, get_text_center(td.endwin_text2));
        sfText_setPosition(td.endwin_text1, textpos);
        sfText_setPosition(td.endwin_text2, textpos2);
        sfSprite_setTexture(td.winlose_header, td.header_win, sfFalse);
    }
    while (sfRenderWindow_isOpen(td.window)) {
        td.mouse_pos = sfMouse_getPositionRenderWindow(td.window);
        td.mouse_pos.x *= td.g_scale;
        td.mouse_pos.y *= td.g_scale;
        td.time = sfClock_getElapsedTime(td.clock);
        td.seconds = td.time.microseconds/1000000.0;
        srand(td.seconds);
        if ((td.main_clock + 0.016) < td.seconds) {
            sfRenderWindow_drawSprite(td.window, screen_capture_sprite, NULL);
            sfRenderWindow_drawSprite(td.window, td.dark, NULL);
            sfRenderWindow_drawSprite(td.window, td.winlose_tab, NULL);
            sfRenderWindow_drawSprite(td.window, td.winlose_header, NULL);
            sfRenderWindow_drawSprite(td.window, td.stars, NULL);
            sfRenderWindow_drawSprite(td.window, contretry, NULL);
            sfRenderWindow_drawSprite(td.window, td.back_mainmenu_endbutton, NULL);
            sfRenderWindow_drawText(td.window, td.endwin_text1, NULL);
            sfRenderWindow_drawText(td.window, td.endwin_text2, NULL);
            td.main_clock = td.seconds;
            while (sfRenderWindow_pollEvent(td.window, &td.event)) {
                if (get_mouse_intersect(td, td.back_mainmenu_endbutton)) {
                    if (button != 1)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 1;
                    update_button_sprite(td.back_mainmenu_endbutton, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        td.exit_code = 1;
                        return td;
                    }
                } else {
                    if (button == 1)
                        button = 0;
                    update_button_sprite(td.back_mainmenu_endbutton, 0);
                }
                if (get_mouse_intersect(td, contretry) && td.custom_level == 0 && td.chapter < 4) {
                    if (button != 2)
                        button = 0;
                    if (button == 0)
                        sfSound_play(td.click_sound);
                    button = 2;
                    update_button_sprite(contretry, 1);
                    if (sfMouse_isButtonPressed(sfMouseLeft))
                        if (end_state == 0) {
                            td.exit_code = 2;
                            return td;
                        } else if (end_state > 0) {
                            td.exit_code = 2;
                            td.chapter++;
                            return td;
                        }
                } else {
                    if (button == 2)
                        button = 0;
                    update_button_sprite(contretry, 0);
                }
                if (td.event.type == sfEvtClosed) {
                    td = exit_game(td);
                    if (td.exit == 1)
                        return td;
                }
            }
            sfRenderWindow_display(td.window);
        }
    } 
}

tower_defense execute_game_loop(tower_defense td, int chapter)
{
    sfVector2f test = {150, 150};
    char *gold_string = malloc(sizeof(char) * 100);
    char *hp_string = malloc(sizeof(char) * 100);
    float effect_delay = 0;
    int defeat = 0;
    int started = 0;
    int wait = 0;

    gold_string[0] = '0';
    gold_string[1] = '\0';
    hp_string = my_strcpy(hp_string, "1000");
    td.p_hp_text = sfText_create();
    td.wave_index = 0;
    td.build_menu_open = 0;
    td.stats_visible = 0;
    td.build_menu_delay = 0;
    td.b_m_button = 0;
    td.end_lvl_delay = 0;
    td.initial_delay = td.seconds;
    td.exit_code = 0;
    sfSprite_setOrigin(td.build_menu, get_sprite_center(td.build_menu));
    td = init_hud_txt(td);
    td.player_health = 1000;

    if (td.custom_level == 0) {
        switch (chapter) {
            case (1):
                td.wave_nb = 5;
                td.buildable = sfTexture_createFromFile("sprites/map/buildable.png", NULL);
                td = load_level(td, "level1");
                sfSprite_setTexture(td.background, sfTexture_createFromFile("sprites/map/map_notree_nopit.png", NULL), sfFalse);
                sfSprite_setTexture(td.background2, sfTexture_createFromFile("sprites/map/map_onlytree.png", NULL), sfFalse);
                sfSprite_setTexture(td.background3, sfTexture_createFromFile("sprites/map/bridge.png", NULL), sfFalse);
                sfSprite_setTexture(td.background4, sfTexture_createFromFile("sprites/empty.png", NULL), sfFalse);
                td.straight_path = sfTexture_createFromFile("sprites/map/straight_path.png", NULL);
                td.L_path = sfTexture_createFromFile("sprites/map/L_path.png", NULL);
                td.X_path = sfTexture_createFromFile("sprites/map/X_path.png", NULL);
                td.T_path = sfTexture_createFromFile("sprites/map/T_path.png", NULL);
                td.gold_a = 55;
                break;
            case (2):
                td.wave_nb = 7;
                td.buildable = sfTexture_createFromFile("sprites/map/desert_buildable.png", NULL);
                td = load_level(td, "level2");
                sfSprite_setTexture(td.background, sfTexture_createFromFile("sprites/map/desert_bg.png", NULL), sfFalse);
                sfSprite_setTexture(td.background2, sfTexture_createFromFile("sprites/map/desert_woods.png", NULL), sfFalse);
                sfSprite_setTexture(td.background3, sfTexture_createFromFile("sprites/map/desert_castle.png", NULL), sfFalse);
                sfSprite_setTexture(td.background4, sfTexture_createFromFile("sprites/empty.png", NULL), sfFalse);
                td.straight_path = sfTexture_createFromFile("sprites/map/sand_straightpath.png", NULL);
                td.L_path = sfTexture_createFromFile("sprites/map/sand_Lpath.png", NULL);
                td.X_path = sfTexture_createFromFile("sprites/map/sand_Xpath.png", NULL);
                td.T_path = sfTexture_createFromFile("sprites/map/sand_Tpath.png", NULL);
                td.gold_a = 70;
                break;
            case (3):
                td.wave_nb = 9;
                td.buildable = sfTexture_createFromFile("sprites/map/snow_buildable.png", NULL);
                td = load_level(td, "level3");
                sfSprite_setTexture(td.background, sfTexture_createFromFile("sprites/map/snow_bg.png", NULL), sfFalse);
                sfSprite_setTexture(td.background3, sfTexture_createFromFile("sprites/map/snow_decors.png", NULL), sfFalse);
                sfSprite_setTexture(td.background2, sfTexture_createFromFile("sprites/map/snow_fronttree.png", NULL), sfFalse);
                sfSprite_setTexture(td.background4, sfTexture_createFromFile("sprites/empty.png", NULL), sfFalse);
                td.straight_path = sfTexture_createFromFile("sprites/map/snow_straightpath.png", NULL);
                td.L_path = sfTexture_createFromFile("sprites/map/snow_Lpath.png", NULL);
                td.X_path = sfTexture_createFromFile("sprites/map/snow_Xpath.png", NULL);
                td.T_path = sfTexture_createFromFile("sprites/map/snow_Tpath.png", NULL);
                td.gold_a = 120;
                break;
            case (4):
                td.wave_nb = 12;
                td.buildable = sfTexture_createFromFile("sprites/map/lava_buildable.png", NULL);
                td = load_level(td, "level4");
                sfSprite_setTexture(td.background, sfTexture_createFromFile("sprites/map/lava_bg.png", NULL), sfFalse);
                sfSprite_setTexture(td.background2, sfTexture_createFromFile("sprites/map/lava_statue.png", NULL), sfFalse);
                sfSprite_setTexture(td.background3, sfTexture_createFromFile("sprites/empty.png", NULL), sfFalse);
                sfSprite_setTexture(td.background4, sfTexture_createFromFile("sprites/empty.png", NULL), sfFalse);
                td.straight_path = sfTexture_createFromFile("sprites/map/lava_straightpath.png", NULL);
                td.L_path = sfTexture_createFromFile("sprites/map/lava_Lpath.png", NULL);
                td.X_path = sfTexture_createFromFile("sprites/map/lava_Xpath.png", NULL);
                td.T_path = sfTexture_createFromFile("sprites/map/lava_Tpath.png", NULL);
                td.gold_a = 200;
                break;
        }
    } else {
        td.wave_nb = 8;
        td.buildable = sfTexture_createFromFile("sprites/map/buildable.png", NULL);
        td = load_level(td, td.player_string2);
        sfSprite_setTexture(td.background, sfTexture_createFromFile("sprites/map/background.jpg", NULL), sfFalse);
        sfSprite_setTexture(td.background2, sfTexture_createFromFile("sprites/empty.png", NULL), sfFalse);
        sfSprite_setTexture(td.background3, sfTexture_createFromFile("sprites/empty.png", NULL), sfFalse);
        sfSprite_setTexture(td.background4, sfTexture_createFromFile("sprites/empty.png", NULL), sfFalse);
        td.straight_path = sfTexture_createFromFile("sprites/map/straight_path.png", NULL);
        td.L_path = sfTexture_createFromFile("sprites/map/L_path.png", NULL);
        td.X_path = sfTexture_createFromFile("sprites/map/X_path.png", NULL);
        td.T_path = sfTexture_createFromFile("sprites/map/T_path.png", NULL);
        td.gold_a = 45 * count_entry_points(td);
    }
    td.cur_wave = malloc(sizeof(wave *) * td.wave_nb);
    td = init_new_wave(td, td.wave_index, 1);
    td.wave_cooldown = td.seconds;
    td.erase = 0;
    td.load_success = -1;
    td.load_delay = 0;
    while (sfRenderWindow_isOpen(td.window)) {
        td.mouse_pos = sfMouse_getPositionRenderWindow(td.window);
        td.mouse_pos.x *= td.g_scale;
        td.mouse_pos.y *= td.g_scale;
        td.time = sfClock_getElapsedTime(td.clock);
        td.seconds = td.time.microseconds/1000000.0;
        srand(td.seconds);
        if ((td.main_clock + 0.016) < td.seconds) {
            td.main_clock = td.seconds;
            if (td.seconds > td.initial_delay + 5)
                started = 1;
            td = gold_tempgain(td);
            sfText_setString(td.wave_index_text, int_to_string(td.wave_index_str, td.wave_index));
            sfText_setString(td.wave_index_text, my_strcat((char *)sfText_getString(td.wave_index_text), "/"));
            sfText_setString(td.wave_index_text, my_strcat((char *)sfText_getString(td.wave_index_text), int_to_string(td.wave_index_str, td.wave_nb)));
            if (td.cur_wave[td.wave_index] != NULL) {
                while (td.cur_wave[td.wave_index] != NULL) {
                    sfSprite_move(td.cur_wave[td.wave_index]->enemy.sprite, td.cur_wave[td.wave_index]->enemy.spd_vect);
                    td.cur_wave[td.wave_index] = td.cur_wave[td.wave_index]->next;
                }
                td.cur_wave[td.wave_index] = td.head;
            }
            sfText_setString(td.p_hp_text, int_to_string(hp_string, td.player_health));
            sfText_setString(td.gold_text, int_to_string(gold_string, td.gold_a));
            sfRenderWindow_clear(td.window, sfBlack);
            if (td.cur_wave[td.wave_index] != NULL)
                td = follow_path(td);
            if (td.cur_wave[td.wave_index] != NULL)
                td = enemy_death(td);
            if (td.cur_wave[td.wave_index] != NULL) {
                td = handle_tower_dmg(td);
                if (td.seconds > effect_delay + 0.1) {
                    effect_delay = td.seconds;
                    td = handle_tower_effect(td);
                }
            }
            td = draw_lvl_scene(td);
            if (td.build_menu_open == 0 && td.seconds > td.build_menu_delay + 0.005) {
                td.build_menu_delay = td.seconds;
                td.b_m_button = 0;
            }
            while (sfRenderWindow_pollEvent(td.window, &td.event)) {
                td = handle_game_input(td);
                if (td.event.type == sfEvtClosed) {
                    td = exit_game(td);
                    if (td.exit == 1)
                        return td;
                }
                if (sfKeyboard_isKeyPressed(sfKeyEscape) && td.seconds > td.load_delay + 0.01) {
                    td = handle_pause_menu(td);
                if (td.exit_code == 1)
                    return td;
                }
            }
            if (td.cur_wave[td.wave_index] == NULL && wait == 0) {
                td.wave_cooldown = td.seconds;
                wait = 1;
            }
            if ((td.cur_wave[td.wave_index] == NULL && td.wave_index < td.wave_nb) && started == 1 && td.seconds > td.wave_cooldown + 5) {
                td.wave_index++;
                td = init_new_wave(td, (td.wave_index), 1);
                td.head = td.cur_wave[td.wave_index];
                td.end_lvl_delay = td.seconds;
                wait = 0;
            }
            if (td.player_health <= 0 && defeat == 0) {
                td.end_lvl_delay = td.seconds;
                defeat = 1;
            }
            if ((td.cur_wave[td.wave_index] == NULL && td.wave_index == td.wave_nb || td.player_health <= 0)  && started == 1) {
                if (td.seconds > td.end_lvl_delay + 1)
                    td = end_of_level(td);
                    if (td.exit_code == 2) {
                        sfSound_stop(td.lose_sound);
                        sfMusic_play(td.menu_music);
                        td = execute_game_loop(td, td.chapter);
                    }
            }
            if (td.exit_code == 1)
                return td;
            sfRenderWindow_display(td.window);
        }
    }
}

tower_defense level_selection(tower_defense td)
{
    sfTexture *screen_capture = sfTexture_create(td.window_size.x, td.window_size.y);
    sfSprite *screen_capture_sprite = sfSprite_create();
    sfVector2f capture_scale;
    int button = 0;
    float error_delay = -2;
    sfVector2f error_text_pos = {750, 900};

    sfRenderWindow_drawSprite(td.window, td.main_menu, NULL);
    sfRenderWindow_display(td.window);
    sfTexture_updateFromRenderWindow(screen_capture, td.window, 0, 0);
    sfSprite_setTexture(screen_capture_sprite, screen_capture, sfTrue);
    update_button_sprite(td.campaign_button, 0);
    capture_scale.x = td.g_scale;
    capture_scale.y = td.g_scale;
    sfSprite_setScale(screen_capture_sprite, capture_scale);
    while (td.seconds <  td.level_selection_delay + 0.2) {
        td.time = sfClock_getElapsedTime(td.clock);
        td.seconds = td.time.microseconds/1000000.0;
        sfRenderWindow_drawSprite(td.window, screen_capture_sprite, NULL);
        sfRenderWindow_drawSprite(td.window, td.button_lvl1, NULL);
        sfRenderWindow_drawSprite(td.window, td.button_lvl2, NULL);
        sfRenderWindow_drawSprite(td.window, td.button_lvl3, NULL);
        sfRenderWindow_drawSprite(td.window, td.button_lvl4, NULL);
        sfRenderWindow_drawSprite(td.window, td.back_start_button, NULL);
        sfRenderWindow_display(td.window);
    }
    while (sfRenderWindow_isOpen(td.window)) {
        td.time = sfClock_getElapsedTime(td.clock);
        td.seconds = td.time.microseconds/1000000.0;
        td.mouse_pos = sfMouse_getPositionRenderWindow(td.window);
        td.mouse_pos.x *= td.g_scale;
        td.mouse_pos.y *= td.g_scale;
        sfRenderWindow_drawSprite(td.window, screen_capture_sprite, NULL);
        sfRenderWindow_drawSprite(td.window, td.button_lvl1, NULL);
        sfRenderWindow_drawSprite(td.window, td.button_lvl2, NULL);
        sfRenderWindow_drawSprite(td.window, td.button_lvl3, NULL);
        sfRenderWindow_drawSprite(td.window, td.button_lvl4, NULL);
        sfRenderWindow_drawSprite(td.window, td.back_start_button, NULL);
        while (sfRenderWindow_pollEvent(td.window, &td.event)) {
            if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
                td.chapter = 0;
                td.level_back_delay = td.seconds;
                return td;
            }
            if (get_mouse_intersect(td, td.button_lvl1)) {
                if (button != 1)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 1;
                update_button_sprite(td.button_lvl1, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.chapter = 1;
                    return td;
                }
            } else {
                if (button == 1)
                    button = 0;
                update_button_sprite(td.button_lvl1, 0);
            }
            if (get_mouse_intersect(td, td.button_lvl2)) {
                if (button != 2)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 2;
                update_button_sprite(td.button_lvl2, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.chapter = 2; 
                    return td;
                }
            } else {
                if (button == 2)
                    button = 0;
                update_button_sprite(td.button_lvl2, 0);
            }
            if (get_mouse_intersect(td, td.button_lvl3)) {
                if (button != 3)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 3;
                update_button_sprite(td.button_lvl3, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.chapter = 3;
                    return td;
                }
            } else {
                if (button == 3)
                    button = 0;
                update_button_sprite(td.button_lvl3, 0);
            }
            if (get_mouse_intersect(td, td.button_lvl4)) {
                if (button != 4)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 4;
                update_button_sprite(td.button_lvl4, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.chapter = 4;
                    return td;
                }
            } else {
                if (button == 4)
                    button = 0;
                update_button_sprite(td.button_lvl4, 0);
            }
            if (get_mouse_intersect(td, td.back_start_button)) {
                if (button != 5)
                    button = 0;
                if (button == 0)
                    sfSound_play(td.click_sound);
                button = 5;
                update_button_sprite(td.back_start_button, 1);
                if (sfMouse_isButtonPressed(sfMouseLeft)) {
                    td.delay_exit = td.seconds; 
                    return td;
                }
            } else {
                if (button == 5)
                    button = 0;
                update_button_sprite(td.back_start_button, 0);
            }
        }
        sfRenderWindow_display(td.window);
    }
    return td;
}

tower_defense restart_game(tower_defense td)
{
    td.connections = 0;
    td.choice = 0;
    td.vol_bar_offset = 0;
    td.exit_code = 0;
    td.main_clock = 0;
    td.move_clock = 0;
    td.custom_level = 0;
    td.vol_bar_scale.x = 0.6;
    td.vol_bar_scale.y = 0.5;
    td.seconds = 0;
    td.hud_tw_dmg_str = malloc(sizeof(char) * 100);
    td.hud_tw_range_str = malloc(sizeof(char) * 100);
    td.hud_tw_atckspd_str = malloc(sizeof(char) * 100);
    td.build_txt_str4 = malloc(sizeof(char) * 100);
    td.upgrade_txt_str1 = malloc(sizeof(char) * 100);
    td.upgrade_txt_str2 = malloc(sizeof(char) * 100);
    int x = 0;
    int w = 0;
    int i = 0;
    int j = 0;
    td.main_menu_button = 0;
    sfVector2f cursor_size = {3, 3};
    sfVector2f cursor_origin = {1.5, 1.5};

    if (td.chapter == 4)
        td.chapter = 1;

    update_button_sprite(td.back_mainmenu_endbutton, 0);
    update_button_sprite(td.start_button, 0);
    update_button_sprite(td.resume_button, 0);
    update_button_sprite(td.settings_button_p, 0);
    update_button_sprite(td.settings_button, 0);
    update_button_sprite(td.exit_button, 0);
    update_button_sprite(td.exit_button_p, 0);
    update_button_sprite(td.vol_bar, 0);
    update_button_sprite(td.apply_button, 0);
    update_button_sprite(td.back_button, 0);
    update_button_sprite(td.x640_button, 0);
    update_button_sprite(td.x960_button, 0);
    update_button_sprite(td.x1280_button, 0);
    update_button_sprite(td.x1920_button, 0);
    sfMusic_setLoop(td.menu_music, sfTrue);
    sfMusic_play(td.menu_music);

    td = handle_main_menu_loop(td);
    if (td.exit == 1)
        return td;

    if (td.main_menu_button == 1)
        td = create_editor_grid(td);
    else if (td.main_menu_button == 2)
        td = create_game_grid(td);
    
    if (td.main_menu_button == 2)
        td = execute_game_loop(td, td.chapter);
    if (td.exit == 1)
        return td;
    else if (td.main_menu_button == 1)
        td = execute_editor_loop(td);
    if (td.exit_code == 1) {
        sfMusic_stop(td.menu_music);
        restart_game(td);
    }
    if (td.exit == 1)
        return td;
}

tower_defense intro_loop(tower_defense td)
{
    sfIntRect intro_rect = {0, 0, 1920, 1080};
    sfVector2f intro_pos = {0, 0};
    int cooldown = 0;
    float clock_intro = 0;

    sfSprite_setPosition(td.intro, intro_pos);
    sfSprite_setTextureRect(td.intro, intro_rect);
    sfRenderWindow_drawSprite(td.window, td.intro, NULL);

    
    while (sfRenderWindow_isOpen(td.window)) {
        td.time = sfClock_getElapsedTime(td.clock);
        td.seconds = td.time.microseconds/1000000.0;
        while (sfRenderWindow_pollEvent(td.window, &td.event)) {
            if (td.event.type == sfEvtClosed) {
                td = exit_game(td);
                if (td.exit == 1)
                    return td;
            }
            if (sfKeyboard_isKeyPressed(sfKeyEscape))
                return td;
        }
        if ((clock_intro + 0.05) < td.seconds) {
            if (intro_rect.left < 3840 || intro_rect.top < 3240) {
                if (intro_rect.left == 3840 && intro_rect.top < 3240) {
                    intro_rect.left = 0;
                    intro_rect.top += 1080;
                } else if (intro_rect.left != 3840)
                   intro_rect.left += 1920;
            }
            if (cooldown == 20 && intro_rect.left == 3840 && intro_rect.top == 3240)
                return (td);
            else if (intro_rect.left == 3840 && intro_rect.top == 3240)
                cooldown++;
        
            sfSprite_setTextureRect(td.intro, intro_rect);
            sfRenderWindow_drawSprite(td.window, td.intro, NULL);
            sfRenderWindow_display(td.window);
            clock_intro = td.seconds;
        }
    }
}

int init_game(tower_defense td)
{
    int x = 0;
    int w = 0;
    int i = 0;
    int j = 0;

    td.window = create_window("tower defense");
    td.font = sfFont_createFromFile("misc/font.ttf");
    td.window_dim = sfRenderWindow_getSize(td.window);
    td.connections = 0;
    td.window_size.x = 600;
    td.window_size.y = 300;
    td.window_pos.x = 0;
    td.window_pos.y = 0;
    td.exit = 0;
    td.how_to_play_open = 0;
    td.custom_level = 0;
    td.start_delay = 0;
    td.intro = new_sprite("sprites/intro.png", 1, 1);
    td.background = new_sprite("sprites/map/background.jpg", 1, 1);
    td.winlose_tab = new_sprite("sprites/hud/winlose_tab.png", 1, 1);
    td.background2 = new_sprite("sprites/map/map_onlytree.png", 1, 1);
    td.background3 = new_sprite("sprites/map/bridge.png", 1, 1);
    td.background4 = new_sprite("sprites/empty.png", 1, 1);
    td.dark = new_sprite("sprites/hud/dark.png", 1, 1);
    td.hud_down = new_sprite("sprites/hud/hud_down.png", 1, 1);
    td.text_zone = new_sprite("sprites/hud/text_zone.png", 1, 1);
    td.rock_button = new_sprite("sprites/buttons/rock_button.png", 1, 1);
    td.enemy_point_button = new_sprite("sprites/buttons/enemy_point_button.png", 1, 1);
    td.defend_point_button = new_sprite("sprites/buttons/defend_point_button.png", 1, 1);
    td.tree_button = new_sprite("sprites/buttons/tree_button.png", 1, 1);
    td.erase_hint = new_sprite("sprites/hud/mouse_l_key.png", 1, 1);
    td.toggle_grid_hint = new_sprite("sprites/hud/T_key.png", 1, 1);
    td.u_button = new_sprite("sprites/buttons/u_button.png", 1, 1);
    td.d_button = new_sprite("sprites/buttons/d_button.png", 1, 1);
    td.r_button = new_sprite("sprites/buttons/r_button.png", 1, 1);
    td.l_button = new_sprite("sprites/buttons/l_button.png", 1, 1);
    td.how_to_play_sprite = new_sprite("sprites/how_to_play.png", 1, 1);
    td.buildable_button = new_sprite("sprites/buttons/buildable_button.png", 1, 1);
    td.menu_editor = new_sprite("sprites/hud/menu_editor.png", 1, 1);
    td.settings_menu = new_sprite("sprites/hud/settings_menu.png", 1, 1);
    td.build_menu = new_sprite("sprites/hud/build_menu.png", 0.5, 0.5);
    td.upgrade_menu = new_sprite("sprites/hud/upgrade_menu.png", 0.5, 0.5);
    td.upgrade_menu_1= new_sprite("sprites/buttons/upgrade_button1.png", 0.5, 0.5);
    td.upgrade_menu_2 = new_sprite("sprites/buttons/upgrade_button2.png", 0.5, 0.5);
    td.pause_menu = new_sprite("sprites/hud/pause_menu.png", 1, 1);
    td.main_menu = new_sprite("sprites/main_menu.png", 1, 1);
    td.build_menu_1 = new_sprite("sprites/buttons/build_menu_button1.png", 0.5, 0.5);
    td.build_menu_2 = new_sprite("sprites/buttons/build_menu_button2.png", 0.5, 0.5);
    td.build_menu_3 = new_sprite("sprites/buttons/build_menu_button3.png", 0.5, 0.5);
    td.build_menu_4 = new_sprite("sprites/buttons/build_menu_button4.png", 0.5, 0.5);
    td.start_button = new_sprite("sprites/buttons/button_start.png", 1, 1);
    td.retry_button = new_sprite("sprites/buttons/button_retry.png", 1, 1);
    td.continue_button = new_sprite("sprites/buttons/button_continue.png", 1, 1);
    td.back_start_button = new_sprite("sprites/buttons/button_back_start.png", 1, 1);
    td.custom_level_button = new_sprite("sprites/buttons/button_custom_level.png", 1, 1);
    td.campaign_button = new_sprite("sprites/buttons/button_campaign.png", 1, 1);
    td.resume_button = new_sprite("sprites/buttons/button_resume_pa.png", 1, 1);
    td.exit_button_p = new_sprite("sprites/buttons/button_exit_pa.png", 1, 1);
    td.settings_button = new_sprite("sprites/buttons/button_settings.png", 1, 1);
    td.settings_button_p = new_sprite("sprites/buttons/button_settings_pa.png", 1, 1);
    td.exit_button = new_sprite("sprites/buttons/button_exit.png", 1, 1);
    td.map_editor_button = new_sprite("sprites/buttons/button_map_editor.png", 1, 1);
    td.vol_up_button = new_sprite("sprites/buttons/vol_up.png", 1, 1);
    td.stars = new_sprite("sprites/hud/stars_end.png", 1, 1);
    td.next_button = new_sprite("sprites/buttons/next_button.png", 1, 1);
    td.prev_button = new_sprite("sprites/buttons/prev_button.png", 1, 1);
    td.back_how_to_button = new_sprite("sprites/buttons/back_how_to_button.png", 1, 1);
    td.vol_down_button = new_sprite("sprites/buttons/vol_down.png", 1, 1);
    td.vol_bar = new_sprite("sprites/hud/sound_bar.png", 1, 1);
    td.heart = new_sprite("sprites/hud/heart.png", 1, 1);
    td.gold = new_sprite("sprites/hud/gold.png", 1, 1);
    td.apply_button = new_sprite("sprites/buttons/button_apply.png", 1, 1);
    td.back_mainmenu_endbutton = new_sprite("sprites/buttons/button_mainmenu_end.png", 1, 1);
    td.save_button = new_sprite("sprites/buttons/button_save.png", 1, 1);
    td.load_button = new_sprite("sprites/buttons/load_button.png", 1, 1);
    td.back_button = new_sprite("sprites/buttons/button_back.png", 1, 1);
    td.x640_button = new_sprite("sprites/buttons/button_640.png", 1, 1);
    td.x960_button = new_sprite("sprites/buttons/button_960.png", 1, 1);
    td.x1280_button = new_sprite("sprites/buttons/button_1280.png", 1, 1);
    td.x1920_button = new_sprite("sprites/buttons/button_1920.png", 1, 1);
    td.button_lvl1 = new_sprite("sprites/buttons/button_lvl1.png", 1, 1);
    td.button_lvl2 = new_sprite("sprites/buttons/button_lvl2.png", 1, 1);
    td.button_lvl3 = new_sprite("sprites/buttons/button_lvl3.png", 1, 1);
    td.button_lvl4 = new_sprite("sprites/buttons/button_lvl4.png", 1, 1);
    td.winlose_header = new_sprite("sprites/hud/header_win.png", 1, 1);
    td.help_button = new_sprite("sprites/buttons/help_button.png", 1, 1);
    td.selected_tower = new_sprite("sprites/empty.png", 0.55, 0.55);
    td.hud_tw_dmg_sprt = new_sprite("sprites/hud/ico_dmg.png", 0.5, 0.5);
    td.hud_tw_range_sprt = new_sprite("sprites/hud/ico_range.png", 0.5, 0.5);
    td.hud_tw_atckspd_sprt = new_sprite("sprites/hud/ico_atckspd.png", 0.5, 0.5);
    td.T_path = sfTexture_createFromFile("sprites/map/T_path.png", NULL);
    td.L_path = sfTexture_createFromFile("sprites/map/L_path.png", NULL);
    td.X_path = sfTexture_createFromFile("sprites/map/X_path.png", NULL);
    td.tree = sfTexture_createFromFile("sprites/map/tree.png", NULL);
    td.rock = sfTexture_createFromFile("sprites/map/rock.png", NULL);
    td.empty_texture = sfTexture_createFromFile("sprites/empty.png", NULL);
    td.type1_texture = sfTexture_createFromFile("sprites/monsters/type1_walk.png", NULL);
    td.type1_death = sfTexture_createFromFile("sprites/monsters/type1_death.png", NULL);
    td.type2_texture = sfTexture_createFromFile("sprites/monsters/type2_walk.png", NULL);
    td.type2_run = sfTexture_createFromFile("sprites/monsters/type2_run.png", NULL);
    td.type2_death = sfTexture_createFromFile("sprites/monsters/type2_death.png", NULL);
    td.frost_effect = sfTexture_createFromFile("sprites/effects/frost_effect.png", NULL);
    td.weakness_effect = sfTexture_createFromFile("sprites/effects/weakness.png", NULL);
    td.explosion_effect = sfTexture_createFromFile("sprites/effects/explosion.png", NULL);
    td.archer1_preview = sfTexture_createFromFile("sprites/towers/archer1_preview.png", NULL);
    td.mage1_preview = sfTexture_createFromFile("sprites/towers/mage1_preview.png", NULL);
    td.catapult1_preview = sfTexture_createFromFile("sprites/towers/catapult1_preview.png", NULL);
    td.supp1_preview = sfTexture_createFromFile("sprites/towers/supp1_preview.png", NULL);
    td.buildable = sfTexture_createFromFile("sprites/map/buildable.png", NULL);
    td.header_win = sfTexture_createFromFile("sprites/hud/header_win.png", NULL);
    td.header_lose = sfTexture_createFromFile("sprites/hud/header_lose.png", NULL);
    td.menu_music = sfMusic_createFromFile("sounds/menu_music.ogg");
    td.win_sound = set_up_new_sound(td.win_sound, "sounds/win_sound.ogg");
    td.lose_sound = set_up_new_sound(td.click_sound, "sounds/lose_sound.ogg");
    td.click_sound = set_up_new_sound(td.click_sound, "sounds/click_sound.ogg");
    td.type1_death_sound = set_up_new_sound(td.type1_death_sound, "sounds/type1_death.ogg");
    td.type2_death_sound = set_up_new_sound(td.type2_death_sound, "sounds/type2_death.ogg");
    td.stab_sound = set_up_new_sound(td.stab_sound, "sounds/stab.ogg");
    td.sell_sound = set_up_new_sound(td.sell_sound, "sounds/sell.ogg");
    td.explosion_sound = set_up_new_sound(td.sell_sound, "sounds/catapult_impact.ogg");
    td.build_sound = set_up_new_sound(td.build_sound, "sounds/build_sound.ogg");
    td.endwin_text1 = new_text(td, sfWhite);
    td.endwin_text2 = new_text(td, sfWhite);
    td.wave_text = new_text(td, sfWhite);
    td.wave_index_text = new_text(td, sfWhite);
    td.build_txt_1 = new_text(td, sfYellow);
    td.build_txt_2 = new_text(td, sfYellow);
    td.build_txt_3 = new_text(td, sfYellow);
    td.build_txt_4 = new_text(td, sfYellow);
    td.hud_tw_dmg_txt = new_text(td, sfWhite);
    td.hud_tw_range_txt = new_text(td, sfWhite);
    td.hud_tw_atckspd_txt = new_text(td, sfWhite);
    td.upgrade_txt_1 = new_text(td, sfYellow);
    td.upgrade_txt_2 = new_text(td, sfYellow);
    td.cursor_hitbox = sfRectangleShape_create();
    td.clock = sfClock_create();
    td.time;
    td.choice = 0;
    td.delay_exit = 0;
    td.vol_bar_offset = 0;
    td.exit_code = 0;
    td.main_clock = 0;
    td.move_clock = 0;
    td.vol_bar_scale.x = 0.6;
    td.vol_bar_scale.y = 0.5;
    td.seconds = 0;
    td.volume = 100;
    td.fullscreen = sfFalse;
    td.hud_tw_dmg_str = malloc(sizeof(char) * 100);
    td.hud_tw_range_str = malloc(sizeof(char) * 100);
    td.hud_tw_atckspd_str = malloc(sizeof(char) * 100);
    td.build_txt_str4 = malloc(sizeof(char) * 100);
    td.upgrade_txt_str1 = malloc(sizeof(char) * 100);
    td.upgrade_txt_str2 = malloc(sizeof(char) * 100);
    td.wave_index_str = malloc(sizeof(char) * 100);

    td.gold_cooldown = 0;

    td.main_menu_button = 0;
    sfVector2f cursor_size = {3, 3};
    sfVector2f cursor_origin = {1.5, 1.5};
    td.grid;

    td = create_editor_grid(td);

    td.window_size.x = 1920/2;
    td.window_size.y = 1080/2;
    td.g_scale = 2;
    sfRenderWindow_setSize(td.window, td.window_size);
    sfRenderWindow_setPosition(td.window, td.window_pos);
    sfRenderWindow_setVerticalSyncEnabled(td.window, sfTrue);
    sfRectangleShape_setSize(td.cursor_hitbox, cursor_size);
    sfRectangleShape_setOrigin(td.cursor_hitbox, cursor_origin);
    sfSprite_setScale(td.vol_bar, td.vol_bar_scale);

    init_animated_sprite(td.stars, 4);
    init_animated_sprite(td.how_to_play_sprite, 3);

    init_animated_button(td.button_lvl1);
    init_animated_button(td.button_lvl2);
    init_animated_button(td.button_lvl3);
    init_animated_button(td.button_lvl4);
    init_animated_button(td.start_button);
    init_animated_button(td.back_how_to_button);
    init_animated_button(td.next_button);
    init_animated_button(td.prev_button);
    init_animated_button(td.help_button);
    init_animated_button(td.back_mainmenu_endbutton);
    init_animated_button(td.continue_button);
    init_animated_button(td.retry_button);
    init_animated_button(td.tree_button);
    init_animated_button(td.enemy_point_button);
    init_animated_button(td.defend_point_button);
    init_animated_button(td.buildable_button);
    init_animated_button(td.rock_button);
    init_animated_button(td.back_start_button);
    init_animated_button(td.vol_up_button);
    init_animated_button(td.vol_down_button);
    init_animated_button(td.u_button);
    init_animated_button(td.d_button);
    init_animated_button(td.r_button);
    init_animated_button(td.l_button);
    init_animated_button(td.save_button);
    init_animated_button(td.load_button);
    init_animated_button(td.custom_level_button);
    init_animated_button(td.campaign_button);
    init_animated_button(td.map_editor_button);
    init_animated_button(td.resume_button);
    init_animated_button(td.settings_button_p);
    init_animated_button(td.settings_button);
    init_animated_button(td.exit_button);
    init_animated_button(td.exit_button_p);
    init_animated_button(td.vol_bar);
    init_animated_button(td.apply_button);
    init_animated_button(td.back_button);
    init_animated_button(td.x640_button);
    init_animated_button(td.x960_button);
    init_animated_button(td.x1280_button);
    init_animated_button(td.x1920_button);

    sfSprite_setOrigin(td.stars, get_sprite_center(td.stars));
    sfSprite_setOrigin(td.how_to_play_sprite, get_sprite_center(td.how_to_play_sprite));
    sfSprite_setOrigin(td.upgrade_menu, get_sprite_center(td.upgrade_menu));
    sfSprite_setOrigin(td.build_menu_1, get_sprite_center(td.build_menu_1));
    sfSprite_setOrigin(td.build_menu_2, get_sprite_center(td.build_menu_2));
    sfSprite_setOrigin(td.build_menu_3, get_sprite_center(td.build_menu_3));
    sfSprite_setOrigin(td.build_menu_4, get_sprite_center(td.build_menu_4));
    sfSprite_setOrigin(td.upgrade_menu_1, get_sprite_center(td.upgrade_menu_1));
    sfSprite_setOrigin(td.upgrade_menu_2, get_sprite_center(td.upgrade_menu_2));
    sfSprite_setOrigin(td.winlose_tab, get_sprite_center(td.winlose_tab));
    sfSprite_setOrigin(td.winlose_header, get_sprite_center(td.winlose_header));

    sfText_setString(td.wave_text, "Wave:");
    setText_pos(td.wave_text, 1600, 1000);
    setText_pos(td.wave_index_text, 1700, 1000);
    setText_pos(td.hud_tw_dmg_txt, 765, 1045);
    setText_pos(td.hud_tw_range_txt, 865, 1045);
    setText_pos(td.hud_tw_atckspd_txt, 965, 1045);

    setSprite_pos(td.hud_tw_dmg_sprt, 750, 965);
    setSprite_pos(td.hud_tw_range_sprt, 850, 965);
    setSprite_pos(td.hud_tw_atckspd_sprt, 950, 965);

    setSprite_pos(td.button_lvl1, 1550, 300);
    setSprite_pos(td.button_lvl2, 1550, 450);
    setSprite_pos(td.button_lvl3, 1550, 600);
    setSprite_pos(td.button_lvl4, 1550, 750);

    setSprite_pos(td.how_to_play_sprite, 960, 540);
    setSprite_pos(td.prev_button, 400, 880);
    setSprite_pos(td.back_how_to_button, 910, 880);
    setSprite_pos(td.next_button, 1385, 880);
    setSprite_pos(td.back_mainmenu_endbutton, 720, 800);
    setSprite_pos(td.selected_tower, 500, 960);
    setSprite_pos(td.retry_button, 1060, 800);
    setSprite_pos(td.help_button, 100, 850);
    setSprite_pos(td.continue_button, 1060, 800);
    setSprite_pos(td.winlose_tab, 960, 500);
    setSprite_pos(td.winlose_header, 960, 160);
    setSprite_pos(td.stars, 960, 390);
    setSprite_pos(td.load_button, 1150, 10);
    setSprite_pos(td.heart, 40, 980);
    setSprite_pos(td.gold, 20, 1020);
    setSprite_pos(td.erase_hint, 1400, 10);
    setSprite_pos(td.toggle_grid_hint, 1700, 10);
    setSprite_pos(td.rock_button, 20, 350);
    setSprite_pos(td.tree_button, 170, 350);
    setSprite_pos(td.defend_point_button, 10, 650);
    setSprite_pos(td.enemy_point_button, 150, 650);
    setSprite_pos(td.u_button, 0, 20);
    setSprite_pos(td.d_button, 150, 20);
    setSprite_pos(td.r_button, 10, 200);
    setSprite_pos(td.l_button, 150, 200);
    setSprite_pos(td.buildable_button, 10, 500);
    setSprite_pos(td.start_button, 1450, 600);
    setSprite_pos(td.text_zone, 20, 890);
    setSprite_pos(td.save_button, 20, 950);
    setSprite_pos(td.campaign_button, 1522, 450);
    setSprite_pos(td.settings_button, 1450, 740);
    setSprite_pos(td.hud_down, 0, 940);
    setSprite_pos(td.custom_level_button, 1490, 600);
    setSprite_pos(td.map_editor_button, 1522, 750);
    setSprite_pos(td.exit_button, 1450, 880);
    setSprite_pos(td.back_start_button, 1550, 900);
    setSprite_pos(td.settings_menu, 0, 0);
    setSprite_pos(td.pause_menu, 0, 0);
    setSprite_pos(td.vol_up_button, 1277, 300);
    setSprite_pos(td.vol_down_button, 527, 300);
    setSprite_pos(td.vol_bar, 667, 315);
    setSprite_pos(td.apply_button, 655, 795);
    setSprite_pos(td.resume_button, 735, 325);
    setSprite_pos(td.settings_button_p, 735, 495);
    setSprite_pos(td.exit_button_p, 735, 665);
    setSprite_pos(td.back_button, 1000, 795);
    setSprite_pos(td.x640_button, 1000, 580);
    setSprite_pos(td.x960_button, 585, 580);
    setSprite_pos(td.x1280_button, 1000, 425);
    setSprite_pos(td.x1920_button, 585, 425);
    
    td = intro_loop(td);

    if (td.exit == 1)
        return 0;
    
    sfMusic_setLoop(td.menu_music, sfTrue);
    sfMusic_play(td.menu_music);

    td = handle_main_menu_loop(td);
    if (td.exit == 1)
        return 0;
    if (td.main_menu_button == 1)
        td = create_editor_grid(td);
    else if (td.main_menu_button == 2)
        td = create_game_grid(td);
    
    if (td.main_menu_button == 2)
        td = execute_game_loop(td, td.chapter);
    else if (td.main_menu_button == 1)
        td = execute_editor_loop(td);
    if (td.exit_code == 1) {
        sfMusic_stop(td.menu_music);
        restart_game(td);
        if (td.exit == 1)
            return 0;
    }
}

int main(int argc, char **argv)
{
    tower_defense td;

    init_game(td);
    return 0;
}
