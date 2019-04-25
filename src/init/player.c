/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:26:52 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/22 11:44:12 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	initplayer(t_win **wn)
{
	((*wn)->player = (t_joueur *)malloc(sizeof(t_joueur))) == NULL
		? stop_exec("Malloc joueur failed\n", *wn) : 0;
	(*wn)->player->posx = 0;
	(*wn)->player->posy = 0;
	(*wn)->player->viewx = 0;
	(*wn)->player->viewy = 0;
	(*wn)->player->rawx = 0;
	(*wn)->player->rawy = 0;
	(*wn)->player->sensi = 1;
}
