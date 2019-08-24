/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_newclip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 14:41:02 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/27 14:34:58 by lomasse          ###   ########.fr       */
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

	curr = toclip;
	before = NULL;
	while (curr != NULL)
	{
		nb = nb_outside(wn, curr, side);
		if (nb == 4 || nb == 2 || nb == 1) // <= Need to create a new triangle
		{
			*value += 1;
			toadd = malloc(sizeof(t_mytriangle)); // MALLOC SECURE of not malloc if i find how to dodge
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
				toadd->vertice[2] = find_intersection(wn, curr->vertice[2], curr->vertice[0], side); // troisieme point bordure scren
				curr->vertice[2] = find_intersection(wn, curr->vertice[1], curr->vertice[2], side);
				curr->vertice[0] = toadd->vertice[2]; // point bordure screen 1
			}
			else if (nb & 0x2)
			{
				toadd->vertice[0] = curr->vertice[0];
				toadd->vertice[1] = curr->vertice[2];
				toadd->vertice[2] = find_intersection(wn, curr->vertice[0], curr->vertice[1], side);
				curr->vertice[1] = find_intersection(wn, curr->vertice[2], curr->vertice[1], side);
				curr->vertice[0] = toadd->vertice[2];
			}
			else
			{
				toadd->vertice[0] = curr->vertice[1];
				toadd->vertice[1] = curr->vertice[2];
				toadd->vertice[2] = find_intersection(wn, curr->vertice[2], curr->vertice[0], side);
				curr->vertice[0] = find_intersection(wn, curr->vertice[1], curr->vertice[0], side);
				curr->vertice[2] = toadd->vertice[2];
			}
			toadd->shade = curr->shade;
			curr->next = toadd;
		}
		else if ((((nb & 0x4) >> 2) + ((nb & 0x2) >> 1) + (nb & 0x1)) == 2)
		{
			curr->splitted = 2;
			if (!(nb & 0x4))
			{
				curr->vertice[0] = find_intersection(wn, curr->vertice[2], curr->vertice[0], side);
				curr->vertice[1] = find_intersection(wn, curr->vertice[2], curr->vertice[1], side);
			}
			if (!(nb & 0x2))
			{
				curr->vertice[0] = find_intersection(wn, curr->vertice[1], curr->vertice[0], side);
				curr->vertice[2] = find_intersection(wn, curr->vertice[1], curr->vertice[2], side);
			}
			if (!(nb & 0x1))
			{
				curr->vertice[1] = find_intersection(wn, curr->vertice[0], curr->vertice[1], side);
				curr->vertice[2] = find_intersection(wn, curr->vertice[0], curr->vertice[2], side);
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

void		clipping(t_win *wn, t_mytriangle toclip, t_mytriangle **tostore) // Need to add wn for fullscreen
{
	t_mytriangle	*ret;
	int				side;
	int				nb;

	ret = &toclip;
	side = -1;
	while (++side < 4)
		ret = clip_side(wn, ret, &nb, side);
	while (ret)
	{
		ft_add_triangle_to_lst(*ret, tostore);
		ret = ret->next;
	}
}