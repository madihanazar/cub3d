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

// void	init_start_game(t_data *data)
// {
// 	gettimeofday(&data->last, NULL);
// 	data->mlx.mlx = mlx_init();
// 	if (!data->mlx.mlx)
// 	{
// 		printf("Error: mlx_init failed\n");
// 		free_data(data);
// 		exit(1);
// 	}
// 	init_texture(data);
// 	data->mlx.win = mlx_new_window(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
// 			"cub3D");
// 	if (!data->mlx.win)
// 	{
// 		printf("Error: mlx_new_window failed\n");
// 		destroy_image(data);
// 		free(data->mlx.mlx);
// 		free_data(data);
// 		exit(1);
// 	}
// 	data->image.img = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
// 	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp,
// 			&data->image.line_len, &data->image.endian);
// 	init_player(data);
// 	mlx_loops_hooks(data);
// }

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
	//init_start_game(&data);
	free_data(&data); //check
}
