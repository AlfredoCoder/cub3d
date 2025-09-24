/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:03:32 by fguerra           #+#    #+#             */
/*   Updated: 2025/04/03 21:03:35 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render(t_game *game)
{
	double perpWallDist;
	double cameraX;
	int mapX;
	int mapY;
	double deltaDistX;
	double deltaDistY;
	double sideDistX;
	double sideDistY;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int pixel;
	int stepX;
	int stepY;
	int side;
	int hit;

	clear_img(game);
	pixel = 0;
	while (pixel < WIDTH)
	{
		cameraX = 2 * pixel / (double)WIDTH - 1;
		game->rayDir.x = game->dir.x + game->plane.x * cameraX;
		game->rayDir.y = game->dir.y + game->plane.y * cameraX;
		mapX = (int)game->player_pos.x;
		mapY = (int)game->player_pos.y;
		deltaDistX = fabs(1 / game->rayDir.x);
		deltaDistY = fabs(1 / game->rayDir.y);
		if (game->rayDir.x < 0)
		{
			stepX = -1;
			sideDistX = (game->player_pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player_pos.x) * deltaDistX;
		}

		if (game->rayDir.y < 0)
		{
			stepY = -1;
			sideDistY = (game->player_pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player_pos.y) * deltaDistY;
		}
		hit = 0;
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				side = 0;
				sideDistX += deltaDistX;
				mapX += stepX;
			}
			else
			{
				side = 1;
				sideDistY += deltaDistY;
				mapY += stepY;
			}

			if (game->map[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = sideDistX - deltaDistX;
		else
			perpWallDist = sideDistY - deltaDistY;
		lineHeight = HEIGHT / perpWallDist;
		drawStart = (HEIGHT - lineHeight) / 2;
		drawEnd = lineHeight + drawStart;
		draw_wall(game, pixel, drawStart, drawEnd, side, perpWallDist);
		pixel++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}