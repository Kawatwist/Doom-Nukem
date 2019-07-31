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

#include "editor.h"

static void	showelem(t_win *wn, t_edit *edit)
{
	t_elem		*curr;
	t_point		*point;
	t_point		start;
	t_point		end;
	t_point		*tmp;

	curr = edit->elem;
	while (curr != NULL)
	{
		point = curr->point;
		SDL_SetRenderDrawColor(wn->rend, 255, 255, 255, 0);
		while (point != NULL && point->next != NULL)
		{
			start = create_t_point((point->x * edit->map->size + edit->map->x) * 10, (point->y * edit->map->size + edit->map->y) * 10);
			end = create_t_point((point->next->x * edit->map->size + edit->map->x) * 10, (point->next->y * edit->map->size + edit->map->y) * 10);
			bresenham(wn, &start, &end);
			point = point->next;
		}
		if (curr->next == NULL && point != NULL)
		{
			start = create_t_point((point->x * edit->map->size + edit->map->x) * 10, (point->y * edit->map->size + edit->map->y) * 10);
			end = create_t_point(wn->input->x, wn->input->y);
			bresenham(wn, &start, &end);
		}
		if (curr->nb_pt > 4 && curr->next != NULL)
		{
			start = create_t_point((curr->point->x * edit->map->size + edit->map->x) * 10, (curr->point->y * edit->map->size + edit->map->y) * 10);
			tmp = curr->point;
			find_last_point(edit, &tmp);
			end = create_t_point((tmp->x * edit->map->size + edit->map->x) * 10, (tmp->y * edit->map->size + edit->map->y) * 10);
			bresenham(wn, &start, &end);
		}
		curr = curr->next;
	}
}

static void	showline2(t_win *wn, t_edit *edit)
{
	float		i;
	float		j;
	t_point		start;
	t_point		end;

	j = edit->map->y;
	i = edit->map->x;
	if (edit->map->size > 1)
	{
		SDL_SetRenderDrawColor(wn->rend, 50 + (edit->map->size * 20 / 6),
				50 + (edit->map->size * 20 / 6),
				50 + (edit->map->size * 20 / 6), 0);
		while (j <= edit->map->y + edit->map->h)
		{
			start = create_t_point(edit->map->x, j);
			end = create_t_point(edit->map->w + edit->map->x, j);
			bresenham(wn, &start, &end);
			j += edit->map->h / 40;
		}
		j = edit->map->y;
		while (i <= edit->map->x + edit->map->w)
		{
			start = create_t_point(i, edit->map->y);
			end = create_t_point(i, edit->map->h + edit->map->y);
			bresenham(wn, &start, &end);
			i += edit->map->w / 40;
		}
	}
}

static void	showline(t_win *wn, t_edit *edit)
{
	float		i;
	float		j;
	t_point		start;
	t_point		end;

	j = edit->map->y;
	i = edit->map->x;
	showline2(wn, edit);
	SDL_SetRenderDrawColor(wn->rend, 150, 100, 100, 0);
	while (j <= edit->map->y + edit->map->h + 1)
	{
		start = create_t_point(edit->map->x, j);
		end = create_t_point(edit->map->w + edit->map->x, j);
		bresenham(wn, &start, &end);
		j += edit->map->h / 10;
	}
	j = edit->map->y;
	while (i <= edit->map->x + edit->map->w + 1)
	{
		start = create_t_point(i, edit->map->y);
		end = create_t_point(i, edit->map->h + edit->map->y);
		bresenham(wn, &start, &end);
		i += edit->map->w / 10;
	}
}

void		showmap(t_win *wn, t_edit *edit)
{
	showline(wn, edit);
	showelem(wn, edit);
}
