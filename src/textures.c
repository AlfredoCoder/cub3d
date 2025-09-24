#include "../include/cub3d.h"

t_texture *select_texture(t_game *game, int side)
{
	if (side == 0 && game->rayDir.x > 0)
		return &game->textures[EAST];
	else if (side == 0 && game->rayDir.x <= 0)
		return &game->textures[WEST];
	else if (side == 1 && game->rayDir.y > 0)
		return &game->textures[SOUTH];
	else
		return &game->textures[NORTH];
}

void draw_texture_column(t_game *game, int x, int start, int end,
                         int texX, t_texture *tex, int lineHeight)
{
	double step = 1.0 * tex->height / lineHeight;
	double texPos = (start - HEIGHT / 2 + lineHeight / 2) * step;

	for (int y = start; y < end; y++)
	{
		int texY = (int)texPos;
		texPos += step;
		if (texY < 0) texY = 0;
		if (texY >= tex->height) texY = tex->height - 1;
		if (texX < 0) texX = 0;
		if (texX >= tex->width) texX = tex->width - 1;

		if (texY >= 0 && texY < tex->height && texX >= 0 && texX < tex->width)
		{
			int color = ((int *)tex->data)[texY * tex->width + texX];
			put_pixel(game, x, y, color);
		}

	}
}


int	load_textures(t_game *game)
{
	int i = 0;

	while (i < 4)
	{
		char *path = ft_strtrim(game->texture_paths[i], " \t\n");
		// game->textures[i] = malloc(sizeof(t_texture));
		// if (!game->textures[i])
		// {
		// 	fprintf(stderr, "Erro ao alocar memória para textura\n");
		// 	return (0);
		// }
		game->textures[i].img_ptr = mlx_xpm_file_to_image(
			game->mlx,
			path,
			&game->textures[i].width,
			&game->textures[i].height
		);
		if (game->textures[i].width <= 0 || game->textures[i].height <= 0)
		{
			fprintf(stderr, "Textura inválida: largura ou altura <= 0 (%s)\n", path);
			return (0);
		}

		if (!game->textures[i].img_ptr)
		{
			fprintf(stderr, "Erro ao carregar textura: %s\n", path);
			free(path);
			return (0);
		}
		game->textures[i].data = mlx_get_data_addr(
			game->textures[i].img_ptr,
			&game->textures[i].bits_per_pixel,
			&game->textures[i].line_length,
			&game->textures[i].endian
		);
		free(path);
		i++;
	}
	return (1);
}


// Código que substitui draw_vertical no seu render()
void draw_wall(t_game *game, int pixel, int drawStart, int drawEnd,
	int side, double perpWallDist)
{
	t_texture *tex = select_texture(game, side);
	double wallX;
	if (side == 0)
		wallX = game->player_pos.y + perpWallDist * game->rayDir.y;
	else
		wallX = game->player_pos.x + perpWallDist * game->rayDir.x;
	wallX -= floor(wallX);
	int texX = (int)(wallX * (double)tex->width);
	if ((side == 0 && game->rayDir.x > 0) || (side == 1 && game->rayDir.y < 0))
		texX = tex->width - texX - 1;
	int lineHeight = HEIGHT / perpWallDist;
	draw_texture_column(game, pixel, drawStart, drawEnd, texX, tex, lineHeight);
}
