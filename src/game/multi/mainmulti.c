/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmulti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:54:13 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/13 15:39:03 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	inputmulti(t_win *wn) // => CHOIX DU MENU HOST OU CLIENT
{
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_UP)  && wn->menu->choice > 40 ? wn->menu->choice -= 1 : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_DOWN) && wn->menu->choice < 42 ? wn->menu->choice += 1 : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MENU : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 0 : 0;
	if (!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_RETURN))
	{
		wn->oldinterface = wn->interface;
		wn->menu->choice == 40 ? wn->interface = HOST : 0;
		wn->menu->choice == 41 ? wn->interface = CLIENT : 0;
		wn->menu->choice == 42 ? wn->interface = MENU : 0;
		wn->menu->choice = 0;
	}
}

void	showmulti(t_win *wn)
{
	SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "Multi"), NULL, NULL);
}

void	mainmulti(t_win *wn)
{
	if (wn->interface == HOST)
		mainhost(wn);
	else if (wn->interface == CLIENT)
		mainclient(wn);
	else
	{
		inputmulti(wn);
		showmulti(wn);
	}
}
