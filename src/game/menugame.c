/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menugame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:01:14 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/10 17:56:27 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	show_game_cursor(t_win *wn)
{
	SDL_Rect	dst;

	dst.x = (wn->xscreen >> 1) - (wn->xscreen >> 4);
	dst.y = (wn->yscreen >> 1) + ((wn->menu->choice - 10) * (wn->yscreen / 35));
	dst.w = 50;
	dst.h = 50;
	SDL_RenderCopy(wn->rend, findtexture(wn,
				"main", "intro", "cursor"), NULL, &dst);
}

void	game_interface(t_win *wn)
{
	if (wn->interface == RGAME || wn->interface == DGAME)
	{
		if (wn->rasterizer == NULL)
		{
			ft_launch_rasterization(wn);
		}
		ingame(wn);
	}
	else if (wn->interface == NGAME)
		newgame(wn);
	else if (wn->interface == LGAME)
		loadgame(wn);
	else
		menugame(wn);
}
		/* ingame(wn); */
