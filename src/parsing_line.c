/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 07:46:00 by fguerra           #+#    #+#             */
/*   Updated: 2025/09/25 07:46:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	process_line(t_game *game, char *no_nl, int k)
{
	char	*tmp;
	int		result;

	if ((no_nl[k] == 'N' && no_nl[k + 1] == 'O' && no_nl[k + 2] == ' ')
		|| (no_nl[k] == 'S' && no_nl[k + 1] == 'O' && no_nl[k + 2] == ' ')
		|| (no_nl[k] == 'W' && no_nl[k + 1] == 'E' && no_nl[k + 2] == ' ')
		|| (no_nl[k] == 'E' && no_nl[k + 1] == 'A' && no_nl[k + 2] == ' ')
		|| (no_nl[k] == 'F' && no_nl[k + 1] == ' ')
		|| (no_nl[k] == 'C' && no_nl[k + 1] == ' '))
	{
		tmp = ft_strdup(no_nl + k);
		result = parse_config_line(game, tmp);
		free(tmp);
		return (result);
	}
	else
	{
		result = parse_config_line(game, no_nl);
		return (result);
	}
}
