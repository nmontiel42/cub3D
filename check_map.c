/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:36:51 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/16 17:59:18 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_colors(t_data *d, char *t_c, char *split_text)
{
	int		j;
	int		commas;
	char	**rgb;

	d->k = -1;
	commas = 0;
	while (t_c && t_c[++d->k])
		if (t_c[d->k] == ',')
			commas++;
	rgb = ft_split(t_c, ',');
	d->k = -1;
	while (rgb && rgb[++d->k])
	{
		j = -1;
		while (rgb[d->k][++j])
			if (!ft_isdigit(rgb[d->k][j]))
				return (free_array(&rgb), ft_error(E_CLRS));
		if (ft_atoi(rgb[d->k]) > 255 || ft_atoi(rgb[d->k]) < 0 || commas != 2)
			return (free_array(&rgb), ft_error(E_CLRS));
	}
	if (!ft_strncmp(split_text, "F ", 2))
		d->f_rgb = rgb;
	else if (!ft_strncmp(split_text, "C ", 2))
		d->c_rgb = rgb;
	return (0);
}

int	check_map(t_data *d)
{
	if (check_only_spaces_fl(d) || check_elements_map(d) || fix_map(d))
		return (1);
	d->i = -1;
	while (d->map[++d->i])
	{
		d->j = -1;
		while (d->map[d->i][++d->j])
		{
			d->c = d->map[d->i][d->j];
			if (((d->i == 0 || d->i == d->h_map) || (d->j == 0 \
			|| d->j == d->w_map)) && d->c != ' ' && d->c != '1')
				return (ft_error(E_WALL));
			if (d->i != 0 && d->i != d->h_map && (d->c == '0' \
			|| d->c == 'N' || d->c == 'S' || d->c == 'E' || d->c == 'W') \
			&& ((d->map[d->i][d->j - 1] == 32 || d->map[d->i][d->j + 1] == 32) \
			|| (d->map[d->i - 1][d->j] == 32 || d->map[d->i + 1][d->j] == 32)))
				return (ft_error(E_VYH));
			if (d->c == 'N' || d->c == 'S' || d->c == 'E' || d->c == 'W')
			{
				d->p_x = d->j;
				d->p_y = d->i;
			}
		}
	}
	return (0);
}

int	check_only_spaces_fl(t_data *d)
{
	d->i = -1;
	while (d->map && d->map[++d->i])
	{
		while (d->i == 0 && (d->map[d->i][d->j] == 32 \
		|| (d->map[d->i][d->j] >= 9 && d->map[d->i][d->j] <= 13)))
			d->j++;
		if (d->i == 0 && (d->map[d->i][d->j] != '1' \
		|| d->map[d->i][ft_strlen(d->map[d->i]) - 1] != '1'))
			return (ft_error(E_SPC));
	}
	return (0);
}

int	check_elements_map(t_data *d)
{
	char	c;

	d->i = -1;
	while (d->map && d->map[++d->i])
	{
		d->j = -1;
		while (d->map[d->i][++d->j])
		{
			c = d->map[d->i][d->j];
			if (c != 32 && c != '1' && c != '0'
				&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
				return (ft_error2(E_ELMNT));
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				d->e_counter++;
				d->orientation = c;
			}
		}
	}
	if (d->e_counter != 1)
		return (ft_error2(E_ELMNT));
	return (0);
}

int	check_elements(t_data *d, char **texture)
{
	int	map_found;

	map_found = 0;
	while (d->line && d->line[0] != '1' && d->line[0] != ' ')
	{
		check_textures(d, texture);
		free(d->line);
		d->line = get_next_line(d->fd);
		if (d->line && (d->line[0] == '1' || d->line[0] == ' '))
			map_found = 1;
	}
	if (!map_found)
		return (free(*texture), free(d->line),
			ft_error2(N_MAP));
	if (d->count_textures != 6)
		return (free(*texture), free(d->line), ft_error(E_TEXT));
	if (save_map(d))
		return (free(*texture), 1);
	return (close(d->fd), 0);
}
