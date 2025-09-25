/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 07:46:00 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 07:46:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	handle_floor_color(t_game *game, char *line)
{
	int	color;

	if (game->floor_color != -1)
		return (-7);
	color = parse_rgb(line + 2);
	if (color < 0)
		return (-2);
	game->floor_color = color;
	return (0);
}

int	handle_ceiling_color(t_game *game, char *line)
{
	int	color;

	if (game->ceiling_color != -1)
		return (-8);
	color = parse_rgb(line + 2);
	if (color < 0)
		return (-3);
	game->ceiling_color = color;
	return (0);
}
