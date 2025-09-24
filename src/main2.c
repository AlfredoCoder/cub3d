#include "../minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

typedef struct s_main {
  void *mlx;
  void *win;
  int bpp;
  int size_line;
  char *addr;
  void *img;
  int endian;
  char **gamemap;
}		t_main;

typedef struct s_coord {
  double x;
  double y;
}		t_coord;

void	put_pixel(t_main *g, int x, int y, int color) {
  char *dest;
  if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
    return ;
  dest = g->addr + (y * g->size_line + x * (g->bpp / 8));
  *(int *)(dest) = color;
}

void	draw_vertical_line(t_main *g, int x, int start_y, int end, int color) {
  if (start_y < 0)
    start_y = 0;
  if (end >= HEIGHT)
    end = HEIGHT - 1;
  while (start_y < end) {
    put_pixel(g, x, start_y, color);
    start_y++;
  }
}

t_coord	get_player_pos(char **map) {
  int x, y;
  t_coord pos = {0, 0};

  y = 0;
  while (map[y]) {
    x = 0;
    while (map[y][x]) {
      if (map[y][x] == 'P') {
        pos.x = x + 0.5;
        pos.y = y + 0.5;
        return (pos);
      }
      x++;
    }
    y++;
  }
  return (pos);
}

void	clear_img(t_main *g) {
  int x, y;

  y = 0;
  while (y < HEIGHT) {
    x = 0;
    while (x < WIDTH) {
      if (y < HEIGHT / 2)
        put_pixel(g, x, y, 0xffffff);
      else
        put_pixel(g, x, y, 0x5b2f0a);
      x++;
    }
    y++;
  }
}

void	render(t_main *g) {
  t_coord pos = get_player_pos(g->gamemap);
  t_coord dir, plane, rayDir;

  dir.x = 0;
  dir.y = 1;

  plane.x = 0.66;
  plane.y = 0;

  clear_img(g);
  for (int pixel = 0; pixel < WIDTH; pixel++) {
    double cameraX = 2 * pixel / (double)WIDTH - 1;
    rayDir.x = dir.x + plane.x * cameraX;
    rayDir.y = dir.y + plane.y * cameraX;

    int mapX = (int)pos.x;
    int mapY = (int)pos.y;

    double deltaDistX = fabs(1 / rayDir.x);
    double deltaDistY = fabs(1 / rayDir.y);

    double sideDistX, sideDistY;
    int stepX, stepY;

    if (rayDir.x < 0) {
      stepX = -1;
      sideDistX = (pos.x - mapX) * deltaDistX;
    } else {
      stepX = 1;
      sideDistX = (mapX + 1.0 - pos.x) * deltaDistX;
    }

    if (rayDir.y < 0) {
      stepY = -1;
      sideDistY = (pos.y - mapY) * deltaDistY;
    } else {
      stepY = 1;
      sideDistY = (mapY + 1.0 - pos.y) * deltaDistY;
    }

    int hit = 0, side;

    while (!hit) {
      if (sideDistX < sideDistY) {
        side = 0;
        sideDistX += deltaDistX;
        mapX += stepX;
      } else {
        side = 1;
        sideDistY += deltaDistY;
        mapY += stepY;
      }

      if (g->gamemap[mapY][mapX] == '1')
        hit = 1;
    }

    double perpWallDist;

    if (side == 0)
      perpWallDist = sideDistX - deltaDistX;
    else
      perpWallDist = sideDistY - deltaDistY;
    int lineHeight = HEIGHT / perpWallDist;
    int drawStart = HEIGHT / 2 - lineHeight / 2;
    int drawEnd = HEIGHT / 2 + lineHeight / 2;
    if (side == 0)
      draw_vertical_line(g, pixel, drawStart, drawEnd, 0x0000FF);
    else
      draw_vertical_line(g, pixel, drawStart, drawEnd, 0x01122d);
  }
  mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}

int	update(t_main *g) {
  render(g);
  return (0);
}

/* int main(void)
{
    t_main g;

    g.mlx = mlx_init();
    g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, "cub3d");
    g.gamemap = malloc(sizeof(char *) * 11);
    g.gamemap[0] = "1111111111";
    g.gamemap[1] = "1111111111";
    g.gamemap[2] = "1000111111";
    g.gamemap[3] = "1000001111";
    g.gamemap[4] = "1001101111";
    g.gamemap[5] = "1000101111";
    g.gamemap[6] = "10P0011111";
    g.gamemap[7] = "1011111111";
    g.gamemap[8] = "1011111111";
    g.gamemap[9] = "1111111111";
    g.gamemap[10] = NULL;
    g.img = mlx_new_image(g.mlx, WIDTH, HEIGHT);
    g.addr = mlx_get_data_addr(g.img, &g.bpp, &g.size_line, &g.endian);
    mlx_loop_hook(g.mlx, &update, &g);
    mlx_loop(g.mlx);
    return (0);
}*/