/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:18:44 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/05 15:19:03 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int key, t_data *a)
{
	if (key == 53)
	{
		mlx_destroy_image(a->mlx, a->i.img);
		mlx_destroy_window(a->mlx, a->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
