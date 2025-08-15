/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:50:40 by mnazar            #+#    #+#             */
/*   Updated: 2025/08/13 22:50:40 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void fr_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_data(t_data *data)
{
	free(data->map.fullcub);
	if (data->map.cmap)
		fr_array(data->map.cmap);
	if (data->map.map)
		fr_array(data->map.map);
	free(data->elements.no);
	free(data->elements.so);
	free(data->elements.we);
	free(data->elements.ea);
}

void	destroy_image(t_data *data)
{
	if (data->texture.no.img)
		mlx_destroy_image(data->mlx.mlx, data->texture.no.img);
	if (data->texture.so.img)
		mlx_destroy_image(data->mlx.mlx, data->texture.so.img);
	if (data->texture.we.img)
		mlx_destroy_image(data->mlx.mlx, data->texture.we.img);
	if (data->texture.ea.img)
		mlx_destroy_image(data->mlx.mlx, data->texture.ea.img);
}