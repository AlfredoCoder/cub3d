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

void	free_textures(t_game *game)
{
	int	i;

	if (!game)
		return;

	for (i = 0; i < 4; i++)
	{
		if (game->textures[i].img_ptr)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img_ptr);
			game->textures[i].img_ptr = NULL;
		}
		// Se tiver strings de caminhos duplicados
		if (game->texture_paths[i])
		{
			free(game->texture_paths[i]);
			game->texture_paths[i] = NULL;
		}
	}
	if (game->map)
	{
		for (i = 0; i < game->map_height; i++)
			free(game->map[i]);
		free(game->map);
		game->map = NULL;
	}
	if (game->lmap)
	{
		free_map_list(game->lmap);
		game->lmap = NULL;
	}
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


int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	supdate(t_game *game)
{
	input_key(game);
	render(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;
	if (ac != 2)
		return (printf("erro deve passar um argumento como mapa"), 0);
	parse_file(av[1], &game);
	game.player_pos = get_player_position(&game);
	game.mlx = mlx_init();
	if (game.mlx == NULL)
	{
		free_textures(&game);
		return 0;
	}
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3d");
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.addr = mlx_get_data_addr(game.img, &game.bpp, &game.size_line, &game.endian);
	if (!load_textures(&game))
		return (printf("Falha ao carregar texturas\n"), 1);
	mlx_hook(game.win, 2, 1L << 0, &key_handler, &game);
	mlx_hook(game.win, 3, 1L << 1, &restart_key, &game);
	mlx_hook(game.win, 17, 0, close_game, &game); // Fechar com o botão X
	mlx_loop_hook(game.mlx, &supdate, &game);
	mlx_loop(game.mlx);
	return (0);
}

