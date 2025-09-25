/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:55:46 by fguerra           #+#    #+#             */
/*   Updated: 2025/07/31 19:55:54 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_texture	*select_texture(t_game *game, int side)
{
	if (side == 0 && game->ray_dir.x > 0)
		return (&game->textures[EAST]);
	else if (side == 0 && game->ray_dir.x <= 0)
		return (&game->textures[WEST]);
	else if (side == 1 && game->ray_dir.y > 0)
		return (&game->textures[SOUTH]);
	else
		return (&game->textures[NORTH]);
}

double	get_step(int tex_height, int line_height)
{
	return (1.0 * tex_height / line_height);
}

double	get_initial_tex_pos(int start, int line_height)
{
	return ((start - HEIGHT / 2 + line_height / 2)
		* get_step(1, line_height));
}

void	draw_texture_column(t_game *game, t_draw_tex draw)
{
	int		y;
	int		tex_y;
	int		color;
	double	tex_pos;

	tex_pos = draw.tex_pos;
	y = draw.start;
	while (y < draw.end)
	{
		tex_y = (int)tex_pos;
		tex_pos += draw.step;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= draw.texture->height)
			tex_y = draw.texture->height - 1;
		color = ((int *)draw.texture->data)[tex_y * draw.texture->width
			+ draw.tex_x];
		put_pixel(game, draw.x, y, color);
		y++;
	}
}
