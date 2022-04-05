/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:49:13 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/05 17:22:34 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	mandelbrot(t_data *a, int x, int y)
{
	t_z		c;
	t_z		z;
	int		i;
	double	tmp;

	(void) a;
	c = convert_pixel_to_z(a, x, y);
	z.r = 0;
	z.i = 0;
	i = 0;
	while (i < a->iter_max && z.r * z.r + z.i * z.i < 4)
	{
		tmp = z.r;
		z.r = z.r * z.r - z.i * z.i + c.r;
		z.i = 2 * z.i * tmp + c.i;
		i++;
	}
	if (i != a->iter_max)
		put_pixel_to_img(&a->i, x, y, get_color(COLOR1, COLOR2, (float)i / a->iter_max));
}

void	animation_julia(t_data *a, double r, double i)
{
	static double	rr;
	static double	ii;

	rr += r;
	ii += i;
	a->c_julia.r = cos(rr);
	a->c_julia.i = sin(ii);
	printf("c.r = %f\n", a->c_julia.r);
	printf("c.i = %f\n", a->c_julia.i);
}

void	julia(t_data *a, int x, int y)
{
	t_z		c;
	t_z		z;
	int		i;
	double	tmp;

	(void) a;
	z = convert_pixel_to_z(a, x, y);
	c.r = a->c_julia.r;
	c.i = a->c_julia.i;
	i = 0;
	while (i < a->iter_max && z.r * z.r + z.i * z.i < 4)
	{
		tmp = z.r;
		z.r = z.r * z.r - z.i * z.i + c.r;
		z.i = 2 * z.i * tmp + c.i;
		i++;
	}
	if (i != a->iter_max)
		put_pixel_to_img(&a->i, x, y, get_color(COLOR1, COLOR2, (float)i / a->iter_max));
}
