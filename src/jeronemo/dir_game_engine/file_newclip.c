/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_newclip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 14:41:02 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/24 14:22:45 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <header_game_engine.h>
#include <math.h>

void		show_vec(t_myvec v1)
{
	printf("Vertex = %f\t %f\t %f\n", v1.x ,v1.y, v1.z);
}
/*
static double	lineslope(t_myvec v1, t_myvec v2)
{
	if (v1.x - v2.x == 0.0)
		return (0.0);
	else
		return ((v1.y - v2.y) / (v1.x - v2.x));
}*/

static t_myvec	find_intersection(t_myvec v1, t_myvec v2, char side) // <= V2 is out0 L=0, U=1, R=2, D=3
{
	t_myvec	pos;
	t_myvec	dir;
	t_myvec	intersection;
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
		pos.x = XSCREEN - 20;
		pos.y = YSCREEN - 100;
	}
	side == 0 ? dir.x = 20 : 0;
	side == 0 ? dir.y = YSCREEN - 100 : 0;
	side == 1 ? dir.x = XSCREEN - 20 : 0;
	side == 1 ? dir.y = 100 : 0;
	side == 2 ? dir.x = XSCREEN - 20 : 0;
	side == 2 ? dir.y = 100 : 0;
	side == 3 ? dir.x = 20 : 0;
	side == 3 ? dir.y = YSCREEN - 100 : 0;
	a1 = v2.y - v1.y;
	b1 = v1.x - v2.x;
	c1 = a1 * v1.x + b1 * v1.y;
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

static int			nb_outside(t_mytriangle *curr, int side)
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
		curr->vertice[0].x > XSCREEN - 20 ? nb = 1 : 0;		// ATTENTION FULLSCREEN
		curr->vertice[1].x > XSCREEN - 20 ? nb = nb | 0x2 : 0;
		curr->vertice[2].x > XSCREEN - 20 ? nb = nb | 0x4 : 0;
	}
	else
	{
		curr->vertice[0].y > YSCREEN - 100 ? nb = 1 : 0;
		curr->vertice[1].y > YSCREEN - 100 ? nb = nb | 0x2 : 0;
		curr->vertice[2].y > YSCREEN - 100 ? nb = nb | 0x4 : 0;
	}
	return (nb);
}

static t_mytriangle	*left_side(t_mytriangle *toclip, int *value, int side)
{
	t_mytriangle	*curr;
	t_mytriangle	*before;
	t_mytriangle	*toadd;
	int				nb;

	curr = toclip;
	before = NULL;
	while (curr != NULL)
	{
		nb = nb_outside(curr, side);
		if (nb == 4 || nb == 2 || nb == 1) // <= Need to create a new triangle
		{
			*value += 1;
			toadd = malloc(sizeof(t_mytriangle)); // MALLOC SECURE of not malloc if i find how to dodge
			toadd->splitted = 1;
			toadd->sub = curr->sub + 1;
			curr->splitted = 1;
			if (curr->next == NULL)
				toadd->next = NULL;
			else
				toadd->next = curr->next;
			if (nb & 0x4)
			{
				toadd->vertice[0] = curr->vertice[0]; // point commun
				toadd->vertice[1] = curr->vertice[1]; // second point inside
				toadd->vertice[2] = find_intersection(curr->vertice[2], curr->vertice[0], side); // troisieme point bordure scren
				curr->vertice[2] = find_intersection(curr->vertice[1], curr->vertice[2], side);
				curr->vertice[0] = toadd->vertice[2]; // point bordure screen 1
			}
			else if (nb & 0x2)
			{
				toadd->vertice[0] = curr->vertice[0];
				toadd->vertice[1] = curr->vertice[2];
				toadd->vertice[2] = find_intersection(curr->vertice[0], curr->vertice[1], side);
				curr->vertice[1] = find_intersection(curr->vertice[2], curr->vertice[1], side);
				curr->vertice[0] = toadd->vertice[2];
			}
			else
			{
				toadd->vertice[0] = curr->vertice[1];
				toadd->vertice[1] = curr->vertice[2];
				toadd->vertice[2] = find_intersection(curr->vertice[2], curr->vertice[0], side);
				curr->vertice[0] = find_intersection(curr->vertice[1], curr->vertice[0], side);
				curr->vertice[2] = toadd->vertice[2];
			}
			toadd->shade = curr->shade;
			curr->next = toadd;
//			curr = toclip;
		}
		else if ((((nb & 0x4) >> 2) + ((nb & 0x2) >> 1) + (nb & 0x1)) == 2)
		{
			curr->splitted = 2;
			if (!(nb & 0x4))
			{
				curr->vertice[0] = find_intersection(curr->vertice[2], curr->vertice[0], side);
				curr->vertice[1] = find_intersection(curr->vertice[2], curr->vertice[1], side);
			}
			if (!(nb & 0x2))
			{
				curr->vertice[0] = find_intersection(curr->vertice[1], curr->vertice[0], side);
				curr->vertice[2] = find_intersection(curr->vertice[1], curr->vertice[2], side);
			}
			if (!(nb & 0x1))
			{
				curr->vertice[1] = find_intersection(curr->vertice[0], curr->vertice[1], side);
				curr->vertice[2] = find_intersection(curr->vertice[0], curr->vertice[2], side);
			}
			curr->sub += 1;
			before = curr;
			curr = curr->next;
		}
		else if (curr != NULL && nb != 7)
		{
			before = curr;
			curr = curr->next;
		}
		else // nb == 7 Triangle out
		{
			if (before == NULL)
				toclip = curr->next;
			else
				before->next = curr->next;
			curr = curr->next;
		}
	}
	return (toclip);
}

t_mytriangle *down_side(t_mytriangle *toclip, int *value, int side); // PROTO

void		clipping(t_mytriangle toclip, t_mytriangle **tostore)
{
	t_mytriangle	*ret;
	int				side;
	int				nb;

	ret = &toclip;
	side = -1;
	while (++side < 4)
		ret = left_side(ret, &nb, side);
	while (ret)
	{
		ft_add_triangle_to_lst(*ret, tostore);
		ret = ret->next;
	}
}
