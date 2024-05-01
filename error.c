/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:41:45 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/01 16:58:32 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_error(int e)
{
	if (e == WNAME)
		printf("Invalid map format\n");
	else if (e == WARG)
		printf("Invalid arguments\n");
	else if (e == NOFD)
		printf("Invalid file\n");
	else if (e == OMAP)
		printf("Error opening map\n");
	else if (e == EGNL)
		printf("get_next_line failed\n");
	else if (e == EIMG)
		printf("Image error\n");
	else if (e == DCLRS)
		printf("Duplicate colors or textures\n");
	else if (e == ELINE)
		printf("Error obtaining line\n");
	else if (e == ECLRS)
		printf("Error in colors\n");
	else if (e == EWALL)
		printf("Map not closed by walls\n");
	else if (e == EVYH)
		printf("Map H/V incorrect element\n");
	else if (e == ESPC)
		printf("Only spaces in first line\n");
	return (ft_error2(e));
}

int	ft_error2(int e)
{
	if (e == ELMNT)
		printf("Incorrect map elements\n");
	else if (e == ETEXT)
		printf("Incorrect textures\n");
	return (1);
}
