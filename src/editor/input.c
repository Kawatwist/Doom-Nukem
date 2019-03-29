/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:02:08 by lomasse           #+#    #+#             */
/*   Updated: 2019/03/29 12:33:08 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	resetmap(t_win *wn)
{
	wn->map->x = 0.1;
	wn->map->y = 0.1;
	wn->map->h = 600;
	wn->map->w = 600;
	wn->map->size = 1;
}

void	inputeditor(t_win *wn)
{
	Uint16			mouse;
	static Uint8	*last = NULL;
	int			x;
	int			y;

	if (last == NULL)
		last = malloc(sizeof(Uint8));
	mouse = SDL_GetMouseState(&x, &y);
	wn->state[SDL_SCANCODE_ESCAPE] ? stop_exec("ESCAPE\n", wn) : 0;
	wn->state[SDL_SCANCODE_LEFT] ? wn->map->x -= (wn->map->size) : 0;
	wn->state[SDL_SCANCODE_RIGHT] ? wn->map->x += (wn->map->size) : 0;
	wn->state[SDL_SCANCODE_UP] ? wn->map->y -= (wn->map->size) : 0;
	wn->state[SDL_SCANCODE_DOWN] ? wn->map->y += (wn->map->size) : 0;
	wn->state[SDL_SCANCODE_KP_PLUS] && wn->map->size < 6 && !last[SDL_SCANCODE_KP_PLUS] ? wn->map->size *= 1.2 : 0;
	wn->state[SDL_SCANCODE_KP_PLUS] && wn->map->size >= 6 ? wn->map->size = 6 : 0;
	wn->state[SDL_SCANCODE_KP_MINUS] && wn->map->size > 0.5 && !last[SDL_SCANCODE_KP_MINUS] ? wn->map->size *= 0.9 : 0;
	wn->state[SDL_SCANCODE_KP_MINUS] && wn->map->size <= 0.5 ? wn->map->size = 0.5 : 0;
	wn->state[SDL_SCANCODE_R] ? resetmap(wn) : 0;
	wn->map->h = 600 * wn->map->size;
	wn->map->w = 600 * wn->map->size;
	setkeyboard(last, wn->state);
}
