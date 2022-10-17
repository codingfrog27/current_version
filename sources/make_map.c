/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mde-cloe <mde-cloe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 14:40:26 by mde-cloe      #+#    #+#                 */
/*   Updated: 2022/10/17 19:48:15 by mde-cloe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief function that, if the input is valid parses
 * the map to a 2d array
 * @param argc
 * @param argv
 * @return char** the map in question
 */
char	**make_map(int argc, char **argv)
{
	char	**map;
	char	*line;
	int		fd;

	if (argc != 2)
		error_exit("Wrong number of arguments silly!");
	if (ft_strlen(argv[1]) < 5 || !ft_strrcmp(argv[1], ".ber", 4))
		error_exit("not a proper .ber file!");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_exit("open failed :(");
	line = make_map_line(fd);
	map = line_to_map(line);
	return (map);
}

/**
 * @brief Reads the file and puts it into a string
 *
 * @param fd
 * @return the map line
 */
char	*make_map_line(int fd)
{
	char	buff[4097];
	char	*map_line;
	char	*tmp;
	int		read_ret;

	map_line = NULL;
	read_ret = read(fd, buff, 0);
	if (read_ret == -1)
		error_exit("can't read this file uwu");
	read_ret = 1;
	while (read_ret != 0)
	{
		ft_bzero(buff, 4097);
		read_ret = read(fd, buff, 4096);
		if (read_ret == -1)
			error_exit("can't read this file uwu");
		tmp = map_line;
		map_line = ft_strjoin(map_line, buff);
		free(tmp);
	}
	return (map_line);
}

/**
 * @brief reads the amount of newlines from the map string
 * and allocates a ptr array of the right size for line_to_map
 * @param map_line the map string
 * @return char** the pointer array
 */
char	**alloc_map(char *map_line)
{
	int		lines_to_alloc;
	int		i;
	char	**map;

	i = 0;
	lines_to_alloc = 0;
	while (map_line[i])
	{
		if (map_line[i] == '\n')
			lines_to_alloc++;
		i++;
	}
	if (map_line[i - 1] != '\n')
		lines_to_alloc += 1;
	map = (char **)malloc((lines_to_alloc + 1) * sizeof(char *));
	if (!map)
		exit(EXIT_FAILURE);
	map[lines_to_alloc] = NULL;
	return (map);
}

/**
 * @brief sets a pointer to different parts of the map
 *turning it into a 2d array without needing extra allocation
 * @param map_line the map string
 * @return char** the map
 */
char	**line_to_map(char *map_line)
{
	int		termpos;
	int		i;
	char	**map;

	termpos = 0;
	i = 0;
	map = alloc_map(map_line);
	while (map_line[termpos])
	{
		if (map_line[termpos] == '\n')
		{
			map_line[termpos] = '\0';
			map[i] = map_line;
			map_line += termpos + 1;
			i++;
			termpos = 0;
		}
		termpos++;
	}
	if (*map_line)
		map[i] = map_line;
	return (map);
}
