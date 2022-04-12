/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:21:25 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/12 19:06:07 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	handle_no_arg(void)
{
	ft_putstr_fd("Please enter an argument : julia or mandelbrot\n", 2);
	exit(EXIT_SUCCESS);
}

void	parser(t_data *a, char *input)
{
	if (ft_strncmp(input, "mandelbrot", 10) == 0)
		a->algo = &mandelbrot;
	else if (ft_strncmp(input, "julia", 5) == 0)
		a->algo = &julia;
	else
	{
		ft_putstr_fd("error : invalid argument\n", 1);
		ft_putstr_fd("Please enter a valid argument : julia or mandelbrot\n", 2);
		exit(EXIT_SUCCESS);
	}
}

int	red_cross(t_data *a)
{
	mlx_destroy_image(a->mlx, a->i.img);
	mlx_destroy_window(a->mlx, a->win);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	a;

	(void) argv;
	if (argc != 2)
		handle_no_arg();
	ft_bzero(&a, sizeof(a));
	parser(&a, argv[1]);
	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, WIN_WIDTH, WIN_HEIGHT, "FRACTOL");
	a.i.img = mlx_new_image(a.mlx, WIN_WIDTH, WIN_HEIGHT);
	a.i.addr = mlx_get_data_addr(a.i.img, &a.i.bpp, &a.i.ll, &a.i.endian);
	init_view(&a);
	animation_julia(&a, 0, 0);
	mlx_key_hook(a.win, &key_hook, &a);
	mlx_hook(a.win, ON_KEYDOWN, 0, &key_down, &a);
	mlx_hook(a.win, ON_MOUSEDOWN, 0, &mouse_down, &a);
	mlx_hook(a.win, ON_MOUSEUP, 0, &mouse_up, &a);
	mlx_hook(a.win, ON_MOUSEMOVE, 0, &mouse_move, &a);
	mlx_hook(a.win, ON_DESTROY, 0, &red_cross, &a);
	mlx_loop_hook(a.mlx, &loop_render, &a);
	mlx_loop(a.mlx);
}
