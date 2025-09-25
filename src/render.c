/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:03:32 by fguerra           #+#    #+#             */
/*   Updated: 2025/08/01 17:02:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_step(t_game *g, int *step_x, int *step_y, double *side_dist)
{
	if (g->ray_dir.x < 0)
	{
		*step_x = -1;
		side_dist[0] = (g->player_pos.x - (int)g->player_pos.x)
			* fabs(1 / g->ray_dir.x);
	}
	else
	{
		*step_x = 1;
		side_dist[0] = ((int)g->player_pos.x + 1.0 - g->player_pos.x)
			* fabs(1 / g->ray_dir.x);
	}
	if (g->ray_dir.y < 0)
	{
		*step_y = -1;
		side_dist[1] = (g->player_pos.y - (int)g->player_pos.y)
			* fabs(1 / g->ray_dir.y);
	}
	else
	{
		*step_y = 1;
		side_dist[1] = ((int)g->player_pos.y + 1.0 - g->player_pos.y)
			* fabs(1 / g->ray_dir.y);
	}
}

static int	calc_hit(t_game *g, t_hit *hit)
{
	int	step_x;
	int	step_y;
	int	side;
	int	hit_wall;

	init_step(g, &step_x, &step_y, hit->side_dist);
	hit_wall = 0;
	while (!hit_wall)
	{
		if (hit->side_dist[0] < hit->side_dist[1])
		{
			hit->side_dist[0] += hit->delta_dist[0];
			hit->map_x += step_x;
			side = 0;
		}
		else
		{
			hit->side_dist[1] += hit->delta_dist[1];
			hit->map_y += step_y;
			side = 1;
		}
		if (g->map[hit->map_y][hit->map_x] == '1')
			hit_wall = 1;
	}
	return (side);
}

static void	set_wall_params(t_wall_params *p, int pixel, int side, double dist)
{
	p->pixel = pixel;
	p->side = side;
	p->perp_wall_dist = dist;
	p->draw_start = (int)((HEIGHT - (HEIGHT / dist)) / 2);
	p->draw_end = p->draw_start + (int)(HEIGHT / dist);
}

static void	render_pixel(t_game *g, int pixel)
{
	double			camera_x;
	double			perp_dist;
	int				side;
	t_hit			h;
	t_wall_params	params;

	camera_x = 2 * pixel / (double)WIDTH - 1;
	g->ray_dir.x = g->dir.x + g->plane.x * camera_x;
	g->ray_dir.y = g->dir.y + g->plane.y * camera_x;
	h.map_x = (int)g->player_pos.x;
	h.map_y = (int)g->player_pos.y;
	h.delta_dist[0] = fabs(1 / g->ray_dir.x);
	h.delta_dist[1] = fabs(1 / g->ray_dir.y);
	side = calc_hit(g, &h);
	if (side == 0)
		perp_dist = h.side_dist[0] - h.delta_dist[0];
	else
		perp_dist = h.side_dist[1] - h.delta_dist[1];
	set_wall_params(&params, pixel, side, perp_dist);
	draw_wall(g, params);
}

void	render(t_game *game)
{
	int	pixel;

	clear_img(game);
	pixel = -1;
	while (++pixel < WIDTH)
		render_pixel(game, pixel);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
