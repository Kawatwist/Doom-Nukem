/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:07:35 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/04 15:55:59 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			find_last_poly(t_elem **curr)
{
	while (*curr != NULL && (*curr)->next != NULL)
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

static void		fill_point(t_win *wn, t_edit *edit, t_point **point)
{
	t_point *old;
	double	x;
	double	y;

	old = *point;
	(*point)->next = malloc(sizeof(t_point));
	*point = (*point)->next;
	(*point)->x = (wn->input->x - edit->map->x) / edit->map->size / 10;
	(*point)->y = (wn->input->y - edit->map->y) / edit->map->size / 10;
	x = (*point)->x - old->x > 0 ? (*point)->x - old->x : old->x - (*point)->x;
	y = (*point)->y - old->y > 0 ? (*point)->y - old->y : old->y - (*point)->y;
	if (wn->state[SDL_SCANCODE_LSHIFT])
	{
		if (x < y)
			(*point)->x = old->x;
		else
			(*point)->y = old->y;
	}
	(*point)->z = edit->indice->val_z;
	(*point)->next = malloc(sizeof(t_point));
	(*point) = (*point)->next;
	(*point)->x = (wn->input->x - edit->map->x) / edit->map->size / 10;
	(*point)->y = (wn->input->y - edit->map->y) / edit->map->size / 10;
	if (wn->state[SDL_SCANCODE_LSHIFT])
	{
		if (x < y)
			(*point)->x = old->x;
		else
			(*point)->y = old->y;
	}
	(*point)->z = 0;
	(*point)->next = NULL;
}

int				check_point(t_win *wn, t_point *point)
{
	if (wn->input->x == point->x && wn->input->y == point->y)
		return (FALSE);
	return (TRUE);
}

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

static void 	add_two_points(t_win *wn, t_edit *edit, t_elem *curr)
{
	t_point *point;

	curr->point = malloc(sizeof(t_point));
	point = curr->point;
	point->x = (wn->input->x - edit->map->x) / edit->map->size / 10;
	point->y = (wn->input->y - edit->map->y) / edit->map->size / 10;
	point->z = edit->indice->val_z;
	point->next = malloc(sizeof(t_point));
	point->next->x = (wn->input->x - edit->map->x) / edit->map->size / 10;
	point->next->y = (wn->input->y - edit->map->y) / edit->map->size / 10;
	point->next->z = 0;
	point->next->next = NULL;
}

void			mouse_input_poly(t_win *wn, t_edit *edit)
{
	t_elem  *curr;
	t_point *point;

	curr = edit->elem;
	find_last_poly(&curr);
	if (wn->input->x > wn->xscreen / 18.28 && (edit->var->cursor & 0xFF) == 1) // (Cursor choice without draw on map)
	{ // USE HITBOX ?
		if (curr->point == NULL && mouse_pressed(wn, SDL_BUTTON_LEFT)  && (wn->input->x - edit->map->x) <= edit->map->w && (wn->input->y - edit->map->y) <= edit->map->h && (wn->input->x - edit->map->x) >= 0 && (wn->input->y - edit->map->y) >= 0)
			add_two_points(wn, edit, curr);
		else if ((mouse_pressed(wn, SDL_BUTTON_LEFT) || mouse_pressed(wn, SDL_BUTTON_RIGHT)) && (wn->input->x - edit->map->x) <= edit->map->w && (wn->input->y - edit->map->y) <= edit->map->h && (wn->input->x - edit->map->x) >= 0 && (wn->input->y - edit->map->y) >= 0)
		{
			edit->var->nb_point = 0;
			if (mouse_pressed(wn, SDL_BUTTON_LEFT))
			{
				point = curr->point;
				find_last_point(edit, &point);
				fill_point(wn, edit, &point);
				curr->nb_pt = edit->var->nb_point;
			}
			if (mouse_pressed(wn, SDL_BUTTON_RIGHT))
			{
				if (curr->nb_pt < 5)
					remove_poly(curr);
				else
				{
					if ((curr->next = malloc(sizeof(t_elem))) == NULL)
						stop_exec("Malloc elem failed\n", wn);
					curr->next->next = NULL;
					curr->next->point = NULL;
				}
			}
		}
	}
}
