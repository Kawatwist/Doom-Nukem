/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:02:08 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/13 16:52:10 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	mousedraw(t_win *wn)
{
	t_elem			*curr;
	t_point			*point;

	curr = wn->elem;
	while (curr != NULL && curr->next != NULL)
		curr = curr->next;
	point = curr->point;
	while (point != NULL && point->next != NULL)
		point = point->next;
	if (!(wn->input->oldmouse & SDL_BUTTON(SDL_BUTTON_LEFT)) && (wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT)))
	{
		if (point == curr->point)
		{
			point->x = wn->input->x;
			point->y = wn->input->y;
			(point->next = malloc(sizeof(t_point))) == NULL ? stop_exec("Point malloc failed\n", wn) : 0;
			(point->next->next = NULL);
		}
		else if (point->x != wn->input->x || point->y != wn->input->y)
		{
			(point->next = malloc(sizeof(t_point))) == NULL ? stop_exec("Point malloc failed\n", wn) : 0;
			point = point->next;
			point->x = wn->input->x;
			point->y = wn->input->y;
			point->next = NULL;
		}
	}
	if (!(wn->input->oldmouse & SDL_BUTTON(SDL_BUTTON_RIGHT)) && (wn->input->mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)))
	{
		(curr->next = malloc(sizeof(t_elem))) == NULL ? stop_exec("Malloc elem failed\n", wn) : 0;
		(curr->next->point = malloc(sizeof(t_point))) == NULL ? stop_exec("Malloc point failed\n", wn) : 0;
		curr->next->next = NULL;
		curr->next->point->next = NULL;
		curr = curr->next;
	}
}

static void	keyboardtool(t_win *wn)
{
	(void)wn;
}

static void	resetmap(t_win *wn)
{
	wn->map->x = 0.1;
	wn->map->y = 0.1;
	wn->map->h = 600;
	wn->map->w = 600;
	wn->map->size = 1;
}

void		inputeditor(t_win *wn)
{
	wn->state[SDL_SCANCODE_ESCAPE] ? wn->interface = MENU : 0;
	wn->state[SDL_SCANCODE_LEFT] ? wn->map->x -= (6.5 - wn->map->size) : 0;
	wn->state[SDL_SCANCODE_RIGHT] ? wn->map->x += (6.5 - wn->map->size) : 0;
	wn->state[SDL_SCANCODE_UP] ? wn->map->y -= (6.5 - wn->map->size) : 0;
	wn->state[SDL_SCANCODE_DOWN] ? wn->map->y += (6.5 - wn->map->size) : 0;
	wn->state[SDL_SCANCODE_KP_PLUS] && wn->map->size < 6
		&& !wn->old[SDL_SCANCODE_KP_PLUS] ? wn->map->size *= 1.2 : 0;
	wn->state[SDL_SCANCODE_KP_PLUS]
		&& wn->map->size >= 6 ? wn->map->size = 6 : 0;
	wn->state[SDL_SCANCODE_KP_MINUS] && wn->map->size > 0.5
		&& !wn->old[SDL_SCANCODE_KP_MINUS] ? wn->map->size *= 0.8 : 0;
	wn->state[SDL_SCANCODE_KP_MINUS]
		&& wn->map->size <= 0.5 ? wn->map->size = 0.5 : 0;
	wn->state[SDL_SCANCODE_R] ? resetmap(wn) : 0;
	wn->state[SDL_SCANCODE_1] && !wn->old[SDL_SCANCODE_1] ? wn->editext.on = -wn->editext.on : 0;
	wn->map->h = wn->editext.map_h * wn->map->size;
	wn->map->w = wn->editext.map_w * wn->map->size;
	keyboardtool(wn);
	mousedraw(wn);
}
