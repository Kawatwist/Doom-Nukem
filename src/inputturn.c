/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputturn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 10:24:41 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/30 16:17:17 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	keyinput(t_win *wn)
{
	if (key_pressed(wn, SDL_SCANCODE_F) && !(wn->flag & CONSOLE))
	{
		wn->flag = set_bit(wn->flag, FS);
		full_screen(wn);
	}
	key_pressed(wn, SDL_SCANCODE_ESCAPE) && wn->interface == MENU
		&& !(wn->flag & CONSOLE) ? stop_exec("Escape\n", wn) : 0;
	key_pressed(wn, SDL_SCANCODE_F5) ? wn->flag = set_bit(wn->flag, CONSOLE) : 0;
}

static void	mouseconfig(t_win *wn)
{
	SDL_ShowCursor(wn->interface != RGAME ? SDL_ENABLE : SDL_DISABLE);
	SDL_CaptureMouse(wn->interface == RGAME ? 1 : 0);
	wn->interface == RGAME
		? SDL_WarpMouseInWindow(wn->window, wn->xscreen / 2, wn->yscreen / 2) : 0;
}

static void	resetinput(t_win *wn)
{
	setkeyboard(wn->old, wn->state);
	wn->input->oldmouse = wn->input->mouse;
	SDL_PumpEvents();
	wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
	wn->input->mouse = SDL_GetMouseState(&wn->input->x, &wn->input->y);
}

void		main_input(t_win *wn)
{
	resetinput(wn);
	keyinput(wn);
	mouseconfig(wn);
}
