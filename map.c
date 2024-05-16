/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:18:09 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/16 17:49:46 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	save_textures_2(t_data *data, char **split_text, char **t_c)
{
	data->j = 2;
	while (split_text[data->i][data->j] == ' '
	|| (split_text[data->i][data->j] >= 9
		&& split_text[data->i][data->j] <= 13))
		data->j++;
	*t_c = ft_strdup(split_text[data->i] + data->j);
	if (!*t_c)
		return (1);
	if (!ft_strncmp(split_text[data->i], "NO ", 3))
		data->no = mlx_load_png(*t_c);
	else if (!ft_strncmp(split_text[data->i], "SO ", 3))
		data->so = mlx_load_png(*t_c);
	else if (!ft_strncmp(split_text[data->i], "WE ", 3))
		data->we = mlx_load_png(*t_c);
	else if (!ft_strncmp(split_text[data->i], "EA ", 3))
		data->ea = mlx_load_png(*t_c);
	return (0);
}

int	check_empty_color(char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line + 2, " ");
	if (ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}

int	check_duplicate_textures(char **split_text, int i, int j)
{
	while (split_text[++j])
		if (!ft_strncmp(split_text[i], split_text[j], 2))
			return (1);
	return (0);
}

int	save_textures(t_data *d, char *text)
{
	char	**split_text;
	char	*t_c;

	t_c = NULL;
	split_text = ft_split(text, '\n');
	if (!split_text)
		return (ft_error2(E_SPLIT));
	d->i = -1;
	while (split_text[++d->i])
	{
		d->j = d->i;
		if (check_duplicate_textures(split_text, d->i, d->j))
			return (free_array(&split_text), free(text),
				free(d->line), ft_error(D_CLRS));
		if ((!ft_strncmp(split_text[d->i], "C ", 2) \
		|| !ft_strncmp(split_text[d->i], "C", 2)) \
		|| ((!ft_strncmp(split_text[d->i], "F ", 2) \
		|| !ft_strncmp(split_text[d->i], "F", 2))))
			if (check_empty_color(split_text[d->i]))
				return (free_array(&split_text), free(text), ft_error2(EM_CLR));
		if (process_textures_and_colors(d, split_text, &t_c))
			return (free_array(&split_text), free(t_c), free(text), 1);
	}
	return (free_array(&split_text), free(text), 0);
}

int	read_map(t_data *data, char *map_fd)
{
	char	*texture;

	texture = NULL;
	data->count_textures = 0;
	data->fd = open(map_fd, O_RDONLY);
	if (data->fd == -1)
		ft_error(O_MAP);
	data->line = get_next_line(data->fd);
	if (!data->line)
		return (ft_error(E_GNL));
	if (check_elements(data, &texture))
		return (1);
	if (save_textures(data, texture))
		return (1);
	if (!data->no || !data->so || !data->we || !data->ea)
		return (free(data->line), ft_error(E_TEXT));
	if (!data->c_rgb || !data->c_rgb[0] || !data->c_rgb[1] || !data->c_rgb[2] \
	|| !data->f_rgb || !data->f_rgb[0] || !data->f_rgb[1] || !data->f_rgb[2])
		return (free(data->line), ft_error(E_CLRS));
	return (0);
}
