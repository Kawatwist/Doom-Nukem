/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_blocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:56:41 by llejeune          #+#    #+#             */
/*   Updated: 2019/07/05 15:56:43 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		print_tbp_editor(t_win *wn)
{
	SDL_Rect	src;
	SDL_Rect	dst;

	wn->edit_image.tbp == 0 ? wn->edit_image.texture_tbp =
	findtexture(wn, "editor", "affichage", "texts") : 0;
	wn->edit_image.tbp == 1 ? wn->edit_image.texture_tbp =
	findtexture(wn, "editor", "affichage", "blocs") : 0;
	wn->edit_image.tbp == 2 ? wn->edit_image.texture_tbp =
	findtexture(wn, "editor", "affichage", "params") : 0;
	(wn->edit_image.texture_tbp == NULL) ?
	stop_exec("texture params failed in print_tbp\n", wn) : 0;
	SDL_QueryTexture(wn->edit_image.texture_tbp, NULL, NULL, &src.w, &src.h);
	if (wn->edit_image.in == 1)
	{
		src = define_rect(0, 0, src.w, src.h);
		dst = define_rect(5.5 * wn->xscreen / 7, 3 * wn->yscreen / 7,
			1.5 * wn->xscreen / 7, 3 * wn->yscreen / 7);
	}
	else
	{
		src = define_rect(0, 0, src.w, 0.25 * src.h / 7);
		dst = define_rect(5.5 * wn->xscreen / 7, 5.75 * wn->yscreen / 7,
			1.5 * wn->xscreen / 7, 0.25 * wn->yscreen / 7);
	}
	if (SDL_RenderCopy(wn->rend, wn->edit_image.texture_tbp, &src, &dst) < 0)
		stop_exec("render copy failed in print_tbp\n", wn);
	print_arrow(wn);
}

void		print_tools_editor(t_win *wn)
{
	SDL_Rect	dst;

	dst.x = 0;
	dst.y = wn->yscreen / 7 * 6;
	dst.w = wn->xscreen;
	dst.h = wn->yscreen / 7;
	wn->edit_image.texture_tools =
	findtexture(wn, "editor", "affichage", "tools");
	if (wn->edit_image.texture_tools == NULL)
		stop_exec("texture print_tools_editor failed\n", wn);
	if (SDL_RenderCopy(wn->rend, wn->edit_image.texture_tools, NULL, &dst) < 0)
		stop_exec("rendercopy failed in print_tools_editor\n", wn);
}

void		print_arrow(t_win *wn)
{
	SDL_Rect	dst;

	dst.x = 6.75 * wn->xscreen / 7;
	dst.w = 0.25 * wn->xscreen / 7;
	dst.h = 0.25 * wn->yscreen / 7;
	if (wn->edit_image.in == 1)
		dst.y = 3 * wn->yscreen / 7;
	else
		dst.y = 5.75 * wn->yscreen / 7;
	wn->edit_image.fleche = findtexture(wn, "editor", "affichage", "fleche");
	(wn->edit_image.fleche == NULL) ?
	stop_exec("fleche failed in print_arrow\n", wn) : 0;
	if (SDL_RenderCopy(wn->rend, wn->edit_image.fleche, NULL, &dst) < 0)
		stop_exec("rendercopy failed in print_arrow\n", wn);
}
