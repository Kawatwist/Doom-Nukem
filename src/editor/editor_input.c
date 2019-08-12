/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:02:08 by lomasse           #+#    #+#             */
/*   Updated: 2019/08/04 13:28:36 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		resetmap(t_edit *edit)
{
	edit->map->x = 0.1;
	edit->map->y = 0.1;
	edit->map->h = edit->indice->map_h;
	edit->map->w = edit->indice->map_w;
	edit->map->size = 1;
}

static void	keyboardtool(t_win *wn, t_edit *edit)
{
	key_pressed(wn, SDL_SCANCODE_O) ? edit->var->cursor -= 1 : 0; // NOT PROTECT IF < 0
	key_pressed(wn, SDL_SCANCODE_P) ? edit->var->cursor += 1 : 0; // NOT PROTECT IF > 9
	wn->state[SDL_SCANCODE_LEFT] ? edit->map->x -= (6.5 - edit->map->size) : 0;
	wn->state[SDL_SCANCODE_RIGHT] ? edit->map->x += (6.5 - edit->map->size) : 0;
	wn->state[SDL_SCANCODE_UP] ? edit->map->y -= (6.5 - edit->map->size) : 0;
	wn->state[SDL_SCANCODE_DOWN] ? edit->map->y += (6.5 - edit->map->size) : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MENU : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 0 : 0;
	wn->state[SDL_SCANCODE_KP_PLUS] && edit->map->size < 6
		&& !wn->old[SDL_SCANCODE_KP_PLUS] ? edit->map->size *= 1.2 : 0;
	wn->state[SDL_SCANCODE_KP_PLUS]
		&& edit->map->size >= 6 ? edit->map->size = 6 : 0;
	wn->state[SDL_SCANCODE_KP_MINUS] && edit->map->size > 0.5
		&& !wn->old[SDL_SCANCODE_KP_MINUS] ? edit->map->size *= 0.8 : 0;
	wn->state[SDL_SCANCODE_KP_MINUS]
		&& edit->map->size <= 0.5 ? edit->map->size = 0.5 : 0;
	wn->state[SDL_SCANCODE_R] ? resetmap(edit) : 0;
	edit->map->h = edit->indice->map_h * edit->map->size;
	edit->map->w = edit->indice->map_w * edit->map->size;
}

void		inputeditor(t_win *wn)
{
	if (!(wn->input->oldmouse & SDL_BUTTON(SDL_BUTTON_LEFT))
		&& (wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT)))
		change_bloc(wn, wn->edit);
	keyboardtool(wn, wn->edit);
	mouse_input_poly(wn, wn->edit);
}
