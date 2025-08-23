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

int	assign_tex(char **tex, char *trim)
{
	*tex = ft_strdup(trim);
	if (*tex)
		return (0);
	return (print_error("Error: Strdup failure\n"));
}

int	store_tex(t_elements *elem, char *trim, char **arr)
{
	if (ft_strncmp(arr[0], "NO", 3) == 0)
	{
		elem->no_count += 1;
		return (assign_tex(&elem->no, trim));
	}
	else if (ft_strncmp(arr[0], "SO", 3) == 0)
	{
		elem->so_count += 1;
		return (assign_tex(&elem->so, trim));
	}
	else if (ft_strncmp(arr[0], "WE", 3) == 0)
	{
		elem->we_count += 1;
		return (assign_tex(&elem->we, trim));
	}
	else if (ft_strncmp(arr[0], "EA", 3) == 0)
	{
		elem->ea_count += 1;
		return (assign_tex(&elem->ea, trim));
	}
	return (1);
}

int	parse_elements(t_elements *elem, t_map *map, t_vars vars)
{
	while (map->cmap[vars.i] != NULL)
	{
		if (!only_spaces(map->cmap[vars.i]))
		{
			if (store_elem(elem, map->cmap[vars.i]) == 0)
				elem->all_parsed += 1;
			else
			{
				while (map->cmap[vars.i][vars.j])
				{
					if (ft_strchr("1\r\n ", map->cmap[vars.i][vars.j]) == NULL) //remove \r only for windows
						return (print_error("Error: Issue with .cub\n"));
					vars.j += 1;
				}
				break ;
			}
		}
		vars.i += 1;
	}
	if (elem->no_count != 1 || elem->so_count != 1 || elem->ea_count != 1 
		|| elem->we_count != 1 || elem->ceil_count != 1 || elem->floor_count != 1 || elem->all_parsed != 6)
		return (print_error("Error: Incomplete .cub file\n"));
	if (store_map(map, vars.i))
		return (1);
	return (0);
}

int	parse_map(char *argv, t_data *data)
{
	t_map		*map;
	t_vars		vars;
	int			size;
	t_elements	*elems;

	init_vars(&vars);
	map = &data->map;
	elems = &data->elements;
	if (check_file(argv))
		return (1);
	size = get_file_size(argv);
	if (size == 0)
		return (printf("File is empty\n"), 1);
	map->cmap = ft_calloc(size + 1, sizeof(char *));
	if (!map->cmap)
		return (print_error("Error: During Map Malloc\n"));
	if (read_file_array(argv, map, vars, size) == 1)
		return (print_error("Error: During CMap creation\n"));
	if (parse_elements(elems, map, vars) == 1)
		return (1);
	if (validate_map(map) == 1)
		return (1);
	return (0);
}
