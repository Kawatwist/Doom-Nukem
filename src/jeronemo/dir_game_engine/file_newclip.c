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

static void ft_init_toadd_texture(t_mytriangle **toadd, t_mytriangle *origin)
{
	(*toadd)->texture[0].u = origin->texture[0].u;
	(*toadd)->texture[0].v = origin->texture[0].v;
	(*toadd)->texture[0].w = origin->texture[0].w;
	(*toadd)->texture[1].u = origin->texture[1].u;
	(*toadd)->texture[1].v = origin->texture[1].v;
	(*toadd)->texture[1].w = origin->texture[1].w;
	(*toadd)->texture[2].u = origin->texture[2].u;
	(*toadd)->texture[2].v = origin->texture[2].v;
	(*toadd)->texture[2].w = origin->texture[2].w;
}

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
			ft_init_toadd_texture(&toadd, curr);
			toadd->zbuff = curr->zbuff;
			toadd->splitted = 1;
			toadd->sub = curr->sub + 1;
			curr->splitted = 1;
			if (curr->next == NULL)
				toadd->next = NULL;
			else
				toadd->next = curr->next;
			ft_clipping_texture_one_side(wn, &curr, &toadd, ((side & 0xF) << 4) + (nb & 0xF));
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
	printf("Start clip\n");
	while (++side < 4)
		ret = clip_side(wn, ret, &nb, side);
	while (ret)
	{
		ft_add_triangle_to_lst(*ret, tostore);
		ret = ret->next;
	}
	printf("END clip\n");
}
