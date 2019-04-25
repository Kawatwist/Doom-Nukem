/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 11:44:06 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/22 15:17:17 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	showmenu(t_win *wn)
{
	SDL_Rect	dst;

	dst.x = XSCREEN / 2 - (XSCREEN / 10);
	dst.y = YSCREEN / 2.15 + (wn->menu->choice * (YSCREEN / 35));
	dst.w = 50;
	dst.h = 50;
	if (wn->menu->choice == 3)
	{
		dst.x = XSCREEN / 2 - (XSCREEN / 40);
		dst.y = YSCREEN / 2 + (YSCREEN / 4) - (YSCREEN >> 5);
	}
	SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 0);
	SDL_RenderClear(wn->rend);
	SDL_RenderCopy(wn->rend, findtexture(wn,
				"main", "intro", "60"), NULL, NULL);
	SDL_RenderCopy(wn->rend, findtexture(wn,
				"main", "intro", "cursor"), NULL, &dst);
}
