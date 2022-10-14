/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/23 21:39:08 by mde-cloe      #+#    #+#                 */
/*   Updated: 2022/10/15 00:07:52 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/**
 * @brief Parent function that houses does all the map validation
 *
 * @param data pointer to data struct that houses everything I need
 */

void	map_validation(t_data *data)
{
	char	**map;

	ft_print_map(data->map);
	is_map_walled_off_and_rectangluar(data);
	data->collect_amount = (count_and_check_valid_tiles(data->map));
	find_player_pos(data);
	map = map_copy(data);
	flood_fill(data, map, data->p_x, data->p_y);
	if (!data->exit_reachable || !data->collects_reachable)
		error_exit("wow I can't even complete this map, what a scam");
	free_map(map);
	ft_printf("\033[0;33m\nPARSING COMPLETE\033[0m\n");
}

/**
 * @brief checks if the edges off the map are walled off
 * and wether all the lines are equally long
 * @param data our good old friend big fuckoff data struct
 */
void	is_map_walled_off_and_rectangluar(t_data *data)
{
	int	i;
	int	len;

	data->map_width = top_bottom_check(data->map[0]);
	i = 1;
	while (data->map[i + 1])
	{
		len = ft_strlen(data->map[i]);
		if (len != data->map_width)
			error_exit("I guess you were there\
			 cause this map is not a square!");
		if (data->map[i][0] != '1' || data->map[i][len - 1] != '1')
			error_exit("No proper wall's my man");
		i++;
	}
	top_bottom_check(data->map[i]);
	if ((int)ft_strlen(data->map[i]) != len)
		error_exit("Guess you'll have to go on grindr because \
		this Bottom (wall) is invalid!");
	data->map_height = i + 1;
}

/**
 * @brief small function to check wether a string only contains 1
 * used to check the first and last line of the map
 *
 * @param str the map of the line
 * @return the line len
 */
int	top_bottom_check(char *str)
{
	int	i;

	i = 0;
	if (!str)
		error_exit("empty string???\n");
	while (str[i])
	{
		if (str[i] != '1')
			error_exit("get your top and bottom (walls) sorted ;)");
		i++;
	}
	return (i);
}

/**
 * @brief checks if the map has the right amount of player, exit and collectibles
 * and that It only has valid characters
 * @param map
 * @return The amount of collectibles
 */
int	count_and_check_valid_tiles(char **map)
{
	int			y;
	int			x;
	static int	table[128] = {['E'] = 1, ['C'] = 1, ['P'] = 1, \
	['1'] = 1, ['0'] = 1};

	y = 0;
	x = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] > 127 || map[y][x] < 0 || table[(int)map[y][x]] < 1)
				error_exit("The map has an invalid Char, go wait in the car!");
			table[(int)map[y][x]]++;
			x++;
		}
		y++;
		x = 0;
	}
	if (table['E'] != 2 || table['P'] != 2 || table['C'] < 2)
		error_exit("wrong amount of exit/player/collectibles sussy baka!");
	return (table['C'] - 1);
}

/**
 * @brief My breadth search function that checks wether the map
 * is completable
 * @param data our big friend data struct ptr
 * @param map cop
 * @param x
 * @param y
 */
void	flood_fill(t_data *data, char **map, int x, int y)
{
	static int	collects;

	if (map[y][x] == '1')
		return ;
	if (map[y][x] == 'E')
	{
		data->exit_reachable = true;
		return ;
	}
	if (map[y][x] == 'C')
	{
		collects++;
		if (collects == data->collect_amount)
			(data)->collects_reachable = true;
	}
	(map)[y][x] = '1';
	flood_fill(data, map, x + 1, y);
	flood_fill(data, map, x - 1, y);
	flood_fill(data, map, x, y + 1);
	flood_fill(data, map, x, y - 1);
}
