/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_newclip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 14:41:02 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/18 18:54:36 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <header_game_engine.h>

/*static void		show_vec(t_myvec v1)
{
	printf("Vertex = %f\t %f\t %f\n", v1.x ,v1.y, v1.z);
}*/

static t_myvec	find_intersection(t_myvec v1, t_myvec v2, char side) // <= V2 is outside L=0, U=1, R=2, D=3
{
	t_myvec	pos;
	t_myvec	dir;
	float	dx;
	float	dy;
	float	c1;
	float	m1;
	float	sdx;
	float	sdy;
	float	c2;
	float	m2;
	t_myvec	intersection;

	if (side == 0 || side == 1)
	{
		pos.x = -1;
		pos.y = -1;
	}
	else
	{
		pos.x = 1;
		pos.y = 1;
	}
	dir.x = pos.x;
	if (side == 0 || side == 1)
	{
		dir.x = pos.x;
		dir.y = 1;
	}
	else
	{
		dir.x = 1;
		dir.y = pos.x;
	}
	dx = v2.x - v1.x; // THIS SHIT IS WRONG (Get inf value on M2 everytime)
	dy = v2.y - v1.y;
	m1 = dy / dx;
	c1 = v1.y - (m1) * v1.x;
	sdx = dir.x - pos.x;
	sdy = dir.y - pos.y;
	m2 = 1;
	c2 = pos.y - (m2) * pos.x;
	intersection.x = (c2 - c1) / ((dy / dx) - (sdy / sdx));
	intersection.y = (dy / dx) * intersection.x + c1;
/*	printf("DX = %f\t DY = %f\t C1 = %f\t M1 = %f\n", dx, dy, c1, dy/dx);
	printf("screen => SDX = %f\t SDY = %f\t C2 = %f\t M2 = %f\n", sdx, sdy, c2, (sdy/sdx));
	printf("First ");
	show_vec(v1);
	printf("Second ");
	show_vec(v2);
	printf("Result ");
	show_vec(intersection);
*/	return (intersection);
}

static t_mytriangle	*left_side(t_mytriangle *toclip)
{
	t_mytriangle	*curr;
	t_mytriangle	*toadd;
	t_myvec			tmp;
	int				nb;

	curr = toclip;
	while (curr != NULL)
	{
		nb = 0;
		if (curr->vertice[0].x < -1)
			nb += 1;
		if (curr->vertice[1].x < -1)
			nb += 2;
		if (curr->vertice[2].x < -1)
			nb += 4;
		if (nb == 4 || nb == 2 || nb == 1) // <= Need to create a new triangle
		{
			toadd = malloc(sizeof(t_mytriangle)); // MALLOC SECURE of not malloc if i find how to dodge
			if (curr->next == NULL)
				toadd->next = NULL;
			else
				toadd->next = curr->next;
			if (nb & 0x4 >> 2)
			{
				tmp = curr->vertice[2]; // Point outside
				toadd->vertice[0] = curr->vertice[0]; // point commun
				toadd->vertice[1] = curr->vertice[1]; // second point inside
				toadd->vertice[2] = find_intersection(curr->vertice[0], curr->vertice[2], 0); // troisieme point bordure scren
				curr->vertice[1] = toadd->vertice[2]; // point bordure screen 1
				curr->vertice[2] = find_intersection(curr->vertice[0], tmp, 0);
			}
			else if (nb & 0x2 >> 1)
			{
				tmp = curr->vertice[1]; // <= MAYBE DOESNT WORK
				toadd->vertice[0] = curr->vertice[0];
				toadd->vertice[1] = curr->vertice[2];
				toadd->vertice[2] = find_intersection(curr->vertice[0], curr->vertice[1], 0);
				curr->vertice[1] = toadd->vertice[2];
				curr->vertice[2] = find_intersection(curr->vertice[2], tmp, 0); // NOT SURE
			}
			else
			{
				tmp = curr->vertice[0];
				toadd->vertice[0] = curr->vertice[1];
				toadd->vertice[1] = curr->vertice[2];
				toadd->vertice[2] = find_intersection(curr->vertice[2], curr->vertice[0], 0);
				curr->vertice[1] = toadd->vertice[2];
				curr->vertice[2] = find_intersection(curr->vertice[1], tmp, 0); // NOT SURE
			}
			curr->next = toadd;
			curr = toadd;
		}
		else if ((((nb & 0x4) >> 2) + ((nb & 0x2) >> 1) + (nb & 0x1)) == 2) // Doesn't recreate anything just reatri value
		{
			printf("2 POINT OUTSIDE\n");
			if (nb & 0x4)
			{
				if (!(nb & 0x2))
					curr->vertice[2] = find_intersection(curr->vertice[1], curr->vertice[2], 0);
				else
					curr->vertice[2] = find_intersection(curr->vertice[0], curr->vertice[2], 0);
			}
			if (nb & 0x2)
			{
				if (!(nb & 0x4))
					curr->vertice[1] = find_intersection(curr->vertice[2], curr->vertice[1], 0);
				else
					curr->vertice[1] = find_intersection(curr->vertice[0], curr->vertice[1], 0);
			}
			if (nb & 0x1)
			{
				if (!(nb & 0x4))
					curr->vertice[0] = find_intersection(curr->vertice[2], curr->vertice[0], 0);
				else
					curr->vertice[0] = find_intersection(curr->vertice[1], curr->vertice[0], 0);
			}
		}
		if (curr != NULL)
			curr = curr->next;
	}
	return (toclip);
}

void		clipping(t_mytriangle toclip, t_mytriangle **tostore)
{
	t_mytriangle *ret;

	printf("Left Start\n");
	ret = left_side(&toclip);
	printf("Left Ended\n");
	while (ret != NULL)
	{
		printf("Ret\n");
		ft_add_triangle_to_lst(*ret, tostore);
		ret = ret->next;
	}
	printf("End\n");
}
