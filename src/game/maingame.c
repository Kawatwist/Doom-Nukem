/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maingame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:01:14 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/19 16:32:49 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	game(t_win *wn)
{
	if (wn->oldinterface != wn->interface)
	{
	//	mainintro(wn, "game", "intro", 60);
		wn->oldinterface = wn->interface;
	}
	gameinput(wn);
	display_skybox(wn);
//	main_cloud(wn);
	maindrawpoly(wn);
	display_crosshair(wn);
}
