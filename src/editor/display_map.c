/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:56:46 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/04 18:05:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	showelem(t_win *wn, t_edit *edit)
{
	t_elem		*curr;
	t_point		*point;
	t_point		*pointbis;
	t_point		start;
	t_point		end;
	t_point		*tmp;
	int			i;

	curr = edit->elem;
	i = 0;
	while (curr != NULL)
	{
		point = curr->point;
		if ((i % 2) == 0)
			pointbis = curr->next->point;
		SDL_SetRenderDrawColor(wn->rend, 255, 255, 255, 0);
		while (point != NULL && point->next != NULL)
		{
			if ((i % 2) == 0 && (edit->var->cursor & 0xFFFF) == SWAP)
			{
				start = create_t_point((point->x * edit->map->size * 10) + edit->map->x, (point->y * edit->map->size * 10) + edit->map->y);
				end = create_t_point((pointbis->x * edit->map->size * 10) + edit->map->x, (pointbis->y * edit->map->size * 10) + edit->map->y);
				//printf("%f|%f -> %f|%f\n", point->x, point->y, pointbis->x, pointbis->y);
				end.x += (pointbis->z / 200) * (short)((edit->var->swapvar & 0xFFFF0000) >> 16);
				end.y += (pointbis->z / 200) * (short)(edit->var->swapvar & 0xFFFF);
				pointbis = pointbis->next;
				bresenham(wn, &start, &end);
			}
			start = create_t_point((point->x * edit->map->size * 10) + edit->map->x, (point->y * edit->map->size * 10) + edit->map->y);
			end = create_t_point((point->next->x * edit->map->size * 10) + edit->map->x, (point->next->y * edit->map->size * 10) + edit->map->y);
			if ((edit->var->cursor & 0xFFFF) == SWAP)
			{
				start.x += (point->z / 200) * (short)((edit->var->swapvar & 0xFFFF0000) >> 16);
				start.y += (point->z / 200) * (short)(edit->var->swapvar & 0xFFFF);
				end.x += (point->next->z / 200) * (short)((edit->var->swapvar & 0xFFFF0000) >> 16);
				end.y += (point->next->z / 200) * (short)(edit->var->swapvar & 0xFFFF);
			}
			bresenham(wn, &start, &end);
			point = point->next;
		}
		if ((i % 2) == 0 && (edit->var->cursor & 0xFFFF) == SWAP && point != NULL)
		{
			start = create_t_point((point->x * edit->map->size * 10) + edit->map->x, (point->y * edit->map->size * 10) + edit->map->y);
			end = create_t_point((pointbis->x * edit->map->size * 10) + edit->map->x, (pointbis->y * edit->map->size * 10) + edit->map->y);
			//printf("%f|%f -> %f|%f\n", point->x, point->y, pointbis->x, pointbis->y);
			end.x += (pointbis->z / 200) * (short)((edit->var->swapvar & 0xFFFF0000) >> 16);
			end.y += (pointbis->z / 200) * (short)(edit->var->swapvar & 0xFFFF);
			bresenham(wn, &start, &end);
		}
		if (curr->next == NULL && point != NULL)
		{
			start = create_t_point((point->x * edit->map->size * 10) + edit->map->x, (point->y * edit->map->size * 10) + edit->map->y);
			end = create_t_point(wn->input->x, wn->input->y);
			bresenham(wn, &start, &end);
		}
		if (curr->next != NULL && curr->next->next != NULL)
		{
			start = create_t_point((curr->point->x * edit->map->size * 10) + edit->map->x, (curr->point->y * edit->map->size * 10) + edit->map->y);
			tmp = curr->point;
			find_last_point(edit, &tmp);
			end = create_t_point((tmp->x * edit->map->size * 10) + edit->map->x, (tmp->y * edit->map->size * 10) + edit->map->y);
			if ((edit->var->cursor & 0xFFFF) == SWAP)
			{
				start.x += (curr->point->z / 200) * (short)((edit->var->swapvar & 0xFFFF0000) >> 16);
				start.y += (curr->point->z / 200) * (short)(edit->var->swapvar & 0xFFFF);
				end.x += (tmp->z / 200) * (short)((edit->var->swapvar & 0xFFFF0000) >> 16);
				end.y += (tmp->z / 200) * (short)(edit->var->swapvar & 0xFFFF);
			}
			bresenham(wn, &start, &end);
		}
		curr = curr->next;
		i++;
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

static void	showselection(t_win *wn, t_edit *edit)
{
	int			i;
	SDL_Rect	selection;

	if (edit->selected != NULL)
	{
		i = 0;
		SDL_SetRenderDrawColor(wn->rend, 255, 0, 255, 255);
		while (edit->selected[i] != NULL)
		{
			if (((edit->var->cursor & 0xFFFF0000) >> 16) == SWAP && (edit->var->cursor & 0xFFFF) == SWAP)
			{
				//printf("Decalage = %f\n", ((edit->selected[i]->z / 200) * ((edit->var->swapvar & 0xFFFF0000) >> 16)));
				selection.x = (edit->selected[i]->x * edit->map->size * 10) - 10 + edit->map->x + ((edit->selected[i]->z / 200) * (short)((edit->var->swapvar & 0xFFFF0000) >> 16));
				selection.y = (edit->selected[i]->y * edit->map->size * 10) - 10 + edit->map->y + ((edit->selected[i]->z / 200) * (short)(edit->var->swapvar & 0xFFFF));
			}
			else
			{
				selection.x = (edit->selected[i]->x * edit->map->size * 10) - 10 + edit->map->x;
				selection.y = (edit->selected[i]->y * edit->map->size * 10) - 10 + edit->map->y;
			}
			selection.w = 20;
			selection.h = 20;
			SDL_RenderFillRect(wn->rend, &selection);
			i++;
		}
	}

}

void		showmap(t_win *wn, t_edit *edit)
{
	showline(wn, edit);
	showelem(wn, edit);
	showselection(wn, edit);
}
