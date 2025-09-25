/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 06:26:00 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 06:26:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*pad_line(char *line, int target_width)
{
	char	*padded;
	int		len;
	int		i;

	len = ft_strlen(line);
	padded = malloc(target_width + 1);
	if (!padded)
		return (NULL);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < target_width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[target_width] = '\0';
	return (padded);
}

void	free_map_list(t_lmapp *list)
{
	t_lmapp	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->line);
		free(list);
		list = tmp;
	}
}
