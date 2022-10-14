/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 21:14:45 by mde-cloe      #+#    #+#                 */
/*   Updated: 2022/10/14 20:37:00 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_sprites(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	load_imgs(data);
	place_background(data);
	while (data->map[i])
	{
		while (data->map[i][j])
		{
			place_tile(data, data->map[i][j], j * TILESIZE, i * TILESIZE);
			j++;
		}
		i++;
		j = 0;
	}
}

void	load_imgs(t_data *data)
{
	char			path[15];
	int				i;
	char			*tiles;

	i = 0;
	tiles = "1CEP0";
	ft_strlcpy(path, "textures/_.png", 15);
	while (tiles[i])
	{
		path[9] = tiles[i];
		data->textures[i] = mlx_load_png(path);
		data->images[i] = mlx_texture_to_image(data->mlx, data->textures[i]);
		i++;
	}
}

void	place_tile(t_data *data, char c, int x, int y)
{
	char	*tiles;
	int		i;

	tiles = "1CEP";
	i = 0;
	while (tiles[i])
	{
		if (tiles[i] == c)
			mlx_image_to_window(data->mlx, data->images[i], x, y);
		i++;
	}
}

void	place_background(t_data *data)
{
	int				x;
	int				y;

	x = 0;
	y = 0;
	while (y < (data->map_height * TILESIZE))
	{
		while (x < (data->map_width * TILESIZE))
		{
			mlx_image_to_window(data->mlx, data->images[BACKGROUND], x, y);
			x += TILESIZE;
			data->bg_tiles_nb++;
		}
		y += TILESIZE;
		x = 0;
	}
}
