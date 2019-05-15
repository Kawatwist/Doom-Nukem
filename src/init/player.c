/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:26:52 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/12 15:18:09 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		initweapon(t_win **wn)
{
	t_weapon *weapon;

	weapon = (*wn)->player->weapon;
	weapon->id = 0;
	weapon->dmg = 30;
	weapon->ammo = -1;
	weapon->range = 1;
	weapon->status = 0;
	weapon->text = findpostxt(*wn, "game", "hand", "none");
	weapon->next = (*wn)->player->weapon;
}

void			initplayer(t_win **wn)
{
	((*wn)->player = (t_joueur *)malloc(sizeof(t_joueur))) == NULL
		? stop_exec("Malloc joueur failed\n", *wn) : 0;
	((*wn)->player->weapon = (t_weapon *)malloc(sizeof(t_weapon))) == NULL
		? stop_exec("Malloc weapon failed\n", *wn) : 0;
	initweapon(wn);
	(*wn)->player->entity = NULL;
	(*wn)->player->rawx = 0;
	(*wn)->player->rawy = 0;
	(*wn)->player->sensi = 1;
}
