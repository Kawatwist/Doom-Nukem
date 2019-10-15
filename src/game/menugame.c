/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menugame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:01:14 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/16 17:36:21 by lomasse          ###   ########.fr       */
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
	if (wn->gametxt == NULL)
		wn->gametxt = SDL_CreateTexture(wn->rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, wn->xscreen, wn->yscreen);
	SDL_LockTexture(wn->gametxt, NULL, (void **)&wn->pixels, &wn->pitch);
	if (wn->interface == RGAME || wn->interface == DGAME)
	{
		if (wn->rasterizer == NULL)
		{
			if (!(wn->rasterizer = malloc(sizeof(t_rasterizer))))
				return ;
			ft_launch_rasterization(wn);
		}
		ingame(wn);
		SDL_UnlockTexture(wn->gametxt);
		// SDL_RenderCopy(wn->rend, wn->gametxt, NULL, NULL); //???useless
		display_monsters(wn);
	}
	else if (wn->interface == NGAME)
		newgame(wn);
	else if (wn->interface == LGAME)
		loadgame(wn);
	else
		menugame(wn);
}
