/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menuinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:39:46 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/19 17:09:22 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	menuinput(t_win *wn)
{
	wn->state[SDL_SCANCODE_UP] == 1
		&& wn->menu->choice > 0
		&& !wn->old[SDL_SCANCODE_UP] ? wn->menu->choice -= 1 : 0;
	wn->state[SDL_SCANCODE_DOWN] == 1
		&& wn->menu->choice < 3
		&& !wn->old[SDL_SCANCODE_DOWN] ? wn->menu->choice += 1 : 0;
	if (wn->state[SDL_SCANCODE_RETURN] == 1
			&& !wn->old[SDL_SCANCODE_RETURN] && wn->debug == -1)
	{
		wn->oldinterface = wn->interface;
		wn->menu->choice == 0 ? wn->interface = GAME : 0;
		wn->menu->choice == 1 ? wn->interface = EDITEUR : 0;
		wn->menu->choice == 2 ? wn->interface = OPTION : 0;
		wn->menu->choice == 3 ? stop_exec("Merci d'avoir joué !\n", wn) : 0;
		// Verif que le joueur veut bien quitter
	}
}
