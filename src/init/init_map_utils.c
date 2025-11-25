#include "cub.h"

bool is_map_line(char *line)
{
    int i;

    if (!line)
        return (false);
    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
            && line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
            && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (false);
        i++;
    }
    return (true);
}

void process_map_char(char c, char **map, t_data *data, int i, int j, int *player)
{
    int valid_char;

    valid_char = 0;
    if (c == ' ')
    {
        map[i][j] = ' ';
        valid_char++;
    }
    if (c == '1')
    {
        map[i][j] = '1';
        valid_char++;
    }
    else if (c == '0')
    {
        map[i][j] = '0';
        valid_char++;
    }
    else if (c == 'N')
    {
        set_player_north(data, i, j);
        map[i][j] = '0';
        valid_char++;
        (*player)++;
    }
    else if (c == 'S')
    {
        set_player_south(data, i, j);
        map[i][j] = '0';
        valid_char++;
        (*player)++;
    }
    else if (c == 'E')
    {
        set_player_east(data, i, j);
        map[i][j] = '0';
        valid_char++;
        (*player)++;
    }
    else if (c == 'W')
    {
        set_player_west(data, i, j);
        map[i][j] = '0';
        valid_char++;
        (*player)++;
    }
    if (valid_char == 0)
        exit_program(data, E_map);
}

char **allocate_char_map(t_map_size *map_size)
{
    char **map;
    int i;
    int w;

    map = ft_calloc(map_size->height + 1, sizeof(char *));
    if (!map)
        return (NULL);
    i = 0;
    while (i < map_size->height)
    {
        w = map_size->width[i];
        map[i] = ft_calloc(w + 1, sizeof(char));
        if (!map[i])
        {
            while (i > 0)
            {
                i--;
                free(map[i]);
            }
            free(map);
            return (NULL);
        }
        i++;
    }
    map[i] = NULL;
    return (map);
}

void fill_map_line(char *line, char **map, t_data *data, int i, int *player)
{
    int j;
    int len;

    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        len--;
    j = 0;
    while (j < data->map_size.width[i])
    {
        if (j < len)
            process_map_char(line[j], map, data, i, j, player);
        j++;
    }
}

bool flood_fill1(char **map, int i, int j, t_map_size *map_size)
{
    if (i < 0 || j < 0 || i >= map_size->height || j >= map_size->width[i])
        return (false);
    
    if (map[i][j] == '1')
        return (true);

    if (map[i][j] == 'V')
        return (true);
    
    if (map[i][j] == ' ')
        return (false);
    
    if (map[i][j] == '0')
    {
        map[i][j] = 'V';
        
        if (!flood_fill1(map, i - 1, j, map_size))
            return (false);
        if (!flood_fill1(map, i + 1, j, map_size))
            return (false);
        if (!flood_fill1(map, i, j - 1, map_size))
            return (false);
        if (!flood_fill1(map, i, j + 1, map_size))
            return (false);
        
        return (true);
    }
    
    return (false);
}

void restore_visited_cells(char **map, t_map_size *map_size)
{
    int i;
    int j;

    i = 0;
    while (i < map_size->height)
    {
        j = 0;
        while (j < map_size->width[i])
        {
            if (map[i][j] == 'V')
                map[i][j] = '0';
            j++;
        }
        i++;
    }
}

bool validate_map_with_flood_fill(char **map, t_map_size *map_size, t_data *data)
{
    int i;
    int j;

    (void)data;
    i = 0;
    while (i < map_size->height)
    {
        j = 0;
        while (j < map_size->width[i])
        {
            if (map[i][j] == '0')
            {
                if (!flood_fill1(map, i, j, map_size))
                {
                    restore_visited_cells(map, map_size);
                    return (false);
                }
            }
            j++;
        }
        i++;
    }
    
    restore_visited_cells(map, map_size);
    return (true);
}

char **add_walls(t_data *data, char **map, t_map_size *map_size)
{
    int i = 0;
    int j = 0;
    char **tmp_map;

    tmp_map = malloc(map_size->height * sizeof(char *));
    if (!tmp_map)
    {
        free_map(map);
        exit_program(data, E_malloc);
    }
    while (i < map_size->height)
    {

        tmp_map[i] = malloc((map_size->width[i] + 2) * sizeof(char));
        if (!tmp_map[i])
        {
            while (i > 0)
            {
                i--;
                free(tmp_map[i]);
            }
            free(tmp_map);
            data->char_map = map;
            exit_program(data, E_malloc);
        }

        j = 0;
        while (j < map_size->width[i])
        {
            tmp_map[i][j] = map[i][j];
            j++;
        }
        free(map[i]);
        map[i] = NULL;
        tmp_map[i][j] = '1';    
        tmp_map[i][j+1] = '\0';
        map_size->width[i]++;
        i++;
    }
    free(map);
    map = NULL;

    return (tmp_map);
}


char **fill_char_map(t_map_size *map_size, t_data *data)
{
    int start;
    int i;
    char *line;
    char **map;
    int player;

    player = 0;
    start = find_map_start(data->cub_doc);
    if (start == -1)
        return (NULL);
    
    map = allocate_char_map(map_size);
    if (!map)
        exit_program(data, E_malloc);
    
    i = 0;
    while (i < map_size->height)
    {
        line = data->cub_doc[start + i];
        fill_map_line(line, map, data, i, &player);
        i++;
    }
    if (!validate_map_with_flood_fill(map, map_size, data) || player != 1)
    {
        free_map(map);
        exit_program(data, E_map);
    }
    map = add_walls(data, map, map_size);
    return (map);
}

int **convert_char_to_int_map(char **char_map, t_map_size *map_size)
{
    int **int_map;
    int i;
    int j;

    int_map = ft_calloc(map_size->height, sizeof(int *));
    if (!int_map)
        return (NULL);
    i = 0;
    while (i < map_size->height)
    {
        int_map[i] = ft_calloc(map_size->width[i], sizeof(int));
        if (!int_map[i])
        {
            while (i > 0)
            {
                i--;
                free(int_map[i]);
            }
            free(int_map);
            return (NULL);
        }
        j = 0;
        while (j < map_size->width[i])
        {
            int_map[i][j] = (char_map[i][j] == '0') ? 0 : 1;
            j++;
        }
        i++;
    }
    return (int_map);
}