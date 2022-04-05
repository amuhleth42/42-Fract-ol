/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:18:44 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/05 16:31:10 by amuhleth         ###   ########.fr       */
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

int	key_down(int key, t_data *a)
{
	if (key == 49)
	{
		if (a->view.animation)
			a->view.animation = 0;
		else
			a->view.animation = 1;
	}
	return (0);
}
