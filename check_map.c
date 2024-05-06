/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:36:51 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/03 11:53:09 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Valida y asigna los colores definidos en el mapa a t_data */

int	check_colors(t_data *d, char *t_c, char *split_text)
{
	int		j;
	int		comas;
	char	**rgb;

	d->k = -1;
	comas = 0;
	while (t_c && t_c[++d->k])
		if (t_c[d->k] == ',')
			comas++;
	rgb = ft_split(t_c, ',');
	d->k = -1;
	while (rgb && rgb[++d->k])
	{
		j = -1;
		while (rgb[d->k][++j])
			if (!ft_isdigit(rgb[d->k][j]))
				return (free_array(&rgb), ft_error(ECLRS));
		if (ft_atoi(rgb[d->k]) > 255 || ft_atoi(rgb[d->k]) < 0 || comas != 2)
			return (free_array(&rgb), ft_error(ECLRS));
	}
	if (!ft_strncmp(split_text, "F ", 2))
		d->f_rgb = rgb;
	else if (!ft_strncmp(split_text, "C ", 2))
		d->c_rgb = rgb;
	return (0);
}

/* Analiza el mapa para comprobar que es valido */

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
				return (ft_error(EWALL));
			if (d->i != 0 && d->i != d->h_map && (d->c == '0' \
			|| d->c == 'N' || d->c == 'S' || d->c == 'E' || d->c == 'W') \
			&& ((d->map[d->i][d->j - 1] == 32 || d->map[d->i][d->j + 1] == 32) \
			|| (d->map[d->i - 1][d->j] == 32 || d->map[d->i + 1][d->j] == 32)))
				return (ft_error(EVYH));
			if (d->c == 'N' || d->c == 'S' || d->c == 'E' || d->c == 'W')
			{
				d->p_x = d->j;
				d->p_y = d->i;
			}
		}
	}
	return (0);
}

/* Verifica si las priemras y las ultimas lineas del mapa son unicamente
espacios u otros caracteres especiales seguidos por un 1 */

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
			return (ft_error(ESPC));
	}
	return (0);
}

/* Verifica si el mapa tiene solo caracteres validos y un elemento de jugador
(N, S, E o W) */

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
				return (ft_error2(ELMNT));
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				d->e_counter++;
				d->orientation = c;
			}
		}
	}
	if (d->e_counter != 1)
		return (ft_error2(ELMNT));
	return (0);
}

/* Lee las lineas del mapa y recopila informacion sobre las texturas y 
los colores. Comprueba que estan las 6 que tiene que haber y si son validas */

int	check_elements(t_data *d, char **text)
{
	while (d->line && d->line[0] != '1' && d->line[0] != ' ')
	{
		if ((!ft_strncmp(d->line, "NO", 2) || !ft_strncmp(d->line, "SO", 2)
				|| !ft_strncmp(d->line, "WE", 2)
				|| !ft_strncmp(d->line, "EA", 2))
			&& (d->line[2] == ' ' || (d->line[2] >= 9 && d->line[2] <= 13)))
		{
			*text = ft_strjoin(*text, d->line);
			d->count_textures++;
		}
		else if ((!ft_strncmp(d->line, "F", 1) || !ft_strncmp(d->line, "C", 1))
			&& (d->line[1] == ' '
				|| (d->line[1] >= 9 && d->line[1] <= 13)))
		{
			*text = ft_strjoin(*text, d->line);
			d->count_textures++;
		}
		free(d->line);
		d->line = get_next_line(d->fd);
	}
	if (d->count_textures != 6)
		return (free(*text), free(d->line), ft_error(ETEXT));
	if (save_map(d))
		return (free(*text), 1);
	return (close(d->fd), 0);
}
