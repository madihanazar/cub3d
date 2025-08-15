/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:14:29 by mnazar            #+#    #+#             */
/*   Updated: 2025/08/14 10:14:29 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	validate_map_chars(t_map *map, t_vars vars)
{
	while (map->map[vars.i])
	{
		vars.j = 0;
		while (map->map[vars.i][vars.j])
		{
			if (ft_strchr("01NSEW ", map->map[vars.i][vars.j]) == NULL)
				return (print_error("Error: Invalid character in map\n"));
			if (ft_strchr("NSEW", map->map[vars.i][vars.j]))
			{
				if (vars.k)
					return (print_error("Error: Multiple players\n"));
				map->p_x = vars.j;
				map->p_y = vars.i;
				map->direction = map->map[vars.i][vars.j];
				vars.k++;
			}
			vars.j++;
		}
		vars.i++;
	}
	if (!vars.k)
		return (print_error("Error: No player\n"));
	return (0);
}

int	validate_map_walls(t_map *map, t_vars vars)
{
	int	i;

	i = 0;
	if (!top_bot_row(map->map[0]) || !top_bot_row(map->map[map->rows - 1]))
		return (print_error("Error: Border is not closed\n"));
	while (++i < map->rows -1)
	{
		vars.k = ft_strlen(map->map[i]);
		vars.j = 0;
		while (map->map[i][vars.j] == ' ')
			vars.j++;
		if (map->map[i][vars.j] == '\0')
		{
			i++;
			continue ;
		}
		if (map->map[i][vars.j] != '1')
			return (print_error("Error: Right border is not closed\n"));
		vars.j = vars.k - 1;
		while (vars.j >= 0 && map->map[i][vars.j] == ' ')
			vars.j--;
		if (map->map[i][vars.j] != '1')
			return (print_error("Error: Left border is not closed\n"));
	}
	return (0);
}

int	check_neighbours(t_map *map, int i, int j)
{
	int	rlen;

	rlen = (int)ft_strlen(map->map[i]);
	if (i <= 0 || i >= map->rows - 1 || j <= 0 || j >= rlen - 1)
		return (0);
	if (j + 1 >= rlen || map->map[i][j + 1] == '\0'
		|| map->map[i][j + 1] == ' ')
		return (0);
	if (j - 1 < 0 || map->map[i][j - 1] == '\0' || map->map[i][j - 1] == ' ')
		return (0);
	if (i + 1 >= map->rows || j >= (int)ft_strlen(map->map[i + 1])
		|| map->map[i + 1][j] == '\0' || map->map[i + 1][j] == ' ')
		return (0);
	if (i - 1 < 0 || j >= (int)ft_strlen(map->map[i - 1])
		|| map->map[i - 1][j] == '\0' || map->map[i - 1][j] == ' ')
		return (0);
	return (1);
}

int	valid_zero_player(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	while (i < map->rows -1)
	{
		j = 1;
		while (j < (int)ft_strlen(map->map[i]) - 1)
		{
			if (map->map[i][j] == '0')
			{
				if (!check_neighbours(map, i, j))
					return (print_error("Error: Floor not enclosed\n"));
			}
			else if (map->map[i][j] == map->direction)
			{
				if (!check_neighbours(map, i, j))
					return (print_error("Error: Player not enclosed\n"));
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map(t_map *map)
{
	t_vars	vars;

	init_vars(&vars);
	if (validate_map_chars(map, vars))
		return (1);
	calculate_map_rows(map);
	init_vars(&vars);
	if (validate_map_walls(map, vars) || validate_spaces(map)
		|| valid_zero_player(map))
		return (1);
	return (0);
}
