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

void process_map_char(char c, char **map, t_data *data, int i, int j)
{
    int valid_char;

    valid_char = 0;
    if (c == '1' || c == ' ')
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
    }
    else if (c == 'S')
    {
        set_player_south(data, i, j);
        map[i][j] = '0';
        valid_char++;
    }
    else if (c == 'E')
    {
        set_player_east(data, i, j);
        map[i][j] = '0';
        valid_char++;
    }
    else if (c == 'W')
    {
        set_player_west(data, i, j);
        map[i][j] = '0';
        valid_char++;
    }
    if (valid_char == 0)
        exit_program(data, E_map);
}

char **allocate_char_map(t_map_size *map_size)
{
    char **map;
    int i;
    int j;
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
        j = 0;
        while (j < w)
        {
            map[i][j] = '1';
            j++;
        }
        map[i][j] = '\0';
        i++;
    }
    map[i] = NULL;
    return (map);
}

void fill_map_line(char *line, char **map, t_data *data, int i, int width)
{
    int j;
    int len;

    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        len--;
    j = 0;
    while (j < width)
    {
        if (j < len)
            process_map_char(line[j], map, data, i, j);
        else
            map[i][j] = '1';
        j++;
    }
}

void find_line_exits(char *line, t_line_exits *exits)
{
    int i;
    int len;

    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        len--;
    exits->first_exit = -1;
    exits->last_exit = -1;
    i = 0;
    while (i < len)
    {
        if (line[i] == '0' || line[i] == 'N' || line[i] == 'S'
            || line[i] == 'E' || line[i] == 'W')
        {
            if (exits->first_exit == -1)
                exits->first_exit = i;
            exits->last_exit = i;
        }
        i++;
    }
}

bool check_first_last_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (false);
        i++;
    }
    return (true);
}

bool is_whitespace(char c)
{
    if (c == ' ' || c == '\t')
        return (true);
    return (false);
}

bool check_line_borders(char *line, t_line_exits *exits)
{
    int len;
    int i;

    if (exits->first_exit == -1)
        return (true);
    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        len--;
    i = 0;
    while (i < exits->first_exit && is_whitespace(line[i]))
        i++;
    if (i < exits->first_exit && line[i] != '1')
        return (false);
    if (exits->first_exit > 0 && !is_whitespace(line[exits->first_exit - 1])
        && line[exits->first_exit - 1] != '1')
        return (false);
    if (exits->last_exit < len - 1)
    {
        if (line[exits->last_exit + 1] != '1'
            && !is_whitespace(line[exits->last_exit + 1]))
            return (false);
        i = exits->last_exit + 1;
        while (i < len && is_whitespace(line[i]))
            i++;
        if (i < len && line[i] != '1')
            return (false);
    }
    return (true);
}

bool check_vertical_coverage(t_data *data, int curr_line, int start)
{
    t_line_exits *curr_exits;
    t_line_exits *prev_exits;
    t_line_exits *next_exits;
    char *prev_line;
    char *next_line;
    int j;
    int len;

    curr_exits = &data->line_exits[curr_line];
    if (curr_exits->first_exit == -1)
        return (true);
    if (curr_line > 0)
    {
        prev_exits = &data->line_exits[curr_line - 1];
        prev_line = data->cub_doc[start + curr_line - 1];
        len = ft_strlen(prev_line);
        if (len > 0 && prev_line[len - 1] == '\n')
            len--;
        j = curr_exits->first_exit;
        while (j <= curr_exits->last_exit)
        {
            if (j >= len || is_whitespace(prev_line[j]))
                return (false);
            if (prev_exits->first_exit != -1
                && (j < prev_exits->first_exit || j > prev_exits->last_exit))
            {
                if (prev_line[j] != '1')
                    return (false);
            }
            j++;
        }
    }
    if (curr_line < data->map_size.height - 1)
    {
        next_exits = &data->line_exits[curr_line + 1];
        next_line = data->cub_doc[start + curr_line + 1];
        len = ft_strlen(next_line);
        if (len > 0 && next_line[len - 1] == '\n')
            len--;
        j = curr_exits->first_exit;
        while (j <= curr_exits->last_exit)
        {
            if (j >= len || is_whitespace(next_line[j]))
                return (false);
            if (next_exits->first_exit != -1
                && (j < next_exits->first_exit || j > next_exits->last_exit))
            {
                if (next_line[j] != '1')
                    return (false);
            }
            j++;
        }
    }
    return (true);
}

bool allocate_exits(t_data *data, t_map_size *map_size)
{
    data->line_exits = ft_calloc(map_size->height, sizeof(t_line_exits));
    if (!data->line_exits)
        return (false);
    return (true);
}

char **fill_char_map(t_map_size *map_size, t_data *data)
{
    int start;
    int i;
    char *line;
    char **map;

    start = find_map_start(data->cub_doc);
    if (start == -1)
        return (NULL);
    if (!allocate_exits(data, map_size))
        return (NULL);
    map = allocate_char_map(map_size);
    if (!map)
    {
        free(data->line_exits);
        data->line_exits = NULL;
        return (NULL);
    }
    i = 0;
    while (i < map_size->height)
    {
        line = data->cub_doc[start + i];
        find_line_exits(line, &data->line_exits[i]);
        if (i == 0)
        {
            if (!check_first_last_line(line))
            {
                free_map(map);
                exit_program(data, E_map);
            }
        }
        else if (i == map_size->height - 1)
        {
            if (!check_first_last_line(line))
            {
                free_map(map);
                exit_program(data, E_map);
            }
            if (!check_vertical_coverage(data, i, start))
            {
                free_map(map);
                exit_program(data, E_map);
            }
        }
        else
        {
            if (!check_line_borders(line, &data->line_exits[i]))
            {
                free_map(map);
                exit_program(data, E_map);
            }
        }
        fill_map_line(line, map, data, i, map_size->width[i]);
        i++;
    }
    i = 0;
    while (i < map_size->height - 1)
    {
        if (!check_vertical_coverage(data, i, start))
        {
            free_map(map);
            exit_program(data, E_map);
        }
        i++;
    }
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