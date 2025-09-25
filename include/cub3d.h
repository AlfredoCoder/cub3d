/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguerra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:48:06 by fguerra           #+#    #+#             */
/*   Updated: 2025/08/01 16:12:00 by fguerra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364
# define ESC_KEY 65307

# define NORTH 0
# define SOUTH 1
# define EAST  2
# define WEST  3

# define WIDTH 800
# define HEIGHT 600
# define TILE_SIZE 64
# define NUM_RAYS WIDTH
# define FOV 60
# define SPEED 0.01
# define ROTATE_ANGLE 0.008

/*----------------------------- STRUCTS -----------------------------*/

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_comands
{
	bool	key_w;
	bool	key_a;
	bool	key_s;
	bool	key_d;
	bool	key_left;
	bool	key_right;
	bool	key_up;
	bool	key_down;
	bool	esc_key;
}	t_comands;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	int		direction;
}	t_player;

typedef struct s_texture
{
	void	*img_ptr;
	char	*data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_draw
{
	int	x;
	int	start_y;
	int	end;
	int	color;
}	t_draw;

typedef struct s_draw_tex
{
	int			x;
	int			start;
	int			end;
	int			tex;
	t_texture	*tex;
	int			lineHeight;
	double		step;
	double		tex_pos;
}	t_draw_tex;

typedef struct s_wall_params
{
	int		pixel;
	int		draw_start;
	int		draw_end;
	int		side;
	double	perp_wall_dist;
}	t_wall_params;

typedef struct s_hit
{
	int		map_x;
	int		map_y;
	double	side_dist[2];
	double	delta_dist[2];
}			t_hit;

typedef struct s_lmapp
{
	char			*line;
	struct s_lmapp	*next;
	struct s_lmapp	*prev;
}	t_lmapp;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			floor_color;
	int			ceiling_color;
	int			map_height;

	t_texture	textures[4];
	char		*texture_paths[4];

	t_coord		player_pos;
	t_coord		dir;
	t_coord		plane;
	t_coord		ray_dir;

	t_player	player;
	t_comands	comands;
	char		**map;
	t_lmapp		*lmap;
}	t_game;

/*------------------------- PROTÓTIPOS: PARSER -------------------------*/

char	**ft_realloc_map(char **map, char *line);
void	parse_file(char *path, t_game *game);
void	load_map(char *file, t_game *game);
void	add_line_list(t_game *game, char *line);
void	convert_list_to_map(t_game *game);
void	free_map_list(t_lmapp *list);

/*---------------------- PROTÓTIPOS: VALIDAÇÕES ------------------------*/

int		is_valid_cub(char *argument);
int		is_valid_map_line(char *line);
int		is_valid_texture_path(char *line);
int		find_max_width(char **map);
int		parse_color(char *str);
int		parse_rgb(char *line);
int		check_rgb_value(char *str, int *pos);

/*------------------------- PROTÓTIPOS: TEXTURAS -------------------------*/

int		load_textures(t_game *game);
void	load_all_textures(t_game *game);
void	free_textures(t_game *game);
t_texture	*select_texture(t_game *game, int side);

/*---------------------- PROTÓTIPOS: MOVIMENTAÇÃO ------------------------*/

void	to_forward(t_game *game);
void	to_backward(t_game *game);
void	to_rotate(t_game *game, double angle);
void	input_key(t_game *game);
int		key_handler(int key, t_game *game);

/*------------------------- PROTÓTIPOS: RENDER ---------------------------*/

void	render(t_game *game);
void	draw(t_game *game);
void	clear_img(t_game *game);
void	draw_vertical(t_game *game, t_draw draw);
void	draw_texture_column(t_game *game, t_draw_tex draw);
void	draw_wall(t_game *game, t_wall_params params);

/*------------------------- PROTÓTIPOS: UTILITÁRIOS ------------------------*/

void	init_game(t_game *game);
void	init_player(t_game *game);
void	set_player_dir_and_plane(t_game *game, char dir);
void	set_north(t_game *game);
void	set_south(t_game *game);
void	set_east(t_game *game);
void	set_west(t_game *game);
t_coord	get_player_position(t_game *game);
char	*read_line(int fd);
void	print_error(char *msg);
void	print_map(t_game *game);
void	free_game(t_game *game);
void	free_textures(t_game *game);
void	free_game_and_exit(t_game *game, const char *msg);
void	free_game_and_exit_xy(t_game *game, const char *msg, int i, int j);

/*----------------------- PROTÓTIPOS: FERRAMENTAS DE DESENHO ------------------*/

void	put_pixel(t_game *game, int x, int y, int color);
double	get_step(int tex_height, int line_height);
double	get_initial_tex_pos(int start, int line_height);

/*------------------------ PROTÓTIPOS: SISTEMA / FECHO ----------------------*/

int		close_game(t_game *game);
int		close_window(void *param);
int		restart_key(int key, t_game *game);
int		supdate(t_game *game);
int		is_wall(t_game *game, double x, double y);

#endif
