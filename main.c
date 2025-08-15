/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:45:09 by mnazar            #+#    #+#             */
/*   Updated: 2025/08/13 22:45:09 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **argv)
{
	t_data	data;

	if (ac != 2)
	{
		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		printf("Error: Invalid file extension\n");
		return (1);
	}
	init_data(&data);
	if (parse_map(argv[1], &data))
	{
		free_data(&data);
		return (1);
	}
	//start game
	free_data(&data);
}
