/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:36:10 by llejeune          #+#    #+#             */
/*   Updated: 2019/09/12 15:36:48 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static t_point	find_intersection(t_win *wn, t_point p1, t_point p2, char side) // <= p2 is out0 L=0, U=1, R=2, D=3
{
	t_point	pos;
	t_point	dir;
	t_point	intersection;
	double	determinant;
	double	a1;
	double	b1;
	double	c1;
	double	a2;
	double	b2;
	double	c2;

	if (side == 0 || side == 1)
	{
		pos.x = 20;
		pos.y = 100;
	}
	else
	{
		pos.x = wn->xscreen - 20;
		pos.y = wn->yscreen - 100;
	}
	side == 0 ? dir.x = 20 : 0;
	side == 0 ? dir.y = wn->yscreen - 100 : 0;
	side == 1 ? dir.x = wn->xscreen - 20 : 0;
	side == 1 ? dir.y = 100 : 0;
	side == 2 ? dir.x = wn->xscreen - 20 : 0;
	side == 2 ? dir.y = 100 : 0;
	side == 3 ? dir.x = 20 : 0;
	side == 3 ? dir.y = wn->yscreen - 100 : 0;
	a1 = p2.y - p1.y;
	b1 = p1.x - p2.x;
	c1 = a1 * p1.x + b1 * p1.y;
	a2 = dir.y - pos.y;
	b2 = pos.x - dir.x;
	c2 = a2 * (pos.x) + b2 * pos.y;
	determinant = a1 * b2 - a2 * b1;
	if (determinant == 0)
	{
		intersection.x = 0;
		intersection.y = 0;
	}
	else
	{
		intersection.x = (b2 * c1 - b1 * c2) / determinant;
		intersection.y = (a1 * c2 - a2 * c1) / determinant;
	}
	return (intersection);
}

void    draw_to_find_position(t_win *wn, t_edit *edit)
{
    t_point     start;
    t_point     end;
    t_point     intersection;

    start = create_t_point(wn->input->x, wn->input->y);
    end = create_t_point(edit->map->x, edit->map->y);
    if (end.y < 0)
        intersection = find_intersection(wn, start, end, 1);
    if(end.y > wn->yscreen)
        intersection = find_intersection(wn, start, end, 3);
    if (end.x < 0)
        intersection = find_intersection(wn, start, end, 0);
    if (end.x > wn->xscreen)
        intersection = find_intersection(wn, start, end, 2);
    if (end.x >= 0 && end.x <= wn->xscreen && end.y >= 0 && end.y <= wn->yscreen)
        intersection = create_t_point(end.x, end.y);
    SDL_SetRenderDrawColor(wn->rend, 255, 0, 0, 0) < 0 ? stop_exec("drawcolor failed in find_map\n", wn) : 0;
    bresenham(wn, &start, &intersection);
    SDL_RenderPresent(wn->rend);
}