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
}
