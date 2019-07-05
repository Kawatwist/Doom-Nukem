/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maingame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:01:14 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/05 16:11:38 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ingame(t_win *wn)
{
	gameinput(wn);
	if (key_pressed(wn, SDL_SCANCODE_ESCAPE))
	{
		wn->interface = MGAME;
		wn->menu->choice = 10;
	}
	display_skybox(wn);
	main_cloud(wn);
	maindrawpoly(wn);
	display_crosshair(wn);
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
	game_interface(wn);
}
