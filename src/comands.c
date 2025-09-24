#include "../include/cub3d.h"

int	key_handler(int keyboard, t_game *game)
{
	(void)game;
	if (keyboard == W)
	{
		game->comands.key_w = true;
	}
	else if (keyboard == A)
	{
		game->comands.key_a = true;
	}
	else if (keyboard == S)
	{
		game->comands.key_s = true;
	}
	else if (keyboard == D)
	{
		game->comands.key_d = true;
	}
	else if (keyboard == LEFT)
	{
		game->comands.key_left = true;
	}
	else if (keyboard == RIGHT)
	{
		game->comands.key_right = true;
	}
	return (0);
}

int	restart_key(int keyboard, t_game *game)
{
	(void)game;
	if (keyboard == W)
	{
		game->comands.key_w = false;
	}
	else if (keyboard == A)
	{
		game->comands.key_a = false;
	}
	else if (keyboard == S)
	{
		game->comands.key_s = false;
	}
	else if (keyboard == D)
	{
		game->comands.key_d = false;
	}
	else if (keyboard == LEFT)
	{
		game->comands.key_left = false;
	}
	else if (keyboard == RIGHT)
	{
		game->comands.key_right = false;
	}
	return (0);
}