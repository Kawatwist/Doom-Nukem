/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicshape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:29:27 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/27 14:25:46 by lomasse          ###   ########.fr       */
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

void		drawlinexyz(t_win *wn, int color, t_xyz_point origin, t_xyz_point dest)
{
	t_point	neworigin;
	t_point	newdest;
	
	neworigin.x = origin.a;
	neworigin.y = origin.b;
	newdest.x = dest.a;
	newdest.y = dest.b;
	wn->coolor = color;
	bresenhamburger(wn, &neworigin, &newdest);
}

void		drawline(t_win *wn, int color, t_point origin, t_point dest)
{
	wn->coolor = color;
	bresenhamburger(wn, &origin, &dest);
}

void		drawpointintcolor(void **pixels, int pitch, t_point position, int color)
{
	((int*)pixels)[(int)((position.y * (pitch >> 2)) + (position.x))] = color;
}

void		drawpoint(void **pixels, int pitch, t_point position, t_color color)
{
	int	place;

	place = (position.y * (pitch >> 2)) + (position.x);
	(((int*)pixels))[place] = ((color.r << 24) + (color.g << 16) + (color.b << 8) + color.a);
}
