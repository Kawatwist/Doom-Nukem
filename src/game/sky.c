/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:57:20 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/16 15:12:14 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
/*
static void	bg2_skybox(t_win *wn)
{
	t_text		*img;
	SDL_Rect	src;

	src.y = (wn->player->rawy * 800 / YSCREEN);
	src.x = 0;
	src.w = 1;
	src.h = 400;
	img = findpostxt(wn, "game", "skybox", "sky2");
	SDL_RenderCopy(wn->rend, img->txt, &src, NULL);
}*/
/*
static void	bg_skybox(t_win *wn)
{
	t_text		*img;
	SDL_Rect	src;

	if (wn->sky == 1)
		src.y = (wn->player->rawy * (1600 - YSCREEN) / YSCREEN);
	else
		src.y = 0;
	if (wn->sky == 3)
		src.x = ((wn->player->rawx * (4500 - XSCREEN)) / 360);
	else if (wn->sky == 5)
		src.x = ((wn->player->rawx * (5400 - XSCREEN)) / 360);
	else
		src.x = ((wn->player->rawx * (3600 - XSCREEN)) / 360);
	src.w = XSCREEN;
	src.h = YSCREEN;
	if (wn->sky == 1)
		img = findpostxt(wn, "game", "skybox", "sky");
	else if (wn->sky == 2)
		img = findpostxt(wn, "game", "skybox", "sky3");
	else if (wn->sky == 3)
		img = findpostxt(wn, "game", "skybox", "sky4");
	else
		img = findpostxt(wn, "game", "skybox", "sky5");
	SDL_RenderCopy(wn->rend, img->txt, &src, NULL);
}*/


static void	bg_skybox(t_win *wn)
{
	t_color color;
	t_point origin;
	
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	origin.x = 50;
	origin.y = 50;
	ft_memset(wn->pixels, 0, wn->xscreen * 4 * wn->yscreen);
//	drawsquare(wn->pixels, wn->xscreen * 4, *create_rect(10, 10, 200, 200), color);
//	drawcircle(wn->pixels, wn->xscreen * 4, origin, 25);
}

void		display_skybox(t_win *wn)
{
	bg_skybox(wn);
}
