/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menuinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 16:39:46 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/06 11:31:33 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	menuinput(t_win *wn)
{
	if (!(wn->flag & CONSOLE) && wn->menu->choice > 0 && key_pressed(wn, SDL_SCANCODE_UP)) 
		wn->menu->choice -= 1;

	if (!(wn->flag & CONSOLE) && wn->menu->choice < 4 && key_pressed(wn, SDL_SCANCODE_DOWN) )  //passage de < 3 a < 4
		wn->menu->choice += 1;

	if (key_pressed(wn, SDL_SCANCODE_RETURN) && !(wn->flag & CONSOLE))
	{
		wn->oldinterface = wn->interface;
		wn->menu->choice == 0 ? wn->interface = GAME : 0;
		wn->menu->choice == 1 ? wn->interface = EDITEUR : 0;
		wn->menu->choice == 2 ? wn->interface = OPTION : 0;
		wn->menu->choice == 3 ? stop_exec("Merci d'avoir joué !\n", wn) : 0;
		wn->menu->choice == 4 ? printf("Le choix 4\n") : 0;
		// Verif que le joueur veut bien quitter
	}
}
