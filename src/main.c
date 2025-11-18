

#include "cub.h"
#include <X11/keysym.h>

int close_window(t_data *data)
{
    exit_program(data, No_error);
    return (0);
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == XK_Escape)
        close_window(data);
    if (keycode == XK_w)
        move_forward(data);
    if (keycode == XK_s)
        move_backward(data);
    if (keycode == XK_a)
        move_left(data);
    if (keycode == XK_d)
        move_right(data);
    if (keycode == XK_Left)
        rotate_left(data);
    if (keycode == XK_Right)
        rotate_right(data);
    return (0);
}

int loop_hook(t_data *data)
{
    draw_background(data, 1500, 1000);
    draw_wall(data, &data->p);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    printf("%.4f %.4f\n", data->p.p_x, data->p.p_y);
    return 0;
}

int main(int ac, char **av)
{
    t_data data;
    t_map_size map_size;
    
    ft_memset(&data, 0, sizeof(t_data));
    data.mlx = mlx_init();
    if (data.mlx == NULL)
        exit_program(&data, E_mlx_env);
    parsing(ac, av, &data);
    init_struct(&data, &map_size, av[1]);
    if (!check_map(&data, &map_size))
        exit_program(&data, E_map);
    init_window(&data);
    mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_loop_hook(data.mlx, loop_hook, &data);
    mlx_loop(data.mlx);
    return 0;
}
