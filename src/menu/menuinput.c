/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menuinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:39:46 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/15 13:19:36 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	menuinput(t_win *wn)
{
	!(wn->flag & CONSOLE) && wn->menu->choice > 0
		&& key_pressed(wn, SDL_SCANCODE_UP) ? wn->menu->choice -= 1 : 0;
	!(wn->flag & CONSOLE) && wn->menu->choice < 3
		&& key_pressed(wn, SDL_SCANCODE_DOWN) ? wn->menu->choice += 1 : 0;
	if (key_pressed(wn, SDL_SCANCODE_RETURN) && !(wn->flag & CONSOLE))
	{
		wn->oldinterface = wn->interface;
		wn->menu->choice == 0 ? wn->interface = MGAME : 0;
		wn->menu->choice == 0 ? wn->menu->choice = 10 : 0;
		wn->menu->choice == 1 ? wn->interface = EDITEUR : 0;
		wn->menu->choice == 1 ? wn->menu->choice = 20 : 0;
		wn->menu->choice == 2 ? wn->interface = MOPTION : 0;
		wn->menu->choice == 2 ? wn->menu->choice = 30 : 0;
		wn->menu->choice == 3 ? stop_exec("Merci d'avoir joué !\n", wn) : 0;
		// Verif que le joueur veut bien quitter
	}
}
