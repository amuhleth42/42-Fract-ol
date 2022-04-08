/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:19:14 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/08 18:47:12 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_down(int button, int x, int y, t_data *a)
{
	if (button == SCROLL_UP)
		zoom(a, x, y, 1.0 + 0.1);
	if (button == SCROLL_DOWN)
		zoom(a, x, y, 1.0 - 0.1);
	if (button == 1)
		a->mouse.left_down = 1;
	render(a);
	return (0);
}

int	mouse_up(int button, int x, int y, t_data *a)
{
	(void) x;
	(void) y;
	if (button == 1)
		a->mouse.left_down = 0;
	return (0);
}

int	mouse_move(int x, int y, t_data *a)
{
	int	dx;
	int	dy;

	a->mouse.lastx = a->mouse.x;
	a->mouse.lasty = a->mouse.y;
	a->mouse.x = x;
	a->mouse.y = y;
	dx = a->mouse.x - a->mouse.lastx;
	dy = a->mouse.y - a->mouse.lasty;
	if (a->mouse.left_down)
		animation_julia(a, dx * 0.01, dx * 0.01);
	return (0);
}
