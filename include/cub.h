#ifndef CUB_H
 #define CUB_H

#include "mlx.h"
#include <stdlib.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <math.h>
#include <fcntl.h>

typedef enum e_error
{
    No_error,
    Error,
    E_malloc,
    E_nbarg,
    E_ext,
    E_path
}           t_error;

typedef struct s_player
{
	double p_x;
	double p_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
}	t_player;

typedef struct s_textures
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    char *F;
    char *C;
}   t_textures;

typedef struct s_map_size
{
    int width;
    int height;
}   t_map_size;

typedef struct s_colors
{
    int RF;
    int GF;
    int BF;
    int RC;
    int GC;
    int BC;
}   t_colors;

typedef struct s_data
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *data;
    int     bpp;
    int     line_len;
    int     endian;
	int **map;
    t_textures textures;
	t_player p;
    t_colors colors;
	
}   t_data;

typedef struct s_ray
{
    double camera_x;
    double dir_x;
    double dir_y;
    int map_x;
    int map_y;
    double delta_dist_x;
    double delta_dist_y;
    double side_dist_x;
    double side_dist_y;
    int step_x;
    int step_y;
    int side;
    double perp_wall_dist;
}   t_ray;

int key_hook(int keycode, t_data *data);
void put_pixel(t_data *data, int x, int y, int color);
void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color);
void draw_wall(t_data *data, t_player *p);
void draw_background(t_data *data, int width, int height);

int **init_map(t_data *data,t_map_size *size, char *map_name);
int open_map_file(char *map_name);
void init_struct(t_data *data,t_map_size *size, char *map_name);
int **fill_map(int fd, t_map_size *size, t_data *data);
void init_textures(t_data *data, char *map_name);
void init_c_colors(t_data *data);
void init_window(t_data *data);

void set_player_north(t_data *data, int i, int j);
void set_player_south(t_data *data, int i, int j);
void set_player_east(t_data *data, int i, int j);
void set_player_west(t_data *data, int i, int j);

int check_map(t_data *data, t_map_size *size);


void move_forward(t_data *data);
void move_backward(t_data *data);
void move_left(t_data *data);
void move_right(t_data *data); 
void rotate_direction(t_player *p, double rotSpeed);
void rotate_plane(t_player *p, double rotSpeed);
void rotate_left(t_data *data);
void rotate_right(t_data *data);


void parsing(int ac, char **av, t_data *data);
void exit_program(t_data *data, t_error error);
void free_all(t_data *data);
void print_error(t_error error);


#endif