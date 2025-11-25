
#include "cub.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
        map[i] = NULL;
		i++;
	}
	free(map);
    map = NULL;
}

int flood_fill(char **map, int x, int y, t_map_size *size)
{
    if (y < 0 || y >= size->height)
        return (0);
    if (x < 0 || x >= size->width[y])
        return (0);

    if (map[y][x] == '1' || map[y][x] == 'F')
        return (1);
    if (map[y][x] == ' ')
        return (0);

    map[y][x] = 'F';

    if (!flood_fill(map, x + 1, y, size))
        return (0);
    if (!flood_fill(map, x - 1, y, size))
        return (0);
    if (!flood_fill(map, x, y + 1, size))
        return (0);
    if (!flood_fill(map, x, y - 1, size))
        return (0);
    return (1);
}


void print_map(char **map, t_map_size *map_size)
{
    int i, j;

    printf("\n----- MAP -----\n");

    for (i = 0; i < map_size->height; i++)
    {
        for (j = 0; j < map_size->width[i]; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("---------------\n");
}

char **duplicate_map(t_data *data, t_map_size *size)
{
    int     i;
    int     j;
    char    **copy;

    copy = malloc(sizeof(char *) * (size->height + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (i < size->height)
    {
        copy[i] = malloc(sizeof(char) * (size->width[i] + 1));
        if (!copy[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
        j = 0;
        while (j < size->width[i])
        {
            copy[i][j] = (data->map[i][j] == 0) ? '0' : '1';
            j++;
        }
        copy[i][j] = '\0';
        i++;
    }
    copy[size->height] = NULL;
    return (copy);
}