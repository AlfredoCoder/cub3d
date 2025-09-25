/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:54:34 by fguerra           #+#    #+#             */
/*   Updated: 2025/08/01 16:54:49 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static double	calc_wall_x(t_game *g, t_wall_params p)
{
	if (p.side == 0)
		return (g->player_pos.y + p.perp_wall_dist * g->ray_dir.y);
	return (g->player_pos.x + p.perp_wall_dist * g->ray_dir.x);
}

static int	calc_tex_x(double wall_x, int tex_width, int side, t_game *g)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex_width);
	if ((side == 0 && g->ray_dir.x > 0)
		|| (side == 1 && g->ray_dir.y < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

void	draw_wall(t_game *g, t_wall_params p)
{
	t_texture	*tex;
	double		wall_x;
	int			tex_x;
	int			height;
	t_draw_tex	draw;

	tex = select_texture(g, p.side);
	wall_x = calc_wall_x(g, p) - floor(calc_wall_x(g, p));
	tex_x = calc_tex_x(wall_x, tex->width, p.side, g);
	height = HEIGHT / p.perp_wall_dist;
	draw = (t_draw_tex){
		p.pixel, p.draw_start, p.draw_end,
		tex_x, tex, height,
		get_step(tex->height, height),
		get_initial_tex_pos(p.draw_start, height)};
	draw_texture_column(g, draw);
}
