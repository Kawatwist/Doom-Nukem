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

static void	resetmap(t_win *wn)
{
	wn->map->x = 0.1;
	wn->map->y = 0.1;
	wn->map->h = wn->editext.map_h;
	wn->map->w = wn->editext.map_w;
	wn->map->size = 1;
}

static void	keyboardtool(t_win *wn)
{
	(wn->state[SDL_SCANCODE_ESCAPE]) ? wn->interface = MENU : 0;
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
	wn->map->h = wn->editext.map_h * wn->map->size;
	wn->map->w = wn->editext.map_w * wn->map->size;
}

void		inputeditor(t_win *wn)
{
	if (!(wn->input->oldmouse & SDL_BUTTON(SDL_BUTTON_LEFT))
		&& (wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT)))
		change_bloc(wn);
	keyboardtool(wn);
	mouse_input_poly(wn);
}
