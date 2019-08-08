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

#include "editor.h"

static void		print_arrow(t_win *wn, t_edit *edit)
{
	edit->tab->arrow.y = 0.5 * wn->yscreen / 8;
	edit->tab->arrow.w = 0.25 * wn->xscreen / 8;
	edit->tab->arrow.h = 0.5 * wn->yscreen / 8;
	if (edit->tab->in == 1)
		edit->tab->arrow.x = 5.75 * wn->xscreen / 8;
	else
		edit->tab->arrow.x = 7.75 * wn->xscreen / 8;
	edit->tab->fleche = findtexture(wn, "editor", "affichage", "fleche");
	(edit->tab->fleche == NULL) ?
	stop_exec("fleche failed in print_arrow\n", wn) : 0;
	if (SDL_RenderCopy(wn->rend, edit->tab->fleche, NULL, &edit->tab->arrow) < 0)
		stop_exec("rendercopy failed in print_arrow\n", wn);
}

static void 	draw_rect_tab(t_win *wn)
{
	SDL_Rect	rect;

	rect = define_rect(6 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 0.5 * wn->xscreen / 8, 0.5 * wn->yscreen / 8);
	SDL_RenderDrawRect(wn->rend, &rect) < 0 ? stop_exec("fail in drawrecttab\n", wn) : 0;
	rect = define_rect(6.5 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 0.5 * wn->xscreen / 8, 0.5 * wn->yscreen / 8);
	SDL_RenderDrawRect(wn->rend, &rect);
	rect = define_rect(7 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 0.5 * wn->xscreen / 8, 0.5 * wn->yscreen / 8);
	SDL_RenderDrawRect(wn->rend, &rect);
	rect = define_rect(7.5 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 0.5 * wn->xscreen / 8, 0.5 * wn->yscreen / 8);
	SDL_RenderDrawRect(wn->rend, &rect);
}

void		print_tab_editor(t_win *wn, t_edit *edit)
{
	SDL_Rect	src;
	SDL_Rect	dst;

	edit->tab->tab = define_rect(6 * wn->xscreen / 8, 0.5 * wn->yscreen / 8,
			2 * wn->xscreen / 8, 7.5 * wn->yscreen / 8);
	display_tab(wn, edit);
	SDL_QueryTexture(edit->tab->texture_tab, NULL, NULL, &src.w, &src.h);
	if (edit->tab->in == 1)
	{
		src = define_rect(0, 0, src.w, src.h);
		dst = edit->tab->tab;
	}
	else
	{
		src = define_rect(0, 0, 0, 0);
		dst = define_rect(0, 0, 0, 0);
	}
	if (SDL_RenderCopy(wn->rend, edit->tab->texture_tab, &src, &dst) < 0)
		stop_exec("render copy failed in print_tbp\n", wn);
    exec_tab(wn, edit);	
	draw_rect_tab(wn);	
	print_arrow(wn, edit);
}
