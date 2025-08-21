/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkunnath <nkunnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:14:44 by mnazar            #+#    #+#             */
/*   Updated: 2025/08/19 17:28:11 by nkunnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_eastside(t_map *map, int i, int j)
{
	if (map->map[i][j + 1] != '1' && map->map[i][j + 1] != ' ')
		return (1);
	return (0);
}

int	check_southside(t_map *map, int i, int j)
{
	if (map->map[i + 1][j] != '1' && map->map[i + 1][j] != ' ')
		return (1);
	return (0);
}

int	check_northside(t_map *map, int i, int j)
{
	if (map->map[i - 1][j] != '1' && map->map[i - 1][j] != ' ')
		return (1);
	return (0);
}

int	check_westside(t_map *map, int i, int j)
{
	if (map->map[i][j - 1] != '1' && map->map[i][j - 1] != ' ') 
		return (1);
	return (0);
}