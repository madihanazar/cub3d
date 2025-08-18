/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:45:51 by mnazar            #+#    #+#             */
/*   Updated: 2025/08/17 17:45:51 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_rays(t_ray *ray, t_player *player, t_data *data)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray_delta(ray, player, x);
		init_step_side(ray, player, data);
		dda_algo(ray, data);
		check_ray_side(ray, player);
		draw_walls(ray, data, x);
		x++;
	}
}