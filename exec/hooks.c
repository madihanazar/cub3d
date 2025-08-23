/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:03:17 by mnazar            #+#    #+#             */
/*   Updated: 2025/08/22 22:24:05 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	render_frames(t_data *data)
{
	struct timeval	current;

	ft_bzero(data->image.addr, WIN_WIDTH * WIN_HEIGHT * (data->image.bpp / 8));
	gettimeofday(&current, NULL);
	data->delta_time = (current.tv_sec - data->last.tv_sec) + (current.tv_usec
			- data->last.tv_usec) * 1e-6;
	if (data->delta_time > 0.1)
		data->delta_time = 0.1;
	data->last = current;
	check_movement(data);
	colour_floor_ceiling(data);
	cast_rays(&data->ray, &data->player, data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->image.img, 0,
		0);
	return (0);
}

int	exit_window(t_data *data)
{
	destroy_image(data);
	if (data->image.img)
		mlx_destroy_image(data->mlx.mlx, data->image.img);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	free(data->mlx.mlx);
	free_data(data);
	exit(0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->keys[0] = 1;
	if (keycode == S_KEY)
		data->keys[1] = 1;
	if (keycode == A_KEY)
		data->keys[2] = 1;
	if (keycode == D_KEY)
		data->keys[3] = 1;
	if (keycode == LEFT_ARROW)
		data->keys[4] = 1;
	if (keycode == RIGHT_ARROW)
		data->keys[5] = 1;
	if (keycode == ESC_KEY)
		exit_window(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->keys[0] = 0;
	if (keycode == S_KEY)
		data->keys[1] = 0;
	if (keycode == A_KEY)
		data->keys[2] = 0;
	if (keycode == D_KEY)
		data->keys[3] = 0;
	if (keycode == LEFT_ARROW)
		data->keys[4] = 0;
	if (keycode == RIGHT_ARROW)
		data->keys[5] = 0;
	return (0);
}

void    mlx_loops_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx.win, 17, 0, exit_window, data);
	mlx_loop_hook(data->mlx.mlx, render_frames, data);
	mlx_loop(data->mlx.mlx);
}