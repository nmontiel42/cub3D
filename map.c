/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:18:09 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/01 17:19:06 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	save_map(t_data *data)
{
	char	*map_join;

	map_join = NULL;
	while (data->line)
	{
		map_join = ft_strjoin(map_join, data->line);
		if (!map_join)
			return (1);
		if (data->line[0] == '\n')
			return (free(map_join), free(data->line), ft_error(ELINE));
		free(data->line);
		data->line = get_next_line(data->fd);
	}
	close(data->fd);
	if (map_join)
	{
		data->map = ft_split(map_join, '\n');
		if (!data->map)
			return (free(map_join), 1);
		if (check_map(data))
			return (free(map_join), 1);
	}
	return (free(map_join), 0);
}

int	fix_map(t_data *d)
{
	size_t	max_l;
	char	*new_ln;

	d->i = -1;
	max_l = 0;
	while (d->map[++d->i])
		if (max_l < ft_strlen(d->map[d->i]))
			max_l = ft_strlen(d->map[d->i]);
	d->i = -1;
	while (d->map[++d->i])
	{
		d->j = ft_strlen(d->map[d->i]);
		new_ln = ft_calloc(1, max_l + 1);
		if (!new_ln)
			return (1);
		ft_strlcpy(new_ln, d->map[d->i], ft_strlen(d->map[d->i]) + 1);
		while ((size_t)d->j < max_l)
			new_ln[d->j++] = ' ';
		new_ln[d->j] = '\0';
		free(d->map[d->i]);
		d->map[d->i] = new_ln;
		d->h_map = d->i;
		d->w_map = max_l - 1;
	}
	return (0);
}

int	save_textures_2(t_data *data, char **split_text, char **tc)
{
	data->j = 2;
	while (split_text[data->i][data->j] == ' '
	|| (split_text[data->i][data->j] >= 9
		&& split_text[data->i][data->j] <= 13))
		data->j++;
	*tc = ft_strdup(split_text[data->i] + data->j);
	if (!*tc)
		return (1);
	if (!ft_strncmp(split_text[data->i], "NO ", 3))
		data->no = mlx_load_png(*tc);
	else if (!ft_strncmp(split_text[data->i], "SO ", 3))
		data->so = mlx_load_png(*tc);
	else if (!ft_strncmp(split_text[data->i], "WE ", 3))
		data->we = mlx_load_png(*tc);
	else if (!ft_strncmp(split_text[data->i], "EA ", 3))
		data->ea = mlx_load_png(*tc);
	return (0);
}

int	save_textures(t_data *data, char *text)
{
	char	**split_text;
	char	*tc;

	tc = NULL;
	split_text = ft_split(text, '\n');
	data->i = -1;
	while (split_text && split_text[++data->i])
	{
		data->j = data->i;
		while (split_text[++data->j])
			if (!ft_strncmp(split_text[data->i], split_text[data->j], 2))
				return (free_b_arr(&split_text), free(text),
					free(data->line), ft_error(DCLRS));
		if (split_text[data->i][data->j])
		{
			if (save_textures_2(data, split_text, &tc))
				return (free_b_arr(&split_text), free(tc), free(text), 1);
			if ((!ft_strncmp(split_text[data->i], "F ", 2)
					|| !ft_strncmp(split_text[data->i], "C ", 2))
				&& check_colors(data, tc, split_text[data->i]))
				return (free_b_arr(&split_text), free(tc), free(text), 1);
			free(tc);
		}
	}
	return (free_b_arr(&split_text), free(text), 0);
}

int	read_map(t_data *data, char *map_fd)
{
	char	*text;

	text = NULL;
	data->count_textures = 0;
	data->fd = open(map_fd, O_RDONLY);
	if (data->fd == -1)
		ft_error(OMAP);
	data->line = get_next_line(data->fd);
	if (!data->line)
		return (ft_error(EGNL));
	if (check_elements(data, &text))
		return (1);
	if (save_textures(data, text))
		return (1);
	if (!data->no || !data->so || !data->we || !data->ea)
		return (free(data->line), ft_error(ETEXT));
	printf("TODO CORRECTO\n");
	return (0);
}
