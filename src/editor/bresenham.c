/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 17:52:27 by llejeune          #+#    #+#             */
/*   Updated: 2019/07/31 17:53:35 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_bres(t_win *wn, t_point *alst, t_point *next)
{
	wn->bres.x = alst->x;
	wn->bres.y = alst->y;
	wn->bres.x1 = next->x;
	wn->bres.y1 = next->y;
	wn->bres.dx = wn->bres.x1 - wn->bres.x;
	wn->bres.dy = wn->bres.y1 - wn->bres.y;
	wn->bres.sx = (wn->bres.dx >= 0) ? 1 : -1;
	wn->bres.sy = (wn->bres.dy >= 0) ? 1 : -1;
	wn->bres.dx = abs(2 * wn->bres.dx);
	wn->bres.dy = abs(2 * wn->bres.dy);
	wn->bres.e = (wn->bres.dx > wn->bres.dy) ?
		wn->bres.dx / 2 : wn->bres.dy / 2;
}

static void	bres_x(t_win *wn)
{
	if (wn->bres.x <= wn->xscreen && wn->bres.x >= 0
			&& wn->bres.y <= wn->yscreen && wn->bres.y >= 0)
		SDL_RenderDrawPoint(wn->rend, wn->bres.x, wn->bres.y);
	wn->bres.e = wn->bres.e - wn->bres.dy;
	if (wn->bres.e < 0)
	{
		wn->bres.y += wn->bres.sy;
		wn->bres.e = wn->bres.e + wn->bres.dx;
	}
	wn->bres.x += wn->bres.sx;
}

static void	bres_y(t_win *wn)
{
	if (wn->bres.x <= wn->xscreen && wn->bres.x >= 0
			&& wn->bres.y <= wn->yscreen && wn->bres.y >= 0)
		SDL_RenderDrawPoint(wn->rend, wn->bres.x, wn->bres.y);
	wn->bres.e = wn->bres.e - wn->bres.dx;
	if (wn->bres.e < 0)
	{
		wn->bres.x += wn->bres.sx;
		wn->bres.e = wn->bres.e + wn->bres.dy;
	}
	wn->bres.y += wn->bres.sy;
}

void	bresenham(t_win *wn, t_point *alst, t_point *next)
{
	init_bres(wn, alst, next);
	if (wn->bres.dx > wn->bres.dy)
	{
		while (wn->bres.x < wn->bres.x1 && wn->bres.sx > 0)
			bres_x(wn);
		while (wn->bres.x > wn->bres.x1 && wn->bres.sx < 0)
			bres_x(wn);
	}
	else
	{
		while (wn->bres.y < wn->bres.y1 && wn->bres.sy > 0)
			bres_y(wn);
		while (wn->bres.y > wn->bres.y1 && wn->bres.sy < 0)
			bres_y(wn);
	}
}
