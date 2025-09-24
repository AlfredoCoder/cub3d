#include "../include/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*print_pixel;

	if (!game || !game->addr || x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	print_pixel = game->addr + (y * game->size_line + x * (game->bpp / 8));
	*(int *)(print_pixel) = color;
}
void	draw_vertical(t_game *game, int x, int start_y, int end, int color)
{
	if (start_y < 0)
		start_y = 0;
	if (end > HEIGHT)
		end = HEIGHT;
	while (start_y < end)
	{
		put_pixel(game, x, start_y, color);
		start_y++;
	}
}

void	clear_img(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(game, x, y, game->ceiling_color);
			else
				put_pixel(game, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

t_coord	get_player_position(t_game *game)
{
	int		x, y;
	char	dir;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			dir = game->map[y][x];
			if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
			{
				game->player_pos.x = x + 0.5;
				game->player_pos.y = y + 0.5;

				// Define a direção e o plano da câmera
				if (dir == 'N')
				{
					game->dir.x = 0;
					game->dir.y = -1;
					game->plane.x = 0.66;
					game->plane.y = 0;
				}
				else if (dir == 'S')
				{
					game->dir.x = 0;
					game->dir.y = 1;
					game->plane.x = -0.66;
					game->plane.y = 0;
				}
				else if (dir == 'E')
				{
					game->dir.x = 1;
					game->dir.y = 0;
					game->plane.x = 0;
					game->plane.y = 0.66;
				}
				else if (dir == 'W')
				{
					game->dir.x = -1;
					game->dir.y = 0;
					game->plane.x = 0;
					game->plane.y = -0.66;
				}
				return (game->player_pos);
			}
			x++;
		}
		y++;
	}
	game->player_pos.x = 0;
	game->player_pos.y = 0;
	return (game->player_pos);
}
