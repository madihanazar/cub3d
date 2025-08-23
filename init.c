/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:45:42 by mnazar            #+#    #+#             */
/*   Updated: 2025/08/13 22:45:42 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	ft_bzero(&data->elements, sizeof(t_elements));
	ft_bzero(&data->map, sizeof(t_map));
	ft_bzero(&data->mlx, sizeof(t_mlx));
	ft_bzero(&data->player, sizeof(t_player));
	ft_bzero(&data->ray, sizeof(t_ray));
	ft_bzero(&data->image, sizeof(t_image));
	ft_bzero(&data->texture, sizeof(t_textures));
	ft_bzero(data->keys, 7);
}

void	init_vars(t_vars *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->k = 0;
}

void	xpm_to_image(t_data *data)
{
	data->texture.no.img = mlx_xpm_file_to_image(data->mlx.mlx,
			data->elements.no, &data->texture.no.width,
			&data->texture.no.height);
	data->texture.so.img = mlx_xpm_file_to_image(data->mlx.mlx,
			data->elements.so, &data->texture.so.width,
			&data->texture.so.height);
	data->texture.we.img = mlx_xpm_file_to_image(data->mlx.mlx,
			data->elements.we, &data->texture.we.width,
			&data->texture.we.height);
	data->texture.ea.img = mlx_xpm_file_to_image(data->mlx.mlx,
			data->elements.ea, &data->texture.ea.width,
			&data->texture.ea.height);
	if (data->texture.no.img == NULL || data->texture.so.img == NULL
		|| data->texture.we.img == NULL || data->texture.ea.img == NULL)
	{
		printf("Error: mlx_xpm_file_to_image failed\n");
		destroy_image(data);
		free(data->mlx.mlx);
		free_data(data);
		exit(1);
	}
}

void	init_texture(t_data *data)
{
	xpm_to_image(data);
	data->texture.no.addr = mlx_get_data_addr(data->texture.no.img,
			&data->texture.no.bpp, &data->texture.no.line_len,
			&data->texture.no.endian);
	data->texture.so.addr = mlx_get_data_addr(data->texture.so.img,
			&data->texture.so.bpp, &data->texture.so.line_len,
			&data->texture.so.endian);
	data->texture.we.addr = mlx_get_data_addr(data->texture.we.img,
			&data->texture.we.bpp, &data->texture.we.line_len,
			&data->texture.we.endian);
	data->texture.ea.addr = mlx_get_data_addr(data->texture.ea.img,
			&data->texture.ea.bpp, &data->texture.ea.line_len,
			&data->texture.ea.endian);
}

void	init_player(t_data *data)
{
	data->player.posX = data->map.p_x + 0.5;
	data->player.posY = data->map.p_y + 0.5;
	if (data->map.direction == 'N')
	{
		data->player.dirY = -1;
		data->player.planeX = 0.66;
	}
	else if (data->map.direction == 'S')
	{
		data->player.dirY = 1;
		data->player.planeX = -0.66;
	}
	else if (data->map.direction == 'W')
	{
		data->player.dirX = -1;
		data->player.planeY = -0.66;
	}
	else if (data->map.direction == 'E')
	{
		data->player.dirX = 1;
		data->player.planeY = 0.66;
	}
}