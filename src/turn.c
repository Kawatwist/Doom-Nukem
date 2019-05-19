/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:12:44 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/19 17:07:59 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	full_screen(t_win *wn)
{
	if (wn->full_screen == -1)
	{
		SDL_SetWindowFullscreen(wn->window, SDL_WINDOW_FULLSCREEN);
		SDL_GetWindowSize(wn->window, &wn->xscreen, &wn->yscreen);
	}
	if (wn->full_screen == 1)
	{
		wn->xscreen = XSCREEN;
		wn->yscreen = YSCREEN;
		SDL_SetWindowSize(wn->window, wn->xscreen, wn->yscreen);
		SDL_SetWindowFullscreen(wn->window, 0);
		SDL_RestoreWindow(wn->window);
	}
}

void	turn(t_win *wn)
{
	Uint32	difftime;
	Uint32	time;

	wn->quality == 0 ? mainintro(wn, "main", "intro", 0) : 0;
	(wn->old = malloc(sizeof(Uint8*) * 284)) == NULL
		? stop_exec("Old not malloc\n", wn) : 0;
	wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
	wn->input->mouse = SDL_GetMouseState(&wn->input->x, &wn->input->y);
	mainintro(wn, "main", "intro", 1);
	while (TRUE)
	{
		time = SDL_GetTicks();
		setkeyboard(wn->old, wn->state);
		printf("PollEvent Avant\n");
		SDL_PumpEvents();
		printf("Poll Event Apres\n");
		wn->input->oldmouse = wn->input->mouse;
		wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
		wn->input->mouse = SDL_GetMouseState(&wn->input->x, &wn->input->y);
		SDL_ShowCursor(wn->interface != GAME ? SDL_ENABLE : SDL_DISABLE);
		SDL_CaptureMouse(wn->interface == GAME ? 1 : 0);
		!wn->old[SDL_SCANCODE_F] && wn->state[SDL_SCANCODE_F] ? wn->full_screen = -wn->full_screen : 0;
		!wn->old[SDL_SCANCODE_F] && wn->state[SDL_SCANCODE_F] ? full_screen(wn) : 0;
		wn->interface == GAME
			? SDL_WarpMouseInWindow(wn->window, wn->xscreen/2, wn->yscreen/2) : 0;
		!wn->old[SDL_SCANCODE_ESCAPE] && wn->state[SDL_SCANCODE_ESCAPE]
			&& wn->interface == MENU && wn->debug == -1 ? stop_exec("Escape\n", wn) : 0;
		wn->interface == MENU ? menu(wn) : 0 ;
		wn->interface == GAME ? game(wn) : 0 ;
		wn->interface == EDITEUR ? edit(wn) : 0;
		wn->interface == OPTION ? option(wn) : 0 ;
		!wn->old[SDL_SCANCODE_F5] && wn->state[SDL_SCANCODE_F5] ? wn->debug *= -1 : 0;
		wn->debug == 1 ? mainconsole(wn) : 0;
		difftime = SDL_GetTicks();
		(difftime - time) <  1000 / 60
			? SDL_Delay((1000 / 60) - (difftime - time)) : 0;
		printf("Render Present Avant\n");
		SDL_RenderPresent(wn->rend);
		printf("Render Present Apres\n");
	}
}
