/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:18:09 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/03 15:04:14 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Esta funcion lee lineas del fd, las junta en una string y luego la divide en
lineas individuales para almacenarlas en data->map. */

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

/* Esta funcion se asegura de que todas las lineas del mapa tengan la
misma longitud, rellenando las lineas mas cortas con espacios en blanco */

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

/* Esta funcion analiza y carga texturas */

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

/* Esta funcion procesa un bloque de texto que contiene definiciones de texturas
y colores, luego asigna esas texturas y colores dentro de t_data */

int	save_textures(t_data *data, char *text)
{
	char	**split_text;
	char	*t_c;

	t_c = NULL;
	split_text = ft_split(text, '\n');
	data->i = -1;
	while (split_text && split_text[++data->i])
	{
		data->j = data->i;
		while (split_text[++data->j])
			if (!ft_strncmp(split_text[data->i], split_text[data->j], 2))
				return (free_array(&split_text), free(text),
					free(data->line), ft_error(DCLRS));
		if (split_text[data->i][data->j])
		{
			if (save_textures_2(data, split_text, &t_c))
				return (free_array(&split_text), free(t_c), free(text), 1);
			if ((!ft_strncmp(split_text[data->i], "F ", 2)
					|| !ft_strncmp(split_text[data->i], "C ", 2))
				&& check_colors(data, t_c, split_text[data->i]))
				return (free_array(&split_text), free(t_c), free(text), 1);
			free(t_c);
		}
	}
	return (free_array(&split_text), free(text), 0);
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
	return (0);
}
