/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainoption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:03:30 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/22 11:33:16 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	option(t_win *wn)
{
	if (wn->oldinterface != wn->interface && !(wn->flag & LQ))
	{
		mainintro(wn, "option", "intro", 120);
		wn->oldinterface = wn->interface;
	}
	optioninput(wn);
	showoption(wn);
}
