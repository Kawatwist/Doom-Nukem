/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawpoly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:32:23 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/19 16:24:10 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		drawtriangle(t_win *wn, t_vec *v1, t_vec *v2, t_vec *v3)
{
	//print_triangle(v1, v2, v3);
	SDL_RenderDrawLine(wn->rend, (int)v1->x, (int)v1->y, (int)v2->x, (int)v2->y);
	SDL_RenderDrawLine(wn->rend, (int)v1->x, (int)v1->y, (int)v3->x, (int)v3->y);
	SDL_RenderDrawLine(wn->rend, (int)v2->x, (int)v2->y, (int)v3->x, (int)v3->y);
}

static void		drawpoly(t_win *wn, t_poly *curr, t_vec *ver)
{
	int		i;

	i = 0;
	while (i < curr->nb_indices)
	{
		drawtriangle(wn, &ver[curr->indices[i]], &ver[curr->indices[i + 1]], &ver[curr->indices[i + 2]]);
		i += 3;
	}
}

void			maindrawpoly(t_win *wn)
{
	t_poly	*curr;

	curr = wn->poly;
	SDL_SetRenderDrawColor(wn->rend, 255, 0, 0, 0);
	while (curr != NULL)
	{
		curr->ver_tmp = ver_copy(wn, curr->ver_list, curr->nb_ver);
		rasterization(wn, curr);
		drawpoly(wn, curr, curr->ver_tmp);
		free(curr->ver_tmp);
		curr = curr->next;
	}
	initmatrice(wn->rast->model);
}
