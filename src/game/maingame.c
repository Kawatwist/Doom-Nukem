/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maingame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:01:14 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/25 12:45:22 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ingame(t_win *wn)
{

//	gameinput(wn);
	if (key_pressed(wn, SDL_SCANCODE_ESCAPE))
	{
		wn->interface = MGAME;
		wn->menu->choice = 10;
	}
	display_skybox(wn);
	turn_rast(wn);
//	main_cloud(wn);
//	display_crosshair(wn);
}

void	newgame(t_win *wn)
{
	new_game_input(wn);
	if (key_pressed(wn, SDL_SCANCODE_ESCAPE))
	{
		wn->interface = MGAME;
		wn->menu->choice = 10;
	}
	SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "NG"), NULL, NULL);
}

void	loadgame(t_win *wn)
{
	load_game_input(wn);
	if (key_pressed(wn, SDL_SCANCODE_ESCAPE))
	{
		wn->interface = MGAME;
		wn->menu->choice = 10;
	}
	SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "LG"), NULL, NULL);
}

void	menugame(t_win *wn)
{
	menu_game_input(wn);
	SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "menu"), NULL, NULL);
	show_game_cursor(wn);
}

void	game(t_win *wn)	// Common info
{
	if (wn->oldinterface != wn->interface)
	{
		wn->oldinterface == MENU ? mainintro(wn, "game", "intro", 60) : 0;
		wn->oldinterface == RGAME ? mainintro(wn, "game", "intro", 60) : 0;
		wn->oldinterface == NGAME ? mainintro(wn, "game", "intro", 60) : 0;
		wn->oldinterface == LGAME ? mainintro(wn, "game", "intro", 60) : 0;
		wn->oldinterface = wn->interface;
	}
	if (wn->interface != RGAME) // USELESS ?
	{
		SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 255);
		SDL_RenderClear(wn->rend);
	}
	game_interface(wn);
}
