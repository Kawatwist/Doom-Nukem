/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:12:44 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/10 11:44:35 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	turn(t_win *wn)
{
	Uint32	difftime;
	Uint32	time;

	wn->quality == 0 ? mainintro(wn, "main", "intro", 0) : 0;
	(wn->old = malloc(sizeof(Uint8*) * 284)) == NULL
		? stop_exec("Old not malloc\n", wn) : 0;
	wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
	mainintro(wn, "main", "intro", 1);
	while (TRUE)
	{
		setkeyboard(wn->old, wn->state);
		SDL_PollEvent(&(wn->ev));
		wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
		wn->input->mouse = SDL_GetMouseState(&wn->input->x, &wn->input->y);
		time = SDL_GetTicks();
		SDL_ShowCursor(wn->interface != GAME ? SDL_ENABLE : SDL_DISABLE);
		SDL_CaptureMouse(wn->interface == GAME ? 1 : 0);
		wn->interface == GAME
			? SDL_WarpMouseInWindow(wn->window, XSCREEN/2, YSCREEN/2) : 0;
		!wn->old[SDL_SCANCODE_ESCAPE] && wn->state[SDL_SCANCODE_ESCAPE]
			&& wn->interface == MENU ? stop_exec("Escape\n", wn) : 0;
		wn->interface == MENU ? menu(wn) : 0 ;
		wn->interface == GAME ? game(wn) : 0 ;
		wn->interface == EDITEUR ? edit(wn) : 0;
		wn->interface == OPTION ? option(wn) : 0 ;
		!wn->old[SDL_SCANCODE_F5]
			&& wn->state[SDL_SCANCODE_F5] ? wn->debug *= -1 : 0;
		wn->debug == 1 ? mainconsole(wn) : 0;
		SDL_RenderPresent(wn->rend);
		difftime = SDL_GetTicks();
		(difftime - time) <  1000 / 60
			? SDL_Delay((1000 / 60) - (difftime - time)) : 0;
	}
}
