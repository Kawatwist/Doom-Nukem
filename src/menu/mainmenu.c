/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmenu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:02:03 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/30 16:24:44 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	menu(t_win *wn)
{
	if (wn->oldinterface != wn->interface)
	{
		if (wn->oldinterface == EDITEUR)
			mainintro(wn, "editor", "intro", -60);
		else if (wn->oldinterface == MOPTION)
			mainintro(wn, "option", "intro", -120);
		else if (wn->oldinterface == MGAME)
			mainintro(wn, "game", "intro", -60);
		wn->oldinterface = wn->interface;
	}
	menuinput(wn);
	showmenu(wn);
}
