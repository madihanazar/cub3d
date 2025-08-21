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


void	check_counts(char c, t_elements *elem)
{
	if (c == 'F')
		elem->floor_count += 1;
	if (c == 'C')
		elem->ceil_count += 1;
}

int	check_map_space(t_map *map, int i, int j)
{
	if ((j + 1 < (int)(ft_strlen(map->map[i])) && map->map[i][j + 1]
	&& check_eastside(map, i, j)) ||
	(j > 0 && map->map[i][j - 1] 
	&& check_westside(map, i, j)) ||
	(i + 1 < (map->rows) && j < (int)ft_strlen(map->map[i + 1]) && map->map[i + 1] 
	&& check_southside(map, i, j)) ||
	(i > 0 && j < (int)ft_strlen(map->map[i - 1]) && map->map[i - 1] &&
	check_northside(map, i, j)))
		return (0);
	return (1);
}

int	validate_spaces(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	while (map->map[i])
	{
		j = 1;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
			{
				if (check_map_space(map, i, j) == 0)
					return (print_error("Error: Space is not closed\n"));
			}
			j++;
		}
		i++;
	}
	return (0);
}
