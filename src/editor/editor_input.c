/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:02:08 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/05 16:49:24 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
	Uint16			mouse;
	int				x;
	int				y;

	mouse = SDL_GetMouseState(&x, &y);
	wn->state[SDL_SCANCODE_ESCAPE] ? wn->interface = MENU : 0;
	wn->state[SDL_SCANCODE_LEFT] ? (wn->map->x > 0 ? wn->map->x -= (6.5 - wn->map->size) : 0) : 0;
	wn->state[SDL_SCANCODE_RIGHT] ? ((wn->map->x + wn->map->w) < 1200 ? wn->map->x += (6.5 - wn->map->size) : 0) : 0;
	wn->state[SDL_SCANCODE_UP] ? (wn->map->y > 0 ? wn->map->y -= (6.5 - wn->map->size) : 0) : 0;
	wn->state[SDL_SCANCODE_DOWN] ? ((wn->map->y + wn->map->h) < 1200 ? wn->map->y += (6.5 - wn->map->size) : 0) : 0;
	wn->state[SDL_SCANCODE_KP_PLUS] && wn->map->size < 6
		&& !wn->old[SDL_SCANCODE_KP_PLUS] ? wn->map->size *= 1.2 : 0;
	wn->state[SDL_SCANCODE_KP_PLUS]
		&& wn->map->size >= 6 ? wn->map->size = 6 : 0;
	wn->state[SDL_SCANCODE_KP_MINUS] && wn->map->size > 0.5
		&& !wn->old[SDL_SCANCODE_KP_MINUS] ? wn->map->size *= 0.9 : 0;
	wn->state[SDL_SCANCODE_KP_MINUS]
		&& wn->map->size <= 0.5 ? wn->map->size = 0.5 : 0;
	wn->state[SDL_SCANCODE_R] ? resetmap(wn) : 0;
	wn->map->h = 600 * wn->map->size;
	wn->map->w = 600 * wn->map->size;
}
