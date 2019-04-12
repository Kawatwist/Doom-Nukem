/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:57:20 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/12 17:13:34 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	bg2_skybox(t_win *wn)
{
	t_text		*img;
	SDL_Rect	src;
	SDL_Rect	dst;
	
	(src.y = (wn->player->rawy * 800 / YSCREEN)) > 700 ? src.y = 700 : 0;
	src.x = 0;
	src.w = 1;
	src.h = 100;
	dst.x = 0;
	dst.y = 0;
	dst.w = XSCREEN;
	dst.h = YSCREEN;
	img = findpostxt(wn, "game", "skybox", "sky2");
	SDL_RenderCopy(wn->rend, img->txt, &src, NULL);
}

static void	bg_skybox(t_win *wn)
{
	t_text	*img;
	SDL_Rect src;
	SDL_Rect dst;

	src.y = (wn->player->rawy * (1600 - YSCREEN) / YSCREEN);
	src.x = (wn->player->rawx * (4000 - XSCREEN) / XSCREEN);
	src.w = XSCREEN;
	src.h = YSCREEN;
	dst.x = 0;
	dst.y = 0;
	dst.w = XSCREEN;
	dst.h = YSCREEN;
	img = findpostxt(wn, "game", "skybox", "sky");
	SDL_RenderCopy(wn->rend, img->txt, &src, NULL);
}

void		display_skybox(t_win *wn)
{
	SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 0);
	SDL_RenderDrawRect(wn->rend, NULL);
	bg_skybox(wn);
	bg2_skybox(wn);
	SDL_RenderPresent(wn->rend);
}
