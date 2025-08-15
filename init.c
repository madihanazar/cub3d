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
	//ft_bzero(data->keys, 7);
}

void	init_vars(t_vars *vars)
{
	vars->i = 0;
	vars->j = 0;
	vars->k = 0;
}