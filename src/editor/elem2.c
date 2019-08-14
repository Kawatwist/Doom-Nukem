/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:07:35 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/07 14:47:10 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			remove_poly(t_elem *curr)
{
	t_point 	*tmp;

	if (curr->point != NULL)
	{
		tmp = curr->point->next;
		while (curr->point != NULL)
		{
			free(curr->point);
			curr->point = NULL;
			curr->point = tmp;
			tmp != NULL ? tmp = tmp->next : 0;
		}
	}
}

void			find_last_poly(t_elem **curr)
{
	while ((*curr) != NULL && (*curr)->next != NULL && (*curr)->next->next != NULL)
		*curr = (*curr)->next;
}

void			find_last_point(t_edit *edit, t_point **point)
{
	edit->var->nb_point = 1;
	while (*point != NULL && (*point)->next != NULL)
	{
		*point = (*point)->next;
		edit->var->nb_point++;
	}
	edit->var->nb_point += 2;
}


static void		fill_first_point(t_win *wn, t_edit *edit, t_point **point, float z)
{
	if (!((*point) = malloc(sizeof(t_point))))
		return ; // STOP_exec
	(*point)->x = (wn->input->x - edit->map->x) / edit->map->size / 10;
	(*point)->y = (wn->input->y - edit->map->y) / edit->map->size / 10;
	(*point)->z = z;
	(*point)->next = NULL;
}

static void		fill_point(t_win *wn, t_edit *edit, t_point **point, float z)
{
	t_point *old;
	double	x;
	double	y;

	old = *point;
	if (!((*point)->next = malloc(sizeof(t_point))))
		return ; // STOP_exec
	(*point) = (*point)->next;
	(*point)->x = (wn->input->x - edit->map->x) / edit->map->size / 10;
	(*point)->y = (wn->input->y - edit->map->y) / edit->map->size / 10;
	(*point)->z = z;
	x = (*point)->x - old->x > 0 ? (*point)->x - old->x : old->x - (*point)->x;
	y = (*point)->y - old->y > 0 ? (*point)->y - old->y : old->y - (*point)->y;
	if (wn->state[SDL_SCANCODE_LSHIFT])
	{
		if (x < y)
			(*point)->x = old->x;
		else
			(*point)->y = old->y;
	}
	(*point)->next = NULL;
}

void			mouse_input_poly(t_win *wn, t_edit *edit)
{
	t_elem	*curr;
	t_point	*point;
	t_point	*pointz;

	curr = edit->elem;
	find_last_poly(&curr);
	if (curr == NULL)
	{
		if ((curr = malloc(sizeof(t_elem))) == NULL)
			stop_exec("Malloc elem failed\n", wn);
		else
			curr->point = NULL;
		curr->next = NULL;
		edit->elem = curr;
	}
	if (curr->next == NULL)
	{
		if ((curr->next = malloc(sizeof(t_elem))) == NULL)
			stop_exec("Malloc elem failed\n", wn);
		else
			curr->next->point = NULL;
		curr->next->next = NULL;
	}
	if (curr != NULL && wn->input->x > wn->xscreen / 18.28 && (edit->var->cursor & 0xFF) == 1) // MODE CURSOR && NOT IN CURSOR AREA
	{
		if (curr->point == NULL && mouse_pressed(wn, SDL_BUTTON_LEFT)  && (wn->input->x - edit->map->x) <= edit->map->w && (wn->input->y - edit->map->y) <= edit->map->h && (wn->input->x - edit->map->x) >= 0 && (wn->input->y - edit->map->y) >= 0)
		{
			fill_first_point(wn, edit, &curr->point, 0);
			fill_first_point(wn, edit, &curr->next->point, 20);
		}
		else if ((mouse_pressed(wn, SDL_BUTTON_LEFT) || mouse_pressed(wn, SDL_BUTTON_RIGHT)) && (wn->input->x - edit->map->x) <= edit->map->w && (wn->input->y - edit->map->y) <= edit->map->h && (wn->input->x - edit->map->x) >= 0 && (wn->input->y - edit->map->y) >= 0)
		{
			edit->var->nb_point = 0;
			if (mouse_pressed(wn, SDL_BUTTON_LEFT))
			{
				point = curr->point;
				pointz = curr->next->point;
				find_last_point(edit, &point);
				fill_point(wn, edit, &point, 0);
				find_last_point(edit, &pointz);
				fill_point(wn, edit, &pointz, 20);
				curr->nb_pt = edit->var->nb_point;
			}
			if (mouse_pressed(wn, SDL_BUTTON_RIGHT))
			{
				if (curr->nb_pt < 4)
				{
					remove_poly(curr->next);
					remove_poly(curr);
				}
				else
				{
					if ((curr->next->next = malloc(sizeof(t_elem))) == NULL)
						stop_exec("Malloc elem failed\n", wn);
					if ((curr->next->next->next = malloc(sizeof(t_elem))) == NULL)
						stop_exec("Malloc elem failed\n", wn);
					curr->next->next->next->next = NULL;
					curr->next->next->point = NULL;
					curr->next->next->next->point = NULL;
				}
			}
		}
	}
}
