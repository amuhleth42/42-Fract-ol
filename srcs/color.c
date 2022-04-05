/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amuhleth <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:30:33 by amuhleth          #+#    #+#             */
/*   Updated: 2022/04/05 15:43:21 by amuhleth         ###   ########.fr       */
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
