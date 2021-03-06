/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainoption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:03:30 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/12 12:47:06 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	keyboardoption(t_win *wn)
{
	SDL_RenderCopy(wn->rend, findtexture(wn, "option", "menu", "menu"), NULL, NULL);
}

void	graphismeoption(t_win *wn)
{
	SDL_RenderCopy(wn->rend, findtexture(wn, "option", "menu", "menu"), NULL, NULL);
}

void	controloption(t_win *wn)
{
	SDL_RenderCopy(wn->rend, findtexture(wn, "option", "menu", "menu"), NULL, NULL);
}

void	menuoption(t_win *wn)
{
	SDL_RenderCopy(wn->rend, findtexture(wn, "option", "menu", "menu"), NULL, NULL);
}

void	option(t_win *wn)
{
	if (wn->oldinterface != wn->interface && !(wn->flag & LQ))
	{
		mainintro(wn, "option", "intro", 120);
		wn->oldinterface = wn->interface;
	}
	menu_option_input(wn);
	showoption(wn);
}
