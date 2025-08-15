/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:14:44 by mnazar            #+#    #+#             */
/*   Updated: 2025/08/13 23:14:44 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	store_tex(t_elements *elem, char *trim, char **arr)
{
	if (ft_strncmp(arr[0], "NO", 3) == 0)
		return (assign_tex(&elem->no, trim));
	else if (ft_strncmp(arr[0], "SO", 3) == 0)
		return (assign_tex(&elem->so, trim));
	else if (ft_strncmp(arr[0], "WE", 3) == 0)
		return (assign_tex(&elem->we, trim));
	else if (ft_strncmp(arr[0], "EA", 3) == 0)
		return (assign_tex(&elem->ea, trim));
	return (1);
}

int	assign_tex(char **tex, char *trim)
{
	if (*tex)
		return (1);
	*tex = ft_strdup(trim);
	if (*tex)
		return (0);
	return (1);
}

int	parse_elements(t_elements *elem, t_map *map, t_vars *vars)
{
	while (map->cmap[vars->i] && elem->all_parsed < 6)
	{
		if (only_spaces(map->cmap[vars->i]))
		{
			if (store_elem(elem, map->cmap[vars->i]) == 0)
				elem->all_parsed++;
			else
				return (print_error("Error: Invalid/Missing element\n"));
		}
		vars->i++;
	}
	if (elem->all_parsed < 6)
		return (print_error("Error: Missing elements\n"));
	while (map->cmap[vars->i] && !only_spaces(map->cmap[vars->i]))
		vars->i++;
	if (store_map(map, vars->i))
		return (1);
	return (0);
}

int	parse_map(char *argv, t_data *data)
{
	t_map		*map;
	t_elements	*elements;
	t_vars		vars;
	int			size;

	init_vars(&vars);
	map = &data->map;
	elements = &data->elements;
	if (check_file(argv))
		return (1);
	size = get_file_size(argv);
	if (size == 0)
		return (file_error(0));
	map->cmap = ft_calloc(size + 1, sizeof(char *));
	if (!map->cmap)
		return (print_error("Error: Malloc\n"));
	if (read_file_array(argv, map, vars))
		return (print_error("Error has occurred\n"));
	if (parse_elements(elements, map, &vars))
		return (1);
	if (validate_map(map))
		return (1);
	return (0);
}
