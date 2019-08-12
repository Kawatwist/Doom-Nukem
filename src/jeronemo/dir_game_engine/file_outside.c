/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_outside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:34:02 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/27 14:34:56 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>
#include <math.h>

static void         finddir(t_win *wn, char side, t_myvec *pos, t_myvec *dir)
{
    if (side == 0 || side == 1)
	{
		pos->x = 20;
		pos->y = 100;
	}
	else
	{
		pos->x = wn->xscreen - 20;
		pos->y = wn->yscreen - 100;
	}
	dir->x = (side == 0 || side == 3 ? 20 : wn->xscreen - 20);
	dir->y = (side == 0 || side == 3 ? wn->yscreen - 100 : 100);
}

t_myvec      find_intersection(t_win *wn, t_myvec v1, t_myvec v2, char side) // <= V2 is out0 L=0, U=1, R=2, D=3
{
	t_myvec	pos;
	t_myvec	dir;
	t_myvec	intersection;
    double  a1;
    double  b1;
	double	determinant;
	double	c1;
	double	a2;
	double	b2;
	double	c2;

    finddir(wn, side, &pos, &dir);
	a1 = v2.y - v1.y;
	b1 = v1.x - v2.x;
	c1 = a1 * v1.x + b1 * v1.y;
	a2 = dir.y - pos.y;
	b2 = pos.x - dir.x;
	c2 = a2 * (pos.x) + b2 * pos.y;
	determinant = a1 * b2 - a2 * b1;
	intersection.x = (determinant != 0 ? (b2 * c1 - b1 * c2) / determinant : 0);
	intersection.y = (determinant != 0 ? (a1 * c2 - a2 * c1) / determinant : 0);
	return (intersection);
}

int			nb_outside(t_win *wn, t_mytriangle *curr, int side)
{
	int		nb;

	nb = 0;
	if (side == 0)
	{
		curr->vertice[0].x < 20 ? nb = 1 : 0;
		curr->vertice[1].x < 20 ? nb = nb | 0x2 : 0;
		curr->vertice[2].x < 20 ? nb = nb | 0x4 : 0;
	}
	else if (side == 1)
	{
		curr->vertice[0].y < 100 ? nb = 1 : 0;
		curr->vertice[1].y < 100 ? nb = nb | 0x2 : 0;
		curr->vertice[2].y < 100 ? nb = nb | 0x4 : 0;
	}
	else if (side == 2)
	{
		curr->vertice[0].x > wn->xscreen - 20 ? nb = 1 : 0;
		curr->vertice[1].x > wn->xscreen - 20 ? nb = nb | 0x2 : 0;
		curr->vertice[2].x > wn->xscreen - 20 ? nb = nb | 0x4 : 0;
	}
	else
	{
		curr->vertice[0].y > wn->yscreen - 100 ? nb = 1 : 0;
		curr->vertice[1].y > wn->yscreen - 100 ? nb = nb | 0x2 : 0;
		curr->vertice[2].y > wn->yscreen - 100 ? nb = nb | 0x4 : 0;
	}
	return (nb);
}