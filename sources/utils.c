/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 21:12:21 by mde-cloe      #+#    #+#                 */
/*   Updated: 2022/10/26 18:31:54 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	so_long_error_exit(char *s)
{
	ft_printf("\033[0;31mERROR\n %s\n", s);
	exit(0);
}

void	find_player_pos(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
			{
				data->player_x = x;
				data->player_y = y;
				return ;
			}
			x++;
		}
	y++;
	x = 0;
	}
}

char	**copy_map(t_data	*data)
{
	int		i;
	char	**new_map;

	i = 0;
	new_map = (char **)malloc(sizeof(char *) * (data->map_height + 1));
	if (!new_map)
		so_long_error_exit("Malloc fail GO TO JAIL");
	while (data->map[i])
	{
		new_map[i] = ft_strdup(data->map[i]);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->images[0] = NULL;
	data->textures[0] = NULL;
	data->step_text = NULL;
	data->map = NULL;
	data->map_copy = NULL;
	data->collects_reachable = false;
	data->exit_reachable = false;
	data->collect_amount = 0;
	data->map_height = 0;
	data->map_width = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->bg_tiles_nb = 0;
}

void	end_game(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		mlx_delete_texture(data->textures[i]);
		mlx_delete_image(data->mlx, data->images[i]);
		i++;
	}
	i = 0;
	if (data->step_text)
		mlx_delete_image(data->mlx, data->step_text);
	free(data->map[0]);
	free(data->map);
	while (data->map_copy[i])
	{
		free(data->map_copy[i]);
		i++;
	}
	free(data->map_copy);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	ft_printf("\033[0;35m Thank you for playing :) \n");
	exit(0);
}
