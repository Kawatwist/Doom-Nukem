/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainedit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:20:52 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/04 15:47:57 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		edit(t_win *wn)
{
	if (wn->oldinterface != wn->interface)
	{
		mainintro(wn, "editor", "intro", 60);
		wn->oldinterface = wn->interface;
	}
	inputeditor(wn);
	printeditor(wn);
	SDL_Rect	pos = define_rect(((t_edit *)wn->edit)->tab->bg.x, ((t_edit*)wn->edit)->tab->bg.y + 200, ((t_edit*)wn->edit)->tab->bg.w - 50, ((t_edit*)wn->edit)->tab->bg.h);	
	SDL_Rect	check = define_rect(wn->input->x, wn->input->y, 0, 0);
	// if (boxhitbox(wn->rend, &check, &pos, 1))
	// 	save_panel(wn, wn->edit);
}
