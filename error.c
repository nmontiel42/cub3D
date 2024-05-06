/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:41:45 by nmontiel          #+#    #+#             */
/*   Updated: 2024/05/03 13:52:39 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_error(int e)
{
	if (e == WNAME)
		printf("Error\nInvalid map format\n");
	else if (e == WARG)
		printf("Error\nInvalid arguments\n");
	else if (e == NOFD)
		printf("Error\nInvalid file\n");
	else if (e == OMAP)
		printf("Error\nFailed opening map\n");
	else if (e == EGNL)
		printf("Error\nget_next_line failed\n");
	else if (e == EIMG)
		printf("Error\nImage error\n");
	else if (e == DCLRS)
		printf("Error\nDuplicate colors or textures\n");
	else if (e == ELINE)
		printf("Error\nFailed obtaining line\n");
	else if (e == ECLRS)
		printf("Error\nError in colors\n");
	else if (e == EWALL)
		printf("Error\nMap not closed by walls\n");
	else if (e == EVYH)
		printf("Error\nMap H/V incorrect element\n");
	else if (e == ESPC)
		printf("Error\nOnly spaces in first line\n");
	return (ft_error2(e));
}

int	ft_error2(int e)
{
	if (e == ELMNT)
		printf("Error\nIncorrect map elements\n");
	else if (e == ETEXT)
		printf("Error\nIncorrect textures or colors\n");
	else if (e == ELIM)
		printf("Error\nHeight, width or fov out of limits\n");
	return (1);
}
