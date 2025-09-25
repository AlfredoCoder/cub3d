/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 06:17:00 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 06:17:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_game_map_data(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->map_height && game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
	if (game->lmap)
	{
		free_map_list(game->lmap);
		game->lmap = NULL;
	}
}

void	free_game_and_exit(t_game *game, const char *msg)
{
	if (msg)
		printf("%s\n", msg);
	get_next_line(-1);
	if (game->texture_paths[0])
		free(game->texture_paths[0]);
	if (game->texture_paths[1])
		free(game->texture_paths[1]);
	if (game->texture_paths[2])
		free(game->texture_paths[2]);
	if (game->texture_paths[3])
		free(game->texture_paths[3]);
	free_game_map_data(game);
	exit(EXIT_FAILURE);
}

void	free_game_and_exit_xy(t_game *game, const char *msg, int i, int j)
{
	if (msg)
		printf("Erro: %s em [%d,%d]\n", msg, i, j);
	free_game_and_exit(game, NULL);
}

static void	check_wall_boundary(t_game *game, int i, int j)
{
	char	current;
	char	up;
	char	down;
	char	left;
	char	right;

	current = get_char_at(game, i, j);
	if (!is_playable(current))
		return ;
	up = get_char_at(game, i - 1, j);
	down = get_char_at(game, i + 1, j);
	left = get_char_at(game, i, j - 1);
	right = get_char_at(game, i, j + 1);
	if (up == 'X' || down == 'X' || left == 'X' || right == 'X'
		|| up == ' ' || down == ' ' || left == ' ' || right == ' ')
		free_game_and_exit_xy(game, "Mapa não está fechado por paredes", i, j);
}

void	validate_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (game->map[i][j])
		{
			check_wall_boundary(game, i, j);
			j++;
		}
		i++;
	}
}
