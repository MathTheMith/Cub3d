/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:05:23 by mvachon           #+#    #+#             */
/*   Updated: 2025/11/26 10:22:22 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

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
	E_maps,
	E_mapc,
	E_read,
	E_color
}	t_error;

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
}	t_key;

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
	int	color;
}	t_square;

typedef struct s_minimap
{
	int	view_distance;
	int	grid_size;
	int	cell_size;
	int	start_x;
	int	start_y;
	int	color_floor;
	int	color_void;
	int	color_player;
}	t_minimap;

typedef struct s_player
{
	double	p_x;
	double	p_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	p_speed;
}	t_player;

typedef struct s_path_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}	t_path_textures;

typedef struct s_teximg
{
	void			*img;
	unsigned int	*px;
	int				width;
	int				height;
	int				bpp;
	int				line_len;
	int				endian;
}	t_teximg;

typedef struct s_wall_calc
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_wall_calc;

typedef struct s_map_size
{
	int	*width;
	int	max_width;
	int	height;
}	t_map_size;

typedef struct s_colors
{
	int	rf;
	int	gf;
	int	bf;
	int	rc;
	int	gc;
	int	bc;
}	t_colors;

typedef struct s_line_exits
{
	int	first_exit;
	int	last_exit;
}	t_line_exits;

typedef struct s_color_init
{
	char	**color_str;
	size_t	*rgb_length;
	int		*color_value;
	int		is_last;
	char	*orig_str;
}	t_color_init;

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
	int				count_player;
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
}	t_data;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_render_ctx
{
	t_data		*data;
	t_teximg	*tex;
	t_ray		*ray;
	int			x;
}	t_render_ctx;

void			parsing(int ac, char **av, t_data *data, t_map_size *map);
void			check_map(t_data *data, t_map_size *map_size, char *map_name);
void			are_textures(t_data *data, char **textures_doc);

void			init_window(t_data *data);
void			init_struct(t_data *data, t_map_size *size,
					char ***char_map_out);
void			init_textures(t_data *data);
void			init_colors(t_data *data, size_t gb_lenght_f,
					size_t rgb_lenght_c);

void			set_player_north(t_data *data, int i, int j);
void			set_player_south(t_data *data, int i, int j);
void			set_player_east(t_data *data, int i, int j);
void			set_player_west(t_data *data, int i, int j);

void			get_doc_size(t_data *data, int fd, int *doc_height,
					int *doc_width);
void			get_map_size(t_data *data, t_map_size *map_size);
int				find_map_start(char **doc);
void			copy_all_doc(t_data *data, char *map_name, int doc_height);
void			open_map_file(t_data *data, char *map_name, int *fd);

int				**allocate_int_map(t_map_size *map_size);
void			fill_int_map_line(char **char_map, int **int_map,
					t_map_size *map_size, int i);
char			**allocate_char_map(t_map_size *map_size);
void			fill_map_line(char *line, t_data *data, int i);
char			**fill_char_map(t_map_size *size, t_data *data);
int				**convert_char_to_int_map(char **char_map, t_map_size *size);

char			**allocate_tmp_map(t_data *data, char **map,
					t_map_size *map_size);
char			*allocate_line(t_data *data, char **map, char **tmp_map, int i);
void			copy_and_add_wall(char **map, char **tmp_map,
					t_map_size *map_size, int i);
char			**add_walls(t_data *data, char **map, t_map_size *map_size);

bool			validate_map_with_flood_fill(char **map, t_map_size *map_size,
					t_data *data);
void			validate_and_add_walls(char ***map, t_map_size *map_size,
					t_data *data);

char			*extract_path(char *line, int i);
void			add_path_textures(t_data *data);
bool			check_line_text(t_data *data, char *line, int *i);
int				parse_color_component(char **str, size_t *rgb_lenght,
					bool last);

void			init_ray_direction(t_ray *ray, t_player *p, int x);
void			init_ray_delta(t_ray *ray);
void			init_ray_step(t_ray *ray, t_player *p);
void			calculate_wall_dimensions(t_wall_calc *calc, t_ray *ray);
void			draw_wall_line(t_data *data, t_ray *ray, t_player *p, int x);
t_teximg		*get_wall_texture(t_data *data, t_ray *ray);
unsigned int	get_texel(t_teximg *tex, int x, int y);

void			draw_wall(t_data *data, t_player *p);
void			draw_background(t_data *data, int width, int height);
void			put_pixel(t_data *data, int x, int y, int color);
int				create_rgb(int r, int g, int b);

void			move_forward(t_data *data, double speed);
void			move_backward(t_data *data, double speed);
void			move_left(t_data *data, double speed);
void			move_right(t_data *data, double speed);

void			rotate_direction(t_player *p, double rotSpeed);
void			rotate_plane(t_player *p, double rotSpeed);
void			rotate_left(t_data *data);
void			rotate_right(t_data *data);

int				mouse_move(int x, int y, t_data *data);
void			process_movement(t_data *data);
int				key_release(int keycode, t_data *data);
int				key_press(int keycode, t_data *data);
int				close_window(t_data *data);

void			minimap(t_data *data);

void			exit_program(t_data *data, t_error error);
void			print_error(t_error error);
void			free_all(t_data *data);
void			free_map(char **map);
void			free_int_map_on_error(int **int_map, int lines_allocated);

#endif