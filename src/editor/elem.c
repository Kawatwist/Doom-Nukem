/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:36:49 by llejeune          #+#    #+#             */
/*   Updated: 2019/06/04 10:36:51 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void     find_last_poly(t_elem **curr)
{
    while (*curr != NULL && (*curr)->next != NULL)
        *curr = (*curr)->next;
}

static void     find_last_point(t_point **point)
{
    while (*point != NULL && (*point)->next != NULL)
        *point = (*point)->next;
}

static void     fill_point(t_win *wn, t_point **point) // SET VALUE OF A POINT AND CREATE THE NEXT ONE
{
   	(*point)->next = malloc(sizeof(t_point));
   	(*point) = (*point)->next;
    (*point)->x = wn->input->x;
    (*point)->y = wn->input->y;
    (*point)->next = NULL;
}


int             check_point(t_win *wn, t_point *point) // DODGE DOUBLE SAME POINT
{
    if (wn->input->x == point->x && wn->input->y == point->y)
        return (FALSE);
    return (TRUE);
}

void            mouse_input_poly(t_win *wn)
{
    t_elem  *curr;
    t_point *point;

    curr = wn->elem;
    find_last_poly(&curr); // REACH LAST POLYGON ACTIF
    point = curr->point;
    find_last_point(&point); // REACH LAST POINT CREATE
    if (mouse_pressed(wn, SDL_BUTTON_LEFT) && check_point(wn, point)) // Create a new point and fill it /!\ NEED TO BE CARE FOR THE FIRST POInt OF THE FIRST POLYGON
        fill_point(wn, &point);
    if (mouse_pressed(wn, SDL_BUTTON_RIGHT)) // CREATE A NEW POLY   /!\ BECARFULL IF A POLYGONE GOT LESS THAN 3 POINT HE'S INVALID
    {
		if ((curr->next = malloc(sizeof(t_elem))) == NULL) // MALLOC NEW POLY
            stop_exec("Malloc elem failed\n", wn);
		if ((curr->next->point = malloc(sizeof(t_point))) == NULL) // MALLOC 1st POINT 
            stop_exec("Malloc point failed\n", wn);
        curr->next->point->x = wn->input->x;    // FILL FIRST POINT
        curr->next->point->y = wn->input->y;
		curr->next->next = NULL;                  // INIT NEXT POINTEUR
		curr->next->point->next = NULL;
	}
}
