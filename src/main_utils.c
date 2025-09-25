/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 06:29:00 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 06:29:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	setup_mlx_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, &key_handler, game);
	mlx_hook(game->win, 3, 1L << 1, &restart_key, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, &supdate, game);
}

int	init_mlx_resources(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		free_textures(game);
		return (0);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3d");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line,
			&game->endian);
	if (!load_textures(game))
		return (printf("Falha ao carregar texturas\n"), (1));
	return (1);
}
