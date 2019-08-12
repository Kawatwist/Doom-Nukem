/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:12:44 by lomasse           #+#    #+#             */
/*   Updated: 2019/08/12 16:12:15 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inventaire.h"

static void		interface(t_win *wn)
{
	if (wn->interface == MENU)
		menu(wn);
	else if (wn->interface == RGAME || wn->interface == MGAME || wn->interface == LGAME || wn->interface == NGAME || wn->interface == DGAME)
		game(wn);
	else if (wn->interface == MEDITEUR || wn->interface == EDITEUR || wn->interface == LEDITEUR || wn->interface == NEDITEUR || wn->interface == REDITEUR)
		edit(wn);
	else if (wn->interface == MOPTION || wn->interface == KOPTION || wn->interface == COPTION || wn->interface == GOPTION)
		option(wn);
	else if (wn->interface == MULTI || wn->interface == HOST || wn->interface == CLIENT)
		mainmulti(wn);
	wn->flag & CONSOLE ? mainconsole(wn) : 0;
}

int			test_joueur_creation(t_joueurs **j);// A DELETE

void			turn(t_win *wn)
{
	Uint32	difftime;
	Uint32	time;

	mainintro(wn, "main", "intro", 1);
	init_inventaire_texture(wn);
	test_joueur_creation(&(wn->joueur));// A DELETE
	while (TRUE)
	{
		time = SDL_GetTicks();
		main_input(wn);
		interface(wn);
		difftime = SDL_GetTicks();
		(difftime - time) < (1000 / 60) ? SDL_Delay((1000 / 60) - (difftime - time)) : 0;
		print_inventory(wn, wn->joueur, 4);// A Deplacer
		SDL_RenderPresent(wn->rend);
		wn->interface != DGAME && wn->interface != RGAME ? SDL_RenderPresent(wn->rend) : 0;
	}
}
