/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moviment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:07:08 by fguerra           #+#    #+#             */
/*   Updated: 2025/08/01 16:07:40 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_wall(t_game *game, double x, double y)
{
	int	mapx;
	int	mapy;

	if (!game || !game->map || y < 0 || y >= game->map_height)
		return (1);
	mapy = (int)y;
	if (!game->map[mapy] || x < 0 || x >= (int)ft_strlen(game->map[mapy]))
		return (1);
	mapx = (int)x;
	return (game->map[mapy][mapx] == '1');
}

void	to_rotate(t_game *game, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->dir.x;
	game->dir.x = game->dir.x * cos(angle) - game->dir.y * sin(angle);
	game->dir.y = old_dirx * sin(angle) + game->dir.y * cos(angle);
	old_planex = game->plane.x;
	game->plane.x = game->plane.x * cos(angle) - game->plane.y * sin(angle);
	game->plane.y = old_planex * sin(angle) + game->plane.y * cos(angle);
}

void	to_forward(t_game *game)
{
	double	new_mapx;
	double	new_mapy;

	new_mapx = game->player_pos.x + game->dir.x * (SPEED + 0.04);
	new_mapy = game->player_pos.y + game->dir.y * (SPEED + 0.04);
	if (!is_wall(game, new_mapx, game->player_pos.y))
		game->player_pos.x = game->player_pos.x + game->dir.x * SPEED;
	if (!is_wall(game, game->player_pos.x, new_mapy))
		game->player_pos.y = game->player_pos.y + game->dir.y * SPEED;
}

void	to_backward(t_game *game)
{
	double	new_mapx;
	double	new_mapy;

	new_mapx = game->player_pos.x - game->dir.x * (SPEED + 0.04);
	new_mapy = game->player_pos.y - game->dir.y * (SPEED + 0.04);
	if (!is_wall(game, new_mapx, game->player_pos.y))
		game->player_pos.x = game->player_pos.x - game->dir.x * SPEED;
	if (!is_wall(game, game->player_pos.x, new_mapy))
		game->player_pos.y = game->player_pos.y - game->dir.y * SPEED;
}
