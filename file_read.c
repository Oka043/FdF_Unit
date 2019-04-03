/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaktion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:19:51 by olaktion          #+#    #+#             */
/*   Updated: 2018/08/23 15:19:53 by olaktion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	max_min(int z, t_env *str)
{
	static int max = 0;
	static int min = 0;

	if (z > max)
	{
		max = z;
		str->max = z;
	}
	else if (z < min)
	{
		min = z;
		str->min = z;
	}
	else if (z == 0 && max == 0 && min == 0)
	{
		str->max = 0;
		str->min = 0;
	}
}

int		words(char *str, char c)
{
	int				count_word;
	int				j;
	int				is_word;

	j = 0;
	count_word = 0;
	is_word = 1;
	while (str[j])
	{
		if (str[j] != c && is_word == 1)
		{
			is_word = 0;
			count_word++;
		}
		if (str[j] == c && is_word == 0)
			is_word = 1;
		j++;
	}
	return (count_word);
}

void	fdf_error(char *file)
{
	ft_putstr("fdf: ");
	ft_putstr(file);
	perror(" ");
	exit(0);
}

void	count_i(char *file, t_env *str)
{
	int		fd;
	char	*s;
	int		r;

	str->count_y = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		fdf_error(file);
	while ((r = get_next_line(fd, &s)))
	{
		if (r == -1)
			fdf_error(file);
		if (!(ft_isprint(s[0])))
		{
			ft_putstrn("fdf: Invalid File");
			exit(0);
		}
		if (str->count_x < words(s, ' '))
			str->count_x = words(s, ' ');
		if (s)
			free(s);
		str->count_y++;
	}
	close(fd);
}

char	***read_file(char *file, int count)
{
	char	*line;
	char	***map;
	int		y;
	int		fd;

	y = 0;
	fd = open(file, O_RDONLY);
	map = (char ***)malloc(sizeof(char **) * count);
	while (get_next_line(fd, &line))
	{
		map[y] = ft_strsplit(line, ' ');
		if (line)
			free(line);
		y++;
	}
	return (map);
}
