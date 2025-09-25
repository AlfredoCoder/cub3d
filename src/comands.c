/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:41:54 by fguerra           #+#    #+#             */
/*   Updated: 2025/07/31 16:41:56 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_handler(int keyboard, t_game *game)
{
	(void)game;
	if (keyboard == W)
		game->comands.key_w = true;
	else if (keyboard == A)
		game->comands.key_a = true;
	else if (keyboard == S)
		game->comands.key_s = true;
	else if (keyboard == D)
		game->comands.key_d = true;
	else if (keyboard == LEFT)
		game->comands.key_left = true;
	else if (keyboard == RIGHT)
		game->comands.key_right = true;
	else if (keyboard == UP)
		game->comands.key_up = true;
	else if (keyboard == DOWN)
		game->comands.key_down = true;
	else if (keyboard == ESC_KEY)
		game->comands.esc_key = true;
	return (0);
}

int	restart_key(int keyboard, t_game *game)
{
	(void)game;
	if (keyboard == W)
		game->comands.key_w = false;
	else if (keyboard == A)
		game->comands.key_a = false;
	else if (keyboard == S)
		game->comands.key_s = false;
	else if (keyboard == D)
		game->comands.key_d = false;
	else if (keyboard == LEFT)
		game->comands.key_left = false;
	else if (keyboard == RIGHT)
		game->comands.key_right = false;
	else if (keyboard == UP)
		game->comands.key_up = false;
	else if (keyboard == DOWN)
		game->comands.key_down = false;
	else if (keyboard == ESC_KEY)
		game->comands.esc_key = false;
	return (0);
}
