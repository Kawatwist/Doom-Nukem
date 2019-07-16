/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicshape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:29:27 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/16 16:25:43 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "header_bresenham.h"

void		drawsquare(void	**pixels, int pitch, SDL_Rect rect, t_color color)
{
	t_point	pos;

	pos.x = rect.x;
	while (pos.x < rect.x + rect.w)
	{
		pos.y = rect.y;
		while (pos.y < rect.y + rect.h)
		{
			drawpoint(pixels, pitch, pos, color);
			pos.y += 1;
		}
		pos.x += 1;
	}
}

void		drawcircle(void **pixels, int pitch, t_point origin, int rayon)
{
	t_point	pos;
	float	k;

	pos.x = origin.x - (rayon >> 1);
	while (pos.x < origin.x + (rayon >> 1))
	{
		pos.y = origin.y - (rayon >> 1);
		while (pos.y < origin.y + (rayon >> 1))
		{
			k = (((pos.x << 1) / rayon) * ((pos.x << 1) / rayon)) + ((pos.y / rayon) * (pos.y / rayon));
			if (k > 0.95 && k < 1.08)
				drawpoint(pixels, pitch, pos, itocolor(0xFF00FF));
			pos.y += 1;
		}
		pos.x += 1;
	}
}

void		drawlinexyz(t_win *wn, int color, t_xyz_point origin, t_xyz_point dest)
{
	t_point	neworigin;
	t_point	newdest;
	
	neworigin.x = origin.a;
	neworigin.y = origin.b;
	newdest.x = dest.a;
	newdest.y = dest.b;
	wn->color = color;
	bresenham(wn, &neworigin, &newdest);
}

void		drawline(t_win *wn, int color, t_point origin, t_point dest)
{
	wn->color = color;
	bresenham(wn, &origin, &dest);
}

void		drawpointintcolor(void **pixels, int pitch, t_point position, int color)
{
	int	place;

	place = (position.y * (pitch >> 2)) + (position.x);
	(((int*)pixels))[place] = color;
}

void		drawpoint(void **pixels, int pitch, t_point position, t_color color)
{
	int	place;

	place = (position.y * (pitch >> 2)) + (position.x);
	(((int*)pixels))[place] = ((color.r << 24) + (color.g << 16) + (color.b << 8) + color.a);
}
