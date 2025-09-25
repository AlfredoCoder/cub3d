/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:31:01 by fguerra           #+#    #+#             */
/*   Updated: 2025/08/01 16:31:28 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_coord	get_player_position(t_game *game)
{
	int		x;
	int		y;
	char	dir;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			dir = game->map[y][x];
			if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
			{
				game->player_pos.x = x + 0.5;
				game->player_pos.y = y + 0.5;
				set_player_dir_and_plane(game, dir);
				return (game->player_pos);
			}
			x++;
		}
		y++;
	}
	game->player_pos.x = 0;
	game->player_pos.y = 0;
	return (game->player_pos);
}
