/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   showoption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:45:38 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/12 12:45:00 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		showoption(t_win *wn)
{
	wn->interface == KOPTION ? keyboardoption(wn) : 0;
	wn->interface == GOPTION ? graphismeoption(wn) : 0;
	wn->interface == COPTION ? controloption(wn) : 0;
	wn->interface == MOPTION ? menuoption(wn) : 0;
//	SDL_SetRenderDrawColor(wn->rend, 100, 0, 100, 0);
//	SDL_RenderClear(wn->rend);
}
