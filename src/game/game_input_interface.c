/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input_interface.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:26:54 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/18 13:40:53 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	new_game_input(t_win *wn)
{
	(void)wn;
}

void	load_game_input(t_win *wn)
{
	(void)wn;
}

void	menu_game_input(t_win *wn)
{
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_UP)  && wn->menu->choice > 10 ? wn->menu->choice -= 1 : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_DOWN) && wn->menu->choice < 14 ? wn->menu->choice += 1 : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MENU : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 0 : 0;
	if (!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_RETURN))
	{
		wn->oldinterface = wn->interface;
		wn->menu->choice == 10 ? wn->interface = DGAME : 0;
		wn->menu->choice == 10 ? SDL_WarpMouseInWindow(wn->window, wn->xscreen / 2, wn->yscreen / 2) : 0;
		wn->menu->choice == 11 ? wn->interface = NGAME : 0;
		wn->menu->choice == 12 ? wn->interface = LGAME : 0;
		wn->menu->choice == 13 ? wn->interface = MULTI : 0;
		wn->menu->choice == 14 ? wn->interface = MENU : 0;
		wn->menu->choice = (wn->interface != MULTI ? 0 : 40);
	}
}
