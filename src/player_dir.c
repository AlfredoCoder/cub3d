/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:35:22 by fguerra           #+#    #+#             */
/*   Updated: 2025/08/01 16:35:29 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_north(t_game *game)
{
	game->dir.x = 0;
	game->dir.y = -1;
	game->plane.x = 0.66;
	game->plane.y = 0;
}

void	set_south(t_game *game)
{
	game->dir.x = 0;
	game->dir.y = 1;
	game->plane.x = -0.66;
	game->plane.y = 0;
}

void	set_east(t_game *game)
{
	game->dir.x = 1;
	game->dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
}

void	set_west(t_game *game)
{
	game->dir.x = -1;
	game->dir.y = 0;
	game->plane.x = 0;
	game->plane.y = -0.66;
}

void	set_player_dir_and_plane(t_game *game, char dir)
{
	if (dir == 'N')
		set_north(game);
	else if (dir == 'S')
		set_south(game);
	else if (dir == 'E')
		set_east(game);
	else if (dir == 'W')
		set_west(game);
}
