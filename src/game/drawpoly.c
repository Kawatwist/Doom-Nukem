/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawpoly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:32:23 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/15 13:27:46 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		matrice(t_win *wn, t_poly *curr,)
{
}

static void		drawtriangle(t_win *wn, t_vec *v1, t_vec *v2, t_vec *v3)
{
	SDL_RenderDrawLine(wn->rend, v1->x, v1->y, v2->x, v2->y);
	SDL_RenderDrawLine(wn->rend, v1->x, v1->y, v3->x, v3->y);
	SDL_RenderDrawLine(wn->rend, v2->x, v2->y, v3->x, v3->y);
}

static void		drawpoly(t_win *wn, t_poly *curr)
{
	int		i;
	t_vec	point[3];

	i = 0;
	while (i < curr->nb_indices)
	{
		matrice(wn, curr, point);
		drawtriangle(wn, &curr->ver_list[curr->indices[i]], &curr->ver_list[curr->indices[i + 1]], &curr->ver_list[curr->indices[i + 2]]);
		i += 3;
	}
}

void			maindrawpoly(t_win *wn)
{
	t_poly	*curr;

	curr = wn->poly;
	SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 0);
	while (curr != NULL)
	{
		drawpoly(wn, curr);
		curr = curr->next;
	}
}
