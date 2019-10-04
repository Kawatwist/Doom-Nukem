/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_newclip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 14:41:02 by lomasse           #+#    #+#             */
/*   Updated: 2019/08/25 19:50:45 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>
#include <math.h>


t_mytriangle	    *clip_side(t_win *wn, t_mytriangle *toclip, int *value, int side)
{
	t_mytriangle	*curr;
	t_mytriangle	*before;
	t_mytriangle	*toadd;
	int				nb;
	float 			t;

	//printf("CLIP SIDE\n");
	curr = toclip;
	before = NULL;
	while (curr != NULL)
	{
		//printf("????\n");
		//printf("%f %f %f ; %f %f %f ; %f %f %f\n", curr->vertice[0].x, curr->vertice[0].y, curr->vertice[0].z,
		//	curr->vertice[1].x, curr->vertice[1].y, curr->vertice[1].z,
		//	curr->vertice[2].x, curr->vertice[2].y, curr->vertice[2].z);
		nb = nb_outside(wn, curr, side);
		if (nb == 4 || nb == 2 || nb == 1) // <= Need to create a new triangle
		{
			//printf("TWO TRIANGLES BASE TEXTURE: %f %f;%f %f;%f %f\n", curr->texture[0].u, curr->texture[0].v, curr->texture[1].u, curr->texture[1].v, curr->texture[2].u, curr->texture[2].v);
			*value += 1;
			toadd = malloc(sizeof(t_mytriangle)); // MALLOC SECURE of not malloc if i find how to dodge
			toadd->texture[0].u = curr->texture[0].u;
			toadd->texture[0].v = curr->texture[0].v;
			toadd->texture[0].w = curr->texture[0].w;
			toadd->texture[1].u = curr->texture[1].u;
			toadd->texture[1].v = curr->texture[1].v;
			toadd->texture[1].w = curr->texture[1].w;
			toadd->texture[2].u = curr->texture[2].u;
			toadd->texture[2].v = curr->texture[2].v;
			toadd->texture[2].w = curr->texture[2].w;
			toadd->zbuff = curr->zbuff;
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
				toadd->vertice[2] = plane_intersection(wn, &curr->vertice[0], &curr->vertice[2], side, &t);
				//printf("TEST 1 %f %f %f \n", toadd->vertice[2].x, toadd->vertice[2].y, toadd->vertice[2].z);
				toadd->texture[2].u = (curr->texture[2].u - curr->texture[0].u) * t + curr->texture[0].u;
				toadd->texture[2].v = (curr->texture[2].v - curr->texture[0].v) * t + curr->texture[0].v;
				toadd->texture[2].w = (curr->texture[2].w - curr->texture[0].w) * t + curr->texture[0].w; // troisieme point bordure scren
				curr->vertice[2] = plane_intersection(wn, &curr->vertice[1], &curr->vertice[2], side, &t);
				curr->texture[2].u = (curr->texture[2].u - curr->texture[1].u) * t + curr->texture[1].u;
				curr->texture[2].v = (curr->texture[2].v - curr->texture[1].v) * t + curr->texture[1].v;
				curr->texture[2].w = (curr->texture[2].w - curr->texture[1].w) * t + curr->texture[1].w;
				curr->vertice[0] = toadd->vertice[2]; // point bordure screen 1
				curr->texture[0] = toadd->texture[2];
			}
			else if (nb & 0x2)
			{
				toadd->vertice[0] = curr->vertice[0];
				//toadd->vertice[2] = curr->vertice[2];
				toadd->vertice[1] = plane_intersection(wn, &curr->vertice[0], &curr->vertice[1], side, &t);
				toadd->texture[1].u = (curr->texture[1].u - curr->texture[0].u) * t + curr->texture[0].u;
				//printf("TEST 2 %f %f %f \n", toadd->vertice[2].x, toadd->vertice[2].y, toadd->vertice[2].z);
				toadd->texture[1].v = (curr->texture[1].v - curr->texture[0].v) * t + curr->texture[0].v;
				toadd->texture[1].w = (curr->texture[1].w - curr->texture[0].w) * t + curr->texture[0].w; // troisieme point bordure scren
				toadd->vertice[2] = plane_intersection(wn, &curr->vertice[2], &curr->vertice[1], side, &t);
				toadd->texture[2].u = (curr->texture[1].u - curr->texture[2].u) * t + curr->texture[2].u;
				toadd->texture[2].v = (curr->texture[1].v - curr->texture[2].v) * t + curr->texture[2].v;
				toadd->texture[2].w = (curr->texture[1].w - curr->texture[2].w) * t + curr->texture[2].w;
				curr->vertice[1] = toadd->vertice[2];
				curr->texture[1] = toadd->texture[2];
			}
			else
			{
				//toadd->vertice[0] = curr->vertice[1];
				toadd->vertice[1] = curr->vertice[1];
				toadd->texture[1] = curr->texture[1];
				toadd->vertice[2] = plane_intersection(wn, &curr->vertice[2], &curr->vertice[0], side, &t);
				//printf("TEST 3 %f %f %f \n", toadd->vertice[2].x, toadd->vertice[2].y, toadd->vertice[2].z);
				toadd->texture[2].u = (curr->texture[0].u - curr->texture[2].u) * t + curr->texture[2].u;
				toadd->texture[2].v = (curr->texture[0].v - curr->texture[2].v) * t + curr->texture[2].v;
				toadd->texture[2].w = (curr->texture[0].w - curr->texture[2].w) * t + curr->texture[2].w; // troisieme point bordure scren
				toadd->vertice[0] = plane_intersection(wn, &curr->vertice[1], &curr->vertice[0], side, &t);
				toadd->texture[0].u = (curr->texture[0].u - curr->texture[1].u) * t + curr->texture[1].u;
				toadd->texture[0].v = (curr->texture[0].v - curr->texture[1].v) * t + curr->texture[1].v;
				toadd->texture[0].w = (curr->texture[0].w - curr->texture[1].w) * t + curr->texture[1].w;
				curr->vertice[0] = toadd->vertice[2];
				curr->texture[0] = toadd->texture[2];
			}
			//printf("TO ADD TEXTURES: %f %f;%f %f;%f %f\n", toadd->texture[0].u, toadd->texture[0].v, toadd->texture[1].u, toadd->texture[1].v, toadd->texture[2].u, toadd->texture[2].v);
			//printf("CURR TEXTURE: %f %f;%f %f;%f %f\n", curr->texture[0].u, curr->texture[0].v, curr->texture[1].u, curr->texture[1].v, curr->texture[2].u, curr->texture[2].v);
			toadd->shade = curr->shade;
			curr->next = toadd;
		}
		else if ((((nb & 0x4) >> 2) + ((nb & 0x2) >> 1) + (nb & 0x1)) == 2)
		{
			//printf("\n CASE 2");
			curr->splitted = 2;
			if (!(nb & 0x4))
			{
				//printf("\n CASE 2.1");
				curr->vertice[0] = plane_intersection(wn, &curr->vertice[2], &curr->vertice[0], side, &t);
				curr->texture[0].u = (curr->texture[0].u - curr->texture[2].u) * t + curr->texture[2].u;
				curr->texture[0].v = (curr->texture[0].v - curr->texture[2].v) * t + curr->texture[2].v;
				curr->texture[0].w = (curr->texture[0].w - curr->texture[2].w) * t + curr->texture[2].w;
				curr->vertice[1] = plane_intersection(wn, &curr->vertice[2], &curr->vertice[1], side, &t);
				curr->texture[1].u = (curr->texture[1].u - curr->texture[2].u) * t + curr->texture[2].u;
				curr->texture[1].v = (curr->texture[1].v - curr->texture[2].v) * t + curr->texture[2].v;
				curr->texture[1].w = (curr->texture[1].w - curr->texture[2].w) * t + curr->texture[2].w;
			}
			if (!(nb & 0x2))
			{
				//printf("\n CASE 2.2");
				curr->vertice[0] = plane_intersection(wn, &curr->vertice[1], &curr->vertice[0], side, &t);
				curr->texture[0].u = (curr->texture[0].u - curr->texture[1].u) * t + curr->texture[1].u;
				curr->texture[0].v = (curr->texture[0].v - curr->texture[1].v) * t + curr->texture[1].v;
				curr->texture[0].w = (curr->texture[0].w - curr->texture[1].w) * t + curr->texture[1].w;
				curr->vertice[2] = plane_intersection(wn, &curr->vertice[1], &curr->vertice[2], side, &t);
				curr->texture[2].u = (curr->texture[2].u - curr->texture[1].u) * t + curr->texture[1].u;
				curr->texture[2].v = (curr->texture[2].v - curr->texture[1].v) * t + curr->texture[1].v;
				curr->texture[2].w = (curr->texture[2].w - curr->texture[1].w) * t + curr->texture[1].w;
			}
			if (!(nb & 0x1))
			{
				//printf("\n CASE 2.3");
				curr->vertice[1] = plane_intersection(wn, &curr->vertice[0], &curr->vertice[1], side, &t);
				curr->texture[1].u = (curr->texture[1].u - curr->texture[0].u) * t + curr->texture[0].u;
				curr->texture[1].v = (curr->texture[1].v - curr->texture[0].v) * t + curr->texture[0].v;
				curr->texture[1].w = (curr->texture[1].w - curr->texture[0].w) * t + curr->texture[0].w;
				curr->vertice[2] = plane_intersection(wn, &curr->vertice[0], &curr->vertice[2], side, &t);
				curr->texture[2].u = (curr->texture[2].u - curr->texture[0].u) * t + curr->texture[0].u;
				curr->texture[2].v = (curr->texture[2].v - curr->texture[0].v) * t + curr->texture[0].v;
				curr->texture[2].w = (curr->texture[2].w - curr->texture[0].w) * t + curr->texture[0].w;
			}
			//printf("OUT \n%f %f %f\n", curr->vertice[0].x, curr->vertice[0].y, curr->vertice[0].z);
			//	printf("%f %f %f\n", curr->vertice[1].x, curr->vertice[1].y, curr->vertice[1].z);
			//	printf("%f %f %f\n", curr->vertice[2].x, curr->vertice[2].y, curr->vertice[2].z);
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

void		clipping(t_win *wn, t_mytriangle toclip, t_mytriangle **tostore) // Need to add wn for fullscreen
{
	t_mytriangle	*ret;
	int				side;
	int				nb;

	ret = &toclip;
	side = -1;
	while (++side < 4) //5 if close camera detectionmake
		ret = clip_side(wn, ret, &nb, side);
	while (ret)
	{
		ft_add_triangle_to_lst(*ret, tostore);
		ret = ret->next;
	}
}
