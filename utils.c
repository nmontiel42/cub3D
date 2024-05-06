/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:35:44 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/03 14:08:41 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Libera un array

void	free_array(char ***str)
{
	int	a;

	if (*str != NULL)
	{
		a = -1;
		while ((*str)[++a] != NULL)
		{
			free((*str)[a]);
			(*str)[a] = NULL;
		}
		free(*str);
		*str = NULL;
	}
}

//pt.2, libera c_rgb , player, ray y direcciones

void	free_data2(t_data *data)
{
	int	i;

	i = -1;
	if (data->c_rgb)
	{
		while (data->c_rgb[++i])
		{
			free(data->c_rgb[i]);
			data->c_rgb[i] = NULL;
		}
		free(data->c_rgb);
		data->c_rgb = NULL;
	}
	if (data->no)
		mlx_delete_texture(data->no);
	if (data->so)
		mlx_delete_texture(data->so);
	if (data->we)
		mlx_delete_texture(data->we);
	if (data->ea)
		mlx_delete_texture(data->ea);
	if (data->person)
		free(data->person);
	if (data->ray)
		free(data->ray);
}

//Libera el mapa y f_rgb

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (data->map)
	{
		while (data->map[++i])
		{
			free(data->map[i]);
			data->map[i] = NULL;
		}
		free(data->map);
		data->map = NULL;
	}
	i = -1;
	if (data->f_rgb)
	{
		while (data->f_rgb[++i])
		{
			free(data->f_rgb[i]);
			data->f_rgb[i] = NULL;
		}
		free(data->f_rgb);
		data->f_rgb = NULL;
	}
	free_data2(data);
}
