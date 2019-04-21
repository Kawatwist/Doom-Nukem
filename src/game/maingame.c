/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maingame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:01:14 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/15 10:55:00 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	game(t_win *wn)
{
	if (wn->oldinterface != wn->interface)
	{
		mainintro(wn, "game", "intro", 180);
		wn->oldinterface = wn->interface;
	}
	gameinput(wn);
	display_skybox(wn);
}
