/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:44:06 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/08 18:00:02 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	showmenu(t_win *wn)
{
	SDL_Rect	dst;

	dst.x = wn->xscreen / 2 - (wn->xscreen / 10);
	dst.y = wn->yscreen / 2.15 + (wn->menu->choice * (wn->yscreen / 35));
	dst.w = 50;
	dst.h = 50;
	if (wn->menu->choice == 3)
	{
		dst.x = wn->xscreen / 2 - (wn->xscreen / 40);
		dst.y = wn->yscreen / 2 + (wn->yscreen / 4) - (wn->yscreen >> 5);
	}
	SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 0);
	SDL_RenderClear(wn->rend);
	SDL_RenderCopy(wn->rend, findtexture(wn,
				"main", "intro", "60"), NULL, NULL);
	SDL_RenderCopy(wn->rend, findtexture(wn,
				"main", "intro", "cursor"), NULL, &dst);
}
