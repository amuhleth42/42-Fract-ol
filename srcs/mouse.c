/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:19:14 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/05 16:33:22 by amuhleth         ###   ########.fr       */
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
	render(a);

	return (0);
}
/*
int	mouse_move(int x, int y, t_data *a)
{
	int	dx;
	int	dy;

	a->mouse.lastx = a->mouse.x;
	a->mouse.lasty = a->mouse.y;
	dx = a->mouse.x - a->mouse.lastx;
	dy = a->mouse.y - a->mouse.lasty;
	if (a->mouse.left_down)
		change_julia(a, dy);
}*/
