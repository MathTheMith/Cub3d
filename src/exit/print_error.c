

#include "cub.h"

void print_error(t_error error)
{
    if (error == E_path)
        printf("Error\nType: E_path\nThe path of the map doesn't exist!\n");
    else if (error == E_malloc)
        printf("Error\nType: E_malloc\nIssue with an allocation!\n");
    else if (error == E_nbarg)
        printf("Error\nType: E_nbarg\nYou just need to put the path of the map!\n");
    else if (error == E_ext)
        printf("Error\nType: E_ext\nYou need a map with .cub at the end!\n");
    else if (error == E_mlx_env)
        printf("Error\nType: E_mlx_env\nYou need the env!\n");
    else if (error == E_mlx_win)
        printf("Error\nType: E_mlx_win\nCreation of the window fail!\n");
    else if (error == E_tex)
        printf("Error\nType: E_tex\nThe textures of the wall is invalid(check the file or the path)!\n");
    else if (error == E_map)
        printf("Error\nType: E_map\nThe map isn't valid\n");
    else if (error == E_read)
        printf("Error\nType: E_read\n\n");
}

