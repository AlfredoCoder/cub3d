/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validation2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 06:26:00 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 06:26:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	validate_player(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		free_game_and_exit(game, "Deve haver exatamente um jogador no mapa");
}

int	check_rgb_value(char *str, int *pos)
{
	int	value;
	int	i;

	value = 0;
	i = *pos;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		if (value > 255)
			return (-1);
		i++;
	}
	*pos = i;
	return (value);
}

void	validate_map(t_game *game)
{
	if (!game->lmap || game->map_height <= 0)
		free_game_and_exit(game, "Mapa vazio ou inválido");
	if (game->floor_color == -1 || game->ceiling_color == -1)
		free_game_and_exit(game, "Cores do chão (F) e teto (C) obrigatórias");
	if (!game->texture_paths[NORTH] || !game->texture_paths[SOUTH]
		|| !game->texture_paths[EAST] || !game->texture_paths[WEST])
		free_game_and_exit(game, "Todas as texturas devem ser definidas");
	validate_walls(game);
	validate_player(game);
}
