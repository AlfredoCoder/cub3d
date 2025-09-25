/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:57:57 by fguerra           #+#    #+#             */
/*   Updated: 2025/08/01 16:58:07 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	load_single_texture(t_game *game, int i)
{
	char	*path;

	path = ft_strtrim(game->texture_paths[i], " \t\n");
	game->textures[i].img_ptr = mlx_xpm_file_to_image(
			game->mlx, path,
			&game->textures[i].width,
			&game->textures[i].height);
	if (!game->textures[i].img_ptr
		|| game->textures[i].width <= 0
		|| game->textures[i].height <= 0)
	{
		ft_putstr_fd("Erro ao carregar textura: ", 2);
		ft_putendl_fd(path, 2);
		free(path);
		return (0);
	}
	game->textures[i].data = mlx_get_data_addr(game->textures[i].img_ptr,
			&game->textures[i].bits_per_pixel,
			&game->textures[i].line_length,
			&game->textures[i].endian);
	free(path);
	return (1);
}

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!load_single_texture(game, i))
			return (0);
		i++;
	}
	return (1);
}
