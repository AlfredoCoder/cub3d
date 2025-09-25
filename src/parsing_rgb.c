/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 06:23:00 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 06:23:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	parse_rgb_values(char *line, int *r, int *g, int *b)
{
	int	pos;

	pos = 0;
	*r = check_rgb_value(line, &pos);
	if (*r < 0)
		return (-1);
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	if (line[pos] != ',')
		return (-1);
	pos++;
	*g = check_rgb_value(line, &pos);
	if (*g < 0)
		return (-1);
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	if (line[pos] != ',')
		return (-1);
	pos++;
	*b = check_rgb_value(line, &pos);
	if (*b < 0)
		return (-1);
	return (0);
}

int	parse_rgb(char *line)
{
	int	r;
	int	g;
	int	b;

	if (parse_rgb_values(line, &r, &g, &b) < 0)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}
