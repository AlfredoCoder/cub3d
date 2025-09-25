/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:07:08 by fguerra           #+#    #+#             */
/*   Updated: 2025/08/01 16:07:40 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*print_pixel;

	if (!game || !game->addr || x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	print_pixel = game->addr + (y * game->size_line + x * (game->bpp / 8));
	*(int *)(print_pixel) = color;
}

void	draw_vertical(t_game *game, t_draw draw)
{
	if (draw.start_y < 0)
		draw.start_y = 0;
	if (draw.end > HEIGHT)
		draw.end = HEIGHT;
	while (draw.start_y < draw.end)
	{
		put_pixel(game, draw.x, draw.start_y, draw.color);
		draw.start_y++;
	}
}

void	clear_img(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(game, x, y, game->ceiling_color);
			else
				put_pixel(game, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}
