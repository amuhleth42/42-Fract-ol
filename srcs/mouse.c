/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:19:14 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/05 15:19:41 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_down(int button, int x, int y, t_data *a)
{
	if (button == SCROLL_UP)
	{
		zoom(a, x, y, 1.0 + 0.1);
		//a->view.zoom *= 1.0 + 0.1;
		//printf("%f\n", a->view.zoom);
	}
	if (button == SCROLL_DOWN)
	{
		zoom(a, x, y, 1.0 - 0.1);
		//a->view.zoom *= 1.0 - 0.1;
		//printf("zoom : %f\n", a->view.zoom);
	}
	fill_image(a);

	return (0);
}
