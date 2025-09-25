/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moviment_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:07:08 by fguerra           #+#    #+#             */
/*   Updated: 2025/08/01 16:07:40 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_to_right(t_game *game)
{
	double	new_mapx;
	double	new_mapy;
	double	perpx;
	double	perpy;

	perpx = -game->dir.y;
	perpy = game->dir.x;
	new_mapx = game->player_pos.x + perpx * (SPEED + 0.04);
	new_mapy = game->player_pos.y + perpy * (SPEED + 0.04);
	if (!is_wall(game, new_mapx, game->player_pos.y))
		game->player_pos.x = game->player_pos.x + perpx * SPEED;
	if (!is_wall(game, game->player_pos.x, new_mapy))
		game->player_pos.y = game->player_pos.y + perpy * SPEED;
}

void	move_to_left(t_game *game)
{
	double	new_mapx;
	double	new_mapy;
	double	perpx;
	double	perpy;

	perpx = game->dir.y;
	perpy = -game->dir.x;
	new_mapx = game->player_pos.x + perpx * (SPEED + 0.04);
	new_mapy = game->player_pos.y + perpy * (SPEED + 0.04);
	if (!is_wall(game, new_mapx, game->player_pos.y))
		game->player_pos.x = game->player_pos.x + perpx * SPEED;
	if (!is_wall(game, game->player_pos.x, new_mapy))
		game->player_pos.y = game->player_pos.y + perpy * SPEED;
}

void	rotate_to_left(t_game *game)
{
	to_rotate(game, -ROTATE_ANGLE);
}

void	rotate_to_right(t_game *game)
{
	to_rotate(game, +ROTATE_ANGLE);
}

void	input_key(t_game *game)
{
	if (game->comands.key_w == true)
		to_forward(game);
	else if (game->comands.key_s == true)
		to_backward(game);
	else if (game->comands.key_a == true)
		move_to_left(game);
	else if (game->comands.key_d == true)
		move_to_right(game);
	else if (game->comands.key_right == true)
		rotate_to_right(game);
	else if (game->comands.key_left == true)
		rotate_to_left(game);
	else if (game->comands.key_up == true)
		to_forward(game);
	else if (game->comands.key_down == true)
		to_backward(game);
	else if (game->comands.esc_key == true)
		close_game(game);
}
