/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:21:25 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/05 17:43:45 by amuhleth         ###   ########.fr       */
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

void	clear_img(t_img *i)
{
	ft_bzero(i->addr, WIN_WIDTH * WIN_HEIGHT * i->bpp / 8);
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
			julia(a, x, y);
			//mandelbrot(a, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(a->mlx, a->win, a->i.img, 0, 0);
}

int	loop_render(t_data *a)
{
	render(a);
	return (0);
}

void	init_view(t_data *a)
{
	a->view.xmin = -2.1;
	a->view.xmax = 0.6;
	a->view.ymin = -1.2;
	a->view.ymax = 1.2;
	a->view.zoom = 1.0;
	a->view.offsetx = -0.5;
	a->view.offsety = 0;
	a->view.animation = 0;
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
	init_view(&a);
	animation_julia(&a, 3.3, 3.3);
	//render(&a);
	mlx_key_hook(a.win, &key_hook, &a);
	mlx_hook(a.win, ON_KEYDOWN, 0, &key_down, &a);
	mlx_hook(a.win, ON_MOUSEDOWN, 0, &mouse_down, &a);
//	mlx_hook(a.win, ON_MOUSEMOVE, 0, &mouse_move, &a);
	mlx_loop_hook(a.mlx, &loop_render, &a);
	mlx_loop(a.mlx);
}
