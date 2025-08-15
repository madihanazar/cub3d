/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:13:36 by mnazar            #+#    #+#             */
/*   Updated: 2025/08/13 23:13:36 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"	

int	file_error(int id)
{
	if (id == 0)
		printf("Error has occurred\n");
	return (1);
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
	char	*line;
	int		size;

	fd = open(file, O_RDONLY);
	if (fd == -1)
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

int	print_error(char *str)
{
	if (str)
	{
		write(2, str, ft_strlen(str));
		return (1);
	}
	return (0);
}

int	read_file_array(char *file, t_map *map, t_vars var)
{
	int		fd;
	char	*line;

	init_vars(&var);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		map->cmap[var.i] = line;
		var.i++;
		line = get_next_line(fd);
	}
	map->cmap[var.i] = NULL;
	close(fd);
	return (0);
}
