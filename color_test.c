/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:12:31 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/04 18:17:05 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	put_pixel_to_img(t_img *i, int x, int y, int color)
{
	char	*dst;

	if (0 <= x && x < 1920 && 0 <= y && y < 1080)
	{
		dst = i->addr + (y * i->ll + x * (i->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	add_shade(int color, double shade)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = r - r * shade;
	g = g - g * shade;
	b = b - b * shade;
	return (r << 16 | g << 8 | b);
}

int	mix_color(int c1, int c2, double shade)
{
	return (c1 - shade * c1 + shade * c2);
}

int	get_gradient(int c1, int c2, double shade)
{
	int	r;
	int	g;
	int	b;

	r = mix_color(c1 >> 16 & 0xFF, c2 >> 16 & 0xFF, shade);
	g = mix_color(c1 >> 8 & 0xFF, c2 >> 8 & 0xFF, shade);
	b = mix_color(c1 & 0xFF, c2 & 0xFF, shade);
	return (r << 16 | g << 8 | b);
}

void	draw_lign_gradient(t_img *i, int x, int y, int len)
{
	int	j;
	int	c1;
	int	c2;
	int	distance;

	c2 = 0xF5291C;
	c1 = 0xB67AD9;
	j = 0;
	distance = len - j;
	while (j < len)
	{
		put_pixel_to_img(i, x + j, y, get_gradient(c1, c2, (double)j / distance));
		printf("Shade : %f\n", (double)j / distance);
		j++;
	}
}

int	main(void)
{
	void	*mlx;
	void	*win;
	t_img	i;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "test");
	i.img = mlx_new_image(mlx, 1920, 1080);
	i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.ll, &i.endian);

	draw_lign_gradient(&i, 200, 200, 500);
	mlx_put_image_to_window(mlx, win, i.img, 0, 0);
	mlx_loop(mlx);
}
