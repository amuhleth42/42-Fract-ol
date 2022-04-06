/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:23:34 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/06 16:30:52 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_z	convert_pixel_to_z(t_data *a, int x, int y)
{
	t_z	p;

	p.r = ((double)x / WIN_HEIGHT) * (a->view.xmax - a->view.xmin) / a->view.zoom + a->view.xmin + a->view.offsetx;
	p.i = ((double)y / WIN_HEIGHT) * (a->view.ymax - a->view.ymin) / a->view.zoom + a->view.ymin + a->view.offsety;
	return (p);
}

void	zoom(t_data *a, int x, int y, double i)
{
	double	w;
	double	h;
	double	new_w;
	double	new_h;

	w = (a->view.xmax - a->view.xmin) / a->view.zoom;
	h = (a->view.ymax - a->view.ymin) / a->view.zoom;
	new_w = (a->view.xmax - a->view.xmin) / a->view.zoom / i;
	new_h = (a->view.ymax - a->view.ymin) / a->view.zoom / i;
	a->view.offsetx -= ((double)x / WIN_HEIGHT) * (new_w - w);
	a->view.offsety -= ((double)y / WIN_HEIGHT) * (new_h - h);
	a->view.zoom *= i;
	//printf("%f\n", a->view.offsetx);
	//printf("%f\n", a->view.offsety);
}
void	render(t_data *a)
{
	int	y;
	int	x;

	a->iter_max = 40;
	clear_img(&a->i);
	if (a->view.animation)
	{
		usleep(200);
		animation_julia(a, 0.01, 0.01);
	}
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			a->algo(a, x, y);
			//julia(a, x, y);
			//mandelbrot(a, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(a->mlx, a->win, a->i.img, 0, 0);
}
