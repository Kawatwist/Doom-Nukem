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

t_myvec      find_intersection(t_win *wn, t_myvec v1, t_myvec v2, char side, float *t) // <= V2 is out0 L=0, U=1, R=2, D=3
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
	if (v2.x - v1.x != 0)
	{
		*t = (intersection.x - v1.x) / (v2.x - v1.x);
		if (*t < 0)
			*t = -*t;
	}
	else if (v2.y - v1.y != 0)
	{
		*t = (intersection.y - v1.y) / (v2.y - v1.y);
		if (*t < 0)
			*t = -*t;
	}
	*t = 1; //faut calculer - rapport entre la distance jusqu'a l'interesection et la longueur totale du segment 
	return (intersection);
}

t_myvec 	plane_intersection(t_win *wn, t_myvec *v1, t_myvec *v2, char side, float *t)
{
	t_pi pi;

	if (side == 0)
	{
		pi.plane_p.x = 0;
		pi.plane_p.y = 0;
		pi.plane_p.z = 0;
		pi.plane_p.w = 1;
		pi.plane_n.x = 1;
		pi.plane_n.y = 0;
		pi.plane_n.z = 0;
		pi.plane_n.w = 1;
	}
	if (side == 1)
	{
		pi.plane_p.x = 0;
		pi.plane_p.y = 0;
		pi.plane_p.z = 0;
		pi.plane_p.w = 1;
		pi.plane_n.x = 0;
		pi.plane_n.y = 1;
		pi.plane_n.z = 0;
		pi.plane_n.w = 1;
	}
	if (side == 2)
	{
		pi.plane_p.x = wn->xscreen - 1;
		pi.plane_p.y = 0;
		pi.plane_p.z = 0;
		pi.plane_p.w = 1;
		pi.plane_n.x = -1;
		pi.plane_n.y = 0;
		pi.plane_n.z = 0;
		pi.plane_n.w = 1;
	}
	if (side == 3)
	{
		pi.plane_p.x = 0;
		pi.plane_p.y = wn->yscreen - 1;
		pi.plane_p.z = 0;
		pi.plane_p.w = 1;
		pi.plane_n.x = 0;
		pi.plane_n.y = -1;
		pi.plane_n.z = 0;
		pi.plane_n.w = 1;
	}
	if (side == 4)
	{
		pi.plane_p.x = 0;
		pi.plane_p.y = 0;
		pi.plane_p.z = 0.1;
		pi.plane_p.w = 1;
		pi.plane_n.x = 0;
		pi.plane_n.y = 0;
		pi.plane_n.z = 1;
		pi.plane_n.w = 1;
	}
	pi.start = v1;
	pi.end = v2;
	//printf("\nPLANE INTERSECTION SIDE %d \n%f %f %f\n", side, v1->x, v1->y, v1->z);
	//printf("%f %f %f\n", v2->x, v2->y, v2->z);
	return(edge_intersection(&pi, t));
}

t_myvec 	edge_intersection(t_pi *pi, float *t)
{

		*t = ((pi->plane_p.x - pi->start->x) * pi->plane_n.x + (pi->plane_p.y - pi->start->y) * pi->plane_n.y + (pi->plane_p.z - pi->start->z) * pi->plane_n.z) /
		((pi->end->x - pi->start->x) * pi->plane_n.x + (pi->end->y - pi->start->y) * pi->plane_n.y + (pi->end->z - pi->start->z) * pi->plane_n.z);
		pi->inter.x = pi->start->x + ((pi->end->x - pi->start->x) * (*t));
		pi->inter.y = pi->start->y + ((pi->end->y - pi->start->y) * (*t));
		pi->inter.z = pi->start->z + ((pi->end->z - pi->start->z) * (*t));
		return(pi->inter);
}

int			nb_outside(t_win *wn, t_mytriangle *curr, int side)
{
	int		nb;

	nb = 0;
	if (side == 0)
	{
		curr->vertice[0].x < -0.001 ? nb = 1 : 0;
		curr->vertice[1].x < -0.001 ? nb = nb | 0x2 : 0;
		curr->vertice[2].x < -0.001 ? nb = nb | 0x4 : 0;
	}
	else if (side == 1)
	{
		curr->vertice[0].y < -0.001 ? nb = 1 : 0;
		curr->vertice[1].y < -0.001 ? nb = nb | 0x2 : 0;
		curr->vertice[2].y < -0.001 ? nb = nb | 0x4 : 0;
	}
	else if (side == 2)
	{
		curr->vertice[0].x > wn->xscreen + 0.001 ? nb = 1 : 0;
		curr->vertice[1].x > wn->xscreen + 0.001 ? nb = nb | 0x2 : 0;
		curr->vertice[2].x > wn->xscreen + 0.001 ? nb = nb | 0x4 : 0;
	}
	else if (side == 4)
	{
		curr->vertice[0].z < 0.098 ? nb = 1 : 0;
		curr->vertice[1].z < 0.098 ? nb = nb | 0x2 : 0;
		curr->vertice[2].z < 0.098 ? nb = nb | 0x4 : 0;
	}
	else
	{
		curr->vertice[0].y > wn->yscreen + 0.001 ? nb = 1 : 0;
		curr->vertice[1].y > wn->yscreen + 0.001 ? nb = nb | 0x2 : 0;
		curr->vertice[2].y > wn->yscreen + 0.001 ? nb = nb | 0x4 : 0;
	}
	if (nb == 0)
	{
		//printf("TRIANGLE %f %f - %f %f - %f %f rejected by side %d \n", curr->vertice[0].x, curr->vertice[0].y,
		//	curr->vertice[1].x, curr->vertice[1].y, curr->vertice[2].x, curr->vertice[2].y, side);
	}
	return (nb);
}