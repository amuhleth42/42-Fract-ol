/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:30:33 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/06 16:39:50 by amuhleth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int	mix_color(int c1, int c2, float shade)
{
	return (c1 - shade * c1 + shade * c2);
}

int	get_color(int c1, int c2, float shade)
{
	int	r;
	int	g;
	int	b;

	r = mix_color(c1 >> 16 & 0xFF, c2 >> 16 & 0xFF, shade);
	g = mix_color(c1 >> 8 & 0xFF, c2 >> 8 & 0xFF, shade);
	b = mix_color(c1 & 0xFF, c2 & 0xFF, shade);
	return (r << 16 | g << 8 | b);
}

int	rainbow_gradient(float shade)
{
	if (shade < 0.2)
		return (get_color(COLOR1, COLOR2, shade * 5));
	else if (shade < 0.4)
		return (get_color(COLOR2, COLOR3, (shade - 0.2) * 5));
	else if (shade < 0.6)
		return (get_color(COLOR3, COLOR4, (shade - 0.4) * 5));
	else if (shade < 0.8)
		return (get_color(COLOR4, COLOR5, (shade - 0.6) * 5));
	else
		return (get_color(COLOR5, COLOR6, (shade - 0.8) * 5));
}
