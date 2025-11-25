/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:00:23 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 15:00:38 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <X11/Xlib.h>
# include <X11/cursorfont.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_error
{
	No_error,
	Error,
	E_malloc,
	E_nbarg,
	E_ext,
	E_path,
	E_mlx_env,
	E_mlx_win,
	E_tex,
	E_map,
	E_read
}					t_error;

typedef enum e_key
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_Ra,
	KEY_La,
	KEY_ESC,
	KEY_SHIFT,
	KEY_COUNT
}					t_key;

typedef struct s_square
{
	int				x;
	int				y;
	int				size;
	int				color;
}					t_square;

typedef struct s_minimap
{
	int				view_distance;
	int				grid_size;
	int				cell_size;
	int				start_x;
	int				start_y;
	int				color_floor;
	int				color_void;
	int				color_player;
}					t_minimap;

typedef struct s_player
{
	double			p_x;
	double			p_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			p_speed;
}					t_player;

typedef struct s_path_textures
{
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	char			*F;
	char			*C;
}					t_path_textures;

typedef struct s_teximg
{
	void			*img;
	unsigned int	*px;
	int				width;
	int				height;
	int				bpp;
	int				line_len;
	int				endian;
}					t_teximg;

typedef struct s_map_size
{
	int				*width;
	int				max_width;
	int				height;
}					t_map_size;

typedef struct s_colors
{
	int				RF;
	int				GF;
	int				BF;
	int				RC;
	int				GC;
	int				BC;
}					t_colors;

typedef struct s_line_exits
{
	int				first_exit;
	int				last_exit;
}					t_line_exits;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				line_len;
	int				endian;
	int				**map;
	char			**char_map;
	char			**cub_doc;
	int				last_mouse_x;
	double			dpi;
	int				key[KEY_COUNT];
	int				screen_w;
	int				screen_h;
	t_map_size		map_size;
	t_teximg		teximg[4];
	t_path_textures	path_textures;
	t_player		p;
	t_colors		colors;
	t_line_exits	*line_exits;
}					t_data;

typedef struct s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				side;
	double			perp_wall_dist;
}					t_ray;

int					key_hook(int keycode, t_data *data);
void				put_pixel(t_data *data, int x, int y, int color);
void				draw_line(t_data *data, int x0, int y0, int x1, int y1,
						int color);
void				draw_wall(t_data *data, t_player *p);
void				draw_background(t_data *data, int width, int height);
int					create_rgb(int r, int g, int b);

char				**duplicate_map(t_data *data, t_map_size *size);
void				get_doc_size(t_data *data, int fd, int *doc_height,
						int *doc_width);
void				free_map(char **map);
void				print_map(char **map, t_map_size *map_size);
void				transfer_cub_map(t_data *data, char *map_name);
void				get_map_size(t_data *data, t_map_size *map_size);
int					find_map_start(char **doc);
void				copy_all_doc(t_data *data, char *map_name, int doc_height);
void				open_map_file(t_data *data, char *map_name, int *fd);
void				init_struct(t_data *data, t_map_size *size,
						char ***char_map_out);
int					**fill_map(t_map_size *size, t_data *data);
char				**fill_char_map(t_map_size *size, t_data *data);
int					**convert_char_to_int_map(char **char_map,
						t_map_size *size);
void				init_textures(t_data *data);
void				init_c_colors(t_data *data);
void				init_window(t_data *data);

void				set_player_north(t_data *data, int i, int j);
void				set_player_south(t_data *data, int i, int j);
void				set_player_east(t_data *data, int i, int j);
void				set_player_west(t_data *data, int i, int j);

void				check_map(t_data *data, t_map_size *map_size,
						char *map_name);

void				move_forward(t_data *data, double speed);
void				move_backward(t_data *data, double speed);
void				move_left(t_data *data, double speed);
void				move_right(t_data *data, double speed);
void				rotate_direction(t_player *p, double rotSpeed);
void				rotate_plane(t_player *p, double rotSpeed);
void				rotate_left(t_data *data);
void				rotate_right(t_data *data);

int					mouse_move(int x, int y, t_data *data);
void				process_movement(t_data *data);
int					key_release(int keycode, t_data *data);
int					key_press(int keycode, t_data *data);
int					close_window(t_data *data);

void				parsing(int ac, char **av, t_data *data, t_map_size *map);
void				exit_program(t_data *data, t_error error);
void				free_all(t_data *data);
void				print_error(t_error error);

void				print_int_map(int **map, t_map_size *map_size);

void				minimap(t_data *data);

#endif