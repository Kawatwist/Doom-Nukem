/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:12:44 by lomasse           #+#    #+#             */
/*   Updated: 2019/09/03 11:25:17 by naali            ###   ########.fr       */
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

/**/
int				test_joueur_creation(t_joueurs **j);
/**/

void			turn(t_win *wn)
{
	Uint32	difftime;
	Uint32	time;

/* TEST */
	t_joueurs	*j;

	test_joueur_creation(&j);
/* TEST */
	mainintro(wn, "main", "intro", 1);
	while (TRUE)
	{
		time = SDL_GetTicks();
		main_input(wn);
		interface(wn);
		difftime = SDL_GetTicks();
		(difftime - time) < (1000 / 60) ? SDL_Delay((1000 / 60) - (difftime - time)) : 0;
/* TEST */
		print_inventory(wn, j, 1);
/* TEST */
		wn->interface != DGAME ? SDL_RenderPresent(wn->rend) : 0;
	}
}
