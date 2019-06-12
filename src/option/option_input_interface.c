/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_input_interface.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:28:10 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/12 12:41:44 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	menu_option_input(t_win *wn)
{
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_UP) && wn->menu->choice > 30 ? wn->menu->choice -= 1 : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_DOWN) && wn->menu->choice < 33 ? wn->menu->choice += 1 : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MENU : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 0 : 0;
	if (!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_RETURN))
	{
		wn->oldinterface = wn->interface;
		wn->menu->choice == 30 ? wn->interface = KOPTION : 0;
		wn->menu->choice == 31 ? wn->interface = GOPTION : 0;
		wn->menu->choice == 32 ? wn->interface = COPTION : 0;
		wn->menu->choice == 33 ? wn->interface = MENU : 0;
		wn->interface == MENU ? wn->menu->choice = 0: 0;
	}
}

void	keyboard_option_input(t_win *wn)
{
	(void)wn;
}

void	graphisme_option_input(t_win *wn)
{
	(void)wn;
}

void	control_option_input(t_win *wn)
{
	(void)wn;
}
