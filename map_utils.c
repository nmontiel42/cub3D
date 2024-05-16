/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:21:17 by etornay-          #+#    #+#             */
/*   Updated: 2024/05/16 17:58:23 by nmontiel         ###   ########.fr       */
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
			return (free(map_join), free(data->line), ft_error(E_LINE));
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

int	fix_map(t_data *dta)
{
	size_t	max_l;
	char	*new;

	dta->i = -1;
	max_l = 0;
	while (dta->map[++dta->i])
		if (max_l < ft_strlen(dta->map[dta->i]))
			max_l = ft_strlen(dta->map[dta->i]);
	dta->i = -1;
	while (dta->map[++dta->i])
	{
		dta->j = ft_strlen(dta->map[dta->i]);
		new = ft_calloc(1, max_l + 1);
		if (!new)
			return (1);
		ft_strlcpy(new, dta->map[dta->i], ft_strlen(dta->map[dta->i]) + 1);
		while ((size_t)dta->j < max_l)
			new[dta->j++] = ' ';
		new[dta->j] = '\0';
		free(dta->map[dta->i]);
		dta->map[dta->i] = new;
		dta->h_map = dta->i;
		dta->w_map = max_l - 1;
	}
	return (0);
}

int	process_textures_and_colors(t_data *data, char **split_text, char **t_c)
{
	if (save_textures_2(data, split_text, t_c))
		return (1);
	if ((!ft_strncmp(split_text[data->i], "F", 1) \
	|| !ft_strncmp(split_text[data->i], "F", 1) \
	|| (!ft_strncmp(split_text[data->i], "C", 1) \
	|| !ft_strncmp(split_text[data->i], "C", 1))) \
	&& check_colors(data, *t_c, split_text[data->i]))
		return (1);
	free(*t_c);
	return (0);
}

void	check_textures(t_data *d, char **texture)
{
	if ((((!ft_strncmp(d->line, "NO", 2) || !ft_strncmp(d->line, "SO", 2) \
	|| !ft_strncmp(d->line, "WE", 2) || !ft_strncmp(d->line, "EA", 2)) \
	&& ((d->line[2] == ' ' || (d->line[2] >= 9 && d->line[2] <= 13)))) \
	|| ((!ft_strncmp(d->line, "F", 1) || !ft_strncmp(d->line, "C", 1)) \
	&& ((d->line[1] == ' ' || (d->line[1] >= 9 && d->line[1] <= 13))))))
	{
		*texture = ft_strjoin(*texture, d->line);
		d->count_textures++;
	}
	else if (ft_strncmp(d->line, "\n", 2) && !(!ft_strncmp(d->line, "F", 1) \
	|| !ft_strncmp(d->line, "C", 1)))
		d->count_textures++;
}
