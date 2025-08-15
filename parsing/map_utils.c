/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:23:37 by mnazar            #+#    #+#             */
/*   Updated: 2025/08/14 10:23:37 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_map_rows(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
		i++;
	map->rows = i;
}

int	top_bot_row(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (0);
		line++;
	}
	return (1);
}

int	only_spaces(char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '\0')
		return (0);
	return (1);
}

int	check_multiple_commas(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (!str[i + 1] || (str[i + 1] && str[i + 1] == ','))
				return (-1);
		}
		i++;
	}
	return (0);
}

void	free_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}
