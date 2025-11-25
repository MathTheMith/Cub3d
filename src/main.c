

#include "cub.h"
#include <sys/time.h>

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int update_fps(void)
{
    static size_t last_time = 0;
    static int frame_count = 0;
    static int fps = 0;

    size_t current_time = get_current_time();
    frame_count++;

    if (current_time - last_time >= 1000)
    {
        fps = frame_count;
        frame_count = 0;
        last_time = current_time;
        printf("FPS: %d\n", fps);
    }
    return fps;
}

void minimap(t_data *data)
{
	int m_y = 0;
	int m_x = 0;
	int size = SCREEN_W / 5;
	while(m_x < size)
	{
		m_y = 0;
		while (m_y < size)
		{
			put_pixel(data, m_x, m_y, 0xFF99FF);
			m_y++;
		}
		m_x++;
	}
	int size_p = 10;
	m_x = SCREEN_W / 10 - size_p;
	m_y = SCREEN_W / 10 - size_p;
	size = SCREEN_W / 10 + size_p;
	while(m_x < size)
	{
		m_y = SCREEN_W / 10 - size_p;
		while (m_y < size)
		{
			put_pixel(data, m_x, m_y, 0x000000FF);
			m_y++;
		}
		m_x++;
	}
}

static int render_loop(t_data *data)
{
    static long last_time = 0;
    struct timeval tv;
    long now;
	int f_time;

	f_time = 1000000 / 60;
    gettimeofday(&tv, NULL);
    now = tv.tv_sec * 1000000 + tv.tv_usec;
    if (now - last_time < f_time)
        return (0);
    last_time = now;
	update_fps();
    process_movement(data);
	draw_background(data, SCREEN_W, SCREEN_H);
    draw_wall(data, &data->p);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}

void	game_loop(t_data *data)
{
	init_window(data);
	mlx_mouse_hide(data->mlx, data->win);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 6, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->mlx, render_loop, data);
	mlx_loop(data->mlx);
}

int main(int ac, char **av)
{
	t_data		data;
	t_map_size	map_size;

	ft_memset(&data, 0, sizeof(t_data));
	ft_memset(&map_size, 0, sizeof(t_map_size));

	data.mlx = mlx_init();
	if (!data.mlx)
		exit_program(&data, E_mlx_env);
	parsing(ac, av, &data, &map_size);
	init_struct(&data, &map_size, &data.char_map);
	print_int_map(data.map, &data.map_size);
	game_loop(&data);
	return (0);
}
