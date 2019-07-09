/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:07:35 by llejeune          #+#    #+#             */
/*   Updated: 2019/07/08 12:07:37 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			find_last_poly(t_elem **curr)
{
	while (*curr != NULL && (*curr)->next != NULL)
		*curr = (*curr)->next;
}

void			find_last_point(t_win *wn, t_point **point)
{
	wn->varedit.nb_point = 1;
	while (*point != NULL && (*point)->next != NULL)
	{
		*point = (*point)->next;
		wn->varedit.nb_point++;
	}
	wn->varedit.nb_point += 2;
}

static void		fill_point(t_win *wn, t_point **point) // SET VALUE OF A POINT AND CREATE THE NEXT ONE
{
	(*point)->next = malloc(sizeof(t_point));
	*point = (*point)->next;
	(*point)->x = (wn->input->x - wn->map->x) / wn->map->size;
	(*point)->y = (wn->input->y - wn->map->y) / wn->map->size;
	(*point)->z = wn->editext.val_z;
	(*point)->next = malloc(sizeof(t_point));
	(*point)->next->x = (wn->input->x - wn->map->x) / wn->map->size;
	(*point)->next->y = (wn->input->y - wn->map->y) / wn->map->size;
	(*point)->next->z = 0;
	(*point)->next->next = NULL;
}

int				check_point(t_win *wn, t_point *point) // DODGE DOUBLE SAME POINT
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

static void 	add_two_points(t_win *wn, t_elem *curr)
{
	t_point *point;

	curr->point = malloc(sizeof(t_point));
	point = curr->point;
	point->x = (wn->input->x - wn->map->x) / wn->map->size;
	point->y = (wn->input->y - wn->map->y) / wn->map->size;
	point->z = wn->editext.val_z;
	point->next = malloc(sizeof(t_point));
	point->next->x = (wn->input->x - wn->map->x) / wn->map->size;
	point->next->y = (wn->input->y - wn->map->y) / wn->map->size;
	point->next->z = 0;
	point->next->next = NULL;
}

void			mouse_input_poly(t_win *wn)
{
	t_elem  *curr;
	t_point *point;

	curr = wn->elem;
	find_last_poly(&curr); // REACH LAST POLYGON ACTIF
	if (curr->point == NULL && mouse_pressed(wn, SDL_BUTTON_LEFT)  && (wn->input->x - wn->map->x) <= wn->map->w && (wn->input->y - wn->map->y) <= wn->map->h && (wn->input->x - wn->map->x) >= 0 && (wn->input->y - wn->map->y) >= 0)
		add_two_points(wn, curr);
	else if ((mouse_pressed(wn, SDL_BUTTON_LEFT) || mouse_pressed(wn, SDL_BUTTON_RIGHT)) && (wn->input->x - wn->map->x) <= wn->map->w && (wn->input->y - wn->map->y) <= wn->map->h && (wn->input->x - wn->map->x) >= 0 && (wn->input->y - wn->map->y) >= 0)
	{
		wn->varedit.nb_point = 0;
		if (mouse_pressed(wn, SDL_BUTTON_LEFT)) // Create a new point and fill it /!\ NEED TO BE CARE FOR THE FIRST POInt OF THE FIRST POLYGON
		{
			point = curr->point;
			find_last_point(wn, &point); // REACH LAST POINT CREATE
			fill_point(wn, &point);
			curr->nb_pt = wn->varedit.nb_point;
		}
		printf("NOMBRE POINTSSSSS = %d\n", wn->varedit.nb_point);
		if (mouse_pressed(wn, SDL_BUTTON_RIGHT)) // CREATE A NEW POLY   /!\ BECARFULL IF A POLYGONE GOT LESS THAN 3 POINT HE'S INVALID
		{
			if (curr->nb_pt < 5)
				remove_poly(curr);
			else
			{
				if ((curr->next = malloc(sizeof(t_elem))) == NULL) // MALLOC NEW POLY
					stop_exec("Malloc elem failed\n", wn);
				curr->next->next = NULL;                  // INIT NEXT POINTEUR
				curr->next->point = NULL;
			}
		}
	}
}
