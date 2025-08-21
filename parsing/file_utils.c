/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkunnath <nkunnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:13:36 by mnazar            #+#    #+#             */
/*   Updated: 2025/08/18 13:19:32 by nkunnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	print_error(char *str)
{
	if (str)
	{
		write(2, str, ft_strlen(str));
		return (1);
	}
	return (0);
}

int	check_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	close(fd);
	return (0);
}

int	get_file_size(char *file)
{
	int		fd;
	int		size;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	size = 0;
	line = get_next_line(fd);
	while (line)
	{
		size++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (size);
}

int	read_file_array(char *file, t_map *map, t_vars vars, int size)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		map->cmap[vars.i] = line;
		vars.i++;
		line = get_next_line(fd);
	}
	map->cmap[vars.i] = NULL;
	close(fd);
	if (vars.i != size)
	{
		fr_array(map->cmap);
		return (1);
	}
	return (0);
}
