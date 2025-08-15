#include "cub3d.h"

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char    *pixel;

    pixel = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
    *(unsigned int *)pixel = color;
}

void draw_walls(t_game *game)
{
    int x;

    for (x = 0; x < WIN_WIDTH; x++)
    {
        // Calculate ray position and direction
        double cameraX = 2 * x / (double)WIN_WIDTH - 1; // x-coordinate in camera space
        double rayDirX = game->dirX + game->planeX * cameraX;
        double rayDirY = game->dirY + game->planeY * cameraX;

        // Which box of the map we're in
        int mapX = (int)game->posX;
        int mapY = (int)game->posY;

        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        // Length of ray from one side to next in map
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        // Step direction and initial sideDist
        int stepX;
        int stepY;

        int hit = 0; // Was a wall hit?
        int side;    // Was a NS or EW wall hit?

        // Calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0)
        {
            // Jump to next map square
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray hit a wall
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        // Calculate distance projected on camera direction (perpendicular distance)
        if (side == 0)
            perpWallDist = (mapX - game->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - game->posY + (1 - stepY) / 2) / rayDirY;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

        // Choose wall color
        int color = RED; // red walls
        if (side == 1) color = DARKRED; // darker red for NS walls

        // Draw the vertical line
        for (int y = drawStart; y <= drawEnd; y++)
            my_mlx_pixel_put(game, x, y, color);
    }
}

void draw_background(t_game *game)
{
    int x, y;

    // Draw sky (top half)
    for (y = 0; y < WIN_HEIGHT / 2; y++)
    {
        for (x = 0; x < WIN_WIDTH; x++)
            my_mlx_pixel_put(game, x, y, SKYBLUE);  // light blue
    }
    // Draw floor (bottom half)
    for (y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
    {
        for (x = 0; x < WIN_WIDTH; x++)
            my_mlx_pixel_put(game, x, y, GREEN); // forest green
    }
}


int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		close_game(game);
	    // Move forward
    if (keycode == 119) // W
    {
        double newX = game->posX + game->dirX * MOVE_SPEED;
        double newY = game->posY + game->dirY * MOVE_SPEED;
        if (worldMap[(int)newX][(int)(game->posY)] == 0)
            game->posX = newX;
        if (worldMap[(int)(game->posX)][(int)newY] == 0)
            game->posY = newY;
    }

    // Move backward
    if (keycode == 115) // S
    {
        double newX = game->posX - game->dirX * MOVE_SPEED;
        double newY = game->posY - game->dirY * MOVE_SPEED;
        if (worldMap[(int)newX][(int)(game->posY)] == 0)
            game->posX = newX;
        if (worldMap[(int)(game->posX)][(int)newY] == 0)
            game->posY = newY;
    }

    // Strafe right
    if (keycode == 100) // D
    {
        double newX = game->posX + game->dirY * MOVE_SPEED;
        double newY = game->posY - game->dirX * MOVE_SPEED;
        if (worldMap[(int)newX][(int)(game->posY)] == 0)
            game->posX = newX;
        if (worldMap[(int)(game->posX)][(int)newY] == 0)
            game->posY = newY;
    }

    // Strafe left
    if (keycode == 97) // A
    {
        double newX = game->posX - game->dirY * MOVE_SPEED;
        double newY = game->posY + game->dirX * MOVE_SPEED;
        if (worldMap[(int)newX][(int)(game->posY)] == 0)
            game->posX = newX;
        if (worldMap[(int)(game->posX)][(int)newY] == 0)
            game->posY = newY;
    }

    // Rotate left
    if (keycode == 65361) // Left arrow
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(ROT_SPEED) - game->dirY * sin(ROT_SPEED);
        game->dirY = oldDirX * sin(ROT_SPEED) + game->dirY * cos(ROT_SPEED);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(ROT_SPEED) - game->planeY * sin(ROT_SPEED);
        game->planeY = oldPlaneX * sin(ROT_SPEED) + game->planeY * cos(ROT_SPEED);
    }

    // Rotate right
    if (keycode == 65363) // Right arrow
    {
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(-ROT_SPEED) - game->dirY * sin(-ROT_SPEED);
        game->dirY = oldDirX * sin(-ROT_SPEED) + game->dirY * cos(-ROT_SPEED);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(-ROT_SPEED) - game->planeY * sin(-ROT_SPEED);
        game->planeY = oldPlaneX * sin(-ROT_SPEED) + game->planeY * cos(-ROT_SPEED);
    }

    // After updating position and direction, redraw the scene
    draw_background(game);
    draw_walls(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

	return (0);
}

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

// int	main(void)
// {
// 	t_game	game;

// 	game.mlx = mlx_init();
// 	if (!game.mlx)
// 		return (1);
// 	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
// 	if (!game.win)
// 		return (1);

// 	game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
//     game.addr = mlx_get_data_addr(game.img, &game.bits_per_pixel,
//                                  &game.line_length, &game.endian);
// 	game.posX = 22.0;
//     game.posY = 12.0;
//     game.dirX = -1.0;
//     game.dirY = 0.0;
//     game.planeX = 0.0;
//     game.planeY = 0.66;

// 	draw_background(&game);
// 	draw_walls(&game);
// 	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	
// 	mlx_hook(game.win, 17, 0, close_game, &game); // Window close button
// 	mlx_key_hook(game.win, key_press, &game);     // Keyboard input

// 	mlx_loop(game.mlx);
// 	return (0);
// }

