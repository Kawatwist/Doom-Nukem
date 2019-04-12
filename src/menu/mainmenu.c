/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainmenu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:02:03 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/11 16:41:35 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	menu(t_win *wn)
{
	if (wn->oldinterface != wn->interface)
	{
		if (wn->oldinterface == EDITEUR)
			mainintro(wn, "editor", "intro", -60);
		else if (wn->oldinterface == OPTION)
			mainintro(wn, "option", "intro", -120);
		else if (wn->oldinterface == GAME)
			mainintro(wn, "game", "intro", -180);
		wn->oldinterface = wn->interface;
	}
	menuinput(wn);
	showmenu(wn);
}
