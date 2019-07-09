/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:56:46 by llejeune          #+#    #+#             */
/*   Updated: 2019/07/05 15:56:48 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	showelem(t_win *wn)
{
	t_elem		*curr;
	t_point		*point;
	t_point		start;
	t_point		end;
	t_point		*tmp;

	curr = wn->elem;
	while (curr != NULL)
	{
		point = curr->point;
		SDL_SetRenderDrawColor(wn->rend, 255, 255, 255, 0);
		while (point != NULL && point->next != NULL)
		{
			start = create_t_point(point->x * wn->map->size + wn->map->x, point->y * wn->map->size + wn->map->y);
			end = create_t_point(point->next->x * wn->map->size + wn->map->x, point->next->y * wn->map->size + wn->map->y);
			bresenham(wn, &start, &end);
			point = point->next;
		}
		if (curr->next == NULL && point != NULL)
		{
			start = create_t_point(point->x * wn->map->size + wn->map->x, point->y * wn->map->size + wn->map->y);
			end = create_t_point(wn->input->x, wn->input->y);
			bresenham(wn, &start, &end);
		}
		if (curr->nb_pt > 4 && curr->next != NULL)
		{
			start = create_t_point(curr->point->x * wn->map->size + wn->map->x, curr->point->y * wn->map->size + wn->map->y);
			tmp = curr->point;
			find_last_point(wn, &tmp);
			end = create_t_point(tmp->x * wn->map->size + wn->map->x, tmp->y * wn->map->size + wn->map->y);
			bresenham(wn, &start, &end);
		}
		curr = curr->next;
	}
}

static void	showline2(t_win *wn)
{
	float		i;
	float		j;
	t_point		start;
	t_point		end;

	j = wn->map->y;
	i = wn->map->x;
	if (wn->map->size > 1)
	{
		SDL_SetRenderDrawColor(wn->rend, 50 + (wn->map->size * 20 / 6),
				50 + (wn->map->size * 20 / 6),
				50 + (wn->map->size * 20 / 6), 0);
		while (j <= wn->map->y + wn->map->h)
		{
			start = create_t_point(wn->map->x, j);
			end = create_t_point(wn->map->w + wn->map->x, j);
			bresenham(wn, &start, &end);
			j += wn->map->h / 40;
		}
		j = wn->map->y;
		while (i <= wn->map->x + wn->map->w)
		{
			start = create_t_point(i, wn->map->y);
			end = create_t_point(i, wn->map->h + wn->map->y);
			bresenham(wn, &start, &end);
			i += wn->map->w / 40;
		}
	}
}

static void	showline(t_win *wn)
{
	float		i;
	float		j;
	t_point		start;
	t_point		end;

	j = wn->map->y;
	i = wn->map->x;
	showline2(wn);
	SDL_SetRenderDrawColor(wn->rend, 150, 100, 100, 0);
	while (j <= wn->map->y + wn->map->h + 1)
	{
		start = create_t_point(wn->map->x, j);
		end = create_t_point(wn->map->w + wn->map->x, j);
		bresenham(wn, &start, &end);
		j += wn->map->h / 10;
	}
	j = wn->map->y;
	while (i <= wn->map->x + wn->map->w + 1)
	{
		start = create_t_point(i, wn->map->y);
		end = create_t_point(i, wn->map->h + wn->map->y);
		bresenham(wn, &start, &end);
		i += wn->map->w / 10;
	}
}

void		showmap(t_win *wn)
{
	showline(wn);
	showelem(wn);
}
