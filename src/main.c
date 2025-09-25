/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:02:36 by fguerra           #+#    #+#             */
/*   Updated: 2025/04/03 21:02:41 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_texture_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture_paths[i])
		{
			free(game->texture_paths[i]);
			game->texture_paths[i] = NULL;
		}
		i++;
	}
}

static void	free_game_map(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
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

void	free_textures(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img_ptr)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img_ptr);
			game->textures[i].img_ptr = NULL;
		}
		i++;
	}
	free_texture_paths(game);
	free_game_map(game);
}

int	close_game(t_game *game)
{
	free_textures(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;
	if (ac != 2)
		return (printf("erro deve passar um argumento como mapa"), (0));
	parse_file(av[1], &game);
	game.player_pos = get_player_position(&game);
	if (!init_mlx_resources(&game))
		return (0);
	setup_mlx_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
