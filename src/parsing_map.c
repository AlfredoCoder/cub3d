/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 06:17:00 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 06:17:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	add_line_list(t_game *game, char *line)
{
	t_lmapp	*new_node;
	t_lmapp	*temp;

	new_node = malloc(sizeof(t_lmapp));
	if (!new_node)
		return ;
	new_node->line = ft_strdup(line);
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!game->lmap)
		game->lmap = new_node;
	else
	{
		temp = game->lmap;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
}

static int	find_max_width(t_lmapp *list)
{
	int		max_width;
	int		current_width;
	t_lmapp	*temp;

	max_width = 0;
	temp = list;
	while (temp)
	{
		current_width = ft_strlen(temp->line);
		if (current_width > max_width)
			max_width = current_width;
		temp = temp->next;
	}
	return (max_width);
}

static int	count_list_lines(t_lmapp *list)
{
	int		count;
	t_lmapp	*temp;

	count = 0;
	temp = list;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static void	fill_map_array(t_game *game, int count, int max_width)
{
	int		i;
	t_lmapp	*temp;

	temp = game->lmap;
	i = 0;
	while (temp && i < count)
	{
		game->map[i] = pad_line(temp->line, max_width);
		temp = temp->next;
		i++;
	}
	game->map[count] = NULL;
}

void	convert_list_to_map(t_game *game)
{
	int	count;
	int	max_width;

	count = count_list_lines(game->lmap);
	max_width = find_max_width(game->lmap);
	game->map = malloc(sizeof(char *) * (count + 1));
	if (!game->map)
		return ;
	fill_map_array(game, count, max_width);
	game->map_height = count;
}
