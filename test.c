/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:42:01 by amuhleth          #+#    #+#             */
/*   Updated: 2022/02/28 17:42:12 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	put_pixel_to_img(t_img *i, int x, int y, int color)
{
	char	*dst;

	if (0 <= x && x < WIN_WIDTH && 0 <= y && y < WIN_HEIGHT)
	{
		dst = i->addr + (y * i->ll + x * (i->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

t_z	convert_pixel_to_z(t_data *a, int x, int y)
{
	t_z	p;

	p.r = ((double)x / WIN_HEIGHT) * (a->view.xmax - a->view.xmin) / a->view.zoom + a->view.xmin + a->view.offsetx;
	p.i = ((double)y / WIN_HEIGHT) * (a->view.ymax - a->view.ymin) / a->view.zoom + a->view.ymin + a->view.offsety;
	return (p);
}

int	mandelbrot(t_data *a, int x, int y)
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
	if (i == a->iter_max)
		return (1);
	return (0);
}

void	clear_img(t_img *i)
{
	ft_bzero(i->addr, WIN_WIDTH * WIN_HEIGHT * i->bpp / 8);
}

void	fill_image(t_data *a)
{
	int	y;
	int	x;
	int	res;

	a->iter_max = 40;
	clear_img(&a->i);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			res = mandelbrot(a, x, y);
			if (res)
				put_pixel_to_img(&a->i, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(a->mlx, a->win, a->i.img, 0, 0);
}

void	init_zoom(t_data *a)
{
	a->view.xmin = -2.1;
	a->view.xmax = 0.6;
	a->view.ymin = -1.2;
	a->view.ymax = 1.2;
	a->view.zoom = 1.0;
	a->view.offsetx = -0.5;
	a->view.offsety = 0;
}

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

/*int	mouse_move(int x, int y, t_data *a)
{
}*/

int	main(void)
{
	t_data	a;

	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, WIN_WIDTH, WIN_HEIGHT, "FRACTOL");
	a.i.img = mlx_new_image(a.mlx, WIN_WIDTH, WIN_HEIGHT);
	a.i.addr = mlx_get_data_addr(a.i.img, &a.i.bpp, &a.i.ll, &a.i.endian);
	init_zoom(&a);
	fill_image(&a);
	//mlx_put_image_to_window(a.mlx, a.win, a.i.img, 0, 0);
	mlx_key_hook(a.win, &key_hook, &a);
	mlx_hook(a.win, ON_MOUSEDOWN, 0, &mouse_down, &a);
//	mlx_hook(a.win, ON_MOUSEMOVE, 0, &mouse_move, &a);
	mlx_loop(a.mlx);
}
